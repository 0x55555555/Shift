#include "GCProject3D.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
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
    auto x = info->add(data, &GCProject3D::xPosition, "xPosition");
    x->setCompute<computeAlignTransform>();

    auto y = info->add(data, &GCProject3D::yPosition, "yPosition");
    y->setCompute<computeAlignTransform>();

    auto v = info->add(data, &GCProject3D::validPosition, "validPosition");
    v->setCompute<computeAlignTransform>();

    const Shift::EmbeddedPropertyInstanceInformation *aff[] = { x, y };
    auto affects = info->createAffects(data, aff, X_ARRAY_COUNT(aff));

    auto cam = info->add(data, &GCProject3D::camera, "camera");
    cam->setAffects(affects, true);

    auto taTr = info->add(data, &GCProject3D::targetTransform, "targetTransform");
    taTr->setAffects(affects, false);
    }
  }
