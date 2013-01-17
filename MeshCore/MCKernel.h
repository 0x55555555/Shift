#ifndef MCKERNEL_H
#define MCKERNEL_H

#include "MCCGALSetup.h"
#include "XGlobal"
#include "XMathVector"
#include "XPlane.h"
#include <CGAL/Cartesian/Cartesian_base.h>
#include <CGAL/Handle_for.h>
#include <CGAL/Kernel/Type_equality_wrapper.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

typedef CGAL::Simple_cartesian<float>::Point_3 F3;
typedef CGAL::Simple_cartesian<double>::Point_3 D3;
typedef CGAL::Exact_predicates_inexact_constructions_kernel::Point_3 EPICK3;

template <typename Kernel_> struct MCKernelBase : public CGAL::Cartesian_base<Kernel_, Eks::Real>
  {
  typedef Eks::Real                                   RT;
  typedef Eks::Real                                   FT;

  typedef Eks::Vector2D                               Point_2;
  typedef Eks::Vector2D                               Vector_2;
  typedef Eks::Vector2D                               Direction_2;
  typedef CGAL::SegmentC2<Kernel>                     Segment_2;
  typedef CGAL::LineC2<Kernel>                        Line_2;
  typedef CGAL::RayC2<Kernel>                         Ray_2;
  typedef CGAL::TriangleC2<Kernel>                    Triangle_2;
  typedef CGAL::CircleC2<Kernel>                      Circle_2;
  typedef CGAL::Iso_rectangleC2<Kernel>               Iso_rectangle_2;
  typedef CGAL::Aff_transformationC2<Kernel>          Aff_transformation_2;

  typedef const Eks::Real * Cartesian_const_iterator_3;
  typedef Eks::Real * Cartesian_iterator_3;

  class Point_3 : public Eks::Vector3D
    {
  public:
    Point_3() : Eks::Vector3D(Eks::Vector3D::Zero()), _w(1.0f) { }
    Point_3(float x, float y, float z) : Eks::Vector3D(x, y, z), _w(1.0f) { }
    Point_3(float x, float y, float z, float w) : Eks::Vector3D(x, y, z), _w(w) { }
    Point_3(const Eks::Vector3D &p) : Eks::Vector3D(p), _w(1.0f) { }
    Point_3(const F3 &p) : Eks::Vector3D(p.x(), p.y(), p.z()), _w(1.0f) { }
    Point_3(const D3 &p) : Eks::Vector3D(p.x(), p.y(), p.z()), _w(1.0f) { }
    Point_3(const EPICK3 &p) : Eks::Vector3D(p.x(), p.y(), p.z()), _w(1.0f) { }
    Point_3(CGAL::Origin) : Eks::Vector3D(Eks::Vector3D::Zero()), _w(1.0f) { }
    Point_3(const Point_3 &p) : Eks::Vector3D(p), _w(p._w) { }
    Point_3& operator=(const Eks::Vector3D& p) { *((Eks::Vector3D*)this) = p; return *this; }

    const Eks::Real *cartesian_begin() const { return data(); }
    const Eks::Real *cartesian_end() const { return data() + 3; }

    Eks::Real *cartesian_begin() { return data(); }
    Eks::Real *cartesian_end() { return data() + 3; }

    const Eks::Real &hx() const { return x(); }
    const Eks::Real &hy() const { return y(); }
    const Eks::Real &hz() const { return z(); }
    const Eks::Real &hw() const { return _w; }

  private:
    Eks::Real _w;
    };

  class Vector_3 : public Eks::Vector3D
    {
  public:
    Vector_3() : Eks::Vector3D(Eks::Vector3D::Zero()) { }
    Vector_3(float x, float y, float z) : Eks::Vector3D(x, y, z) { }
    Vector_3(const Eks::Vector3D &p) : Eks::Vector3D(p) { }

    Eks::Real squared_length() const { return squaredNorm(); }
    };

  typedef CGAL::LineC3<Kernel>                        Line_3;
  class Direction_3 : public Eks::Vector3D
    {
  public:
    Direction_3() : Eks::Vector3D(Eks::Vector3D::Zero()) { }
    Direction_3(float x, float y, float z) : Eks::Vector3D(x, y, z) { }
    Direction_3(const Eks::Vector3D &p) : Eks::Vector3D(p) { }
    Direction_3(const Line_3 &p) : Eks::Vector3D(p.direction()) { }

    const Eks::Real &dx() const { return x(); }
    const Eks::Real &dy() const { return y(); }
    const Eks::Real &dz() const { return z(); }
    };

  typedef Eks::Plane                                  Plane_3;
  typedef CGAL::RayC3<Kernel>                         Ray_3;
  typedef CGAL::SegmentC3<Kernel>                     Segment_3;
  typedef CGAL::TriangleC3<Kernel>                    Triangle_3;
  typedef CGAL::TetrahedronC3<Kernel>                 Tetrahedron_3;
  typedef CGAL::Iso_cuboidC3<Kernel>                  Iso_cuboid_3;
  typedef CGAL::SphereC3<Kernel>                      Sphere_3;
  typedef CGAL::CircleC3<Kernel>                      Circle_3;
  typedef CGAL::Aff_transformationC3<Kernel>          Aff_transformation_3;

  // The mechanism that allows to specify reference-counting or not.
  template <typename T> struct Handle { typedef T   type; };

  template <typename Kernel2>
  struct Base { typedef MCKernelBase<Kernel2>  Type; };

  typedef Kernel_ K;
#define CGAL_Kernel_pred(Y,Z) typedef CGAL::CartesianKernelFunctors::Y<K> Y; \
                              Y Z() const { return Y(); }
#define CGAL_Kernel_cons(Y,Z) CGAL_Kernel_pred(Y,Z)

#include <CGAL/Kernel/interface_macros.h>
  };

struct MCKernel : public CGAL::Type_equality_wrapper<MCKernelBase<MCKernel>, MCKernel>
  {
  };

#endif // MCKERNEL_H
