#ifndef RCTEXTURE_H
#define RCTEXTURE_H

#include "RCGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "XTexture.h"

typedef Shift::Data<Eks::Texture2D, Shift::ComputedData> RCTexture2D;

S_TYPED_POINTER_TYPE(RENDERCORE_EXPORT, RCTexture2DPointer, RCTexture2D);

S_DECLARE_METATYPE(RCTexture2D, "Texture2D");

#endif // RCTEXTURE_H
