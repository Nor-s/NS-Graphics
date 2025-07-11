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
		if(instancingLayout_.size() == 0 || geometry_.instancingVertex.size() == 0) 
			return 0;
		return geometry_.instancingVertex[0].size()/instancingLayout_[0].count;
	}
	GeometryInfo& getGeoInfo()
	{
		return geometry_;
	}
	void pushInstancingLayout(int startIndex, int count)
	{
		instancingLayout_.emplace_back(startIndex, count);
	}

	virtual void init(const GeometryInfo& info, const Layouts& layouts, const InstancingLayouts& instancingLayout = {}) = 0;
	virtual void updateInstancingBuffer(int idx){};

protected:
	GeometryInfo geometry_;
	InstancingLayouts instancingLayout_;
};

}	 // namespace ns

#endif