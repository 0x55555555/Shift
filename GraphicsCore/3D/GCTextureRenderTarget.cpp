#include "GCTextureRenderTarget.h"
#include "styperegistry.h"
#include "spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCTextureRenderTarget, GraphicsCore)

void GCTextureRenderTarget::createTypeInformation(PropertyInformationTyped<GCTextureRenderTarget> *,
                                                  const PropertyInformationCreateData &)
  {
  }

GCTextureRenderTarget::GCTextureRenderTarget()
  {
  }
