#include "GCScene.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sbaseproperties.inl"
#include "shift/Utilities/siterator.h"
#include "XShader.h"
#include "XRenderer.h"
#include "XFrameBuffer.h"
#include "XMathMatrix"
#include "XLine.h"
#include "XCuboid.h"

void GCScene::computeRasteriser(GCScene *s)
  {
  Eks::Renderer *r = s->renderer();
  if(!r)
    {
    return;
    }
  
  auto lock = s->_rasteriserState.computeLock();
  if(lock->isValid())
    {
    lock->~RasteriserState();
    }
  new(lock.data()) Eks::RasteriserState(r, Eks::RasteriserState::CullBack);
  }

S_IMPLEMENT_PROPERTY(GCScene, GraphicsCore)

void GCScene::createTypeInformation(Shift::PropertyInformationTyped<GCScene> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    childBlock.add(&GCScene::activeCamera, "activeCamera");
    childBlock.add(&GCScene::cameraTransform, "cameraTransform");
    childBlock.add(&GCScene::cameraProjection, "cameraProjection");

    auto ras = childBlock.add(&GCScene::_rasteriserState, "_rasteriserState");
    ras->setCompute<computeRasteriser>();

    auto render = childBlock.add(&GCScene::renderer, "renderer");
    render->setAffects(data, ras);
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

  r->setRasteriserState(&(_rasteriserState()));
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
    auto childBlock = info->createChildrenBlock(data);

    auto manInfo = childBlock.add(&GCManipulatableScene::manipulators, "manipulators");
    manInfo->setCompute<computeManips>();

    auto selInfo = childBlock.add(&GCManipulatableScene::selection, "selection");
    selInfo->setAffects(data, manInfo);

    auto scale = childBlock.add(&GCManipulatableScene::manipulatorDisplayScale, "manipulatorDisplayScale");
    scale->setDefaultValue(100.0f);
    }
  }

GCManipulatableScene::GCManipulatableScene() : _currentManipulator(0), _mouseSelecting(false)
  {
  }

void GCManipulatableScene::initialise()
  {
  Eks::Renderer *r = renderer();
  xAssert(r);

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
      renderer(),
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

  if(!(_shader = r->stockShader(Eks::PlainColour, &_shaderLayout)) || !_shaderLayout)
    {
    xAssertFail();
    }
  }

void GCManipulatableScene::clearManipulators()
  {
  manipulators.clear();
  }

void GCManipulatableScene::refreshManipulators()
  {
  Shift::Block b(handler());

  clearManipulators();

  class Manipulator : public GCManipulatable
    {
  public:
    GCScene *scene;
    GCRenderablePointerArray *manipulatableChildren() { return &scene->renderGroup; }
    } manip;

  manip.scene = this;

  GCManipulatable::ManipInfo info;
  info.viewTransform = activeCamera();

  info.displayScale = &manipulatorDisplayScale;
  manip.addManipulators(&manipulators, info);
  }

void GCManipulatableScene::render(Eks::Renderer *x, const RenderState &state) const
  {
  GCScene::render(x, state);

  const GCCamera *cam = activeCamera();
  xAssert(cam);
  if(cam)
    {
    x->setViewTransform(cameraTransform());

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
        x->drawLines(&_bounds);
        }
      }

    if(manipulators.size())
      {
      state.framebuffer->clear(Eks::FrameBuffer::ClearDepth);

      xForeach(auto m, manipulators.walker<GCVisualManipulator>())
        {
        m->render(cam, x);
        }
      }
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
