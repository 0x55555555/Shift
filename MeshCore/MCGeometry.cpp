#include "MCGeometry.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XTemporaryAllocator"

S_IMPLEMENT_PROPERTY(MCGeometry, MeshCore)

void computeRuntimeGeometry(MCGeometry *rtGeo)
  {
  GCRenderer *gcR = rtGeo->renderer();
  if(!gcR)
    {
    return;
    }

  Eks::Renderer* r = gcR->value();
  xAssert(r);

  GCRuntimeGeometry::ComputeLock l(&rtGeo->runtimeGeometry);
  GCRuntimeIndexGeometry::ComputeLock l2(&rtGeo->runtimeIndexGeometry);

  Eks::TemporaryAllocator alloc(rtGeo->handler()->temporaryAllocator());

  rtGeo->bakeTo(&alloc, r, l.data(), l2.data());
  }

void MCGeometry::createTypeInformation(Shift::PropertyInformationTyped<MCGeometry> *info,
                                       const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto childBlock = info->createChildrenBlock(data);

    auto rtGeo = info->child(&MCGeometry::runtimeGeometry);
    rtGeo->setCompute<computeRuntimeGeometry>();

    auto rtIGeo = info->child(&MCGeometry::runtimeIndexGeometry);
    rtGeo->setCompute<computeRuntimeGeometry>();

    const Shift::EmbeddedPropertyInstanceInformation *affects[] =
    {
      rtGeo,
      rtIGeo
    };
    auto affectsGeos = childBlock.createAffects(affects, X_ARRAY_COUNT(affects));


    auto attrs = childBlock.add(&MCGeometry::polygons, "polygons");
    attrs->setAffects(affectsGeos, true);

    auto renderer = childBlock.add(&MCGeometry::renderer, "renderer");
    renderer->setAffects(affectsGeos, false);
    }
  }

void MCGeometry::bakeTo(
    Eks::AllocatorBase *alloc,
    Eks::Renderer *r,
    Eks::Geometry *geo,
    Eks::IndexGeometry *geoI) const
  {
  const MCPolyhedron &p = polygons();

  xsize vec3Size = sizeof(float) * 3;
  xsize vertexSize = vec3Size * 2;

  Eks::Vector<xuint8> vertexData(alloc);
  Eks::Vector<xuint16> indexData(alloc);

  MCPolyhedron::Facet_const_iterator it = p.facets_begin();
  MCPolyhedron::Facet_const_iterator end = p.facets_end();
  for(size_t i = 0; it != end; ++i, ++it)
    {
    const MCPolyhedron::Facet& f = *it;

    xsize size = 0;

    MCPolyhedron::Halfedge_const_handle fIt = f.halfedge();
    MCPolyhedron::Halfedge_const_handle fEnd = f.halfedge();
    do
      {
      ++size;
      fIt = fIt->next();
      } while(fIt != fEnd);

    fIt = f.halfedge();
    MCPolyhedron::Vertex_const_iterator vBegin = p.vertices_begin();
    xsize zeroIdx = indexData.size();
    xsize ptIdx = 0;
    do
      {
      MCPolyhedron::Vertex_const_iterator vIt = fIt->vertex();
      const MCPolyhedron::Vertex& v = *vIt;

      // emit triangle
      if(ptIdx >= 2)
        {
        xAssert(zeroIdx + ptIdx <= X_UINT16_SENTINEL);
        indexData << zeroIdx << zeroIdx + ptIdx - 1 << zeroIdx + ptIdx;
        }

      vertexData.resizeAndCopy(vertexData.size() + vec3Size, (xuint8*)&v.point());
      vertexData.resizeAndCopy(vertexData.size() + vec3Size, (xuint8*)&v.normal());

      fIt = fIt->next();
      ptIdx++;
      } while(fIt != fEnd);
    }

  xsize vertexCount = vertexData.size() / vertexSize;
  xAssert(vertexData.size() % vertexSize == 0);

  geo->~Geometry();
  new(geo) Eks::Geometry(r, vertexData.data(), vertexSize, vertexCount);

  geoI->~IndexGeometry();
  new(geo) Eks::IndexGeometry(r, Eks::IndexGeometry::Unsigned16, indexData.data(), indexData.size());
  }
