#include "GCElementArray.h"
#include "spropertyinformationhelpers.h"
#include "spropertycontaineriterators.h"

void GCElementArray::createTypeInformation(SPropertyInformationTyped<GCElementArray> *,
                                           const SPropertyInformationCreateData &)
  {
  }

void GCElementArray::render(XRenderer *r) const
  {
  xForeach(auto child, walkerFrom<GCElement>(&height))
    {
    child->render(r);
    }
  }
