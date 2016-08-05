/*
 *  qianqians
 *  2014-11-28
 */
#ifndef _context_h_
#define _context_h_

#include "glextARB.h"

#include <mutex>
#include <vector>
#include <unordered_map>
#include <memory>

#include "render.h"
#include "camera .h"

class wnd;

class context{
public:
	context(wnd * wnd);
	~context();

	void init();

	void lookat(float postionx, float postiony, float postionz, float upx, float upy, float upz, float lookatx, float lookaty, float lookatz);

	void make_current();

	void release();

public:
	void addrender(std::shared_ptr<render> _render);

	void removerender(std::string uuid);

private:
	void draw();

	friend class wnd;

private:
	HDC hdc;
	HGLRC rc;

	GLuint _program;

	std::mutex _mu_addlist;
	std::list<std::shared_ptr<render> > addlist;
	std::mutex _mu_removelist;
	std::list<std::string> removelist;
	std::unordered_map<std::string, std::shared_ptr<render> > drawlist;

	camera _camera;

};

#endif