#ifndef GCCOMPOSETRANSFORM_H
#define GCCOMPOSETRANSFORM_H

#include "shift/sentity.h"
#include "shift/Properties/sbaseproperties.h"
#include "GCBaseProperties.h"

class GCComposeTransform : public Shift::Entity
  {
  S_ENTITY(GCComposeTransform, Entity, 0)

public:
  GCComposeTransform();

  Shift::Vector3DProperty rotationAxisIn;
  Shift::FloatProperty rotationAngleIn;

  Shift::Vector3DProperty translationIn;

  TransformProperty transformOut;
  };

S_PROPERTY_INTERFACE(GCComposeTransform)

#endif // GCCOMPOSETRANSFORM_H
