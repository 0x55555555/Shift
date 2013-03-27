#include "GCTextureRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCTextureRenderTarget, GraphicsCore)

void GCTextureRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<GCTextureRenderTarget> *info,
                                                  const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }
