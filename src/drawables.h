#include "pos_size.h"

// Forward declaration.
class VisualizerImpl;

// Drawable object interface.
class DrawableObj{
public:
	virtual void draw(VisualizerImpl& visu)=0;
	virtual ~DrawableObj() = default;
};

// Rectangle centered at p, with sides sz.
class DrawableRectangle:public DrawableObj{
public:
	DrawableRectangle(pos p, size sz, Color c);
	void draw(VisualizerImpl& visu);
private:
	pos p;
	size sz;
	Color color;
};

// Circle centered at p, with given diameter.
class DrawableCircle:public DrawableObj{
public:
	DrawableCircle(pos p, double diameter, Color c);
	void draw(VisualizerImpl& visu);
private:
	pos p;
	double diameter;
	Color color;
};

// Line from p1 to p2.
class DrawableLine:public DrawableObj{
public:
	DrawableLine(pos p1, pos p2, Color c);
	void draw(VisualizerImpl& visu);
private:
	pos p1, p2;
	Color color;
};
