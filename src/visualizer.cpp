#include "visualizer.h"

#include "visualizerimpl.h"

Visualizer::Visualizer():pimpl(new VisualizerImpl()){}
Visualizer::~Visualizer(){}

std::map<MouseFlag, pos> Visualizer::getClickPos(){
	return pimpl->getClickPos();
}
void Visualizer::flip(){
	pimpl->flip();
}
void Visualizer::add(std::unique_ptr<DrawableObj> obj){
	pimpl->add(std::move(obj));
}
