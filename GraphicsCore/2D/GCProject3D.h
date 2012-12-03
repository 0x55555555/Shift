#ifndef GCPROJECT3D_H
#define GCPROJECT3D_H

#include "3D/GCTransform.h"
#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "GCElement.h"
#include "3D/GCCamera.h"

class GRAPHICSCORE_EXPORT GCProject3D : public Entity
  {
  S_ENTITY(GCProject3D, Entity, 0)

public:

  GCCameraPointer camera;
  TransformProperty targetTransform;

  FloatProperty xPosition;
  FloatProperty yPosition;
  BoolProperty validPosition;
  };

S_PROPERTY_INTERFACE(GCProject3D)

#endif // GCPROJECT3D_H
