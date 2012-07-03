#include "GCPlate.h"
#include "spropertyinformationhelpers.h"
#include "XRenderer.h"

S_IMPLEMENT_PROPERTY(GCPlate, GraphicsCore)

void GCPlate::createTypeInformation(SPropertyInformationTyped<GCPlate> *info,
                                    const SPropertyInformationCreateData &data)
  {
  }

GCPlate::GCPlate()
  {
  }

void GCPlate::render(XRenderer *r) const
  {
  r->debugRenderLocator(XRenderer::ClearShader);
  }
