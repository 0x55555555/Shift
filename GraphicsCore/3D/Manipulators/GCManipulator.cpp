#include "GCManipulator.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "3D/GCCamera.h"
#include "GCRenderable.h"
#include "XPlane.h"
#include "XLine.h"
#include "XFrame"

S_IMPLEMENT_ABSTRACT_PROPERTY(GCVisualManipulator, GraphicsCore)

void GCVisualManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCVisualManipulator> *info,
                                                const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto sh = childBlock.add(&GCVisualManipulator::show, "show");
    sh->setDefaultValue(true);

    struct Utils
      {
      static void computeWorldTransform(GCVisualManipulator *manip)
        {
        manip->worldTransform = manip->parentTransform() * manip->localTransform();
        }
      };

    auto wt = childBlock.add(&GCVisualManipulator::worldTransform, "worldTransform");
    wt->setCompute<Utils::computeWorldTransform>();

    auto wtAff = childBlock.createAffects(&wt, 1);

    auto pt = childBlock.add(&GCVisualManipulator::parentTransform, "parentTransform");
    pt->setAffects(wtAff, true);
    auto lt = childBlock.add(&GCVisualManipulator::localTransform, "localTransform");
    lt->setAffects(wtAff, false);


    auto scale = childBlock.add(&GCVisualManipulator::displayScale, "displayScale");
    scale->setDefaultValue(1.0f);

    auto scaleMode = childBlock.add(&GCVisualManipulator::scaleMode, "scaleMode");
    scaleMode->setDefaultValue(ScreenSpaceScale);
    }
  }

GCVisualManipulator::GCVisualManipulator() : _delegate(0)
  {
  }

Eks::Transform GCVisualManipulator::resultTransform(const GCViewableTransform *tr) const
  {
  return computeScaledResultTransform(worldTransform(), scaleMode(), tr, displayScale());
  }

Eks::Transform GCVisualManipulator::computeScaledResultTransform(
    const Eks::Transform &worldTransform,
    ScaleType mode,
    const GCViewableTransform *tr,
    float displayScale)
  {
  float scaleToApply = displayScale;
  if(mode == ScreenSpaceScale)
    {
    xAssert(tr);
    if(tr)
      {
      float dist = (worldTransform.translation() - tr->transform().translation()).norm();

      float x = 0.0f, y = 0.0f;
      tr->approximatePixelSizeAtDistance(dist, x, y);

      scaleToApply *= x;
      }
    }

  Eks::Transform result = worldTransform;
  result.scale(scaleToApply);
  return result;
  }

const GCVisualManipulator::Delegate *GCVisualManipulator::delegate() const
  {
  return _delegate.value();
  }

void GCVisualManipulator::render(const GCCamera *camera, Eks::Renderer *r) const
  {
  if(show() && delegate())
    {
    delegate()->render(this, camera, r);
    }
  }

Eks::Vector3D GCVisualManipulator::focalPoint(const GCViewableTransform *cam) const
  {
  if(delegate())
    {
    return resultTransform(cam).translation();
    }
  return Eks::Vector3D::Zero();
  }

bool GCVisualManipulator::hitTest(
    const QPoint &widgetSpacePoint,
    const GCViewableTransform *camera,
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

bool GCVisualCompoundManipulator::hitTest(
    const QPoint &widgetSpacePoint,
    const GCViewableTransform *camera,
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


S_IMPLEMENT_ABSTRACT_PROPERTY(GCDisplacementDragManipulator, GraphicsCore)

void GCDisplacementDragManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCDisplacementDragManipulator> *info,
                                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCDisplacementDragManipulator::lockMode, "lockMode");
    childBlock.add(&GCDisplacementDragManipulator::lockDirection, "lockDirection");
    }
  }

void GCDisplacementDragManipulator::onDrag(const MouseMoveEvent &e, Eks::Vector3D &rel)
  {
  rel = Eks::Vector3D::Zero();

  Eks::Vector3D focus = focalPoint(e.cam);
  const Eks::Vector3D &camPosition = e.cam->transform().translation();
  float focalDistanceFromCamera = (camPosition - focus).norm();

  Eks::Vector3D lockDir = resultTransform(e.cam).linear() * lockDirection();

  xuint32 lock = lockMode();
  if(lock == Linear)
    {
    Eks::Line p(focus, lockDir, Eks::Line::PointAndDirection);
    Eks::Line a(camPosition, e.lastDirection, Eks::Line::PointAndDirection);
    Eks::Line b(camPosition, e.direction, Eks::Line::PointAndDirection);

    float lastHitT = a.closestPointOn(p);
    float hitT = b.closestPointOn(p);

    if(lastHitT > 0.0f && lastHitT < HUGE_VAL &&
       hitT > 0.0f && hitT < HUGE_VAL)
      {
      Eks::Vector3D lastHit = a.sample(lastHitT);
      Eks::Vector3D hit = b.sample(hitT);

      if(lastHit.isApprox(hit))
        {
        return;
        }

      float lastPT = p.closestPointTo(lastHit);
      float pT = p.closestPointTo(hit);

      rel = p.sample(pT) - p.sample(lastPT);
      xAssert(fabs(rel.normalized().dot(p.direction().normalized())) > 0.80f);

      if(rel.norm() > HUGE_VAL)
        {
        xAssertFail();
        }
      }
    }
  else if(lock == Planar)
    {
    Eks::Plane p(focus, lockDir);
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



S_IMPLEMENT_ABSTRACT_PROPERTY(GCAngularDragManipulator, GraphicsCore)

void GCAngularDragManipulator::createTypeInformation(Shift::PropertyInformationTyped<GCAngularDragManipulator> *info,
                                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCAngularDragManipulator::lockMode, "lockMode");
    childBlock.add(&GCAngularDragManipulator::lockDirection, "lockDirection");
    }
  }

void GCAngularDragManipulator::onDrag(const MouseMoveEvent &e, Eks::Quaternion &rel)
  {
  rel = Eks::Quaternion::Identity();

  Eks::Vector3D focus = focalPoint(e.cam);
  const Eks::Vector3D &camPosition = e.cam->transform().translation();
  //float focalDistanceFromCamera = (camPosition - focus).norm();

  xuint32 lock = lockMode();
  if(lock == Planar)
    {
    Eks::Plane p(focus, lockDirection());
    Eks::Line a(camPosition, e.lastDirection, Eks::Line::PointAndDirection);
    Eks::Line b(camPosition, e.direction, Eks::Line::PointAndDirection);

    Eks::Frame f(p.normal());
    
    Eks::Vector3D isectA = a.sample(p.intersection(a));
    Eks::Vector3D isectB = b.sample(p.intersection(b));
    
    Eks::Vector3D subA = isectA - focus;
    Eks::Vector3D subB = isectB - focus;

    Eks::Vector3D lastHitDir = subA.normalized();
    Eks::Vector3D hitDir = subB.normalized();

    float x1 = lastHitDir.dot(f.across());
    float x2 = hitDir.dot(f.across());
    float y1 = lastHitDir.dot(f.up());
    float y2 = hitDir.dot(f.up());

    float oldAngle = atan2f(y1, x1);
    float angle = atan2f(y2, x2);

    rel = Eigen::AngleAxisf(angle - oldAngle, f.facing());
    }
  else // Free.
    {
    /*Eks::Vector3D a = camPosition + e.lastDirection*focalDistanceFromCamera;
    Eks::Vector3D b = camPosition + e.direction*focalDistanceFromCamera;

    rel = b - a;*/
    }
  }
