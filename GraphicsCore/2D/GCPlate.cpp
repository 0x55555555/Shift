#include "GCPlate.h"
#include "spropertyinformationhelpers.h"
#include "XRenderer.h"

S_IMPLEMENT_PROPERTY(GCPlate, GraphicsCore)

void GCPlate::createTypeInformation(SPropertyInformationTyped<GCPlate> *info,
                                    const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto w = info->add(&GCPlate::viewportWidth, "viewportWidth");

    auto h = info->add(&GCPlate::viewportHeight, "viewportHeight");

    auto el = info->add(&GCPlate::element, "element");
    auto elEx = info->extendContainedProperty(el);

    auto elW = elEx->child(&GCElement::width);
    elW->setDefaultInput(w);

    auto elH = elEx->child(&GCElement::height);
    elH->setDefaultInput(h);
    }
  }

void GCPlate::render(XRenderer *r) const
  {
  r->pushTransform(transform());

  element.render(r);

  r->popTransform();
  }
