#ifndef SKCONSTRAINT_H
#define SKCONSTRAINT_H

#include "SkGlobal.h"
#include "shift/sentity.h"
#include "shift/Properties/sbasepointerproperties.h"

class SKETCHCORE_EXPORT Constraint : public Shift::Entity
  {
  S_ENTITY(Constraint, Entity, 0)
public:

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
