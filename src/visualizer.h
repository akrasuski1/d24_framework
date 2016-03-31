#ifndef VISUALIZER_H_
#define VISUALIZER_H_

#include "color.h"
#include "drawables.h"
#include "pos_size.h"

#include <memory>
#include <map>

// Forward declaration.
class VisualizerImpl;

// Bit flags describing mouse click - mouse button and modifier keys.
enum class MouseFlag : uint8_t{
	left   = 0x0,
	right  = 0x1,
	middle = 0x2,

	ctrl   = 0x4,
	shift  = 0x8
};
inline MouseFlag operator| (MouseFlag a, MouseFlag b){
	return static_cast<MouseFlag>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}
inline MouseFlag operator& (MouseFlag a, MouseFlag b){
	return static_cast<MouseFlag>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

// Visualizer class.
class Visualizer{
public:

	Visualizer();
	~Visualizer();
	
	// Returns current cursor marks with their mouse flags as index,
	// and position on the map as the value.
	std::map<MouseFlag, pos> getClickPos();

	// Add an object to current scene.
	void add(std::unique_ptr<DrawableObj> obj);
	// Commit current scene (make it actually appear). This should be
	// the last thing executed after adding all the objects.
	void flip();
private:
	std::unique_ptr<VisualizerImpl> pimpl;
};

#endif
