#pragma once
#include <OGL3D/OPrerequisites.h>

class OShaderProgram {
public:
	OShaderProgram(const OShaderProgramDesc& desc);
	~OShaderProgram();

	ui32 getID() {
		return m_programID;
	}

private:
	void attach(const wchar_t* shaderFilePath, const OShaderType& type);
	void link();

	ui32 m_programID = 0;
	ui32 m_attachedPrograms[2] = {};
};

