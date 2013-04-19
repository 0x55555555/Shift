#ifndef GCROTATEMANIPULATOR_H
#define GCROTATEMANIPULATOR_H

#include "GCManipulator.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"

class GCSingularRotateManipulator : public GCAngularDragManipulator
  {
  S_PROPERTY_CONTAINER(GCSingularRotateManipulator, GCAngularDragManipulator, 0);

public:
  GCSingularRotateManipulator();

  void addDriven(TransformProperty *in);

  void onDrag(const MouseMoveEvent &);

private:
  Eks::Vector <TransformProperty *> _driven;
  };

class GRAPHICSCORE_EXPORT GCRotateManipulator : public GCVisualCompoundManipulator
  {
  S_PROPERTY_CONTAINER(GCRotateManipulator, GCVisualCompoundManipulator, 0);

public:
  GCRotateManipulator();

  GCSingularRotateManipulator x;
  GCSingularRotateManipulator y;
  GCSingularRotateManipulator z;
  //GCSingularRotateManipulator central;
  //GCSingularRotateManipulator outer;

  void addDriven(TransformProperty *in);

  void setDriver(TransformProperty *f)
    {
    localTransform.setInput(f);
    }
  };

#endif // GCROTATEMANIPULATOR_H
