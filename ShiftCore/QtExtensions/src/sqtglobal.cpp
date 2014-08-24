#include "sqtglobal.h"
#include "sinterfaces.h"
#include "shift/TypeInformation/smodule.h"
#include "shift/Changes/shandler.h"
#include "shift/Properties/sattribute.inl"

S_IMPLEMENT_MODULE_WITH_INTERFACES(ShiftQt)
  {
  using namespace Shift;
  module.addStaticInterface<Entity, SBasicPositionInterface>();
  module.addStaticInterface<Property, SBasicColourInterface>();
  }
