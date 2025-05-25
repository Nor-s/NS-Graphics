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
        // x, y, z
         -0.5f,  0.5f,  0.5f, 
         -0.5f,  -0.5f,  0.5f,
         0.5f,  -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f,  0.5f,  -0.5f,   // 0 --- 4
        -0.5f,  -0.5f,  -0.5f,  // 1 --- 5
         0.5f,  -0.5f,  -0.5f,  // 2 --- 6
         0.5f,  0.5f,  -0.5f,   // 3 --- 7
    };
    geoInfo.index = {0, 1, 2, 
                     0, 2, 3, // front 
                     0, 5, 1,
                     0, 4, 5, // left 
                     4, 5, 6, 
                     4, 6, 7, // back
                     3, 2, 6,
                     3, 6, 7, // right
                     0, 3, 4,
                     3, 7, 4, // top
                     1, 5, 2,
                     5, 6, 2 // bottom
                    };
    uint32_t stride = 3 * sizeof(float);
    ret->init(geoInfo, {ns::GlVertexLayout{0, 3, stride, 0}});

    return ret;
}

std::unique_ptr<GlGeometry> GlGeometry::genCubeWithNormal()
{
    std::unique_ptr<GlGeometry> ret = std::make_unique<GlGeometry>(); 
    GeometryInfo geoInfo;
    geoInfo.vertex = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
   
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
   
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
   
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
   
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
   
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    uint32_t stride = 6 * sizeof(float);
    ret->init(geoInfo, {
        ns::GlVertexLayout{0, 3, stride, 0},
        ns::GlVertexLayout{1, 3, stride, 3*sizeof(float)},
    });

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
