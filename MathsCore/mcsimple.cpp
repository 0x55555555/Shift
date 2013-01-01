#include "mcsimple.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(MCSimple, MathsCore)

void MCSimple::createTypeInformation(Shift::PropertyInformationTyped<MCSimple> *info,
                                     const Shift::PropertyInformationCreateData &data)
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
