/*
 *  qianqians
 *  2014-12-12
 */
#include "render.h"

render::render(std::string uuid, size_t vertex_count, float * mesh, float * color, size_t texture_width, size_t texture_height, float * texture, float * uv){
	bodyid = uuid;
	_vertex_count = vertex_count;
	_mesh = mesh;
	_color = color;
	_texture_width = texture_width;
	_texture_height = texture_height;
	_texture = texture;
	_uv = uv;
}

render::~render() {
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &_gltexture);
}

void render::update(GLint _program) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, _mesh);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, 0, _color);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, _uv);

	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_gltexture);
	glBindTexture(GL_TEXTURE_2D, _gltexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _texture_width, _texture_height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, _texture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::shared_ptr<shader> render::get_shader() {
	return _shader;
}

void render::drawrender(GLint _program) {
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao);
	glBindTexture(GL_TEXTURE_2D, _gltexture);
	glDrawArrays(GL_TRIANGLES, 0, _vertex_count);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}