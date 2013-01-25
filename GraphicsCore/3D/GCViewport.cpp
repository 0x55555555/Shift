#include "GCViewport.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCViewport, GraphicsCore)

void GCViewport::createTypeInformation(Shift::PropertyInformationTyped<GCViewport> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto xInst = childBlock.add(&GCViewport::x, "x");
    xInst->setMode(Shift::PropertyInstanceInformation::Output);

    auto yInst = childBlock.add(&GCViewport::y, "y");
    yInst->setMode(Shift::PropertyInstanceInformation::Output);
    }
  }
