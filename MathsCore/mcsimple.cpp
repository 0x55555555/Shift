#include "mcsimple.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(MCSimple, MathsCore)

void MCSimple::createTypeInformation(Shift::PropertyInformationTyped<MCSimple> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto outInst = childBlock.add(&MCSimple::output, "output");

    auto aInst = childBlock.add(&MCSimple::inputA, "inputA");
    auto bInst = childBlock.add(&MCSimple::inputB, "inputB");

    auto outAffects = childBlock.createAffects(&outInst, 1);

    aInst->setAffects(outAffects, true);
    bInst->setAffects(outAffects, false);
    }
  }
