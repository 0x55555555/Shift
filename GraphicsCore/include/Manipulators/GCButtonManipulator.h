#ifndef GCBUTTONMANIPULATOR_H
#define GCBUTTONMANIPULATOR_H

#include "GCManipulator.h"

class GRAPHICSCORE_EXPORT GCButtonManipulator : public GCVisualClickManipulator
  {
  S_PROPERTY_CONTAINER(GCButtonManipulator, GCVisualClickManipulator)

public:
  enum
    {
    StaticChildMode = Shift::NamedChildren
    };

  GCButtonManipulator();
  ~GCButtonManipulator();

  Shift::BoolProperty checked;
  Shift::BoolProperty checkable;

  virtual void onClick();
  };

#endif // GCBUTTONMANIPULATOR_H
