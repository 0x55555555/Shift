#ifndef SKANGLE_H
#define SKANGLE_H

#include "SkGlobal.h"
#include "SkConstraint.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Angle : public Constraint
  {
  S_ENTITY(Angle, Constraint, 0)
public:

  PointPointer origin;
  PointPointer a;
  PointPointer b;
  Shift::Data<float> angle;
  };

#endif // SKANGLE_H
