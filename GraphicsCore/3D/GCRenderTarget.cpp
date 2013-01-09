#include "GCRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"

S_IMPLEMENT_PROPERTY(GCRenderTarget, GraphicsCore)

void computeAspectRatio(GCRenderTarget *vp)
  {
  vp->aspectRatio = (float)vp->width() / (float)vp->height();
  }


void GCRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<GCRenderTarget> *info,
                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto sourceInst = info->add(data, &GCRenderTarget::source, "source");
    sourceInst->setMode(Shift::PropertyInstanceInformation::InternalInput);

    auto aR = info->add(data, &GCRenderTarget::aspectRatio, "aspectRatio");
    aR->setCompute<computeAspectRatio>();
    aR->setDefault(1.0f);

    auto width = info->add(data, &GCRenderTarget::width, "width");
    width->setAffects(data, aR);
    width->setMode(Shift::PropertyInstanceInformation::Output);

    auto height = info->add(data, &GCRenderTarget::height, "height");
    height->setAffects(data, aR);
    height->setMode(Shift::PropertyInstanceInformation::Output);
    }
  }
