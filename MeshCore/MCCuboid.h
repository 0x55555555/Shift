#ifndef MCCUBOID_H
#define MCCUBOID_H

#include "MCShape.h"
#include "3D/Manipulators/GCManipulator.h"

class MCCuboid : public MCShape, public GCManipulatable
  {
  S_ENTITY(MCCuboid, MCShape, 0)

public:
  MCCuboid();

  Shift::FloatProperty width;
  Shift::FloatProperty height;
  Shift::FloatProperty depth;

private:
  void addManipulators(Shift::Array *, const ManipInfo &info) X_OVERRIDE;
  static void computeGeometry(MCCuboid* cube);
  };

S_PROPERTY_INTERFACE(MCCuboid);

#endif // MCSPHERE_H
