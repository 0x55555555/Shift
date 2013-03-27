#include "MeshCore.h"
#include "shift/TypeInformation/styperegistry.h"
#include "shift/TypeInformation/spropertygroup.h"
#include "shift/TypeInformation/sinterface.h"
#include "MCSphere.h"
#include "MCCuboid.h"

namespace MeshCore
{
void initiate()
  {
  Shift::TypeRegistry::addPropertyGroup(propertyGroup());


  Shift::Interface::addInheritedInterface<MCSphere, GCManipulatable>();
  Shift::Interface::addInheritedInterface<MCCuboid, GCManipulatable>();
  }

Shift::PropertyGroup &propertyGroup()
  {
  static Shift::PropertyGroup grp;
  return grp;
  }
}
