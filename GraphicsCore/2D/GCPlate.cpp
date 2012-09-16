#include "GCPlate.h"
#include "spropertyinformationhelpers.h"
#include "XRenderer.h"

S_IMPLEMENT_PROPERTY(GCPlate, GraphicsCore)

void GCPlate::createTypeInformation(SPropertyInformationTyped<GCPlate> *info,
                                    const SPropertyInformationCreateData &data)
  {
  }

void GCPlate::render(XRenderer *r) const
  {
  r->clear(XRenderer::ClearDepth);

  XRendererFlagBlock f(r, XRenderer::AlphaBlending);

  GCElement::render(r);
  }
