#ifndef VISUALIZERIMPL_H_
#define VISUALIZERIMPL_H_

#include "visualizer.h"

#include "CImg.h"
#include "color.h"
#include "pos_size.h"

#include <cstdint>
#include <thread>
#include <mutex>
#include <vector>


class VisualizerImpl{
	friend class Visualizer;

	std::map<MouseFlag, pos> getClickPos();
	void flip();
	
	void add(std::unique_ptr<DrawableObj> obj);

	void draw();
	void dispatchEvents();
	void loop();

	pos fromWindowPos(pos p);
	void moveWindow(pos world, pos p);
	
public:
	cimg_library::CImg<uint8_t> window;
	cimg_library::CImgDisplay display;

private:
	std::vector<std::unique_ptr<DrawableObj>> objects;
	std::vector<std::unique_ptr<DrawableObj>> backlog;
	double zoom;
	pos offset;
	std::map<MouseFlag, pos> clickPos;
	unsigned int lastClick=0;
	pos dragPos;

	bool running;
	std::mutex mtx;
	std::thread drawing_thread;

public:
	VisualizerImpl();
	~VisualizerImpl();
	size toWindowSize(size sz);
	pos toWindowPos(pos p);
};

#endif
