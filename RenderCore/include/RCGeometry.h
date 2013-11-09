#ifndef RCGEOMETRY_H
#define RCGEOMETRY_H

#include "RCGlobal.h"
#include "shift/Properties/scontainer.h"
#include "shift/Properties/sarray.h"
#include "shift/Properties/sbasepointerproperties.h"
#include "shift/sdatabase.h"
#include "XGeometry.h"
#include "Utilities/RCBaseProperties.h"

class RENDERCORE_EXPORT RCGeometry : public Shift::Container
  {
  S_PROPERTY_CONTAINER(RCGeometry, Container)

public:
  RCRuntimeGeometry runtimeGeometry;
  };

class RENDERCORE_EXPORT RCIndexedGeometry : public RCGeometry
  {
  S_PROPERTY_CONTAINER(RCIndexedGeometry, RCGeometry)

public:
  RCRuntimeIndexGeometry runtimeIndexGeometry;
  };

#endif // RCGEOMETRY_H
