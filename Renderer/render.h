#pragma once
#include "glew/glew.h"
#include "glm/glm.hpp"
struct vertex
{
	float pos[4];
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
geometry makeGeometry(vertex * verts, size_t vertCount,	unsigned int * indices, size_t indexCount);
void freeGeometry(geometry &geo);
shader makeShader(const char * vertSource, const char * fragSource);
void freeShader(shader &shad);
void draw(const shader &shad, const geometry & geo);
void setUniform(const shader &shad, GLuint location, const glm::mat4 &value);