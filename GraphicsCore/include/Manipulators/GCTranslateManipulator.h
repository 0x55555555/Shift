#ifndef GCTRANSLATEMANIPULATOR_H
#define GCTRANSLATEMANIPULATOR_H

#include "GCManipulator.h"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sbasepointerproperties.h"

class GCSingularTranslateManipulator : public GCDisplacementDragManipulator
  {
  S_PROPERTY_CONTAINER(GCSingularTranslateManipulator, GCDisplacementDragManipulator);

public:
  GCSingularTranslateManipulator();

  void addDriven(TransformProperty *in);

  void onDrag(const MouseMoveEvent &);

private:
  Eks::Vector <TransformProperty *> _driven;
  };

class GRAPHICSCORE_EXPORT GCTranslateManipulator : public GCVisualCompoundManipulator
  {
  S_PROPERTY_CONTAINER(GCTranslateManipulator, GCVisualCompoundManipulator);

public:
  enum
    {
    StaticChildMode = Shift::NamedChildren
    };

  GCTranslateManipulator();

  GCSingularTranslateManipulator x;
  GCSingularTranslateManipulator y;
  GCSingularTranslateManipulator z;
  GCSingularTranslateManipulator central;

  void addDriven(TransformProperty *in);

  void setDriver(TransformProperty *f)
    {
    localTransform.setInput(f);
    }
  };

#endif // GCTRANSLATEMANIPULATOR_H
