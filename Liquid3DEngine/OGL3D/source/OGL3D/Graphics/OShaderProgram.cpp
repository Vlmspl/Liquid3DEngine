#include <OGL3D/Graphics/OShaderProgram.h>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>

OShaderProgram::OShaderProgram(const OShaderProgramDesc& desc) {
	m_programID = glCreateProgram();
	attach(desc.vertexShaderPath, VertexShader);
	attach(desc.fragmentShaderPath, FragmentShader);
	link();
}

OShaderProgram::~OShaderProgram() {
	for (ui32 i = 0; i < 2; i++) {
		glDetachShader(m_programID, m_attachedPrograms[i]);
		glDeleteShader(m_attachedPrograms[i]);
	}
	glDeleteProgram(m_programID);
}

void OShaderProgram::attach(const wchar_t* shaderFilePath, const OShaderType& type) {
	std::string shaderCode;
	std::ifstream shaderStream(shaderFilePath);
	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	} else {
		return;
	}

	ui32 shaderID = 0;
	if (type == VertexShader)
		shaderID = glCreateShader(GL_VERTEX_SHADER);
	else if (type == FragmentShader)
		shaderID = glCreateShader(GL_FRAGMENT_SHADER);

	auto sourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);


	glAttachShader(m_programID, shaderID);
	m_attachedPrograms[type] = shaderID;
}

void OShaderProgram::link() {
	glLinkProgram(m_programID);
}
