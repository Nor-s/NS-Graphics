#include "geometry.h"

#include "gl/glGeometry.h"

namespace ns
{
std::unique_ptr<Geometry> Geometry::CreateGeometry()
{
	return std::make_unique<GlGeometry>();
}

std::unique_ptr<Geometry> Geometry::CreateTriangle()
{
	std::unique_ptr<Geometry> ret = CreateGeometry();
	GeometryInfo geoInfo;
	geoInfo.vertex = {
		0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f,
	};
	geoInfo.index = {0, 1, 2};
	uint32_t stride = 3 * sizeof(float);
	ret->init(geoInfo, {ns::VertexLayout{0, 3, stride, 0}});

	return ret;
}

std::unique_ptr<Geometry> Geometry::CreateRectangle()
{
	std::unique_ptr<Geometry> ret = CreateGeometry();
	GeometryInfo geoInfo;
	geoInfo.vertex = {
		0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f,
	};
	geoInfo.index = {0, 1, 3, 1, 2, 3};
	uint32_t stride = 3 * sizeof(float);
	ret->init(geoInfo, {ns::VertexLayout{0, 3, stride, 0}});

	return ret;
}

std::unique_ptr<Geometry> Geometry::CreateCube()
{
	std::unique_ptr<Geometry> ret = CreateGeometry();
	GeometryInfo geoInfo;
	geoInfo.vertex = {
		// x, y, z
		-0.5f, 0.5f,  0.5f,	 -0.5f, -0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f,  -0.5f,	// 0 --- 4
		-0.5f, -0.5f, -0.5f,	// 1 --- 5
		0.5f,  -0.5f, -0.5f,	// 2 --- 6
		0.5f,  0.5f,  -0.5f,	// 3 --- 7
	};
	geoInfo.index = {
		0, 1, 2, 0, 2, 3,	 // front
		0, 5, 1, 0, 4, 5,	 // left
		4, 5, 6, 4, 6, 7,	 // back
		3, 2, 6, 3, 6, 7,	 // right
		0, 3, 4, 3, 7, 4,	 // top
		1, 5, 2, 5, 6, 2	 // bottom
	};
	uint32_t stride = 3 * sizeof(float);
	ret->init(geoInfo, {ns::VertexLayout{0, 3, stride, 0}});

	return ret;
}

std::unique_ptr<Geometry> Geometry::CreateCubeWithNormal()
{
	std::unique_ptr<Geometry> ret = CreateGeometry();
	GeometryInfo geoInfo;
	geoInfo.vertex = {-0.5f, -0.5f, -0.5f, 0.0f,  0.0f,	 -1.0f, 0.5f,  -0.5f, -0.5f, 0.0f,	0.0f,  -1.0f,
					  0.5f,	 0.5f,	-0.5f, 0.0f,  0.0f,	 -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,	0.0f,  -1.0f,
					  -0.5f, 0.5f,	-0.5f, 0.0f,  0.0f,	 -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,	0.0f,  -1.0f,

					  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,	 1.0f,	0.5f,  -0.5f, 0.5f,	 0.0f,	0.0f,  1.0f,
					  0.5f,	 0.5f,	0.5f,  0.0f,  0.0f,	 1.0f,	0.5f,  0.5f,  0.5f,	 0.0f,	0.0f,  1.0f,
					  -0.5f, 0.5f,	0.5f,  0.0f,  0.0f,	 1.0f,	-0.5f, -0.5f, 0.5f,	 0.0f,	0.0f,  1.0f,

					  -0.5f, 0.5f,	0.5f,  -1.0f, 0.0f,	 0.0f,	-0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f,
					  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,	 0.0f,	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
					  -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f,	 0.0f,	-0.5f, 0.5f,  0.5f,	 -1.0f, 0.0f,  0.0f,

					  0.5f,	 0.5f,	0.5f,  1.0f,  0.0f,	 0.0f,	0.5f,  0.5f,  -0.5f, 1.0f,	0.0f,  0.0f,
					  0.5f,	 -0.5f, -0.5f, 1.0f,  0.0f,	 0.0f,	0.5f,  -0.5f, -0.5f, 1.0f,	0.0f,  0.0f,
					  0.5f,	 -0.5f, 0.5f,  1.0f,  0.0f,	 0.0f,	0.5f,  0.5f,  0.5f,	 1.0f,	0.0f,  0.0f,

					  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,	0.5f,  -0.5f, -0.5f, 0.0f,	-1.0f, 0.0f,
					  0.5f,	 -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,	0.5f,  -0.5f, 0.5f,	 0.0f,	-1.0f, 0.0f,
					  -0.5f, -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,	-0.5f, -0.5f, -0.5f, 0.0f,	-1.0f, 0.0f,

					  -0.5f, 0.5f,	-0.5f, 0.0f,  1.0f,	 0.0f,	0.5f,  0.5f,  -0.5f, 0.0f,	1.0f,  0.0f,
					  0.5f,	 0.5f,	0.5f,  0.0f,  1.0f,	 0.0f,	0.5f,  0.5f,  0.5f,	 0.0f,	1.0f,  0.0f,
					  -0.5f, 0.5f,	0.5f,  0.0f,  1.0f,	 0.0f,	-0.5f, 0.5f,  -0.5f, 0.0f,	1.0f,  0.0f};
	uint32_t stride = 6 * sizeof(float);
	ret->init(geoInfo, {
						   ns::VertexLayout{0, 3, stride, 0},
						   ns::VertexLayout{1, 3, stride, 3 * sizeof(float)},
					   });

	return ret;
}
}	 // namespace ns