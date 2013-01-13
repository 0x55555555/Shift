#include "GCViewport.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCViewport, GraphicsCore)

void GCViewport::createTypeInformation(Shift::PropertyInformationTyped<GCViewport> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto xInst = info->add(data, &GCViewport::x, "x");
    xInst->setMode(Shift::PropertyInstanceInformation::Output);

    auto yInst = info->add(data, &GCViewport::y, "y");
    yInst->setMode(Shift::PropertyInstanceInformation::Output);
    }
  }
