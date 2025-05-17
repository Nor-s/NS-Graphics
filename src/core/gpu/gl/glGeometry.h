#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_GEOMETRY_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_GEOMETRY_H_

#include "glBuffer.h"

namespace ns
{

class GlGeometry
{
public:
    static std::unique_ptr<GlGeometry> genTriangle();
    static std::unique_ptr<GlGeometry> genRectangle();
    static std::unique_ptr<GlGeometry> genCube();

public:
    GlGeometry() = default;
    ~GlGeometry() = default;
    const GlMeshBuffer* getBuffer();
    void init(const GeometryInfo& info, const GlMeshBuffer::Layouts& layouts);
    size_t getIndexSize() {return geometry_.index.size();}

private:
	std::unique_ptr<GlMeshBuffer> buffer_;
    GeometryInfo geometry_;
	Mat4 world_;
};
}	 // namespace ns

#endif