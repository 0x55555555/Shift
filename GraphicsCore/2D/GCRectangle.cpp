#include "GCRectangle.h"
#include "spropertyinformationhelpers.h"
#include "XTransform.h"
#include "XGLRenderer.h"

S_IMPLEMENT_PROPERTY(GCRectangle, GraphicsCore)

void GCRectangle::createTypeInformation(SPropertyInformationTyped<GCRectangle> *info,
                                        const SPropertyInformationCreateData &data)
  {
  }

void GCRectangle::render(XRenderer *r) const
  {
  XTransform tr = XTransform::Identity();

  tr.translate(XVector3D(left(), bottom(), 0));

  XTransform tr2 = tr;
  tr.translate(XVector3D(width(), height(), 0));

  tr.scale(100);
  tr2.scale(100);

  r->pushTransform(tr);
  r->debugRenderLocator(XRenderer::ClearShader);
  r->popTransform();

  r->pushTransform(tr2);
  r->debugRenderLocator(XRenderer::ClearShader);
  r->popTransform();
  }
