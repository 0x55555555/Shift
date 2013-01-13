#include "GCScreenRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCScreenRenderTarget, GraphicsCore)

void GCScreenRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<GCScreenRenderTarget> *,
                                                 const Shift::PropertyInformationCreateData &)
  {
  }

GCScreenRenderTarget::GCScreenRenderTarget()
  {
  }
