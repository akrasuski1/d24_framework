#include "visualizerimpl.h"

#include <chrono>

VisualizerImpl::VisualizerImpl():
	window(800,600,1,3,0),
	display(window, "Visualization"),
	zoom(30.0),
	offset({-zoom/2,-zoom/2}),
	clickPos(),
	running(true),
	drawing_thread([this](){this->loop();})
{}

VisualizerImpl::~VisualizerImpl(){
	running=false;
	drawing_thread.join();
}

void VisualizerImpl::add(std::unique_ptr<DrawableObj> obj){
	backlog.push_back(std::move(obj));
}

std::map<MouseFlag, pos> VisualizerImpl::getClickPos(){
	std::lock_guard<std::mutex> lock(mtx);
	return clickPos;
}

void VisualizerImpl::flip(){
	std::lock_guard<std::mutex> lock(mtx);
	objects.clear();
	std::swap(objects, backlog);
}

size VisualizerImpl::toWindowSize(size sz){
	sz.x*=zoom;
	sz.y*=zoom;
	return sz;
}

pos VisualizerImpl::toWindowPos(pos p){
	p.x*=zoom;
	p.x-=offset.x;

	p.y*=zoom;
	p.y-=offset.y;

	return p;
}
pos VisualizerImpl::fromWindowPos(pos p){
	p.x+=offset.x;
	p.x/=zoom;

	p.y+=offset.y;
	p.y/=zoom;

	return p;
}

void VisualizerImpl::moveWindow(pos world, pos p){
	offset.x=world.x*zoom-p.x;
	offset.y=world.y*zoom-p.y;
}

void VisualizerImpl::dispatchEvents(){
	unsigned int nowClick=display.button();
	MouseFlag mf=static_cast<MouseFlag>(0);
	pos mpos={double(display.mouse_x()), double(display.mouse_y())};
	pos wpos=fromWindowPos(mpos);

	int wheel=display.wheel();
	display.set_wheel();
	wpos=fromWindowPos(mpos);
	for(;wheel>0;wheel--){zoom*=1.05;}
	for(;wheel<0;wheel++){zoom/=1.05;}
	moveWindow(wpos, mpos);

	bool anyMod=false;
	if(display.is_keyCTRLLEFT() || display.is_keyCTRLRIGHT()){
		mf=mf|MouseFlag::ctrl;
		anyMod=true;
	}
	if(display.is_keySHIFTLEFT() || display.is_keySHIFTRIGHT()){
		mf=mf|MouseFlag::shift;
		anyMod=true;
	}
	for(int but=0;but<3;but++){
		bool last = lastClick & (1<<but);
		bool now  = nowClick  & (1<<but);
		if(but==1 && anyMod==false){
			// Right click with no modifiers.
			if(!last && now){ // Rising edge.
				dragPos=fromWindowPos(mpos);
			}
			if(now){ // Dragging.
				moveWindow(dragPos, mpos);
			}
		}
		else if(!last && now){ // Rising edge.
			std::lock_guard<std::mutex> lock(mtx);
			MouseFlag mflag=mf|static_cast<MouseFlag>(but);
			if(clickPos.count(mflag)){
				clickPos.erase(mflag);
			}
			else{
				clickPos[mflag]=wpos;
			}
		}
	}
	lastClick=nowClick;
}

void VisualizerImpl::draw(){
	{
		std::lock_guard<std::mutex> lock(mtx);
		window.fill(32);
		for(auto& drawable : objects){
			drawable->draw(*this);
		}
	}
	for(auto& mouse : getClickPos()){
		Color col={0,0,0};
		DrawableCircle(mouse.second, 0.4, col).draw(*this);
		col.rgb[0]=255;
		if(static_cast<bool>(mouse.first & MouseFlag::shift)){col.rgb[1]+=160;}
		if(static_cast<bool>(mouse.first & MouseFlag::ctrl)) {col.rgb[1]+=80;}
		col.rgb[2]=63+64*(static_cast<uint8_t>(mouse.first) & 3);
		DrawableCircle(mouse.second, 0.3, col).draw(*this);
	}
	window.display(display);
}

void VisualizerImpl::loop(){
	using std::chrono::system_clock;
	auto prevFrame=system_clock::now();
	auto frameDur=std::chrono::milliseconds(25);
	while(!display.is_closed() && running){
		auto time_taken=system_clock::now()-prevFrame;
		std::this_thread::sleep_for(frameDur-time_taken);
		auto wall_time=system_clock::now()-prevFrame;
		prevFrame=system_clock::now();
		auto dur=std::chrono::duration_cast<std::chrono::duration<double>>(time_taken).count();
		auto dur_wall=std::chrono::duration_cast<std::chrono::duration<double>>(wall_time).count();
		int fps=int(1/dur_wall+0.5);
		display.set_title("Visualization real FPS: %d @ %.3lfms per frame\n", fps, dur);

		dispatchEvents();
		draw();

	}
}
