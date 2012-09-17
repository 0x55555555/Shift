#ifndef GCPROJECT3D_H
#define GCPROJECT3D_H

#include "3D/GCTransform.h"
#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "GCElement.h"
#include "3D/GCCamera.h"

class GRAPHICSCORE_EXPORT GCProject3D : public SEntity
  {
  S_ENTITY(GCProject3D, SEntity, 0)

public:

  GCCameraPointer camera;
  TransformProperty targetTransform;

  FloatProperty xPosition;
  FloatProperty yPosition;
  };

S_PROPERTY_INTERFACE(GCProject3D)

#endif // GCPROJECT3D_H
