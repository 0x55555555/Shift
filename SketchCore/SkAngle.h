#ifndef SKANGLE_H
#define SKANGLE_H

#include "SkGlobal.h"
#include "SkConstraint.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Angle : public Constraint
  {
  S_ENTITY(Angle, Constraint, 0)
public:

  void gatherPoints(Eks::Vector<Point *> &) X_OVERRIDE;
  Solution apply(Point::SolvingMap &m) X_OVERRIDE;

  ConstraintPointPointer origin;
  ConstraintPointPointer a;
  ConstraintPointPointer b;
  Shift::Data<float> angle;
  };

#endif // SKANGLE_H
