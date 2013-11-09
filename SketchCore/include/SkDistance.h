#ifndef SKDISTANCE_H
#define SKDISTANCE_H

#include "SkGlobal.h"
#include "SkConstraint.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Distance : public Constraint
  {
  S_ENTITY(Distance, Constraint)
public:

  void gatherPoints(Eks::Vector<Point *> &) X_OVERRIDE;
  Solution apply(Point::SolvingMap &m) X_OVERRIDE;

  Shift::Data<float> distance;
  ConstraintPointPointer a;
  ConstraintPointPointer b;
  };

#endif // SKDISTANCE_H
