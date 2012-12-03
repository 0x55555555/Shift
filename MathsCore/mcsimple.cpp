#include "mcsimple.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(MCSimple, MathsCore)

void MCSimple::createTypeInformation(PropertyInformationTyped<MCSimple> *info,
                                     const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->add(&MCSimple::output, "output");

    auto aInst = info->add(&MCSimple::inputA, "inputA");
    auto bInst = info->add(&MCSimple::inputB, "inputB");

    aInst->setAffects(outInst);
    bInst->setAffects(outInst);
    }
  }

MCSimple::MCSimple()
  {
  }
