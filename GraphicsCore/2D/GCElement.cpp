#include "GCElement.h"
#include "spropertyinformationhelpers.h"
#include "XTransform.h"
#include "XGLRenderer.h"

S_IMPLEMENT_PROPERTY(GCElement, GraphicsCore)

void GCElement::createTypeInformation(SPropertyInformationTyped<GCElement> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&GCElement::left, "left");
    info->add(&GCElement::top, "top");

    info->add(&GCElement::width, "width");
    info->add(&GCElement::height, "height");
    }
  }

void GCElement::render(XRenderer *r) const
  {
  XTransform tr = XTransform::Identity();
  tr.scale(100);

  r->pushTransform(tr);

  r->debugRenderLocator(XRenderer::ClearShader);

  r->popTransform();
  }
