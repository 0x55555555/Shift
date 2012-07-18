#ifndef GCELEMENTARRAY_H
#define GCELEMENTARRAY_H

#include "GCGlobal.h"
#include "GCElement.h"

class GRAPHICSCORE_EXPORT GCElementArray : public GCElement
  {
  S_ENTITY(GCElementArray, GCElement, 0);

public:

  virtual void render(XRenderer *) const;
  };

S_PROPERTY_INTERFACE(GCElementArray)

#endif // GCELEMENTARRAY_H
