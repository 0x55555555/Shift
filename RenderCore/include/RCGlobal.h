#ifndef RCGLOBAL_H
#define RCGLOBAL_H

#include "XGlobal"
#include "shift/sglobal.h"
#include "shift/TypeInformation/spropertygroup.h"

#ifdef RENDERCORE_BUILD
# define RENDERCORE_EXPORT X_DECL_EXPORT
#else
# define RENDERCORE_EXPORT X_DECL_IMPORT
#endif

#define RCProfileScope 1090
#define RCProfileFunction XProfileFunctionBase(RCProfileScope)
#define RCProfileFunctionScopedBlock(mess) XProfileScopedBlockBase(RCProfileScope, mess)

S_DEFINE_INTERFACE_TYPE(RCShaderBindableResource, 50)
S_DEFINE_INTERFACE_TYPE(RCShaderBindableData, 51)

namespace RenderCore
{
void RENDERCORE_EXPORT initiate();
Shift::PropertyGroup &propertyGroup();
}

#endif // RCGLOBAL_H
