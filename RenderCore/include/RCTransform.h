#ifndef RCTRANSFORM_H
#define RCTRANSFORM_H

#include "RCGlobal.h"
#include "RCRenderable.h"
#include "XTransform.h"
#include "shift/Properties/sbaseproperties.h"
#include "Utilities/RCBaseProperties.h"

class RENDERCORE_EXPORT RCTransform : public RCRenderArray
  {
  S_ENTITY(RCTransform, RCRenderArray)

public:

  TransformProperty transform;

  void render(Eks::Renderer *, const RenderState &state) const X_OVERRIDE;

  RCRenderablePointerArray *manipulatableChildren() { return &renderGroup; }

  void intersect(const Eks::Line& line, Selector *) X_OVERRIDE;
  void intersect(const Eks::Frustum& frus, Selector *) X_OVERRIDE;
  };

#endif // RCTRANSFORM3D_H
