#include "mcsimplemultiply.h"
#include "spropertyinformationhelpers.h"

void computeAddOutput(MCSimpleMultiply *add)
  {
  FloatProperty::ComputeLock l(&add->output);

  *l.data() = add->inputA() * add->inputB();
  }

S_IMPLEMENT_PROPERTY(MCSimpleMultiply, MathsCore)

void MCSimpleMultiply::createTypeInformation(SPropertyInformationTyped<MCSimpleMultiply> *info,
                                             const SPropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->child(&MCSimpleMultiply::output);
    outInst->setCompute<computeAddOutput>();
    }
  }

MCSimpleMultiply::MCSimpleMultiply()
  {
  }
