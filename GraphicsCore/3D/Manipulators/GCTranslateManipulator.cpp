#include "GCTranslateManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "3D/GCCamera.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "XTransform.h"
#include "XShader.h"
#include "XLine.h"
#include "XCuboid.h"

class CentralTranslateDelegate : public GCVisualManipulator::Delegate
  {
public:
  CentralTranslateDelegate()
    {
    /*XModeller m(&_geo, 64);

    m.drawCube(Eks::Vector3D(0.1f, 0.0f, 0.0f), Eks::Vector3D(0.0f, 0.1f, 0.0f), Eks::Vector3D(0.0f, 0.0f, 0.1f));
    */}

  virtual bool hitTest(
      const GCVisualManipulator *toRender,
      const QPoint &,
      const GCCamera *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance)
    {
    const Eks::Vector3D &camTrans = camera->transform().translation();
    Eks::Line l(camTrans, clickDirection, Eks::Line::PointAndDirection);

    const Eks::Transform &wC = toRender->worldCentre();

    Eks::Matrix4x4 t = wC.matrix();
    Eks::Matrix4x4 tInv = t.inverse();
    Eks::Transform lineTransform(tInv);
    l.transform(lineTransform);

    /* // need to rethink this.
    if(Eks::MeshUtilities::intersect("vertex", l, _geo))
      {
      const Eks::Vector3D &wcTrans = wC.translation();
      *distance = (camTrans - wcTrans).norm() - 0.05f;
      return true;
      }*/

    return false;
    }

  virtual void render(const GCVisualManipulator *toRender,
      const GCCamera *,
      Eks::Renderer *r)
    {
    xAssertFail();
    /*
    const Eks::Transform &wC = toRender->worldCentre();

    r->pushTransform(wC);
    r->setShader(&_shader);
    r->drawGeometry(_geo);
    r->setShader(0);
    r->popTransform();*/
    }

private:
  Eks::Geometry _geo;
  Eks::Shader _shader;
  };


class LinearTranslateDelegate : public GCVisualManipulator::Delegate
  {
public:
  LinearTranslateDelegate()
    {
    /*
    XModeller m(&_geo, 64);

    m.begin(XModeller::Lines);
      m.vertex(0.0f, 0.0f, 0.0f);
      m.vertex(1.0f, 0.0f, 0.0f);
    m.end();

    m.drawCone(Eks::Vector3D(0.8f, 0.0f, 0.0f), Eks::Vector3D(1.0f, 0.0f, 0.0f), 0.2f, 0.06f);

    _shader.setToDefinedType("plainColour");*/
    }

  virtual bool hitTest(
      const GCVisualManipulator *manip,
      const QPoint &,
      const GCCamera *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance)
    {
    const GCSingularTranslateManipulator *toRender = manip->uncheckedCastTo<GCSingularTranslateManipulator>();

    const Eks::Vector3D &camTrans = camera->transform().translation();
    Eks::Line clickLine(camTrans, clickDirection, Eks::Line::PointAndDirection);

    Eks::Line manipLine(Eks::Vector3D(0.0f, 0.0f, 0.0f), toRender->lockDirection().normalized());

    const Eks::Transform &wC = toRender->worldCentre();
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
      Eks::Renderer *r)
    {
    const GCSingularTranslateManipulator *toRender = manip->uncheckedCastTo<GCSingularTranslateManipulator>();

    Eks::Transform wC = toRender->worldCentre();

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
/*
    _shader.getVariable("colour")->setValue(col);

    r->pushTransform(wC);
    r->setShader(&_shader);
    r->drawGeometry(_geo);
    r->setShader(0);
    r->popTransform();*/
    }

private:
  Eks::Geometry _geo;
  Eks::Shader _shader;
  };

S_IMPLEMENT_PROPERTY(GCSingularTranslateManipulator, GraphicsCore)

void GCSingularTranslateManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCSingularTranslateManipulator> *,
                                                           const Shift::PropertyInformationCreateData &)
  {
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

void postCreateTranslateManip(GCTranslateManipulator *m)
  {
  m->worldCentre.connect(&m->x.worldCentre);
  m->x.setDelegate(new LinearTranslateDelegate());

  m->x.lockMode = GCSingularTranslateManipulator::Linear;
  m->x.lockDirection = Eks::Vector3D(1.0f, 0.0f, 0.0f);


  m->worldCentre.connect(&m->y.worldCentre);
  m->y.setDelegate(new LinearTranslateDelegate());

  m->y.lockMode = GCSingularTranslateManipulator::Linear;
  m->y.lockDirection = Eks::Vector3D(0.0f, 1.0f, 0.0f);


  m->worldCentre.connect(&m->z.worldCentre);
  m->z.setDelegate(new LinearTranslateDelegate());

  m->z.lockMode = GCSingularTranslateManipulator::Linear;
  m->z.lockDirection = Eks::Vector3D(0.0f, 0.0f, 1.0f);


  m->worldCentre.connect(&m->central.worldCentre);
  m->central.setDelegate(new CentralTranslateDelegate());
  }

void GCTranslateManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCTranslateManipulator> *info,
                                                   const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCTranslateManipulator::x, "x");
    childBlock.add(&GCTranslateManipulator::y, "y");
    childBlock.add(&GCTranslateManipulator::z, "z");
    childBlock.add(&GCTranslateManipulator::central, "central");
    }
  }

GCTranslateManipulator::GCTranslateManipulator()
  {
  }

void GCTranslateManipulator::addDriven(TransformProperty *in)
  {
  central.addDriven(in);
  x.addDriven(in);
  y.addDriven(in);
  z.addDriven(in);
  }
