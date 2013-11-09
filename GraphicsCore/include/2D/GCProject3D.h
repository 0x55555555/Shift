#ifndef GCPROJECT3D_H
#define GCPROJECT3D_H

#include "RCTransform.h"
#include "RCCamera.h"
#include "Utilities/RCBaseProperties.h"
#include "GCGlobal.h"
#include "GCElement.h"

class GRAPHICSCORE_EXPORT GCProject3D : public Shift::Entity
  {
  S_ENTITY(GCProject3D, Entity)

public:

  RCCameraPointer camera;
  TransformProperty targetTransform;

  Shift::FloatProperty xPosition;
  Shift::FloatProperty yPosition;
  Shift::BoolProperty validPosition;
  };

#endif // GCPROJECT3D_H
