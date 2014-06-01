#include "Tools/GCTool.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(GCTool, GraphicsCore)

void GCTool::createTypeInformation(Shift::PropertyInformationTyped<GCTool> *info,
                                                const Shift::PropertyInformationCreateData &data)
  {
  auto childBlock = info->createChildrenBlock(data);
  }

