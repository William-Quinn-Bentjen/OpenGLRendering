#include "render.h"

geometry makeGeometry(vertex * verts, size_t vertCount, unsigned int * indices, size_t indexCount)
{
	//create an instance of geometry
	geometry newGeo = {};
	newGeo.size = indexCount;
	//generate buffers
	glGenVertexArrays(1, &newGeo.vao);
	glGenBuffers(1, &newGeo.vbo);
	glGenBuffers(1, &newGeo.ibo);
	//bind buffers
	glBindVertexArray(newGeo.vao); //must be bound first so they vertex buffer object and ibo bind correctly
	glBindBuffer(GL_ARRAY_BUFFER, newGeo.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newGeo.ibo);
	//populate buffers
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(vertex), verts, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
	//describe vertex data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
	//unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//return geometry
	return newGeo;
}

void freeGeometry(geometry & geo)
{
	glDeleteBuffers(1, &geo.vbo);
	glDeleteBuffers(1, &geo.ibo);
	glDeleteVertexArrays(1, &geo.vao);
	geo = {};
}

shader makeShader(const char * vertSource, const char * fragSource)
{
	//make shader object
	shader newShad = {};
	newShad.program = glCreateProgram();
	//create shaders
	GLuint vert = glCreateShader(GL_VERTEX_SHADER);
	GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
	//compile shaders
	glShaderSource(vert, 1, &vertSource, 0);
	glShaderSource(frag, 1, &fragSource, 0);
	glCompileShader(vert);
	glCompileShader(frag);
	//attach shaders
	glAttachShader(newShad.program, vert);
	glAttachShader(newShad.program, frag);
	//link shaders
	glLinkProgram(newShad.program);
	//delete shaders
	glDeleteShader(vert);
	glDeleteShader(frag);
	//return shader object
	return newShad;
}

void freeShader(shader & shad)
{
	glDeleteProgram(shad.program);
	shad = {};
}

void draw(const shader & shad, const geometry & geo)
{
	glUseProgram(shad.program);
	glBindVertexArray(geo.vao);
	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}
