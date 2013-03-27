#include "MCSphere.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "3D/GCTransform.h"
#include "3D/Manipulators/GCDistanceManipulator.h"

S_IMPLEMENT_PROPERTY(MCSphere, MeshCore)

void MCSphere::createTypeInformation(Shift::PropertyInformationTyped<MCSphere> *info,
                                    const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto geomInst = childBlock.child(&MCSphere::geometry);

    auto radInst = childBlock.add(&MCSphere::radius, "radius");
    radInst->setAffects(data, geomInst);
    radInst->setDefault(1.0f);
    }
  }

float MCSphere::evaluate(const Eks::Vector3D &p) const
  {
  float r = radius();
  const float x2=p.x()*p.x(), y2=p.y()*p.y(), z2=p.z()*p.z();
  return x2+y2+z2 - (r*r);
  }

void MCSphere::addManipulators(Shift::PropertyArray *a, const ManipInfo &info)
  {
  // radius
    {
    GCDistanceManipulator *manip = a->add<GCDistanceManipulator>();

    manip->lockDirection = Eks::Vector3D(1.0f, 0.0f, 0.0f);
    manip->lockMode = GCDistanceManipulator::Linear;

    radius.connect(&manip->distance);

    manip->addDriven(&radius);

    if(info.parentTransform)
      {
      manip->worldTransform.setInput(info->parentTransform);
      }
    }
  }
