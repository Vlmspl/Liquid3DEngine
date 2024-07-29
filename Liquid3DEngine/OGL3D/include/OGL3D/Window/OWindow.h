#pragma once
#include <OGL3D/Math/ORect.h>

class OWindow {
public:
	OWindow();
	~OWindow();

	void makeCurrentContext();
	void present(bool vsync);
	ORect InnerSize();

private:
	void* m_handle = nullptr;
	void* m_context = nullptr;
};

