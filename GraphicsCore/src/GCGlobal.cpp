#include "GCGlobal.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/TypeInformation/sinterface.h"
#include "shift/Properties/sbaseproperties.h"
#include "Manipulators/GCTranslateManipulator.h"
#include "Manipulators/GCRotateManipulator.h"
#include "Manipulators/GCManipulatable.h"

#include "RCTexture.h"
#include "RCTransform.h"
#include "Shader/RCShadingGroup.h"
#include "Shader/RCShaderDataBindings.h"

namespace GraphicsCore
{

class TransformManipulator : public GCManipulatable
  {
  void addManipulators(
      RCRenderable* renderable,
      Shift::Array *a,
      const GCManipulatable::ManipInfo &info) X_OVERRIDE
    {
    RCTransform* tr = renderable->uncheckedCastTo<RCTransform>();
    if (!tr)
      {
      return;
      }

    GCManipulatable::createManipulator<GCRotateManipulator>(a, &tr->transform, info, nullptr);
    auto *t = GCManipulatable::createManipulator<GCTranslateManipulator>(a, &tr->transform, info, &tr->transform);

    ManipInfo newInfo(info);
    newInfo.parentTransform = &t->worldTransform;

    GCManipulatable::addManipulators(renderable, a, newInfo);
    }
  };

void initiate()
  {
  Shift::TypeRegistry::addPropertyGroup(propertyGroup());

  Shift::Interface::addStaticInterface<Shift::Vector3DProperty, RCShaderDataBindings::Vector3>();
  Shift::Interface::addStaticInterface<Shift::ColourProperty, RCShaderDataBindings::Vector4>();
  Shift::Interface::addStaticInterface<RCTexture2DPointer, RCShaderDataBindings::Texture2DRef>();
  Shift::Interface::addStaticInterface<RCShaderConstantDataPointer, RCShaderDataBindings::DataRef>();

  Shift::Interface::addStaticInterface<RCShadingGroup, GCManipulatable>();
  Shift::Interface::addStaticInterface<RCTransform, TransformManipulator>();
  }

Shift::PropertyGroup &propertyGroup()
  {
  static Shift::PropertyGroup grp;
  return grp;
  }
}
