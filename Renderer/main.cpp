#include "render.h"
#include "context.h"
#include "shaderReader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iostream>
//glEnable(GL_BLEND);
//glEnable(FL_DEPTHTEST);
//glEnable(GL_CULL_FACE);
//
//glDepthFunc(GL_LEQUAL);

int main()
{
	context game;
	game.init(800, 600, "3angle3side");
	vertex triVerts[] = 
	{
		// pos				normal			uv
		{{-.5f,-.5f, 0, 1},	{ 0,0,1,1 },	{0,0}},		//vert 0
		{{ .5f,-.5f, 0, 1 },{ 0,0,1,1 },	{ 1,0 } },	//vert 1
		{{ 0,.5f, 0, 1 },	{ 0,0,1,1 },	{ 0.5,1 } }	//vert 2
	};
	unsigned triIndices[] = { 2,1,0 };
	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);
	shader fileShad = makeShaderFrom("vertexShaderExample.txt", "fragmentShaderExample.txt");
	shader mvpShad = makeShaderFrom("mvpVert.txt", "fragmentShaderExample.txt");
	shader texShad = makeShaderFrom("mvpVert.txt", "texFrag.txt");

	unsigned char whitePixel[] = { 0, 0, 0 };
	texture whiteTexture = makeTexture(1, 1, 3, whitePixel);
	texture testTexture = loadTexture("cole.png"/*"uvchecker.jpg"*/);

	glm::mat4 cam_proj = glm::perspective(glm::radians(45.f), 800.0f / 600.0f, 0.1f, 1000.0f);
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 0, -2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 triangle_model = glm::identity<glm::mat4>();

	glm::vec3 lightDir = glm::vec3(-1, 0, 0);


	while (!game.shouldClose())
	{
		//services
		game.tick();
		game.clear();

		triangle_model = glm::rotate(triangle_model, glm::radians(5.f), glm::vec3(0, 1, 0));

		setUniform(texShad, 0, cam_proj);
		setUniform(texShad, 1, cam_view);
		setUniform(texShad, 2, triangle_model);
		setUniform(texShad, 3, testTexture, 0);
		setUniform(texShad, 4, lightDir);

		draw(texShad, triangle);
	}
	game.term();
	return 0;
}