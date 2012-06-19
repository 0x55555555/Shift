#include "GCScene.h"
#include "spropertyinformationhelpers.h"
#include "XShader.h"
#include "XRenderer.h"
#include "XMatrix4x4"
#include "siterator.h"
#include "sprocessmanager.h"
#include "XLine.h"
#include "QVarLengthArray"
#include "XCuboid.h"

S_IMPLEMENT_PROPERTY(GCScene, GraphicsCore)

void GCScene::createTypeInformation(SPropertyInformationTyped<GCScene> *info,
                                    const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&GCScene::activeCamera, "activeCamera");
    info->add(&GCScene::cameraTransform, "cameraTransform");
    info->add(&GCScene::cameraProjection, "cameraProjection");
    }

  if(data.registerInterfaces)
    {
    auto ifc = info->apiInterface();
    ifc->addMethod<void(GCViewableTransform*), &GCScene::setCamera>("setCamera");
    }
  }

GCScene::GCScene() : XCameraCanvasController(0)
  {
  }

XCameraCanvasController::CameraInterface *GCScene::camera()
  {
  return activeCamera.pointed();
  }

void GCScene::render(XRenderer *r) const
  {
  r->setProjectionTransform(cameraProjection());

  r->pushTransform(cameraTransform());

  GCRenderArray::render(r);

  r->popTransform();
  }

void GCScene::setCamera(GCViewableTransform *e)
  {
  cameraProjection.setInput(&e->projection);
  cameraTransform.setInput(&e->viewTransform);
  activeCamera.setInput(e);
  }

S_IMPLEMENT_PROPERTY(GCManipulatableScene, GraphicsCore)

void computeManips(GCManipulatableScene *s)
  {
  s->refreshManipulators();
  }

void GCManipulatableScene::createTypeInformation(SPropertyInformationTyped<GCManipulatableScene> *info,
                                                 const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto manInfo = info->add(&GCManipulatableScene::manipulators, "manipulators");
    manInfo->setCompute<computeManips>();

    auto selInfo = info->add(&GCManipulatableScene::selection, "selection");
    selInfo->setAffects(manInfo);
    }
  }

GCManipulatableScene::GCManipulatableScene() : _currentManipulator(0), _mouseSelecting(false)
  {
  XVector3D points[] = {
    XVector3D(0, 0, 0),
    XVector3D(1, 0, 0),
    XVector3D(0, 1, 0),
    XVector3D(1, 1, 0),
    XVector3D(0, 0, 1),
    XVector3D(1, 0, 1),
    XVector3D(0, 1, 1),
    XVector3D(1, 1, 1)
  };
  _bounds.setAttribute("vertex", points, X_ARRAY_COUNT(points));


  xuint32 lines[] = {
    0, 1,
    2, 3,
    4, 5,
    6, 7,

    0, 2,
    1, 3,
    4, 6,
    5, 7,

    0, 4,
    1, 5,
    2, 6,
    3, 7
  };
  _bounds.setLines(lines, X_ARRAY_COUNT(lines));

  _boundsShader.setToDefinedType("plainColour");
  _boundsShader.getVariable("colour")->setValue(XColour(1.0f, 1.0f, 1.0f));
  }

void GCManipulatableScene::clearManipulators()
  {
  manipulators.clear();
  }

void GCManipulatableScene::refreshManipulators()
  {
  SBlock b(handler());

  clearManipulators();

  xForeach(auto groupPtr, renderGroup.walker<GCRenderablePointer>())
    {
    SProperty* inp = groupPtr->input();

    if(inp)
      {
      GCRenderable* group = inp->uncheckedCastTo<GCRenderable>(); // pointer() only returns const...
      if(group)
        {
        //group->addManipulators(&manipulators);
        }
      }
    }
  }

void GCManipulatableScene::render(XRenderer *x) const
  {
  xAssert(SProcessManager::isMainThread());

  GCScene::render(x);

  const GCCamera *cam = activeCamera();
  xAssert(cam);
  if(cam)
    {
    x->pushTransform(cameraTransform());

    x->setShader(&_boundsShader);
    xForeach(auto m, selection.walker<Pointer>())
      {
      const GCRenderable* ren = m->pointed<GCRenderable>();

      if(ren)
        {
        XCuboid bounds = ren->bounds();
        bounds.expand(0.015f);

        XTransform trans = XTransform::Identity();
        trans.scale(bounds.size().toVector3D());
        trans.pretranslate(bounds.minimum());

        x->pushTransform(trans);
        x->drawGeometry(_bounds);
        x->popTransform();
        }
      }

    if(!manipulators.isEmpty())
      {
      x->clear(XRenderer::ClearDepth);

      xForeach(auto m, manipulators.walker<GCVisualManipulator>())
        {
        m->render(cam, x);
        }
      }
    x->popTransform();
    }
  }

