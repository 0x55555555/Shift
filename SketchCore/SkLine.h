#ifndef SKLINE_H
#define SKLINE_H

#include "SkGlobal.h"
#include "SkConstraint.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Line : public Constraint
  {
  S_ENTITY(Line, Constraint)
public:

  void gatherPoints(Eks::Vector<Point *> &) X_OVERRIDE;
  Solution apply(Point::SolvingMap &m) X_OVERRIDE;

  ConstraintPointPointerArray points;
  };

#endif // SKLINE_H
