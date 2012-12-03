#ifndef GCCOMPOSETRANSFORM_H
#define GCCOMPOSETRANSFORM_H

#include "sentity.h"
#include "sbaseproperties.h"
#include "GCBaseProperties.h"

class GCComposeTransform : public Entity
  {
  S_ENTITY(GCComposeTransform, Entity, 0)

public:
  GCComposeTransform();

  Vector3DProperty rotationAxisIn;
  FloatProperty rotationAngleIn;

  Vector3DProperty translationIn;

  TransformProperty transformOut;
  };

S_PROPERTY_INTERFACE(GCComposeTransform)

#endif // GCCOMPOSETRANSFORM_H
