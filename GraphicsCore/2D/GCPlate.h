#ifndef GCPLATE_H
#define GCPLATE_H

#include "XSignature.h"
#include "3D/GCTransform.h"
#include "GCGlobal.h"
#include "GCBaseProperties.h"
#include "GCElement.h"
#include "3D/GCShadingGroup.h"

#include "XOptionalPointer"

class GRAPHICSCORE_EXPORT GCPlate : public GCElement
  {
  S_ENTITY(GCPlate, GCElement, 0)

  template <typename T> typename GCElement *addChildElement(T **out = 0, GCShadingGroup *material = 0)
    {
    GCElement *el = T::addAsChild(this, material, out);
    return el;
    }

  template <typename T> GCShadingGroup *addMaterial(T **matOut = 0)
    {
    XOptionalPointer<T> mat(matOut);

    GCShadingGroup* grp = addChild<GCShadingGroup>();
    renderGroup.addPointer(grp);

    mat = addChild<T>();
    grp->shader.setPointed(mat);

    return grp;
    }

  void render(XRenderer *) const X_OVERRIDE;
  };

S_PROPERTY_INTERFACE(GCPlate)

#endif // GCPLATE_H
