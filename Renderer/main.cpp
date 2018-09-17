#include "render.h"
#include "context.h"
#include "shaderReader.h"
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
	//upside down tri
	vertex triVerts2[] =
	{
		{ { .5f,.5f, 0, 1 } },
		{ { -.5f,.5f, 0, 1 } },
		{ { 0,-.5f, 0, 1 } }
	};
	unsigned triIndices[] = { 2,1,0 };
	geometry triangle = makeGeometry(triVerts, 3, triIndices, 3);
	//upside down tri
	geometry triangle2 = makeGeometry(triVerts2, 3, triIndices, 3);
	/*const char * basicVert =
		"#version 410\n"
		"layout (location = 0) in vec4 position;\n"
		"void main() {gl_Position = position;}";
	const char * basicFrag =
		"#version 330\n"
		"out vec4 vertColor;\n"
		"void main() {vertColor = vec4(1.0, 0.0, 0.0 ,1.0); }";
	shader basicShad = makeShader(basicVert, basicFrag);*/
	shader fileShad = makeShaderFrom("vertexShaderExample.txt", "fragmentShaderExample.txt");
	while (!game.shouldClose())
	{
		game.tick();
		draw(fileShad, triangle);
		//upside down tri
		draw(fileShad, triangle2);
	}
	game.term();
	return 0;
}