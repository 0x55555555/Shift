#include "RCGlobal.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/TypeInformation/sinterface.h"
#include "shift/Properties/sbaseproperties.h"

#include "RCTexture.h"
#include "RCTransform.h"
#include "Shader/RCShadingGroup.h"
#include "Shader/RCShaderDataBindings.h"

namespace RenderCore
{
void initiate()
  {
  Shift::TypeRegistry::addPropertyGroup(propertyGroup());

  Shift::Interface::addStaticInterface<Shift::Vector3DProperty, RCShaderDataBindings::Vector3>();
  Shift::Interface::addStaticInterface<Shift::ColourProperty, RCShaderDataBindings::Vector4>();
  Shift::Interface::addStaticInterface<RCTexture2DPointer, RCShaderDataBindings::Texture2DRef>();
  Shift::Interface::addStaticInterface<RCShaderConstantDataPointer, RCShaderDataBindings::DataRef>();
  }

Shift::PropertyGroup &propertyGroup()
  {
  static Shift::PropertyGroup grp;
  return grp;
  }
}
