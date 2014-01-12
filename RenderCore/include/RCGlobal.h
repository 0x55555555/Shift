#ifndef RCGLOBAL_H
#define RCGLOBAL_H

#include "XGlobal.h"
#include "shift/sglobal.h"

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
S_DEFINE_INTERFACE_TYPE(RCShaderInterface, 52)

S_MODULE(RENDERCORE_EXPORT, RenderCore)

#endif // RCGLOBAL_H
