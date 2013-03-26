#include "GCManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "3D/GCCamera.h"
#include "GCRenderable.h"
#include "XPlane.h"
#include "XLine.h"

void GCManipulatable::addManipulators(
    Shift::PropertyArray *arr,
    const ManipInfo &info)
  {
  GCRenderablePointerArray *children = manipulatableChildren();
  if(!children)
    {
    return;
    }

  xForeach(auto prop, children->walker<GCRenderablePointer>())
    {
    GCRenderable *geo = prop->pointed();
    if(geo)
      {
      GCManipulatable *manip = geo->interface<GCManipulatable>();

      if(manip)
        {
        manip->addManipulators(arr, info);
        }
      }
    }
  }

S_IMPLEMENT_ABSTRACT_PROPERTY(GCVisualManipulator, GraphicsCore)

void GCVisualManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCVisualManipulator> *info,
                                                const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCVisualManipulator::show, "show");

    struct Utils
      {
      static void computeWorldTransform(GCVisualManipulator *manip)
        {
        manip->worldTransform = manip->parentTransform() * manip->localTransform();
        }
      };

    auto wt = childBlock.add(&GCVisualManipulator::worldTransform, "worldTransform");
    wt->setCompute<Utils::computeWorldTransform>();

    auto affects = childBlock.createAffects(&wt, 1);

    auto pt = childBlock.add(&GCVisualManipulator::parentTransform, "parentTransform");
    pt->setAffects(affects, true);
    auto lt = childBlock.add(&GCVisualManipulator::localTransform, "localTransform");
    lt->setAffects(affects, false);

    childBlock.add(&GCVisualManipulator::manipulatorsDisplayScale, "manipulatorsDisplayScale");
    }
  }

GCVisualManipulator::GCVisualManipulator() : _delegate(0)
  {
  }

void GCVisualManipulator::render(const GCCamera *camera, Eks::Renderer *r) const
  {
  if(delegate())
    {
    delegate()->render(this, camera, r);
    }
  }

Eks::Vector3D GCVisualManipulator::focalPoint() const
  {
  if(delegate())
    {
    return delegate()->focalPoint(this);
    }
  return Eks::Vector3D::Zero();
  }

bool GCVisualManipulator::hitTest(
    const QPoint &widgetSpacePoint,
    const GCCamera *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance,
    GCVisualManipulator **clicked)
  {
  if(delegate())
    {
    if(delegate()->hitTest(this, widgetSpacePoint, camera, clickDirection, distance))
      {
      *clicked = this;
      return true;
      }
    }
  return false;
  }

S_IMPLEMENT_PROPERTY(GCVisualCompoundManipulator, GraphicsCore)

void GCVisualCompoundManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCVisualCompoundManipulator> *info,
                                                        const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }

GCVisualCompoundManipulator::GCVisualCompoundManipulator()
  {
  }

bool GCVisualCompoundManipulator::hitTest(
    const QPoint &widgetSpacePoint,
    const GCCamera *camera,
    const Eks::Vector3D &clickDirection, // in world space
    float *distance,
    GCVisualManipulator **clicked)
  {
  xAssert(distance);
  xAssert(clicked);

  *clicked = 0;
  *distance = HUGE_VAL;

  float tempDistance = HUGE_VAL;

  xForeach(auto m, walker<GCVisualManipulator>())
    {
    if(m->hitTest(widgetSpacePoint, camera, clickDirection, &tempDistance, clicked) &&
       tempDistance < *distance)
      {
      *distance = tempDistance;
      *clicked = m;
      }
    }
  return *clicked != 0;
  }

void GCVisualCompoundManipulator::render(const GCCamera *camera, Eks::Renderer *r) const
  {
  xForeach(auto m, walker<GCVisualManipulator>())
    {
    m->render(camera, r);
    }
  }

void GCVisualCompoundManipulator::onMouseClick(const MouseEvent &)
  {
  xAssertFail();
  }

void GCVisualCompoundManipulator::onMouseDoubleClick(const MouseEvent &)
  {
  xAssertFail();
  }

void GCVisualCompoundManipulator::onMouseDrag(const MouseMoveEvent &)
  {
  xAssertFail();
  }

