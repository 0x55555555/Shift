#include "GCElement.h"
#include "spropertyinformationhelpers.h"
#include "mcsimpleadd.h"
#include "XRenderer.h"

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

void computeElementTransform(GCElement *e)
  {
  XTransform t = XTransform::Identity();

  t.translate(XVector3D(e->left(), e->bottom(), 0.0f));

  e->transform = t;
  }

S_IMPLEMENT_PROPERTY(GCElement, GraphicsCore)

void GCElement::createTypeInformation(SPropertyInformationTyped<GCElement> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto tr = info->child(&GCElement::transform);
    tr->setCompute<computeElementTransform>();

    auto w = info->add(&GCElement::width, "width");
    w->setAffects(tr);
    auto h = info->add(&GCElement::height, "height");
    h->setAffects(tr);

    auto l = info->add(&GCElement::left, "left");
    l->setAffects(tr);
    auto b = info->add(&GCElement::bottom, "bottom");
    b->setAffects(tr);
    }
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


void computeUnitElementTransform(GCUnitElement *e)
  {
  XTransform t = XTransform::Identity();

  t.translate(XVector3D(e->left(), e->bottom(), 0.0f));

  t.scale(XVector3D(e->width(), e->height(), 1.0f));

  e->transform = t;
  }

S_IMPLEMENT_PROPERTY(GCElementArray, GraphicsCore)

void GCElementArray::createTypeInformation(SPropertyInformationTyped<GCElementArray> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->add(&GCElementArray::elements, "elements");
    }
  }

void GCElementArray::render(XRenderer *renderer) const
  {
  GCElement::render(renderer);

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
  }

S_IMPLEMENT_PROPERTY(GCUnitElement, GraphicsCore)

void GCUnitElement::createTypeInformation(SPropertyInformationTyped<GCUnitElement> *info,
                                      const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto tr = info->child(&GCElement::transform);
    tr->setCompute<computeUnitElementTransform>();
    }
  }
