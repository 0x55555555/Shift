#include "SkConstraint.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "SkGlobal.h"

S_IMPLEMENT_TYPED_POINTER_TYPE(ConstraintPointer, SketchCore)
S_IMPLEMENT_TYPED_POINTER_ARRAY_TYPE(ConstraintPointerArray, SketchCore)

S_IMPLEMENT_ABSTRACT_PROPERTY(Constraint, SketchCore)

void Constraint::createTypeInformation(
    Shift::PropertyInformationTyped<Constraint> *info,
    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto cb = info->createChildrenBlock(data);
    }
  }

