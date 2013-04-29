#include "GCComposeTransform.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XMacroHelpers"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"

void computeTransform(GCComposeTransform *vec)
  {
  Eks::Transform tr = Eks::Transform::Identity();
  tr *= Eigen::AngleAxisf(Eks::degreesToRadians(vec->rotationAngleIn()), vec->rotationAxisIn());

  tr.translation() = vec->translationIn();


  vec->transformOut.computeLock() = tr;
  }

S_IMPLEMENT_PROPERTY(GCComposeTransform, GraphicsCore)

void GCComposeTransform::createTypeInformation(Shift::PropertyInformationTyped<GCComposeTransform> *info,
                                               const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto transformInst = childBlock.add(&GCComposeTransform::transformOut, "transformOut");
    transformInst->setCompute<computeTransform>();

    auto axInst = childBlock.add(&GCComposeTransform::rotationAxisIn, "rotationAxisIn");
    auto angInst = childBlock.add(&GCComposeTransform::rotationAngleIn, "rotationAngleIn");
    auto trInst = childBlock.add(&GCComposeTransform::translationIn, "translationIn");

    auto affectsTransform = childBlock.createAffects(&transformInst, 1);

    axInst->setAffects(affectsTransform, true);
    angInst->setAffects(affectsTransform, false);
    trInst->setAffects(affectsTransform, false);
    }
  }
