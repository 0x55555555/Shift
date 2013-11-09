#include "SkGlobal.h"
#include "shift/TypeInformation/styperegistry.h"

namespace SketchCore
{
void initiate()
  {
  Shift::TypeRegistry::addPropertyGroup(propertyGroup());
  }

Shift::PropertyGroup &propertyGroup()
  {
  static Shift::PropertyGroup grp;
  return grp;
  }
}
