#include "Targets/RCTextureRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(RCTextureRenderTarget, RenderCore)

void RCTextureRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<RCTextureRenderTarget> *info,
                                                  const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }
