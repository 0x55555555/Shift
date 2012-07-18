#ifndef GCELEMENTCONTAINER_H
#define GCELEMENTCONTAINER_H

#include "GCElement.h"

class GRAPHICSCORE_EXPORT GCElementContainer : public GCElement
  {
  S_ENTITY(GCElementContainer, GCElement, 0);

public:

  virtual void render(XRenderer *) const;
  };

S_PROPERTY_INTERFACE(GCElementContainer)

#endif // GCELEMENTCONTAINER_H
