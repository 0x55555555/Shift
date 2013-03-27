#include "mcsimplemultiply.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

void computeAddOutput(MCSimpleMultiply *add)
  {
  Shift::FloatProperty::ComputeLock l(&add->output);

  *l.data() = add->inputA() * add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleMultiply, MathsCore)

void MCSimpleMultiply::createTypeInformation(Shift::PropertyInformationTyped<MCSimpleMultiply> *info,
                                             const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto outInst = childBlock.overrideChild(&MCSimpleMultiply::output);
    outInst->setCompute<computeAddOutput>();
    }
  }
