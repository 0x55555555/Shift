#include "Utilities/GCComposeVector3.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Changes/shandler.inl"
#include "shift/Properties/sbaseproperties.h"
#include "shift/Properties/sdata.inl"

S_IMPLEMENT_PROPERTY(GCComposeVector3, GraphicsCore)

void GCComposeVector3::createTypeInformation(Shift::PropertyInformationTyped<GCComposeVector3> *info,
                                             const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto vectorInst = childBlock.add(&GCComposeVector3::vectorOut, "vectorOut");
    vectorInst->setCompute([](GCComposeVector3 *vec)
      {
      vec->vectorOut.computeLock() = Eks::Vector3D(vec->xIn(), vec->yIn(), vec->zIn());
      });

    auto xInst = childBlock.add(&GCComposeVector3::xIn, "xIn");
    auto yInst = childBlock.add(&GCComposeVector3::yIn, "yIn");
    auto zInst = childBlock.add(&GCComposeVector3::zIn, "zIn");

    auto aff = childBlock.createAffects(&vectorInst, 1);

    xInst->setAffects(aff, true);
    yInst->setAffects(aff, false);
    zInst->setAffects(aff, false);
    }
  }
