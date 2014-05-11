#include "2D/GCPlate.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "XFramebuffer.h"

S_IMPLEMENT_PROPERTY(GCPlate, GraphicsCore)

void GCPlate::createTypeInformation(Shift::PropertyInformationTyped<GCPlate> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  info->createChildrenBlock(data);
  }

void GCPlate::render(Eks::Renderer *renderer, const RenderState &state) const
  {
  xAssert(state.framebuffer)
  state.framebuffer->clear(Eks::FrameBuffer::ClearDepth);

  //XRendererFlagBlock f(renderer, XRenderer::AlphaBlending);



  renderer->setTransform(state.transform * transform());

  // render all elements and embedded and attached elements with the transform applied
  RCRenderArray::render(renderer, state);

  xForeach(auto r, elements.walker<RCRenderablePointer>())
    {
    const RCRenderable* ptd = r->pointed();
    if(!ptd)
      {
      qWarning() << "Null element";
      continue;
      }

    ptd->render(renderer, state);
    }
  }
