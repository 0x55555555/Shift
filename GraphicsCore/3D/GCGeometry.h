#ifndef GCGEOMETRY_H
#define GCGEOMETRY_H

#include "GCGlobal.h"
#include "shift/Properties/scontainer.h"
#include "shift/Properties/sarray.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/sdatabase.h"
#include "XGeometry.h"
#include "GCBaseProperties.h"

class GRAPHICSCORE_EXPORT GCGeometry : public Shift::Container
  {
  S_PROPERTY_CONTAINER(GCGeometry, Container, 0)

public:
  GCRuntimeGeometry runtimeGeometry;
  };

class GRAPHICSCORE_EXPORT GCIndexedGeometry : public GCGeometry
  {
  S_PROPERTY_CONTAINER(GCIndexedGeometry, GCGeometry, 0)

public:
  GCRuntimeIndexGeometry runtimeIndexGeometry;
  };

#endif // GCGEOMETRY_H
