#ifndef SKDISTANCE_H
#define SKDISTANCE_H

#include "SkGlobal.h"
#include "SkConstraint.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Distance : public Constraint
  {
  S_ENTITY(Distance, Constraint, 0)
public:

  Shift::Data<float> distance;
  PointPointer a;
  PointPointer b;
  };

#endif // SKDISTANCE_H
