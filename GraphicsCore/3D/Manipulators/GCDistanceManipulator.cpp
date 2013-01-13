#include "GCDistanceManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "3D/GCCamera.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "XTransform.h"
#include "XShader.h"
#include "XLine.h"
#include "XCuboid.h"
#include "shift/Changes/shandler.inl"

class DistanceDelegate : public GCVisualManipulator::Delegate
  {
public:
  DistanceDelegate()
    {
    XModeller m(&_geo, 64);

    m.drawCube(Eks::Vector3D(0.1f, 0.0f, 0.0f), Eks::Vector3D(0.0f, 0.1f, 0.0f), Eks::Vector3D(0.0f, 0.0f, 0.1f));
    }

  virtual bool hitTest(
      const GCVisualManipulator *manip,
      const QPoint &,
      const GCCamera *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance)
    {
    const GCDistanceManipulator *toRender = manip->uncheckedCastTo<GCDistanceManipulator>();
    const Eks::Vector3D &camTrans = camera->transform().translation();
    XLine l(camTrans, clickDirection, XLine::PointAndDirection);

    XTransform wC = toRender->worldCentre();
    wC.translate(toRender->absoluteDisplacement());

    XMatrix4x4 t = wC.matrix();
    XMatrix4x4 tInv = t.inverse();
    XTransform lineTransform(tInv);
    l.transform(lineTransform);

    if(XMeshUtilities::intersect("vertex", l, _geo))
      {
      const Eks::Vector3D &wcTrans = wC.translation();
      *distance = (camTrans - wcTrans).norm() - 0.05f;
      return true;
      }

    return false;
    }

  virtual void render(const GCVisualManipulator *manip,
      const GCCamera *,
      XRenderer *r)
    {
    const GCDistanceManipulator *toRender = manip->uncheckedCastTo<GCDistanceManipulator>();

    XTransform wC = toRender->worldCentre();
    wC.translate(toRender->absoluteDisplacement());

    r->pushTransform(wC);
    r->setShader(&_shader);
    r->drawGeometry(_geo);
    r->setShader(0);
    r->popTransform();
    }

  virtual Eks::Vector3D focalPoint(const GCVisualManipulator *manip) const
    {
    const GCDistanceManipulator *toRender = manip->uncheckedCastTo<GCDistanceManipulator>();

    XTransform wC = toRender->worldCentre();
    wC.translate(toRender->absoluteDisplacement());
    return wC.translation();
    }

private:
  XGeometry _geo;
  XShader _shader;
  };

S_IMPLEMENT_PROPERTY(GCDistanceManipulator, GraphicsCore)

void computeAbsDisp(GCDistanceManipulator *d)
  {
  d->absoluteDisplacement = d->lockDirection().normalized() * (d->distance() * d->scaleFactor());
  }

void GCDistanceManipulator::createTypeInformation(PropertyInformationTyped<GCDistanceManipulator> *info,
                                                  const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto absDispInfo = info->add(&GCDistanceManipulator::absoluteDisplacement, "absoluteDisplacement");
    absDispInfo->setCompute<computeAbsDisp>();

    auto dirInfo = info->child(&GCDistanceManipulator::lockDirection);
    dirInfo->setAffects(absDispInfo);

    auto distInfo = info->add(&GCDistanceManipulator::distance, "distance");
    distInfo->setAffects(absDispInfo);

    auto sfInfo = info->add(&GCDistanceManipulator::scaleFactor, "scaleFactor");
    sfInfo->setAffects(absDispInfo);
    }
  }

GCDistanceManipulator::GCDistanceManipulator()
  {
  setDelegate(new DistanceDelegate());
  }

void GCDistanceManipulator::addDriven(FloatProperty *in)
  {
  _driven << in;
  }

void GCDistanceManipulator::onDrag(const MouseMoveEvent &e)
  {
  Eks::Vector3D relativeDisp;
  GCLinearDragManipulator::onDrag(e, relativeDisp);

  float rel = relativeDisp.norm() / scaleFactor();

  if(relativeDisp.dot(lockDirection()) < 0.0f)
    {
    rel *= -1.0f;
    }

  Q_FOREACH(FloatProperty *f, _driven)
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
