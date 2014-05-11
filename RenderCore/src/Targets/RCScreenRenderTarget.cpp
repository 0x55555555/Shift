#include "Targets/RCScreenRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(RCScreenRenderTarget, RenderCore)

void RCScreenRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<RCScreenRenderTarget> *info,
                                                 const Shift::PropertyInformationCreateData &data)
  {
  info->createChildrenBlock(data);
  }

RCScreenRenderTarget::RCScreenRenderTarget()
  {
  }
