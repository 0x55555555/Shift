#ifndef SKSOLVER_H
#define SKSOLVER_H

#include "SkGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sarray.h"
#include "SkPoint.h"
#include "SkConstraint.h"

class SKETCHCORE_EXPORT Solver : public Shift::Entity
  {
  S_ENTITY(Solver, Entity, 0)
public:

  ConstraintPointerArray constraints;

  Shift::Array points;

private:
  void solve();

  };

#endif // SKSOLVER_H
