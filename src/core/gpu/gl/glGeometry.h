#ifndef _NS_GRAPHICS_CORE_GPU_GL_GL_GEOMETRY_H_
#define _NS_GRAPHICS_CORE_GPU_GL_GL_GEOMETRY_H_

#include "../geometry.h"
#include "glBuffer.h"

namespace ns
{

class GlGeometry : public Geometry
{
public:
	GlGeometry() = default;
	~GlGeometry() = default;
	void init(const GeometryInfo& info, const Layouts& layouts, const InstancingLayouts& instancingLayout={});
	virtual void updateInstancingBuffer(int idx, size_t size, void* data) override;
 	GlMeshBuffer* getBuffer();

private:
	std::unique_ptr<GlMeshBuffer> buffer_;
};

}	 // namespace ns

#endif