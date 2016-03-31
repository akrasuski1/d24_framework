#ifndef COLOR_H_
#define COLOR_H_

#include <cstdint>

struct Color{
	uint8_t rgb[3];
};

namespace Colors{
	extern Color black;
	extern Color red;
	extern Color green;
	extern Color blue;
	extern Color yellow;
	extern Color pink;
	extern Color cyan;
	extern Color white;

	extern Color navy;
	extern Color dgreen;
	extern Color maroon;
	extern Color purple;
	extern Color olive;

	extern Color grey;

	extern Color violet;
	extern Color orange;
	extern Color brown;
}

#endif
