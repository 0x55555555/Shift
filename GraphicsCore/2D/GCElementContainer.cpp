#include "GCElementContainer.h"
#include "spropertyinformationhelpers.h"
#include "spropertycontaineriterators.h"

S_IMPLEMENT_PROPERTY(GCElementContainer, GraphicsCore)

void GCElementContainer::createTypeInformation(SPropertyInformationTyped<GCElementContainer> *,
                                           const SPropertyInformationCreateData &)
  {
  }

void GCElementContainer::render(XRenderer *r) const
  {
  xForeach(auto child, children.walker<GCElement>())
    {
    child->render(r);
    }
  }
