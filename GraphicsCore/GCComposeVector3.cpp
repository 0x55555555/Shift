#include "GCComposeVector3.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"

void computeVector(GCComposeVector3 *vec)
  {
  Shift::Vector3DProperty::ComputeLock l(&vec->vectorOut);
  *l.data() = Eks::Vector3D(vec->xIn(), vec->yIn(), vec->zIn());
  }

S_IMPLEMENT_PROPERTY(GCComposeVector3, GraphicsCore)

void GCComposeVector3::createTypeInformation(Shift::PropertyInformationTyped<GCComposeVector3> *info,
                                             const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto vectorInst = childBlock.add(&GCComposeVector3::vectorOut, "vectorOut");
    vectorInst->setCompute<computeVector>();

    auto xInst = childBlock.add(&GCComposeVector3::xIn, "xIn");
    auto yInst = childBlock.add(&GCComposeVector3::yIn, "yIn");
    auto zInst = childBlock.add(&GCComposeVector3::zIn, "zIn");

    auto aff = childBlock.createAffects(&vectorInst, 1);

    xInst->setAffects(aff, true);
    yInst->setAffects(aff, false);
    zInst->setAffects(aff, false);
    }
  }
