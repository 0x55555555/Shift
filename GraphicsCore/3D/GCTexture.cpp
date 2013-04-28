#include "GCTexture.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sbaseproperties.inl"

S_IMPLEMENT_TYPED_POINTER_TYPE(GCTexture2DPointer, GraphicsCore)

IMPLEMENT_POD_PROPERTY(GRAPHICSCORE_EXPORT, GraphicsCore, Eks::Texture2D, ComputedData, tex)
