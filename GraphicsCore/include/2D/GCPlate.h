#ifndef GCPLATE_H
#define GCPLATE_H

#include "GCGlobal.h"
#include "RCTransform.h"
#include "Utilities/RCBaseProperties.h"
#include "2D/GCElement.h"
#include "Shader/RCShadingGroup.h"
#include "Utilities/XOptional.h"

class GRAPHICSCORE_EXPORT GCPlate : public GCElementArray
  {
  S_ABSTRACT_ENTITY(GCPlate, GCElementArray)

  template <typename T> RCShadingGroup *addMaterial(T **matOut = 0)
    {
    Eks::Optional<T> mat(matOut);

    RCShadingGroup* grp = addChild<RCShadingGroup>();
    renderGroup.addPointer(grp);

    mat = addChild<T>();
    grp->shader.setPointed(mat);

    return grp;
    }

  void render(Eks::Renderer *, const RenderState &state) const X_OVERRIDE;

  virtual void transformPoint(float inX, float inY, float &x, float &y) = 0;
  };


#endif // GCPLATE_H
