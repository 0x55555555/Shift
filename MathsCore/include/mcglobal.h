#ifndef MCGLOBAL_H
#define MCGLOBAL_H

#include "XGlobal"
#include "shift/sglobal.h"

#ifdef MATHSCORE_BUILD
# define MATHSCORE_EXPORT X_DECL_EXPORT
#else
# define MATHSCORE_EXPORT X_DECL_IMPORT
#endif

#define MCProfileScope 1091
#define MCProfileFunction XProfileFunctionBase(MCProfileScope)
#define MCProfileFunctionScopedBlock(mess) XProfileScopedBlockBase(MCProfileScope, mess)

namespace MathsCore
{
void MATHSCORE_EXPORT initiate();
Shift::PropertyGroup &propertyGroup();
}

#endif // MCGLOBAL_H