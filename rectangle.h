#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle {
public:
	Rectangle() {}
	Rectangle(int x, int y, int width, int height) :
		x(x),
		y(y),
		width(width),
		height(height) {}
	const int getCenterX() const {
		return x + width / 2;
	}
	const int getCenterY() const {
		return x + height / 2;
	}
	const int getLeft() const {
		return x;
	}
	const int getRight() const {
		return x + width;
	}
	const int getTop() const {
		return y;
	}
	const int getBottom() const {
		return y + height;
	}
	const int getWidth() const {
		return width;
	}
	const int getHeight() const {
		return height;
	}
	const int getSide(sides::Side side) const {
		switch (side)
		{
		case sides::LEFT:
			return getLeft();
		case sides::RIGHT:
			return getRight();
		case sides::TOP:
			return getTop();
		case sides::BOTTOM:
			return getBottom();
		default:
			break;
		}
	}
	const bool collidesWith(const Rectangle &rectangle) const {
		return (this->getRight() >= rectangle.getLeft() &&
			this->getLeft() <= rectangle.getRight() &&
			this->getTop() <= rectangle.getBottom() &&
			this->getBottom() >= rectangle.getTop());
	}
	const bool isValidRectangle() const {
		return
			x >= 0 &&
			y >= 0 &&
			width >= 0 &&
			height >= 0;
	}
private:
	int x, y, width, height;
};

#endif // !RECTANGLE_H
