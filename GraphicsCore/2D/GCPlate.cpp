#include "GCPlate.h"
#include "spropertyinformationhelpers.h"
#include "XRenderer.h"

S_IMPLEMENT_PROPERTY(GCPlate, GraphicsCore)

void GCPlate::createTypeInformation(SPropertyInformationTyped<GCPlate> *info,
                                    const SPropertyInformationCreateData &data)
  {
  }

void GCPlate::render(XRenderer *renderer) const
  {
  renderer->clear(XRenderer::ClearDepth);

  XRendererFlagBlock f(renderer, XRenderer::AlphaBlending);



  renderer->pushTransform(transform());

  // render all elements and embedded and attached elements with the transform applied
  GCRenderArray::render(renderer);

  xForeach(auto r, elements.walker<GCRenderablePointer>())
    {
    const GCRenderable* ptd = r->pointed();
    if(!ptd)
      {
      qWarning() << "Null element";
      continue;
      }

    ptd->render(renderer);
    }

  renderer->popTransform();
  }
