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

  void transformPoint(int &x, int &y);
  };

S_PROPERTY_INTERFACE(GCCameraAlignedPlate)

#endif // GCCAMERAALIGNEDPLATE_H
