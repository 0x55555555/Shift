#ifndef SKLINE_H
#define SKLINE_H

#include "SkGlobal.h"
#include "SkConstraint.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Line : public Constraint
  {
  S_ENTITY(Line, Constraint, 0)
public:

  ConstraintPointPointerArray points;
  };

#endif // SKLINE_H
