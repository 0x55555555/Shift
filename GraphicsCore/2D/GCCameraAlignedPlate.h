#ifndef GCCAMERAALIGNEDPLATE_H
#define GCCAMERAALIGNEDPLATE_H

#include "GCPlate.h"

class GRAPHICSCORE_EXPORT GCCameraAlignedPlate : public GCPlate
  {
  S_ENTITY(GCCameraAlignedPlate, GCPlate, 0)

public:
  TransformProperty cameraTransform;
  TransformProperty offsetTransform;

  FloatProperty distanceFromCamera;
  FloatProperty cameraFieldOfView;

  void transformPoint(float inX, float inY, float &x, float &y) X_OVERRIDE;
  };

S_PROPERTY_INTERFACE(GCCameraAlignedPlate)

#endif // GCCAMERAALIGNEDPLATE_H
