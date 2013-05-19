#ifndef SKCONSTRAINT_H
#define SKCONSTRAINT_H

#include "SkGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "SkPoint.h"

class SKETCHCORE_EXPORT Constraint : public Shift::Entity
  {
  S_ABSTRACT_ENTITY(Constraint, Entity, 0)
public:

  enum Solution
    {
    UnderConstrained,
    Constrained,
    OverConstrained
    };

  virtual void gatherPoints(Eks::Vector<Point *> &) = 0;
  virtual Solution apply(Point::SolvingMap &m) = 0;
  virtual bool canApply(const Point::SolvingMap &) { return true; }

  };

class SKETCHCORE_EXPORT ConstraintPointer : public Shift::TypedPointer<Constraint>
  {
  S_PROPERTY(ConstraintPointer, Pointer, 0);
  };

S_TYPED_POINTER_ARRAY_TYPE(SKETCHCORE_EXPORT, ConstraintPointerArray, ConstraintPointer)

S_PROPERTY_INTERFACE(Constraint)
S_PROPERTY_INTERFACE(ConstraintPointer)
S_PROPERTY_INTERFACE(ConstraintPointerArray)
S_PROPERTY_INTERFACE(Shift::TypedPointerArray<ConstraintPointer>)

#endif // SKCONSTRAINT_H
