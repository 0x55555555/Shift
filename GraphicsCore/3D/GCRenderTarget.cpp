#include "GCRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(GCRenderTarget, GraphicsCore)

void computeAspectRatio(GCRenderTarget *vp)
  {
  vp->aspectRatio.computeLock() = (float)vp->width() / (float)vp->height();
  }


void GCRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<GCRenderTarget> *info,
                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto sourceInst = childBlock.add(&GCRenderTarget::source, "source");
    sourceInst->setMode(Shift::PropertyInstanceInformation::InternalInput);

    auto aR = childBlock.add(&GCRenderTarget::aspectRatio, "aspectRatio");
    aR->setCompute<computeAspectRatio>();
    aR->setDefault(1.0f);

    auto affectsAr = childBlock.createAffects(&aR, 1);

    auto width = childBlock.add(&GCRenderTarget::width, "width");
    width->setAffects(affectsAr, true);
    width->setMode(Shift::PropertyInstanceInformation::Output);

    auto height = childBlock.add(&GCRenderTarget::height, "height");
    height->setAffects(affectsAr, false);
    height->setMode(Shift::PropertyInstanceInformation::Output);
    }
  }
