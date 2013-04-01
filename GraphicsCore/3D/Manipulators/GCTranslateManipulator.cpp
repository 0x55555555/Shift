#include "GCTranslateManipulator.h"
#include "GCDistanceManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "3D/GCCamera.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "XTransform.h"
#include "XShader.h"
#include "XLine.h"
#include "XCuboid.h"

class LinearTranslateDelegate : public GCVisualManipulator::Delegate
  {
public:
  virtual bool hitTest(
      const GCVisualManipulator *manip,
      const QPoint &,
      const GCCamera *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance) const
    {
    const GCSingularTranslateManipulator *toRender = manip->uncheckedCastTo<GCSingularTranslateManipulator>();

    const Eks::Vector3D &camTrans = camera->transform().translation();
    Eks::Line clickLine(camTrans, clickDirection, Eks::Line::PointAndDirection);

    Eks::Line manipLine(Eks::Vector3D(0.0f, 0.0f, 0.0f), toRender->lockDirection().normalized());

    const Eks::Transform &wC = toRender->worldTransform();
    manipLine.transform(wC);

    float clickT = clickLine.closestPointOn(manipLine);
    Eks::Vector3D clickPt = clickLine.sample(clickT);

    float manipT = manipLine.closestPointTo(clickPt);
    if(manipT >= 0.0f && manipT <= 1.0f)
      {
      const float maxPixels = 5.0f;

      float worldDist = (manipLine.sample(manipT) - clickPt).norm();

      *distance = (clickPt - camTrans).norm();

      float pixelSizeX, pixelSizeY;
      camera->approximatePixelSizeAtDistance(*distance, pixelSizeX, pixelSizeY);

      float maxWorld = maxPixels * pixelSizeX;

      if(worldDist >= 0.0f && worldDist < maxWorld)
        {
        return true;
        }
      }

    return false;
    }

  virtual void render(const GCVisualManipulator *manip,
      const GCCamera *,
      Eks::Renderer *r) const
    {
    const GCSingularTranslateManipulator *toRender = manip->uncheckedCastTo<GCSingularTranslateManipulator>();

    if(!_geo.isValid())
      {
      Eks::TemporaryAllocator alloc(manip->temporaryAllocator());
      Eks::Modeller m(&alloc, 64);

      m.begin(Eks::Modeller::Lines);
        m.vertex(0.0f, 0.0f, 0.0f);
        m.vertex(1.0f, 0.0f, 0.0f);
      m.end();

      m.drawCone(Eks::Vector3D(0.8f, 0.0f, 0.0f), Eks::Vector3D(1.0f, 0.0f, 0.0f), 0.2f, 0.06f);

      Eks::ShaderVertexLayoutDescription::Semantic sem[] =
      {
        Eks::ShaderVertexLayoutDescription::Position
      };

      m.bakeVertices(r, sem, X_ARRAY_COUNT(sem), &_geo);

      m.bakeTriangles(r, sem, X_ARRAY_COUNT(sem), &_tigeo);
      m.bakeLines(r, sem, X_ARRAY_COUNT(sem), &_ligeo);

      _shader = r->stockShader(Eks::PlainColour, &_layout);

      Eks::ShaderConstantDataDescription dataDesc[] =
      {
        { "colour", Eks::ShaderConstantDataDescription::Float4 }
      };
      const Eks::Colour &col = Eks::Colour(toRender->lockDirection());
      Eks::ShaderConstantData::delayedCreate(_data, r, dataDesc, X_ARRAY_COUNT(dataDesc), col.data());
      }

    Eks::Transform wC = toRender->worldTransform();

    Eks::Vector3D x = Eks::Vector3D(1.0f, 0.0f, 0.0f);
    Eks::Vector3D lockDir = toRender->lockDirection().normalized();
    if(lockDir.dot(x) < 0.99f)
      {
      Eks::Vector3D dir = x.cross(lockDir);
      Eigen::AngleAxisf a((float)M_PI/2.0f, dir);

      wC.rotate(a);
      }

    Eks::Vector4D col;
    col(3) = 1.0f;
    col.head<3>() = toRender->lockDirection();

    r->setTransform(wC);

    _shader->setShaderConstantData(0, &_data);
    r->setShader(_shader, _layout);
    r->drawTriangles(&_tigeo, &_geo);
    r->drawLines(&_ligeo, &_geo);
    }

private:
  mutable Eks::Geometry _geo;
  mutable Eks::IndexGeometry _tigeo;
  mutable Eks::IndexGeometry _ligeo;
  mutable Eks::Shader *_shader;
  mutable const Eks::ShaderVertexLayout *_layout;
  mutable Eks::ShaderConstantData _data;
  };

