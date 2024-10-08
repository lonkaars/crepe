#pragma once



class Engine{

public:
	Engine(int windowWith, int windowHeight);
	~Engine() = default;

	void loop();


private:
	int window_height;
	int window_width;
};
