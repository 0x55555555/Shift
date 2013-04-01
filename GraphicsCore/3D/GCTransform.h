#ifndef GCTRANSFORM_H
#define GCTRANSFORM_H

#include "GCGlobal.h"
#include "GCRenderable.h"
#include "XTransform.h"
#include "shift/Properties/sbaseproperties.h"
#include "3D/Manipulators/GCManipulatable.h"
#include "GCBaseProperties.h"

class GRAPHICSCORE_EXPORT GCTransform : public GCRenderArray, public GCManipulatable
  {
  S_ENTITY(GCTransform, GCRenderArray, 0)

public:

  TransformProperty transform;

  void render(Eks::Renderer *, const RenderState &state) const X_OVERRIDE;

  GCRenderablePointerArray *manipulatableChildren() { return &renderGroup; }
  void addManipulators(Shift::PropertyArray *, const ManipInfo &info) X_OVERRIDE;

  void intersect(const Eks::Line& line, Selector *) X_OVERRIDE;
  void intersect(const Eks::Frustum& frus, Selector *) X_OVERRIDE;
  };

S_PROPERTY_INTERFACE(GCTransform)

#endif // GCTRANSFORM3D_H
