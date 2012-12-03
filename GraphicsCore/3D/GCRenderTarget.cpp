#include "GCRenderTarget.h"
#include "styperegistry.h"
#include "spropertyinformationhelpers.h"
#include "shandlerimpl.h"

S_IMPLEMENT_PROPERTY(GCRenderTarget, GraphicsCore)

void computeAspectRatio(GCRenderTarget *vp)
  {
  vp->aspectRatio = (float)vp->width() / (float)vp->height();
  }


void GCRenderTarget::createTypeInformation(PropertyInformationTyped<GCRenderTarget> *info,
                                           const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto sourceInst = info->add(&GCRenderTarget::source, "source");
    sourceInst->setMode(PropertyInstanceInformation::InternalInput);

    auto aR = info->add(&GCRenderTarget::aspectRatio, "aspectRatio");
    aR->setCompute<computeAspectRatio>();
    aR->setDefault(1.0f);

    auto width = info->add(&GCRenderTarget::width, "width");
    width->setAffects(aR);
    width->setMode(PropertyInstanceInformation::Output);

    auto height = info->add(&GCRenderTarget::height, "height");
    height->setAffects(aR);
    height->setMode(PropertyInstanceInformation::Output);
    }
  }

GCRenderTarget::GCRenderTarget()
  {
  }
