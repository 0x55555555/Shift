#include "GCProject3D.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/Properties/sbaseproperties.inl"
#include "XOptional"

void computeAlignTransform(GCProject3D *el)
  {
  Shift::PointerComputeLock cLock(&el->camera);
  GCCamera *c = el->camera();
  const Eks::Vector3D &pos = el->targetTransform().translation();

  if(!c)
    {
    el->xPosition = 0.0f;
    el->yPosition = 0.0f;
    el->validPosition = false;
    return;
    }

  Eks::Vector3D screenPosition;
  if(!c->screenSpaceFromWorldSpace(pos, screenPosition))
    {
    el->xPosition = 0.0f;
    el->yPosition = 0.0f;
    el->validPosition = false;
    return;
    }

  el->xPosition = screenPosition.x();
  el->yPosition = -screenPosition.y();
  el->validPosition = true;
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
