#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
	const int SCREENWIDTH = 640;
	const int SCREENHEIGHT = 480;
	const float SPRITESCALE = 2.0;
}

namespace sides {
	enum Side {
		LEFT, RIGHT, TOP, BOTTOM, NONE
	};
	inline Side getOppositeSide(Side side) {
		switch (side)
		{
		case sides::LEFT:
			return sides::RIGHT;
		case sides::RIGHT:
			return sides::LEFT;
		case sides::TOP:
			return sides::BOTTOM;
		case sides::BOTTOM:
			return sides::TOP;
		default:
			break;
		}
	}
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

