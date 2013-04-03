#include "GCRotateManipulator.h"
#include "GCDistanceManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "GCManipulatorHelpers.h"
#include "shift/Changes/shandler.inl"
#include "3D/GCCamera.h"
#include "XModeller.h"
#include "XRenderer.h"
#include "XTransform.h"
#include "XShader.h"
#include "XLine.h"
#include "XPlane.h"
#include "XCuboid.h"

class CircularRotateDelegate : public GCVisualManipulator::Delegate
  {
public:
  virtual bool hitTest(
      const GCVisualManipulator *manip,
      const QPoint &,
      const GCViewableTransform *camera,
      const Eks::Vector3D &clickDirection, // in world space
      float *distance) const
    {
    const GCSingularRotateManipulator *toRender = manip->uncheckedCastTo<GCSingularRotateManipulator>();

    const Eks::Vector3D &camTrans = camera->transform().translation();
    Eks::Line clickLine(camTrans, clickDirection, Eks::Line::PointAndDirection);

    Eks::Transform wC = toRender->resultTransform(camera);

    Eks::Plane p(Eks::Vector3D::Zero(), toRender->lockDirection());
    clickLine.transform(wC.inverse());

    float t = p.intersection(clickLine);
    if(t == HUGE_VAL)
      {
      return false;
      }

    Eks::Vector3D closest = clickLine.sample(t);
    float worldDist = closest.norm();

    const float maxPixels = 2.5f;

    *distance = (closest - camTrans).norm();

    float pixelSizeX, pixelSizeY;
    camera->approximatePixelSizeAtDistance(*distance, pixelSizeX, pixelSizeY);

    float maxWorld = maxPixels * pixelSizeX;

    if(worldDist <= (1.0f + maxWorld) &&
       worldDist >= (1.0f - maxWorld))
      {
      return true;
      }

    return false;
    }

  virtual void render(const GCVisualManipulator *manip,
      const GCViewableTransform *cam,
      Eks::Renderer *r) const
    {
    const GCSingularRotateManipulator *toRender = manip->uncheckedCastTo<GCSingularRotateManipulator>();

    const Eks::Vector3D &direction = toRender->lockDirection();

    if(!_geo.isValid())
      {
      Eks::TemporaryAllocator alloc(manip->temporaryAllocator());
      Eks::Modeller m(&alloc, 64);

      m.drawWireCircle(Eks::Vector3D::Zero(), Eks::Vector3D(1.0f, 0.0f, 0.0f), 1.0f);

      Eks::ShaderVertexLayoutDescription::Semantic sem[] =
      {
        Eks::ShaderVertexLayoutDescription::Position
      };

      m.bakeVertices(r, sem, X_ARRAY_COUNT(sem), &_geo);

      m.bakeLines(r, sem, X_ARRAY_COUNT(sem), &_igeo);

      _shader = r->stockShader(Eks::PlainColour, &_layout);

      Eks::ShaderConstantDataDescription dataDesc[] =
      {
        { "colour", Eks::ShaderConstantDataDescription::Float4 }
      };
      const Eks::Colour &col = Eks::Colour(direction);
      Eks::ShaderConstantData::delayedCreate(_data, r, dataDesc, X_ARRAY_COUNT(dataDesc), col.data());
      }

    Eks::Transform wC = toRender->resultTransform(cam);

    Eks::Vector3D x = Eks::Vector3D(1.0f, 0.0f, 0.0f);
    Eks::Vector3D lockDir = toRender->lockDirection().normalized();
    if(lockDir.dot(x) < 0.99f)
      {
      Eks::Vector3D dir = x.cross(lockDir);
      Eigen::AngleAxisf a((float)M_PI/2.0f, dir);

      wC.rotate(a);
      }

    r->setTransform(wC);

    _shader->setShaderConstantData(0, &_data);
    r->setShader(_shader, _layout);
    r->drawLines(&_igeo, &_geo);
    }

private:
  mutable Eks::Geometry _geo;
  mutable Eks::IndexGeometry _igeo;
  mutable Eks::Shader *_shader;
  mutable const Eks::ShaderVertexLayout *_layout;
  mutable Eks::ShaderConstantData _data;
  };

S_IMPLEMENT_PROPERTY(GCSingularRotateManipulator, GraphicsCore)

void GCSingularRotateManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCSingularRotateManipulator> *info,
                                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);
    }
  }

GCSingularRotateManipulator::GCSingularRotateManipulator()
    : _driven(generalPurposeAllocator())
  {
  }

void GCSingularRotateManipulator::addDriven(TransformProperty *in)
  {
  _driven << in;
  }

void GCSingularRotateManipulator::onDrag(const MouseMoveEvent &e)
  {
  Eks::Quaternion relativeDisp;
  GCAngularDragManipulator::onDrag(e, relativeDisp);

  xForeach(TransformProperty *t, _driven)
    {
    Eks::Transform trans = t->value();
    trans *= relativeDisp;
    *t = trans;
    }
  }

S_IMPLEMENT_PROPERTY(GCRotateManipulator, GraphicsCore)

void GCRotateManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCRotateManipulator> *info,
                                                   const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto x = childBlock.add(&GCRotateManipulator::x, "x");
    auto y = childBlock.add(&GCRotateManipulator::y, "y");
    auto z = childBlock.add(&GCRotateManipulator::z, "z");

    Eks::Vector3D dir[] =
      {
      Eks::Vector3D(1.0f, 0.0f, 0.0f),
      Eks::Vector3D(0.0f, 1.0f, 0.0f),
      Eks::Vector3D(0.0f, 0.0f, 1.0f),
      };

    Shift::PropertyInstanceInformationTyped<GCRotateManipulator, GCSingularRotateManipulator>
      *components[] = { x, y, z };

    for(xsize i = 0; i < X_ARRAY_COUNT(components); ++i)
      {
      embedChildManipulator(
        info,
        data,
        childBlock,
        components[i],
        [&dir, i](Shift::PropertyInformationChildrenCreatorTyped<GCSingularRotateManipulator> &block)
          {
          auto lm = block.overrideChild(&GCSingularRotateManipulator::lockMode);
          lm->setDefaultValue(GCSingularRotateManipulator::Planar);

          auto ld = block.overrideChild(&GCSingularRotateManipulator::lockDirection);
          ld->setDefaultValue(dir[i]);
          }
        );
      }

    //auto cent = childBlock.add(&GCTranslateManipulator::central, "central");
    //embedChildManipulator(info, data, childBlock, cent);
    }
  }

GCRotateManipulator::GCRotateManipulator()
  {
  x.createDelegate<CircularRotateDelegate>();
  y.createDelegate<CircularRotateDelegate>();
  z.createDelegate<CircularRotateDelegate>();
  //central.createDelegate<GCManipulatorDistanceDelegate>();
  }

void GCRotateManipulator::addDriven(TransformProperty *in)
  {
  x.addDriven(in);
  y.addDriven(in);
  z.addDriven(in);
  //central.addDriven(in);
  }
