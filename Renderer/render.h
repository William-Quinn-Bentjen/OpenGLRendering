#pragma once
#include "glew/glew.h"
#include "glm/glm.hpp"
struct vertex
{
	//float pos[4];
	glm::vec4 pos;
	glm::vec4 norm;
	glm::vec2 uv;
};
struct geometry
{
	//vbo vertex buffer object (stores verts and where they are located), ibo index buffer object , vao vertex array 
	GLuint vao, vbo, ibo;	//buffers
	GLuint size;			//index count
};
struct shader
{
	GLuint program;
};
struct texture
{
	GLuint handle;
	unsigned width, height, channels;
};
geometry makeGeometry(vertex * verts, size_t vertCount,	unsigned int * indices, size_t indexCount);
void freeGeometry(geometry &geo);
shader makeShader(const char * vertSource, const char * fragSource);
texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char *pixels);
void freeTexture(texture & tex);
void freeShader(shader &shad);
texture loadTexture(const char * imagePath);
void draw(const shader &shad, const geometry & geo);
void setUniform(const shader &shad, GLuint location, const glm::mat4 &value);
void setUniform(const shader &shad, GLuint location, const texture &value, GLuint textureSlot);
void setUniform(const shader &shad, GLuint location, const glm::vec3 &value);