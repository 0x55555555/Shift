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
  r->pushTransform(transform());

  {
  XTransform tr = XTransform::Identity();
  tr.scale(100);

  r->pushTransform(tr);

  r->debugRenderLocator(XRenderer::ClearShader);

  r->popTransform();
  }

  r->popTransform();
  }
