#include "Targets/RCRenderTarget.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(RCRenderTarget, RenderCore)

void computeAspectRatio(RCRenderTarget *vp)
  {
  vp->aspectRatio.computeLock() = (float)vp->width() / (float)vp->height();
  }


void RCRenderTarget::createTypeInformation(Shift::PropertyInformationTyped<RCRenderTarget> *info,
                                           const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto sourceInst = childBlock.add(&RCRenderTarget::source, "source");
    sourceInst->setMode(Shift::PropertyInstanceInformation::InternalInput);

    auto aR = childBlock.add(&RCRenderTarget::aspectRatio, "aspectRatio");
    aR->setCompute<computeAspectRatio>();
    aR->setDefault(1.0f);

    auto affectsAr = childBlock.createAffects(&aR, 1);

    auto width = childBlock.add(&RCRenderTarget::width, "width");
    width->setAffects(affectsAr, true);
    width->setMode(Shift::PropertyInstanceInformation::Output);

    auto height = childBlock.add(&RCRenderTarget::height, "height");
    height->setAffects(affectsAr, false);
    height->setMode(Shift::PropertyInstanceInformation::Output);
    }
  }
