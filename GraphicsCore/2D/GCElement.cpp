#include "GCElement.h"
#include "spropertyinformationhelpers.h"
#include "mcsimpleadd.h"

S_IMPLEMENT_PROPERTY(GCElement, GraphicsCore)

void GCElement::createTypeInformation(SPropertyInformationTyped<GCElement> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&GCElement::left, "left");
    info->add(&GCElement::bottom, "bottom");

    info->add(&GCElement::width, "width");
    info->add(&GCElement::height, "height");
    }
  }

void GCElement::render(XRenderer *r) const
  {
  }

FloatProperty* GCElement::right()
  {
  MCSimpleAdd* adder = children.findChild<MCSimpleAdd>("right");
  if(!adder)
    {
    adder = addChild<MCSimpleAdd>("right");
    xAssert(adder->name() == "right");
    }

  adder->inputA.setInput(&left);
  adder->inputB.setInput(&width);
  return &adder->output;
  }
