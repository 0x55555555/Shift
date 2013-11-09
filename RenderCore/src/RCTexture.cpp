#include "RCTexture.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_TYPED_POINTER_TYPE(RCTexture2DPointer, RenderCore)

IMPLEMENT_POD_PROPERTY(RENDERCORE_EXPORT, RenderCore, Eks::Texture2D, ComputedData, tex)
