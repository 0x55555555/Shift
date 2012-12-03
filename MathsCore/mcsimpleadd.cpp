#include "mcsimpleadd.h"
#include "spropertyinformationhelpers.h"
#include "shandlerimpl.h"

void computeAddOutput(MCSimpleAdd *add)
  {
  FloatProperty::ComputeLock l(&add->output);

  *l.data() = add->inputA() + add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleAdd, MathsCore)

void MCSimpleAdd::createTypeInformation(PropertyInformationTyped<MCSimpleAdd> *info,
                                        const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&MCSimpleAdd::output);
    outInst->setCompute<computeAddOutput>();
    }
  }

void computeSubOutput(MCSimpleSubtract *add)
  {
  FloatProperty::ComputeLock l(&add->output);

  *l.data() = add->inputA() - add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleSubtract, MathsCore)

void MCSimpleSubtract::createTypeInformation(PropertyInformationTyped<MCSimpleSubtract> *info,
                                        const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&MCSimpleSubtract::output);
    outInst->setCompute<computeSubOutput>();
    }
  }