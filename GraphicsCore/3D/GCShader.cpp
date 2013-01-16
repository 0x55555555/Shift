#include "GCShader.h"
#include "shift/TypeInformation/spropertyinformationhelpers.h"
#include "XRenderer.h"
#include "shift/Changes/shandler.inl"

S_IMPLEMENT_PROPERTY(GCShader, GraphicsCore)

void GCShader::createTypeInformation(Shift::PropertyInformationTyped<GCShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rtInfoCore = info->add(data, &GCShader::runtimeShaderCore, "runtimeShaderCore");

    auto r = info->add(data, &GCShader::renderer, "renderer");
    r->setAffects(data, rtInfoCore);

    auto rtInfo = info->add(data, &GCShader::runtimeShader, "runtimeShader");
    rtInfo->setCompute<setupShaderRuntime>();
    }
  }

void GCShader::setupShaderRuntime(GCShader *shader)
  {
  GCRuntimeShaderInstance::ComputeLock lock(&shader->runtimeShader);

  GCRenderer *gcR = shader->renderer();
  if(!gcR)
    {
    return;
    }

  Eks::Renderer *r = gcR->value();
  if(!r)
    {
    return;
    }

  GCShaderBindableData::DataBlock data;

  shader->resources.clear();

  lock.data()->instance = (Eks::Shader*)&shader->runtimeShaderCore();
  xForeach(auto p, shader->walkerFrom((Property*)&shader->runtimeShaderCore))
    {
    const GCShaderBindableData *binder = p->interface<GCShaderBindableData>();
    if(binder)
      {
      binder->bindData(&data, &shader->resources, p);
      }
    }

  if(!shader->constantData.isValid())
    {
    Eks::ShaderConstantData::delayedCreate(shader->constantData, r, data.size(), data.data());
    }
  else
    {
    shader->constantData.update(data.data());
    }
  }

void GCShader::bind(Eks::Renderer *r) const
  {
  Eks::Shader *s = runtimeShader().instance;
  r->setShader(s, &layout);

  s->setFragmentShaderConstantData(0, &constantData);
  s->setVertexShaderConstantData(0, &constantData);

  s->setFragmentShaderResources(0, resources.size(), resources.data());
  s->setVertexShaderResources(0, resources.size(), resources.data());
  }


S_IMPLEMENT_PROPERTY(GCStaticShader, GraphicsCore)

void GCStaticShader::createTypeInformation(Shift::PropertyInformationTyped<GCStaticShader> *info,
                                     const Shift::PropertyInformationCreateData &data)
  {
  if(data.registerAttributes)
    {
    auto rtInfoCore = info->child(&GCShader::runtimeShaderCore);
    rtInfoCore->setCompute<computeShaderRuntime>();
    }
  }

void GCStaticShader::computeShaderRuntime(GCStaticShader *shader)
  {
  GCRuntimeShader::ComputeLock lock(&shader->runtimeShaderCore);

  GCRenderer *gcR = shader->renderer();
  if(!gcR)
    {
    return;
    }

  Eks::Renderer *r = gcR->value();
  if(!r)
    {
    return;
    }

  const Eks::String vSrc = shader->embeddedInstanceInformation()->vertexData();
  const Eks::String fSrc = shader->embeddedInstanceInformation()->fragmentData();

  GCVertexLayout *gcLayout = shader->layoutDescription();
  if(!r)
    {
    return;
    }

  const GCVertexLayoutWrapper &layoutDesc = gcLayout->value();
  if(!layoutDesc.layout)
    {
    return;
    }


  shader->layout.~ShaderVertexLayout();
  new(&shader->layout) Eks::ShaderVertexLayout();

  shader->vertex.~ShaderVertexComponent();
  new(&shader->vertex) Eks::ShaderVertexComponent(
        r,
        vSrc.data(),
        vSrc.length(),
        layoutDesc.layout,
        layoutDesc.layoutCount,
        &shader->layout);

  shader->fragment.~ShaderFragmentComponent();
  new(&shader->fragment) Eks::ShaderFragmentComponent(r, fSrc.data(), fSrc.length());

  lock.data()->~Shader();
  new(lock.data()) Eks::Shader(r, &shader->vertex, &shader->fragment);
  }
