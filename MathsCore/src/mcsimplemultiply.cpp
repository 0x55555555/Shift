#include "mcsimplemultiply.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"

void computeAddOutput(MCSimpleMultiply *add)
  {
  add->output.computeLock() = add->inputA() * add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleMultiply, MathsCore)

void MCSimpleMultiply::createTypeInformation(Shift::PropertyInformationTyped<MCSimpleMultiply> *info,
                                             const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto outInst = childBlock.overrideChild(&MCSimpleMultiply::output);
  outInst->setCompute<computeAddOutput>();
  }
