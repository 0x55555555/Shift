#include "RCGlobal.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "shift/TypeInformation/sinterface.h"
#include "shift/Properties/sbaseproperties.h"

#include "RCTexture.h"
#include "RCTransform.h"
#include "Shader/RCShadingGroup.h"
#include "Shader/RCShaderDataBindings.h"

S_IMPLEMENT_MODULE_WITH_INTERFACES(RenderCore)
  {
  module.addStaticInterface<Shift::Vector3DProperty, RCShaderDataBindings::Vector3>();
  module.addStaticInterface<Shift::ColourProperty, RCShaderDataBindings::Vector4>();
  module.addStaticInterface<RCTexture2DPointer, RCShaderDataBindings::Texture2DRef>();
  module.addStaticInterface<RCShaderConstantDataPointer, RCShaderDataBindings::DataRef>();
  }