GCManipulatableScene::UsedFlags GCManipulatableScene::mouseEvent(const MouseEvent &e)
  {
  UsedFlags parentFlags = XCameraCanvasController::mouseEvent(e).hasFlag(Used);
  if(parentFlags.hasFlag(Used))
    {
    return parentFlags;
    }

  GCVisualManipulator::MouseMoveEvent manipEv;
  manipEv.cam = activeCamera();

  manipEv.widgetPoint = e.point;

  manipEv.direction = manipEv.cam->worldSpaceFromScreenSpace(e.point.x(), e.point.y());
  manipEv.direction -= manipEv.cam->transform().translation();
  manipEv.direction.normalize();

  if(!isMouseSelecting())
    {
    if(!_currentManipulator && e.type == XAbstractCanvasController::Press && e.modifiers == Qt::NoModifier && e.triggerButton == Qt::LeftButton)
      {
      float chosenDistance = HUGE_VAL;
      GCVisualManipulator *chosenManip = 0;

      xForeach(auto m, manipulators.walker<GCVisualManipulator>())
        {
        float tempDistance = HUGE_VAL;
        GCVisualManipulator *clicked = 0;
        if(m->hitTest(e.point, manipEv.cam, manipEv.direction, &tempDistance, &clicked))
          {
          if(tempDistance < chosenDistance)
            {
            chosenManip = clicked;
            chosenDistance = tempDistance;
            xAssert(chosenManip);
            }
          }
        }
      _currentManipulator = chosenManip;
      }

    if(_currentManipulator)
      {
      if(e.type == XAbstractCanvasController::Press)
        {
        _currentManipulator->onMouseClick(manipEv);
        }
      else if(e.type == XAbstractCanvasController::Release)
        {
        _currentManipulator->onMouseRelease(manipEv);
        _currentManipulator = 0;
        }
      else if(e.type == XAbstractCanvasController::DoubleClick)
        {
        _currentManipulator->onMouseDoubleClick(manipEv);
        // reset current manip?
        }
      else if(e.type == XAbstractCanvasController::Move)
        {
        manipEv.lastDirection = manipEv.cam->worldSpaceFromScreenSpace(e.lastPoint.x(), e.lastPoint.y());
        manipEv.lastDirection -= manipEv.cam->transform().translation();
        manipEv.lastDirection.normalize();

        manipEv.lastWidgetPoint = e.lastPoint;

        _currentManipulator->onMouseDrag(manipEv);
        }

      return Used|NeedsUpdate;
      }
    }
  else
    {
    if(e.type == Move)
      {
      moveMouseSelection(manipEv.direction);
      }
    if(e.type == Release)
      {
      endMouseSelection(manipEv.direction);
      }
    }

  if(!_currentManipulator && e.type == Press && e.modifiers == Qt::NoModifier && e.triggerButton == Qt::LeftButton)
    {
    beginMouseSelection(manipEv.direction);
    }

  return NotUsed;
  }

GCManipulatableScene::UsedFlags GCManipulatableScene::wheelEvent(const WheelEvent &w)
  {
  return XCameraCanvasController::wheelEvent(w);
  }


void GCManipulatableScene::beginMouseSelection(const XVector3D &sel)
  {
  _mouseSelecting = true;
  _hasMouseMoved = false;
  _initialRay = sel;
  }

void GCManipulatableScene::moveMouseSelection(const XVector3D &sel)
  {
  _hasMouseMoved = true;
  _finalRay = sel;
  }

void GCManipulatableScene::endMouseSelection(const XVector3D &sel)
  {
  _mouseSelecting = false;
  _finalRay = sel;

  if(_hasMouseMoved)
    {
    //marqueeSelect();
    raySelect(_finalRay);
    }
  else
    {
    raySelect(_initialRay);
    }
  }

bool GCManipulatableScene::isMouseSelecting() const
  {
  return _mouseSelecting;
  }

void GCManipulatableScene::raySelect(const XVector3D &dir)
  {
  const float farDist = 1000.0f;
  const XVector3D& camPos = cameraTransform().inverse().translation();
  XLine line(camPos, camPos + (dir * farDist));

  class InternalSelector : public GCRenderable::Selector
    {
  XProperties:
    XROProperty(Hit, hit);

  public:
    InternalSelector(const XVector3D &cP) : camPos(cP), oldDistSq(HUGE_VAL)
      {
      Hit h = { XVector3D::Zero(), XVector3D::Zero(), 0x0 };
      _hit = h;
      }

    void onHit(const XVector3D& pos, const XVector3D& normal, GCRenderable *r)
      {
      float newDistSq = (pos - camPos).squaredNorm();

      if(newDistSq < oldDistSq)
        {
        Hit h = { pos, normal, r };
        _hit = h;
        }
      }

  private:
    float oldDistSq;
    XVector3D camPos;
    };

  InternalSelector interface(camPos);
  GCRenderArray::intersect(line, &interface);

  SBlock b(database());
  selection.clear();

  if(interface.hit().object)
    {
    selection.addPointer(interface.hit().object);
    }
  }

void GCManipulatableScene::marqueeSelect(const XFrustum &)
  {
  xAssertFail();
  }
