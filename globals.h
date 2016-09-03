#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int SCREENWIDTH = 640;
	const int SCREENHEIGHT = 480;
	const float SPRITESCALE = 2.0;
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct Vector2 {
	int x, y;
	Vector2() :
		x(0), y(0) {}
	Vector2(int x, int y) :
		x(x), y(y) {}
	Vector2 zero() {
		return Vector2();
	}
};

#endif // !GLOBALS_H

