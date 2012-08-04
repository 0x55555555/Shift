#include "GCElement.h"
#include "spropertyinformationhelpers.h"
#include "mcsimpleadd.h"

void computeCentreOutput(GCElementCentre *e)
  {
  FloatProperty::ComputeLock l(&e->output);

  *l.data() = e->inputA() + (0.5f * e->inputB());
  }

S_IMPLEMENT_PROPERTY(GCElementCentre, GraphicsCore)

void GCElementCentre::createTypeInformation(SPropertyInformationTyped<GCElementCentre> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&GCElementCentre::output);
    outInst->setCompute<computeCentreOutput>();
    }
  }

void computeUnCentreOutput(GCElementUnCentre *e)
  {
  FloatProperty::ComputeLock l(&e->output);

  *l.data() = e->inputA() - (0.5f * e->inputB());
  }

S_IMPLEMENT_PROPERTY(GCElementUnCentre, GraphicsCore)

void GCElementUnCentre::createTypeInformation(SPropertyInformationTyped<GCElementUnCentre> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&GCElementUnCentre::output);
    outInst->setCompute<computeUnCentreOutput>();
    }
  }

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

    adder->inputA.setInput(&left);
    adder->inputB.setInput(&width);
    }
  return &adder->output;
  }

FloatProperty* GCElement::horizontalCentre()
  {
  GCElementCentre* centre = children.findChild<GCElementCentre>("hCentre");
  if(!centre)
    {
    centre = addChild<GCElementCentre>("hCentre");
    xAssert(centre->name() == "hCentre");

    centre->inputA.setInput(&left);
    centre->inputB.setInput(&width);
    }
  return &centre->output;
  }

FloatProperty* GCElement::verticalCentre()
  {
  GCElementCentre* centre = children.findChild<GCElementCentre>("vCentre");
  if(!centre)
    {
    centre = addChild<GCElementCentre>("vCentre");
    xAssert(centre->name() == "vCentre");

    centre->inputA.setInput(&bottom);
    centre->inputB.setInput(&height);
    }
  return &centre->output;
  }

void GCElement::setHorizontalCentreInput(FloatProperty* input)
  {
  xAssert(!left.hasInput());

  GCElementUnCentre* centre = addChild<GCElementUnCentre>();
  centre->inputA.setInput(input);

  centre->inputB.setInput(&width);

  left.setInput(&centre->output);
  }

void GCElement::setVerticalCentreInput(FloatProperty* input)
  {
  xAssert(!bottom.hasInput());

  GCElementUnCentre* centre = addChild<GCElementUnCentre>();
  centre->inputA.setInput(input);

  centre->inputB.setInput(&height);

  bottom.setInput(&centre->output);
  }
