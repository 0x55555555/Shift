#ifndef MCGEOMETRY_H
#define MCGEOMETRY_H

#include "MeshCore.h"
#include "3D/GCGeometry.h"
#include "MCPolyhedron.h"

class MESHCORE_EXPORT MCGeometry : public GCIndexedGeometry
  {
  S_PROPERTY_CONTAINER(MCGeometry, GCIndexedGeometry, 0)

public:
  MCPolyhedronProperty polygons;

  GCRenderer renderer;

  void bakeTo(
      Eks::AllocatorBase *allocator,
      Eks::Renderer *r,
      Eks::Geometry *geo,
      Eks::IndexGeometry *iGeo) const;
  };

#endif // MCGEOMETRY_H
