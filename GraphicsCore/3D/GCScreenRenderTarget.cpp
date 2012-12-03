#include "GCScreenRenderTarget.h"
#include "styperegistry.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCScreenRenderTarget, GraphicsCore)

void GCScreenRenderTarget::createTypeInformation(PropertyInformationTyped<GCScreenRenderTarget> *,
                                                 const PropertyInformationCreateData &)
  {
  }

GCScreenRenderTarget::GCScreenRenderTarget()
  {
  }