S_IMPLEMENT_PROPERTY(GCSingularTranslateManipulator, GraphicsCore)

void GCSingularTranslateManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCSingularTranslateManipulator> *info,
                                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto world = childBlock.child(&GCDistanceManipulator::worldTransform);


    auto result = childBlock.overrideChild(&GCDistanceManipulator::resultTransform);
    result->setDefaultInput(world);
    }
  }

GCSingularTranslateManipulator::GCSingularTranslateManipulator()
  {
  }

void GCSingularTranslateManipulator::addDriven(TransformProperty *in)
  {
  _driven << in;
  }

void GCSingularTranslateManipulator::onDrag(const MouseMoveEvent &e)
  {
  Eks::Vector3D relativeDisp;
  GCLinearDragManipulator::onDrag(e, relativeDisp);

  Q_FOREACH(TransformProperty *t, _driven)
    {
    Eks::Transform trans = t->value();
    trans.translation() += relativeDisp;
    *t = trans;
    }
  }


S_IMPLEMENT_PROPERTY(GCTranslateManipulator, GraphicsCore)

void GCTranslateManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCTranslateManipulator> *info,
                                                   const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto wt = childBlock.child(&GCTranslateManipulator::worldTransform);

    auto x = childBlock.add(&GCTranslateManipulator::x, "x");
    auto y = childBlock.add(&GCTranslateManipulator::y, "y");
    auto z = childBlock.add(&GCTranslateManipulator::z, "z");

    Eks::Vector3D dir[] =
      {
      Eks::Vector3D(1.0f, 0.0f, 0.0f),
      Eks::Vector3D(0.0f, 1.0f, 0.0f),
      Eks::Vector3D(0.0f, 0.0f, 1.0f),
      };

    Shift::PropertyInstanceInformationTyped<GCTranslateManipulator, GCSingularTranslateManipulator>
      *components[] = { x, y, z };
    for(xsize i = 0; i < X_ARRAY_COUNT(components); ++i)
      {
      auto iInfo = info->extendContainedProperty(data, components[i]);
      auto iChildBlock = iInfo->createChildrenBlock(data);

      auto iWt = iChildBlock.overrideChild(&GCSingularTranslateManipulator::parentTransform);
      iWt->setDefaultInput(wt);

      auto lm = iChildBlock.overrideChild(&GCSingularTranslateManipulator::lockMode);
      lm->setDefaultValue(GCSingularTranslateManipulator::Linear);

      auto ld = iChildBlock.overrideChild(&GCSingularTranslateManipulator::lockDirection);
      ld->setDefaultValue(dir[i]);
      }

    auto cent = childBlock.add(&GCTranslateManipulator::central, "central");

    auto iInfo = info->extendContainedProperty(data, cent);
    auto iChildBlock = iInfo->createChildrenBlock(data);
    auto iWt = iChildBlock.overrideChild(&GCSingularTranslateManipulator::parentTransform);
    iWt->setDefaultInput(wt);
    }
  }

GCTranslateManipulator::GCTranslateManipulator()
  {
  x.createDelegate<LinearTranslateDelegate>();
  y.createDelegate<LinearTranslateDelegate>();
  z.createDelegate<LinearTranslateDelegate>();
  central.createDelegate<GCManipulatorDistanceDelegate>();
  }

void GCTranslateManipulator::addDriven(TransformProperty *in)
  {
  central.addDriven(in);
  x.addDriven(in);
  y.addDriven(in);
  z.addDriven(in);
  }
