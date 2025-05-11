#include "glShader.h"

#include <fstream>
#include <sstream>

namespace ns
{
GlShader::GlShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	std::ifstream vertShaderFile;
	std::ifstream fragShaderFile;
	std::ifstream geoShaderFile;

	vertShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	geoShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertShaderFile.open(vertexPath);
		fragShaderFile.open(fragmentPath);

		std::stringstream vertShaderStream, fragShaderStream;

		vertShaderStream << vertShaderFile.rdbuf();
		fragShaderStream << fragShaderFile.rdbuf();

		vertShaderFile.close();
		fragShaderFile.close();

		vertexCode = vertShaderStream.str();
		fragmentCode = fragShaderStream.str();

		if (geometryPath != nullptr)
		{
			geoShaderFile.open(geometryPath);
			std::stringstream geo_shader_stream;
			geo_shader_stream << geoShaderFile.rdbuf();
			geoShaderFile.close();
			geometryCode = geo_shader_stream.str();
		}
	}
	catch (std::ifstream::failure& e)
	{
		NS_LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
	}

	init(vertexCode, fragmentCode, geometryCode);
}

GlShader::GlShader(std::string_view vertexCode, std::string_view fragmentCode, std::string_view geometryCode)
{
	init(vertexCode, fragmentCode, geometryCode);
}

GlShader::~GlShader()
{
	GLCHECK(glDeleteProgram(id_));
}

void GlShader::init(std::string_view vertexCode, std::string_view fragmentCode, std::string_view geometryCode)
{
	bool bIsCompileGeometry = (geometryCode != "");
	unsigned int vertexShader, fragmentShader;

	const char* vShaderCode = vertexCode.data();
	const char* fShaderCode = fragmentCode.data();
	const char* gShaderCode = geometryCode.data();

	// vertex
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLCHECK(glShaderSource(vertexShader, 1, &vShaderCode, NULL));
	GLCHECK(glCompileShader(vertexShader));
	checkCompileErrors(vertexShader, "VERTEX");

	// fragment
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLCHECK(glShaderSource(fragmentShader, 1, &fShaderCode, NULL));
	GLCHECK(glCompileShader(fragmentShader));
	checkCompileErrors(fragmentShader, "FRAGMENT");

	// geometry
	unsigned int geometryShader = 0;
	if (bIsCompileGeometry)
	{
		geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
		GLCHECK(glShaderSource(geometryShader, 1, &gShaderCode, NULL));
		GLCHECK(glCompileShader(geometryShader));
		checkCompileErrors(geometryShader, "GEOMETRY");
	}

	// program
	id_ = glCreateProgram();
	GLCHECK(glAttachShader(id_, vertexShader));
	GLCHECK(glAttachShader(id_, fragmentShader));
	if (bIsCompileGeometry)
		glAttachShader(id_, geometryShader);

	// link
	GLCHECK(glLinkProgram(id_));
	checkCompileErrors(id_, "PROGRAM");

	// delete shader
	GLCHECK(glDeleteShader(vertexShader));
	GLCHECK(glDeleteShader(fragmentShader));
	if (bIsCompileGeometry)
		GLCHECK(glDeleteShader(geometryShader));
}

void GlShader::use()
{
	GLCHECK(glUseProgram(id_));
}
const unsigned int GlShader::getId() const
{
	return id_;
}
void GlShader::setBool(std::string_view name, bool value) const
{
	GLCHECK(glUniform1i(glGetUniformLocation(id_, name.data()), (int) value));
}
void GlShader::setFloat(std::string_view name, float value) const
{
	GLCHECK(glUniform1f(glGetUniformLocation(id_, name.data()), value));
}
void GlShader::setVec2(std::string_view name, const Vec2& value) const
{
	GLCHECK(glUniform2fv(glGetUniformLocation(id_, name.data()), 1, value.value));
}
void GlShader::setVec3(std::string_view name, const Vec3& value) const
{
	GLCHECK(glUniform3fv(glGetUniformLocation(id_, name.data()), 1, value.value));
}
void GlShader::setVec4(std::string_view name, const Vec4& value) const
{
	GLCHECK(glUniform4fv(glGetUniformLocation(id_, name.data()), 1, value.value));
}
void GlShader::setMat3(std::string_view name, const Mat3& mat) const
{
	GLCHECK(glUniformMatrix3fv(glGetUniformLocation(id_, name.data()), 1, GL_FALSE, &mat.value[0][0]));
}
void GlShader::setMat4(std::string_view name, const Mat4& mat) const
{
	GLCHECK(glUniformMatrix4fv(glGetUniformLocation(id_, name.data()), 1, GL_FALSE, &mat.value[0][0]));
}

void GlShader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar info_log[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, info_log);
			NS_ERROR("ERROR::SHADER_COMPILATION_ERROR of type: {} -- log: {}", type, info_log);
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, info_log);
			NS_ERROR("ERROR::PROGRAM_LINKING_ERROR of type: {} -- log: {}", type, info_log);
		}
	}
}
}	 // namespace ns