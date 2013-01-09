#ifndef GCTRANSFORM_H
#define GCTRANSFORM_H

#include "GCGlobal.h"
#include "GCRenderable.h"
#include "XTransform.h"
#include "shift/Properties/sbaseproperties.h"
#include "3D/Manipulators/GCManipulator.h"
#include "GCBaseProperties.h"

class GRAPHICSCORE_EXPORT GCTransform : public GCRenderArray, public GCManipulatable
  {
  S_ENTITY(GCTransform, GCRenderArray, 0)

public:
  GCTransform();

  TransformProperty transform;

  virtual void render(Eks::Renderer *) const;

  virtual void addManipulators(Shift::PropertyArray *, const GCTransform *tr=0);

  virtual void intersect(const Eks::Line& line, Selector *);
  virtual void intersect(const Eks::Frustum& frus, Selector *);
  };

S_PROPERTY_INTERFACE(GCTransform)

#endif // GCTRANSFORM3D_H
