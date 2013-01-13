#include "GCComposeTransform.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XMacroHelpers"
#include "shift/Changes/shandler.inl"

void computeTransform(GCComposeTransform *vec)
  {
  Eks::Transform tr = Eks::Transform::Identity();
  tr *= Eigen::AngleAxisf(Eks::degreesToRadians(vec->rotationAngleIn()), vec->rotationAxisIn());

  tr.translation() = vec->translationIn();


  TransformProperty::ComputeLock l(&vec->transformOut);
  *l.data() = tr;
  }

S_IMPLEMENT_PROPERTY(GCComposeTransform, GraphicsCore)

void GCComposeTransform::createTypeInformation(Shift::PropertyInformationTyped<GCComposeTransform> *info,
                                               const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto transformInst = info->add(data, &GCComposeTransform::transformOut, "transformOut");
    transformInst->setCompute<computeTransform>();

    auto axInst = info->add(data, &GCComposeTransform::rotationAxisIn, "rotationAxisIn");
    auto angInst = info->add(data, &GCComposeTransform::rotationAngleIn, "rotationAngleIn");
    auto trInst = info->add(data, &GCComposeTransform::translationIn, "translationIn");

    axInst->setAffects(data, transformInst);
    angInst->setAffects(data, transformInst);
    trInst->setAffects(data, transformInst);
    }
  }

GCComposeTransform::GCComposeTransform()
  {
  }
