#ifndef _NS_GRAPHICS_CORE_GPU_GEOMETRY_H_
#define _NS_GRAPHICS_CORE_GPU_GEOMETRY_H_

#include "common/common.h"

namespace ns
{

class Geometry
{
public:
    static std::unique_ptr<Geometry> CreateGeometry();
	static std::unique_ptr<Geometry> CreateTriangle();
	static std::unique_ptr<Geometry> CreateRectangle();
	static std::unique_ptr<Geometry> CreateCube();
	static std::unique_ptr<Geometry> CreateCubeWithNormal();

public:
    virtual ~Geometry()=default;
    size_t getIndexSize() {return geometry_.index.size();}
    virtual void init(const GeometryInfo& info, const Layouts& layouts) = 0;

protected:
	GeometryInfo geometry_;
};

}	 // namespace ns

#endif