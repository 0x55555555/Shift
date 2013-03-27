#ifndef GCGEOMETRY_H
#define GCGEOMETRY_H

#include "GCGlobal.h"
#include "shift/Properties/spropertycontainer.h"
#include "shift/Properties/spropertyarray.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/sdatabase.h"
#include "XGeometry.h"
#include "GCBaseProperties.h"

class GRAPHICSCORE_EXPORT GCGeometry : public Shift::PropertyContainer
  {
  S_PROPERTY_CONTAINER(GCGeometry, PropertyContainer, 0)

public:
  GCRuntimeGeometry runtimeGeometry;
  };

class GRAPHICSCORE_EXPORT GCIndexedGeometry : public GCGeometry
  {
  S_PROPERTY_CONTAINER(GCIndexedGeometry, GCGeometry, 0)

public:
  GCRuntimeIndexGeometry runtimeIndexGeometry;
  };

S_PROPERTY_INTERFACE(GCGeometry)
S_PROPERTY_INTERFACE(GCIndexedGeometry)

#endif // GCGEOMETRY_H
