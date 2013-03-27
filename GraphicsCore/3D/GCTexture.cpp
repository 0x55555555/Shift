#include "GCTexture.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCTexture2DPointer, GraphicsCore)

S_IMPLEMENT_PROPERTY(GCTexture2D, GraphicsCore)

void GCTexture2D::createTypeInformation(Shift::PropertyInformationTyped<GCTexture2D> *info,
                                      const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    info->createChildrenBlock(data);
    }
  }
