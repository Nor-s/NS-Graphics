#include "glGeometry.h"

namespace ns
{

std::unique_ptr<GlGeometry> GlGeometry::genTriangle()
{
    std::unique_ptr<GlGeometry> ret = std::make_unique<GlGeometry>(); 
    GeometryInfo geoInfo;
    geoInfo.vertex = {
        0.0f,  0.5f,  0.0f,	   
        -0.5f,  -0.5f, 0.0f,	 
        0.5f, -0.5f,  0.0f,	
    };
    geoInfo.index = {0, 1, 2};
    uint32_t stride = 3 * sizeof(float);
    ret->init(geoInfo, {ns::GlVertexLayout{0, 3, stride, 0}});

    return ret;
}
std::unique_ptr<GlGeometry> GlGeometry::genRectangle()
{
    std::unique_ptr<GlGeometry> ret = std::make_unique<GlGeometry>(); 
    GeometryInfo geoInfo;
    geoInfo.vertex = {
        0.5f, 0.5f,  0.0f,	   
        0.5f,  -0.5f, 0.0f,	 
        -0.5f, -0.5f,  0.0f,	
        -0.5f, 0.5f,  0.0f,	
    };
    geoInfo.index = {0, 1, 3, 1, 2, 3};
    uint32_t stride = 3 * sizeof(float);
    ret->init(geoInfo, {ns::GlVertexLayout{0, 3, stride, 0}});

    return ret;
}
std::unique_ptr<GlGeometry> GlGeometry::genCube()
{
    std::unique_ptr<GlGeometry> ret = std::make_unique<GlGeometry>(); 
    GeometryInfo geoInfo;
    geoInfo.vertex = {
        0.5f, 0.5f,  0.0f,	   
        0.5f,  -0.5f, 0.0f,	 
        -0.5f, -0.5f,  0.0f,	
        -0.5f, 0.5f,  0.0f,	
    };
    geoInfo.index = {0, 1, 3, 1, 2, 3};
    uint32_t stride = 3 * sizeof(float);
    ret->init(geoInfo, {ns::GlVertexLayout{0, 3, stride, 0}});

    return ret;
}

const GlMeshBuffer* GlGeometry::getBuffer()
{
	return buffer_.get();
}

void GlGeometry::init(const GeometryInfo& info, const GlMeshBuffer::Layouts& layouts)
{
	auto& index = info.index;
	auto& vertex = info.vertex;

	geometry_.index = index;
	geometry_.vertex = vertex;

	buffer_.reset();
	buffer_ = std::make_unique<GlMeshBuffer>();
	buffer_->bind();
	buffer_->setVertexBuffer(vertex.size() * sizeof(float), vertex.data(), layouts);
	buffer_->setIndexBuffer(index.size() * sizeof(uint32_t), index.data());
	buffer_->unbind();
}

}	 // namespace ns
