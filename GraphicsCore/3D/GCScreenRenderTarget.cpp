#include "GCScreenRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCScreenRenderTarget, GraphicsCore)

void GCScreenRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<GCScreenRenderTarget> *info,
                                                 const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }

GCScreenRenderTarget::GCScreenRenderTarget()
  {
  }
