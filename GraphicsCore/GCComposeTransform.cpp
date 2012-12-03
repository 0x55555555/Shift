#include "GCComposeTransform.h"
#include "spropertyinformationhelpers.h"
#include "XMacroHelpers"
#include "shandlerimpl.h"

void computeTransform(GCComposeTransform *vec)
  {
  XTransform tr = XTransform::Identity();
  tr *= Eigen::AngleAxisf(X_DEGTORAD(vec->rotationAngleIn()), vec->rotationAxisIn());

  tr.translation() = vec->translationIn();


  TransformProperty::ComputeLock l(&vec->transformOut);
  *l.data() = tr;
  }

S_IMPLEMENT_PROPERTY(GCComposeTransform, GraphicsCore)

void GCComposeTransform::createTypeInformation(PropertyInformationTyped<GCComposeTransform> *info,
                                               const PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto transformInst = info->add(&GCComposeTransform::transformOut, "transformOut");
    transformInst->setCompute<computeTransform>();

    auto axInst = info->add(&GCComposeTransform::rotationAxisIn, "rotationAxisIn");
    auto angInst = info->add(&GCComposeTransform::rotationAngleIn, "rotationAngleIn");
    auto trInst = info->add(&GCComposeTransform::translationIn, "translationIn");

    axInst->setAffects(transformInst);
    angInst->setAffects(transformInst);
    trInst->setAffects(transformInst);
    }
  }

GCComposeTransform::GCComposeTransform()
  {
  }
