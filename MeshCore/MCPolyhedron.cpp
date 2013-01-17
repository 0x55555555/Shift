#include "MCPolyhedron.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"

S_IMPLEMENT_PROPERTY(MCPolyhedronProperty, MeshCore)

void MCPolyhedronProperty::createTypeInformation(Shift::PropertyInformationTyped<MCPolyhedronProperty> *,
                                                 const Shift::PropertyInformationCreateData &)
  {
  }

void MCPolyhedron::computeNormals()
  {
    {
    Facet_iterator it = facets_begin();
    Facet_iterator end = facets_end();
    do
      {
      Eks::Vector3D sum = Eks::Vector3D::Zero();

      Halfedge_around_facet_circulator h = it->facet_begin();
      do
        {
        Eks::Vector3D normal = (h->next()->vertex()->point() - h->vertex()->point()).cross(
                             h->next()->next()->vertex()->point() - h->next()->vertex()->point());

        sum = sum + normal.normalized();
        } while (++h != it->facet_begin());

      it->plane() = Eks::Plane(Eks::Vector3D::Zero(), sum.normalized());
      } while (++it != end);
    }

    {
    Vertex_iterator it = vertices_begin();
    Vertex_iterator end = vertices_end();
    do
      {
      Eks::Vector3D normal = Eks::Vector3D::Zero();
      Halfedge_around_vertex_const_circulator pHalfedge = it->vertex_begin();
      Halfedge_around_vertex_const_circulator begin = pHalfedge;

      CGAL_For_all(pHalfedge,begin)
        {
        if(!pHalfedge->is_border())
          {
          normal = normal + pHalfedge->facet()->plane().normal();
          }
        }

      it->normal() = normal.normalized();
      } while (++it != end);
    }
  }
