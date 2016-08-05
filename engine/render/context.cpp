/*
 *  qianqians
 *  2014-12-12
 */
#include <exception>

#include "context.h"
#include "wnd.h"

context::context(wnd * wnd){
	hdc = wnd->getDC();
}

context::~context(){
}

void context::lookat(float postionx, float postiony, float postionz, float upx, float upy, float upz, float lookatx, float lookaty, float lookatz){
	_camera.postion[0] = postionx;
	_camera.postion[1] = postiony;
	_camera.postion[2] = postionz;
	
	_camera.up[0] = upx;
	_camera.up[1] = upy;
	_camera.up[2] = upz;
	
	_camera.lookat[0] = lookatx;
	_camera.lookat[1] = lookaty;
	_camera.lookat[2] = lookatz;
}

void context::init() {
	if (rc == 0) {
		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA,
			16,
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			16,
			0,
			0,
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};

		GLint iPixelFormat;
		if ((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0) {
			throw std::exception("ChoosePixelFormat Failed");
		}

		if (SetPixelFormat(hdc, iPixelFormat, &pfd) == false) {
			throw std::exception("SetPixelFormat Failed");
		}

		rc = wglCreateContext(hdc);
	}

	if (glGetShaderInfoLog == 0) {
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	}
	if (glGetShaderiv == 0) {
		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	}
	if (glDetachShader == 0) {
		glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	}
	if (glAttachShader == 0) {
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	}
	if (glDeleteShader == 0) {
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	}
	if (glCompileShader == 0) {
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	}
	if (glShaderSource == 0) {
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	}
	if (glCreateShader == 0) {
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	}
	if (glUseProgram == 0) {
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	}
	if (glGetProgramInfoLog == 0) {
		glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	}
	if (glGetProgramiv == 0) {
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	}
	if (glCreateProgram == 0) {
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	}
	if (glBindVertexArray == 0) {
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	}
	if (glLinkProgram == 0) {
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	}
	if (glVertexAttribPointer == 0) {
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	}
	if (glEnableVertexAttribArray == 0) {
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	}
	if (glBufferData == 0) {
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	}
	if (glBindBuffer == 0) {
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	}
	if (glGenBuffers == 0) {
		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	}
	if (glDeleteVertexArrays == 0) {
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	}
	if (glGenVertexArrays == 0) {
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	}
	if (glGetAttribLocation == 0) {
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	}
	if (glValidateProgram == 0) {
		glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wglGetProcAddress("glValidateProgram");
	}
	if (glActiveTexture == 0) {
		glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	}

	_program = glCreateProgram();

	glEnable(GL_TEXTURE_2D);
}

void context::make_current(){
	wglMakeCurrent(hdc, rc);

	gluLookAt(_camera.lookat[0], _camera.lookat[1], _camera.lookat[2], _camera.postion[0], _camera.postion[1], _camera.postion[2], _camera.up[0], _camera.up[1], _camera.up[2]);
}

void context::release(){   
	wglMakeCurrent(0, 0);
}

void context::addrender(std::shared_ptr<render> _render) {
	std::lock_guard<std::mutex> lock(_mu_addlist);
	addlist.push_back(_render);
}

void context::removerender(std::string uuid) {
	std::lock_guard<std::mutex> lock(_mu_removelist);
	removelist.push_back(uuid);
}

void context::draw() {
	{
		std::lock_guard<std::mutex> lock1(_mu_removelist);
		for (auto id : removelist) {
			drawlist.erase(id);
		}
	}

	{
		std::lock_guard<std::mutex> lock(_mu_addlist);
		for (auto rd : addlist) {
			drawlist.insert(std::make_pair(rd->bodyid, rd));
		}
	}

	{
		std::unordered_map<std::shared_ptr<shader>, std::vector<std::shared_ptr<render> > > draw;
		for (auto pair : drawlist) {
			auto it = draw.find(pair.second->get_shader());
			if (it == draw.end()) {
				draw.insert(std::make_pair(pair.second->get_shader(), std::vector<std::shared_ptr<render> >()));
				it = draw.find(pair.second->get_shader());
			}

			it->second.push_back(pair.second);
		}

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glUseProgram(_program);
		for (auto pair : draw) {
			pair.first->make_current(_program);
			for (auto rd : pair.second) {
				rd->drawrender(_program);
			}
			pair.first->release(_program);
		}
		glUseProgram(0);

		SwapBuffers(hdc);
	}
}