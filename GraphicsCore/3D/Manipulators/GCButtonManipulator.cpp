#include "GCButtonManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "3D/GCCamera.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "XTransform.h"
#include "XShader.h"
#include "XLine.h"
#include "XCuboid.h"

class ButtonDelegate : public GCVisualManipulator::Delegate
  {
public:
  ButtonDelegate()
    {
    Eks::Transform t;
    t = Eigen::Translation3f(10.0f, 10.0f, 0.0f);

    /*
    Eks::Modeller m(&_geo, 64);
    m.setTransform(t);

    m.drawQuad(XVector3D(20.0f, 0.0f, 0.0f), XVector3D(0.0f, 20.0f, 0.0f));*/
    }

  virtual bool hitTest(
      const GCVisualManipulator *toRender,
      const QPoint &,
      const GCCamera *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance)
    {
    Eks::Line l(camera->transform().translation(), clickDirection, Eks::Line::PointAndDirection);

    Eks::Matrix4x4 t = camera->getPixelScaleFacingTransform(toRender->worldTransform().translation()).matrix();
    Eks::Matrix4x4 tInv = t.inverse();

    Eks::Transform lineTransform(tInv);

    l.transform(lineTransform);

    Eks::Cuboid c(Eks::Vector3D(0.0f, 0.0f, 0.0f), Eks::Vector3D(20.0f, 20.0f, 0.1f));

    if(c.intersects(l, *distance))
      {
      *distance *= t.row(0).norm();
      return true;
      }

    return false;
    }

  virtual void render(const GCVisualManipulator *,
      const GCCamera *,
      Eks::Renderer *)
    {
    /*XTransform t = camera->getPixelScaleFacingTransform(toRender->worldCentre().translation());

    r->pushTransform(t);
    r->setShader(&_shader);
    r->drawGeometry(_geo);
    r->setShader(0);
    r->popTransform();*/
    }

private:
  Eks::Geometry _geo;
  Eks::Shader _shader;
  };

S_IMPLEMENT_PROPERTY(GCButtonManipulator, GraphicsCore)

void GCButtonManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCButtonManipulator> *info,
                                                const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCButtonManipulator::checked, "checked");
    childBlock.add(&GCButtonManipulator::checkable, "checkable");
    }
  }

GCButtonManipulator::GCButtonManipulator()
  {
  }

GCButtonManipulator::~GCButtonManipulator()
  {
  }

void GCButtonManipulator::onClick()
  {
  qDebug() << "Click";
  }
