#ifndef SQTGLOBAL_H
#define SQTGLOBAL_H

#include "shift/sglobal.h"

#if defined(SHIFTQT_BUILD)
#  define SHIFTUI_EXPORT X_DECL_EXPORT
#else
#  define SHIFTUI_EXPORT X_DECL_IMPORT
#endif

S_MODULE(SHIFTUI_EXPORT, ShiftQt)

#endif // SQTGLOBAL_H
