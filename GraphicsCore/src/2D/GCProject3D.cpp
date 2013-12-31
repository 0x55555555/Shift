#include "2D/GCProject3D.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sdata.inl"
#include "shift/Changes/shandler.inl"
#include "Utilities/XOptional.h"

void computeAlignTransform(GCProject3D *el)
  {
  Shift::PointerComputeLock cLock(&el->camera);
  RCCamera *c = el->camera();
  const Eks::Vector3D &pos = el->targetTransform().translation();

  if(!c)
    {
    el->xPosition.computeLock() = 0.0f;
    el->yPosition.computeLock() = 0.0f;
    el->validPosition.computeLock() = false;
    return;
    }

  Eks::Vector3D screenPosition;
  if(!c->screenSpaceFromWorldSpace(pos, screenPosition))
    {
    el->xPosition.computeLock() = 0.0f;
    el->yPosition.computeLock() = 0.0f;
    el->validPosition.computeLock() = false;
    return;
    }

  el->xPosition.computeLock() = screenPosition.x();
  el->yPosition.computeLock() = -screenPosition.y();
  el->validPosition.computeLock() = true;
  }

S_IMPLEMENT_PROPERTY(GCProject3D, GraphicsCore)

void GCProject3D::createTypeInformation(Shift::PropertyInformationTyped<GCProject3D> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto x = childBlock.add(&GCProject3D::xPosition, "xPosition");
    x->setCompute<computeAlignTransform>();

    auto y = childBlock.add(&GCProject3D::yPosition, "yPosition");
    y->setCompute<computeAlignTransform>();

    auto v = childBlock.add(&GCProject3D::validPosition, "validPosition");
    v->setCompute<computeAlignTransform>();

    const Shift::EmbeddedPropertyInstanceInformation *aff[] = { x, y };
    auto affects = childBlock.createAffects(aff, X_ARRAY_COUNT(aff));

    auto cam = childBlock.add(&GCProject3D::camera, "camera");
    cam->setAffects(affects, true);

    auto taTr = childBlock.add(&GCProject3D::targetTransform, "targetTransform");
    taTr->setAffects(affects, false);
    }
  }
