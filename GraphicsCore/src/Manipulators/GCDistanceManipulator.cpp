#include "Manipulators/GCDistanceManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "RCCamera.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "XTransform.h"
#include "XShader.h"
#include "XLine.h"
#include "XBoundingBox.h"
#include "shift/Changes/shandler.inl"


static const float Radius = 0.1f;
bool GCManipulatorDistanceDelegate::hitTest(
    const GCVisualManipulator *manip,
    const QPoint &,
    const RCViewableTransform *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance) const
  {
  const Eks::Vector3D &camTrans = camera->transform().translation();
  Eks::Line l(camTrans, clickDirection, Eks::Line::PointAndDirection);

  Eks::Transform wC = manip->resultTransform(camera);

  Eks::Matrix4x4 t = wC.matrix();
  Eks::Matrix4x4 tInv = t.inverse();
  Eks::Transform lineTransform(tInv);
  l.transform(lineTransform);

  if(l.sample(l.closestPointTo(Eks::Vector3D::Zero())).norm() < Radius)
    {
    const Eks::Vector3D &wcTrans = wC.translation();
    *distance = (camTrans - wcTrans).norm() - 0.05f;
    return true;
    }

  return false;
  }

void GCManipulatorDistanceDelegate::render(
    const GCVisualManipulator *manip,
    const RCViewableTransform *cam,
    Eks::Renderer *r) const
  {
  if(!_geo.isValid())
    {
    Eks::TemporaryAllocator alloc(manip->temporaryAllocator());
    Eks::Modeller m(&alloc, 1024);

    m.drawSphere(Radius);

    Eks::ShaderVertexLayoutDescription::Semantic sem[] = { Eks::ShaderVertexLayoutDescription::Position };
    m.bakeTriangles(r, sem, X_ARRAY_COUNT(sem), &_igeo, &_geo);

    _shader = r->stockShader(Eks::PlainColour, &_layout);

    Eks::ShaderConstantDataDescription dataDesc[] =
    {
      { "colour", Eks::ShaderConstantDataDescription::Float4 }
    };
    const Eks::Colour &col = Eks::Colour(1.0f, 1.0f, 0.0f);
    Eks::ShaderConstantData::delayedCreate(_data, r, dataDesc, X_ARRAY_COUNT(dataDesc), col.data());
    }

  Eks::Transform wC = manip->resultTransform(cam);

  r->setTransform(wC);
  _shader->setShaderConstantData(0, &_data);
  r->setShader(_shader, _layout);
  r->drawTriangles(&_igeo, &_geo);
  }

S_IMPLEMENT_PROPERTY(GCDistanceManipulator, GraphicsCore)

void computeAbsDisp(GCDistanceManipulator *d)
  {
  d->absoluteDisplacement = d->lockDirection().normalized() * (d->distance() * d->scaleFactor());
  }

void GCDistanceManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCDistanceManipulator> *info,
                                                  const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto absDispInfo = childBlock.add(&GCDistanceManipulator::absoluteDisplacement, "absoluteDisplacement");
  absDispInfo->setCompute<computeAbsDisp>();

  auto affectsAbsDisp = childBlock.createAffects(&absDispInfo, 1);

  auto dirInfo = childBlock.overrideChild(&GCDistanceManipulator::lockDirection);
  dirInfo->setAffects(affectsAbsDisp, true);

  auto distInfo = childBlock.add(&GCDistanceManipulator::distance, "distance");
  distInfo->setAffects(affectsAbsDisp, false);

  auto sfInfo = childBlock.add(&GCDistanceManipulator::scaleFactor, "scaleFactor");
  sfInfo->setAffects(affectsAbsDisp, false);
  sfInfo->setDefaultValue(1.0f);
  }

GCDistanceManipulator::GCDistanceManipulator()
  {
  createDelegate<GCManipulatorDistanceDelegate>();
  }

Eks::Transform GCDistanceManipulator::resultTransform(const RCViewableTransform *tr) const
  {
  Eks::Transform wC = worldTransform();

  wC.translate(absoluteDisplacement());

  return computeScaledResultTransform(
    wC,
    scaleMode(),
    tr,
    displayScale());
  }

void GCDistanceManipulator::addDriven(Shift::FloatProperty *in)
  {
  _driven << in;
  }

void GCDistanceManipulator::onDrag(const MouseMoveEvent &e)
  {
  Eks::Vector3D relativeDisp;
  GCDisplacementDragManipulator::onDragHelper(e, relativeDisp);

  float rel = relativeDisp.norm() / scaleFactor();

  if(relativeDisp.dot(lockDirection()) < 0.0f)
    {
    rel *= -1.0f;
    }

  xForeach(Shift::FloatProperty *f, _driven)
    {
    float newVal = f->value() + rel;
    if(newVal == newVal && newVal < HUGE_VAL)
      {
      *f = newVal;
      }
    else
      {
      xAssertFail();
      }
    }
  }
