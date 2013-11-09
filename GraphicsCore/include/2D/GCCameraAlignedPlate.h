#ifndef GCCAMERAALIGNEDPLATE_H
#define GCCAMERAALIGNEDPLATE_H

#include "GCPlate.h"

class GRAPHICSCORE_EXPORT GCCameraAlignedPlate : public GCPlate
  {
  S_ENTITY(GCCameraAlignedPlate, GCPlate)

public:
  TransformProperty cameraTransform;
  TransformProperty offsetTransform;

  Shift::FloatProperty distanceFromCamera;
  Shift::FloatProperty cameraFieldOfView;

  void transformPoint(float inX, float inY, float &x, float &y) X_OVERRIDE;
  };


#endif // GCCAMERAALIGNEDPLATE_H
