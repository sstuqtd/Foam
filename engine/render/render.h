/*
*  qianqians
*  2014-12-12
*/
#ifndef _render_h
#define _render_h

#include <list>
#include <memory>

#include "shader.h"

class render{
public:
	render(std::string uuid, size_t vertex_count, float * mesh, float * color, size_t texture_width, size_t texture_height, float * texture, float * uv);
	~render();

	std::shared_ptr<shader> get_shader();

	void update(GLint _program);

public:
	std::string bodyid;

private:
	void drawrender(GLint _program);

	friend class context;

private:
	std::shared_ptr<shader> _shader;

	size_t _vertex_count;
	float * _mesh;
	float * _color;
	size_t _texture_width, _texture_height;
	float * _texture;
	float * _uv;

	GLuint vao;
	GLuint _gltexture;

};

#endif _render_h