#include "GCViewport.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCViewport, GraphicsCore)

void GCViewport::createTypeInformation(PropertyInformationTyped<GCViewport> *info,
                                       const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto xInst = info->add(&GCViewport::x, "x");
    xInst->setMode(PropertyInstanceInformation::Output);

    auto yInst = info->add(&GCViewport::y, "y");
    yInst->setMode(PropertyInstanceInformation::Output);
    }
  }

GCViewport::GCViewport()
  {
  }
