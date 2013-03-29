#ifndef GCDISTANCEMANIPULATOR_H
#define GCDISTANCEMANIPULATOR_H

#include "GCGlobal.h"
#include "GCManipulator.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"

class GRAPHICSCORE_EXPORT GCDistanceManipulator : public GCLinearDragManipulator
  {
  S_PROPERTY_CONTAINER(GCDistanceManipulator, GCLinearDragManipulator, 0);

public:
  GCDistanceManipulator();

  Shift::FloatProperty distance;
  Shift::FloatProperty scaleFactor;

  // displacement moved from click point in local space
  Shift::Vector3DProperty absoluteDisplacement;

  void addDriven(Shift::FloatProperty *in);

  void onDrag(const MouseMoveEvent &);

  void setDriver(Shift::FloatProperty *f)
    {
    distance.setInput(f);
    }

private:
  QVector <Shift::FloatProperty *> _driven;
  };

S_PROPERTY_INTERFACE(GCDistanceManipulator);

#endif // GCDISTANCEMANIPULATOR_H
