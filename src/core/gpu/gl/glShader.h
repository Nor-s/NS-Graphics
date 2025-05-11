#ifndef _NS_GRAPHICS_CORE_GPU_GL_SHADER_H
#define _NS_GRAPHICS_CORE_GPU_GL_SHADER_H

#include "glCommon.h"

namespace ns
{

class GlShader
{
public:
	GlShader() = default;
	GlShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
	GlShader(std::string_view vertexCode, std::string_view fragmentCode, std::string_view geometryCode="");
	~GlShader();

	void init(std::string_view vertexCode, std::string_view fragmentCode, std::string_view geometryCode="");
	void use();
	const unsigned int getId() const;

	void setBool(std::string_view name, bool value) const;
	void setFloat(std::string_view name, float value) const;
	void setVec2(std::string_view name, const Vec2& value) const;
	void setVec3(std::string_view name, const Vec3& value) const;
	void setVec4(std::string_view name, const Vec4& value) const;
	void setMat3(std::string_view name, const Mat3& mat) const;
	void setMat4(std::string_view name, const Mat4& mat) const;

private:
	unsigned int id_=0;

	void checkCompileErrors(GLuint shader, std::string type);
};
}	 // namespace ns

#endif