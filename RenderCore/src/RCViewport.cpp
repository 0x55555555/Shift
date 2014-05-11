#include "RCViewport.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(RCViewport, RenderCore)

void RCViewport::createTypeInformation(Shift::PropertyInformationTyped<RCViewport> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);

  auto xInst = childBlock.add(&RCViewport::x, "x");
  xInst->setMode(Shift::PropertyInstanceInformation::Output);

  auto yInst = childBlock.add(&RCViewport::y, "y");
  yInst->setMode(Shift::PropertyInstanceInformation::Output);
  }