void GCVisualCompoundManipulator::onMouseRelease(const MouseEvent &)
  {
  xAssertFail();
  }


S_IMPLEMENT_ABSTRACT_PROPERTY(GCVisualDragManipulator, GraphicsCore)

void GCVisualDragManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCVisualDragManipulator> *info,
                                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }

GCVisualDragManipulator::GCVisualDragManipulator()
  {
  }

void GCVisualDragManipulator::onMouseClick(const MouseEvent &)
  {
  }

void GCVisualDragManipulator::onMouseDoubleClick(const MouseEvent &)
  {
  }

void GCVisualDragManipulator::onMouseDrag(const MouseMoveEvent &e)
  {
  onDrag(e);
  }

void GCVisualDragManipulator::onMouseRelease(const MouseEvent &)
  {
  }


S_IMPLEMENT_ABSTRACT_PROPERTY(GCVisualClickManipulator, GraphicsCore)

void GCVisualClickManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCVisualClickManipulator> *info,
                                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }

GCVisualClickManipulator::GCVisualClickManipulator()
  {
  }

void GCVisualClickManipulator::onMouseClick(const MouseEvent &)
  {
  onClick();
  }

void GCVisualClickManipulator::onMouseDoubleClick(const MouseEvent &)
  {
  }

void GCVisualClickManipulator::onMouseDrag(const MouseMoveEvent &)
  {
  }

void GCVisualClickManipulator::onMouseRelease(const MouseEvent &)
  {
  }


S_IMPLEMENT_ABSTRACT_PROPERTY(GCLinearDragManipulator, GraphicsCore)

void GCLinearDragManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCLinearDragManipulator> *info,
                                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCLinearDragManipulator::lockMode, "lockMode");
    childBlock.add(&GCLinearDragManipulator::lockDirection, "lockDirection");
    }
  }

GCLinearDragManipulator::GCLinearDragManipulator()
  {
  }

void GCLinearDragManipulator::onDrag(const MouseMoveEvent &e, Eks::Vector3D &rel)
  {
  rel = Eks::Vector3D::Zero();

  Eks::Vector3D focus = focalPoint();
  const Eks::Vector3D &camPosition = e.cam->transform().translation();
  float focalDistanceFromCamera = (camPosition - focus).norm();

  xuint32 lock = lockMode();
  if(lock == Linear)
    {
    Eks::Line p(focus, lockDirection(), Eks::Line::PointAndDirection);
    Eks::Line a(camPosition, e.lastDirection, Eks::Line::PointAndDirection);
    Eks::Line b(camPosition, e.direction, Eks::Line::PointAndDirection);

    float lastHitT = a.closestPointOn(p);
    float hitT = b.closestPointOn(p);

    xAssert(fabs(lastHitT) < HUGE_VAL);
    xAssert(fabs(hitT) < HUGE_VAL);

    if(lastHitT > 0.0f && lastHitT < HUGE_VAL &&
       hitT > 0.0f && hitT < HUGE_VAL)
      {
      Eks::Vector3D lastHit = a.sample(lastHitT);
      Eks::Vector3D hit = b.sample(hitT);

      float lastPT = p.closestPointTo(lastHit);
      float pT = p.closestPointTo(hit);

      rel = p.sample(pT) - p.sample(lastPT);
      xAssert(fabs(rel.normalized().dot(p.direction())) > 0.97f);

      if(rel.norm() > HUGE_VAL)
        {
        xAssertFail();
        }
      }
    }
  else if(lock == Planar)
    {
    Eks::Plane p(focus, lockDirection());
    Eks::Line a(camPosition, e.lastDirection, Eks::Line::PointAndDirection);
    Eks::Line b(camPosition, e.direction, Eks::Line::PointAndDirection);

    Eks::Vector3D lastHit = a.sample(p.intersection(a));
    Eks::Vector3D hit = b.sample(p.intersection(b));

    rel = hit - lastHit;
    }
  else // Free.
    {
    Eks::Vector3D a = camPosition + e.lastDirection*focalDistanceFromCamera;
    Eks::Vector3D b = camPosition + e.direction*focalDistanceFromCamera;

    rel = b - a;
    }
  }
