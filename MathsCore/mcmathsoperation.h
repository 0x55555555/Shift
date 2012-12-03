#ifndef MCMATHSOPERATION_H
#define MCMATHSOPERATION_H

#include "mcglobal.h"
#include "sbaseproperties.h"
#include "XArrayMath"

class MATHSCORE_EXPORT MCMathsOperation : public PODPropertyBase<XMathsOperation, MCMathsOperation>
  {
  S_PROPERTY(MCMathsOperation, Property, 0)

public:
  static void assignProperty(const Property *, Property *);

  bool saveResultToFile(QString filename);
  QImage asQImage(const XVectorI2D &pt, xuint32 scale, xuint32 w, xuint32 h) const;
  };

S_PROPERTY_INTERFACE(MCMathsOperation)

#endif // MCMATHSOPERATION_H
