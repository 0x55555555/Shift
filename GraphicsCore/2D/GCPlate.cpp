#include "GCPlate.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"

S_IMPLEMENT_PROPERTY(GCPlate, GraphicsCore)

void GCPlate::createTypeInformation(Shift::PropertyInformationTyped<GCPlate> *,
                                    const Shift::PropertyInformationCreateData &)
  {
  }

void GCPlate::render(Eks::Renderer *renderer, const RenderState &state) const
  {
  xAssertFail();
  //renderer->clear(Eks::Renderer::ClearDepth);

  //XRendererFlagBlock f(renderer, XRenderer::AlphaBlending);



  renderer->setTransform(state.transform * transform());

  // render all elements and embedded and attached elements with the transform applied
  GCRenderArray::render(renderer, state);

  xForeach(auto r, elements.walker<GCRenderablePointer>())
    {
    const GCRenderable* ptd = r->pointed();
    if(!ptd)
      {
      qWarning() << "Null element";
      continue;
      }

    ptd->render(renderer, state);
    }
  }
