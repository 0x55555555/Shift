#include "mcsimple.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(MCSimple, MathsCore)

void MCSimple::createTypeInformation(Shift::PropertyInformationTyped<MCSimple> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto outInst = info->add(data, &MCSimple::output, "output");

    auto aInst = info->add(data, &MCSimple::inputA, "inputA");
    auto bInst = info->add(data, &MCSimple::inputB, "inputB");

    auto outAffects = info->createAffects(data, &outInst, 1);

    aInst->setAffects(outAffects, true);
    bInst->setAffects(outAffects, false);
    }
  }
