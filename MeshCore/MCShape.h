#ifndef MCSHAPE_H
#define MCSHAPE_H

#include "GCRenderable.h"
#include "MCGeometry.h"

class MCShape : public GCRenderable
  {
  S_ENTITY(MCShape, GCRenderable, 0)

public:
  MCGeometry geometry;

  void render(Eks::Renderer *, const RenderState &state) const X_OVERRIDE;

  virtual void intersect(const Eks::Line& line, Selector *);
  virtual void intersect(const Eks::Frustum& frus, Selector *);
  };

#endif // MCSHAPE_H
