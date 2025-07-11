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
    size_t getInstancingCount() 
	{
		if(instancingLayout_.count == 0) 
			return 0;
		return geometry_.instancingVertex.size()/instancingLayout_.count;
	}
	GeometryInfo& getGeoInfo()
	{
		return geometry_;
	}
	void setInstancingLayout(int startIndex, int count)
	{
		instancingLayout_.count = count;
		instancingLayout_.startIndex= startIndex;
	}

	virtual void init(const GeometryInfo& info, const Layouts& layouts, const InstancingLayout& instancingLayout = {}) = 0;
	virtual void updateInstancingBuffer(){};

protected:
	GeometryInfo geometry_;
	InstancingLayout instancingLayout_;
};

}	 // namespace ns

#endif