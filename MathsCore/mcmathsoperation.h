#ifndef MCMATHSOPERATION_H
#define MCMATHSOPERATION_H

#include "mcglobal.h"
#include "shift/Properties/sbaseproperties.h"
#include "XArrayMath"

class MATHSCORE_EXPORT MCMathsOperation : public Shift::PODPropertyBase<XMathsOperation, MCMathsOperation>
  {
  S_PROPERTY(MCMathsOperation, Shift::Property, 0)

public:
  static void assignProperty(const Shift::Property *, Shift::Property *);

  bool saveResultToFile(QString filename);
  QImage asQImage(const Eks::VectorI2D &pt, xuint32 scale, xuint32 w, xuint32 h) const;
  };

S_PROPERTY_INTERFACE(MCMathsOperation)

#endif // MCMATHSOPERATION_H
