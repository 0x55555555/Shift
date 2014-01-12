#ifndef MCGLOBAL_H
#define MCGLOBAL_H

#include "XGlobal.h"
#include "shift/sglobal.h"

#ifdef MATHSCORE_BUILD
# define MATHSCORE_EXPORT X_DECL_EXPORT
#else
# define MATHSCORE_EXPORT X_DECL_IMPORT
#endif

#define MCProfileScope 1091
#define MCProfileFunction XProfileFunctionBase(MCProfileScope)
#define MCProfileFunctionScopedBlock(mess) XProfileScopedBlockBase(MCProfileScope, mess)

S_MODULE(MATHSCORE_EXPORT, MathsCore)

#endif // MCGLOBAL_H
