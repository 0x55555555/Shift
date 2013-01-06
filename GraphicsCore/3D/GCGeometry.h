#ifndef GCGEOMETRY_H
#define GCGEOMETRY_H

#include "GCGlobal.h"
#include "shift/Properties/spropertycontainer.h"
#include "shift/Properties/spropertyarray.h"
#include "shift/Properties/sarrayproperty.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/sdatabase.h"
#include "XGeometry.h"
#include "GCBaseProperties.h"

class GRAPHICSCORE_EXPORT GCGeometry : public PropertyContainer
  {
  S_PROPERTY_CONTAINER(GCGeometry, PropertyContainer, 0)

public:
  GCGeometry();

  GCRuntimeGeometry runtimeGeometry;
  };

S_PROPERTY_INTERFACE(GCGeometry)

S_TYPED_POINTER_TYPE(GRAPHICSCORE_EXPORT, GCGeometryPointer, GCGeometry)

S_TYPED_POINTER_ARRAY_TYPE(GRAPHICSCORE_EXPORT, GCGeometryPointerArray, GCGeometryPointer)

#endif // GCGEOMETRY_H
