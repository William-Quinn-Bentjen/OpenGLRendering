#pragma once
class context
{
	struct GLFWwindow * window;
public: 
	bool init(int width, int height, const char * title);
	void tick();
	void term();

	bool shouldClose() const;
};