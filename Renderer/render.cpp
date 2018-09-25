#include "render.h"
#include "glm/ext.hpp"
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

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
	glEnableVertexAttribArray(0); //position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0/*memory offset for vertex data struct so it effects correct data*/);
	glEnableVertexAttribArray(1); //normal
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)16);
	glEnableVertexAttribArray(2); //uv
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)32);
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

texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char * pixels)
{
	GLenum oglFormat = 0;
	switch (channels)
	{
	case 1: oglFormat = GL_RED; break;
	case 2: oglFormat = GL_RG; break;
	case 3: oglFormat = GL_RGB; break;
	case 4: oglFormat = GL_RGBA; break;
	}
	texture newTexture = { 0,width, height, channels };
	glGenTextures(1, &newTexture.handle);
	glBindTexture(GL_TEXTURE_2D, newTexture.handle);

	glTexImage2D(GL_TEXTURE_2D, 0, oglFormat, width, height, 0, oglFormat, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	return newTexture;
	return texture();
}

void freeTexture(texture & tex)
{
	glDeleteTextures(1, &tex.handle);
	tex = {};
}

void freeShader(shader & shad)
{
	glDeleteProgram(shad.program);
	shad = {};
}

texture loadTexture(const char * imagePath)
{
	int imageWidth, imageHeight, imageFormat;
	imageWidth = imageHeight = imageFormat = -1;
	unsigned char *rawPixelData = nullptr;
	//load image
	//get the format/spec/whatever
	stbi_set_flip_vertically_on_load(true);
	rawPixelData = stbi_load(imagePath, &imageWidth, &imageHeight, &imageFormat, STBI_default);
	//pass it to opengl
	texture newTex = makeTexture(imageWidth, imageHeight, imageFormat, rawPixelData);
	//destroy any other data
	stbi_image_free(rawPixelData);
	return newTex;
}

void draw(const shader & shad, const geometry & geo)
{
	glUseProgram(shad.program);
	glBindVertexArray(geo.vao);
	glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, 0);
}

void setUniform(const shader & shad, GLuint location, const glm::mat4 & value)
{
	glProgramUniformMatrix4fv(shad.program, location, 1, GL_FALSE, glm::value_ptr(value));
}

void setUniform(const shader & shad, GLuint location, const texture & value, GLuint textureSlot)
{
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, value.handle);
	glProgramUniform1i(shad.program, location, textureSlot);
}

void setUniform(const shader & shad, GLuint location, const glm::vec3 & value)
{
	glProgramUniform3fv(shad.program, location, 1, glm::value_ptr(value));
}
