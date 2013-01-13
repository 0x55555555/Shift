#include "GCScene.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Utilities/siterator.h"
#include "XShader.h"
#include "XRenderer.h"
#include "XMathMatrix"
#include "XLine.h"
#include "XCuboid.h"

S_IMPLEMENT_PROPERTY(GCScene, GraphicsCore)

void GCScene::createTypeInformation(Shift::PropertyInformationTyped<GCScene> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(data, &GCScene::activeCamera, "activeCamera");
    info->add(data, &GCScene::cameraTransform, "cameraTransform");
    info->add(data, &GCScene::cameraProjection, "cameraProjection");
    }

  if(data.registerInterfaces)
    {
    auto ifc = info->apiInterface();

    static XScript::ClassDef<0,0,1> cls = {
      {
      ifc->method<void(GCViewableTransform*), &GCScene::setCamera>("setCamera"),
      }
    };

    ifc->buildInterface(cls);
    }
  }

GCScene::GCScene() : Eks::CameraCanvasController(0)
  {
  }

Eks::CameraCanvasController::CameraInterface *GCScene::camera()
  {
  return activeCamera.pointed();
  }

void GCScene::render(Eks::Renderer *r, const RenderState &state) const
  {
  r->setProjectionTransform(cameraProjection());
  r->setViewTransform(cameraTransform());

  GCRenderArray::render(r, state);
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

void GCManipulatableScene::createTypeInformation(
    Shift::PropertyInformationTyped<GCManipulatableScene> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto manInfo = info->add(data, &GCManipulatableScene::manipulators, "manipulators");
    manInfo->setCompute<computeManips>();

    auto selInfo = info->add(data, &GCManipulatableScene::selection, "selection");
    selInfo->setAffects(data, manInfo);
    }
  }

GCManipulatableScene::GCManipulatableScene() : _currentManipulator(0), _mouseSelecting(false)
  {
  }

void GCManipulatableScene::initialise(Eks::Renderer *r)
  {
  Eks::Vector3D vertices[] = {
    Eks::Vector3D(0, 0, 0),
    Eks::Vector3D(1, 0, 0),
    Eks::Vector3D(0, 1, 0),
    Eks::Vector3D(1, 1, 0),
    Eks::Vector3D(0, 0, 1),
    Eks::Vector3D(1, 0, 1),
    Eks::Vector3D(0, 1, 1),
    Eks::Vector3D(1, 1, 1)
  };

  Eks::Geometry::delayedCreate(
    _bounds,
    r,
    vertices,
    sizeof(vertices[0]),
    X_ARRAY_COUNT(vertices));


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
  Eks::IndexGeometry::delayedCreate(
    _boundIndices,
    r,
    Eks::IndexGeometry::Unsigned16,
    lines,
    X_ARRAY_COUNT(lines));

#if 0
  if(!Eks::ShaderManager::findShader(kPlainColour, &_shader, &_shaderLayout))
    {
    xAssertFail();
    }
#endif
  }

void GCManipulatableScene::clearManipulators()
  {
  manipulators.clear();
  }

void GCManipulatableScene::refreshManipulators()
  {
  Shift::Block b(handler());

  clearManipulators();

  xForeach(auto groupPtr, renderGroup.walker<GCRenderablePointer>())
    {
    Property* inp = groupPtr->input();

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

void GCManipulatableScene::render(Eks::Renderer *x, const RenderState &state) const
  {
  GCScene::render(x, state);

  const GCCamera *cam = activeCamera();
  xAssert(cam);
  if(cam)
    {
    x->setViewTransform(cameraTransform());

    xAssertFail();
    /*
    x->setShader(_shader, _shaderLayout);
    xForeach(auto m, selection.walker<Shift::Pointer>())
      {
      const GCRenderable* ren = m->pointed<GCRenderable>();

      if(ren)
        {
        Eks::Cuboid bounds = ren->bounds();
        bounds.expand(0.015f);

        Eks::Transform trans = Eks::Transform::Identity();
        trans.scale(bounds.size());
        trans.pretranslate(bounds.minimum());

        Eks::Transform fullTransform = state.transform * trans;

        x->setTransform(fullTransform);
        //x->drawGeometry(_bounds);
        }
      }

    if(!manipulators.isEmpty())
      {
      x->clear(Eks::Renderer::ClearDepth);

      xForeach(auto m, manipulators.walker<GCVisualManipulator>())
        {
        m->render(cam, x);
        }
      }*/
    }
  }

GCManipulatableScene::UsedFlags GCManipulatableScene::mouseEvent(const MouseEvent &e)
  {
  UsedFlags parentFlags = Eks::CameraCanvasController::mouseEvent(e).hasFlag(Used);
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
    if(!_currentManipulator && e.type == Eks::AbstractCanvasController::Press && e.modifiers == Qt::NoModifier && e.triggerButton == Qt::LeftButton)
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
      if(e.type == Eks::AbstractCanvasController::Press)
        {
        _currentManipulator->onMouseClick(manipEv);
        }
      else if(e.type == Eks::AbstractCanvasController::Release)
        {
        _currentManipulator->onMouseRelease(manipEv);
        _currentManipulator = 0;
        }
      else if(e.type == Eks::AbstractCanvasController::DoubleClick)
        {
        _currentManipulator->onMouseDoubleClick(manipEv);
        // reset current manip?
        }
      else if(e.type == Eks::AbstractCanvasController::Move)
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
  return Eks::CameraCanvasController::wheelEvent(w);
  }


void GCManipulatableScene::beginMouseSelection(const Eks::Vector3D &sel)
  {
  _mouseSelecting = true;
  _hasMouseMoved = false;
  _initialRay = sel;
  }

void GCManipulatableScene::moveMouseSelection(const Eks::Vector3D &sel)
  {
  _hasMouseMoved = true;
  _finalRay = sel;
  }

void GCManipulatableScene::endMouseSelection(const Eks::Vector3D &sel)
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

void GCManipulatableScene::raySelect(const Eks::Vector3D &dir)
  {
  const float farDist = 1000.0f;
  const Eks::Vector3D& camPos = cameraTransform().inverse().translation();
  Eks::Line line(camPos, camPos + (dir * farDist));

  class InternalSelector : public GCRenderable::Selector
    {
  XProperties:
    XROProperty(Hit, hit);

  public:
    InternalSelector(const Eks::Vector3D &cP) : camPos(cP), oldDistSq(HUGE_VAL)
      {
      Hit h = { Eks::Vector3D::Zero(), Eks::Vector3D::Zero(), 0x0 };
      _hit = h;
      }

    void onHit(const Eks::Vector3D& pos, const Eks::Vector3D& normal, GCRenderable *r)
      {
      float newDistSq = (pos - camPos).squaredNorm();

      if(newDistSq < oldDistSq)
        {
        Hit h = { pos, normal, r };
        _hit = h;
        }
      }

  private:
    Eks::Vector3D camPos;
    float oldDistSq;
    };

  InternalSelector interface(camPos);
  GCRenderArray::intersect(line, &interface);

  Shift::Block b(database());
  selection.clear();

  if(interface.hit().object)
    {
    selection.addPointer(interface.hit().object);
    }
  }

void GCManipulatableScene::marqueeSelect(const Eks::Frustum &)
  {
  xAssertFail();
  }
