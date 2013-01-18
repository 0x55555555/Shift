#ifndef MCDENSITYSHAPE_H
#define MCDENSITYSHAPE_H

#include "MeshCore.h"
#include "MCShape.h"
#include "MCGeometry.h"

class MESHCORE_EXPORT MCDensityShape : public MCShape
  {
  S_ENTITY(MCDensityShape, MCShape, 0)

public:
  virtual float boundingRadius() const { return 1.0f; }
  virtual float minimumSurfaceAngle() const { return 30.0f; }
  virtual float maximumApproximateTriangleSize() const { return 0.1f; }
  virtual float evaluate(const Eks::Vector3D &fn) const;

private:
  static void computeGeometry(MCDensityShape* cube);
  };

S_PROPERTY_INTERFACE(MCDensityShape);

#endif // MCDENSITYSHAPE_H
