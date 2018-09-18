#include "render.h"
#include "context.h"
#include "shaderReader.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <iostream>
int main()
{
	context game;
	game.init(800, 600, "Banana");
	vertex triVerts[] = 
	{
		{{-.5f,-.5f, 0, 1}},
		{{ .5f,-.5f, 0, 1 }},
		{{ 0,.5f, 0, 1 }}
	};
	unsigned triIndices[] = { 2,1,0 };
	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);
	shader fileShad = makeShaderFrom("vertexShaderExample.txt", "fragmentShaderExample.txt");
	shader mvpShad = makeShaderFrom("mvpVert.txt", "fragmentShaderExample.txt");
	glm::mat4 cam_proj = glm::perspective(glm::radians(45.f), 800.0f / 600.0f, 0.1f, 1000.0f);
	glm::mat4 cam_view = glm::lookAt(glm::vec3(0, 0, -1), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 triangle_model = glm::identity<glm::mat4>();
	while (!game.shouldClose())
	{
		game.tick();
		game.clear();

		triangle_model = glm::rotate(triangle_model, glm::radians(5.f), glm::vec3(0, 1, 0));

		setUniform(mvpShad, 0, cam_proj);
		setUniform(mvpShad, 1, cam_view);
		setUniform(mvpShad, 2, triangle_model);
		draw(mvpShad, triangle);
	}
	game.term();
	return 0;
}