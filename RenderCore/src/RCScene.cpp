#include "RCScene.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"
#include "shift/Utilities/siterator.h"

void RCScene::computeRasteriser(RCScene *s)
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

S_IMPLEMENT_PROPERTY(RCScene, RenderCore)

void RCScene::createTypeInformation(Shift::PropertyInformationTyped<RCScene> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  childBlock.add(&RCScene::activeCamera, "activeCamera");
  childBlock.add(&RCScene::cameraTransform, "cameraTransform");
  childBlock.add(&RCScene::cameraProjection, "cameraProjection");

  auto ras = childBlock.add(&RCScene::_rasteriserState, "_rasteriserState");
  ras->setCompute<computeRasteriser>();

  auto render = childBlock.add(&RCScene::renderer, "renderer");
  render->setAffects(data, ras);
  }

RCScene::RCScene() : Eks::CameraCanvasController(0)
  {
  }

Eks::CameraCanvasController::CameraInterface *RCScene::camera()
  {
  return activeCamera.pointed();
  }

void RCScene::render(Eks::Renderer *r, const RenderState &state) const
  {
  r->setProjectionTransform(cameraProjection());
  r->setViewTransform(cameraTransform());

  r->setRasteriserState(&(_rasteriserState()));
  RCRenderArray::render(r, state);
  }

void RCScene::setCamera(RCViewableTransform *e)
  {
  cameraProjection.setInput(&e->projection);
  cameraTransform.setInput(&e->viewTransform);
  activeCamera.setInput(e);
  }
