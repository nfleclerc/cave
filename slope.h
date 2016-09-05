#ifndef SLOPE_H
#define SLOPE_H

#include "globals.h"
#include <cmath>
#include <iostream>

class Slope {
public:
	Slope() {}
	Slope(Vector2 p1, Vector2 p2) :
		p1(p1),
		p2(p2)
	{
		if (p2.x - p1.x != 0) {
			slope = (fabs(p2.y) - fabs(p1.y)) / (fabs(p2.x) - fabs(p1.x));
		}
	}
	const inline float getSlope() const {
		return slope;
	}
	const bool collidesWith(const Rectangle &other) const {
		return
			(other.getRight() >= this->p2.x &&
				other.getLeft() <= this->p1.x &&
				other.getTop() <= this->p2.y &&
				other.getBottom() >= this->p1.y) ||
				(other.getRight() >= this->p1.x &&
					other.getLeft() <= this->p2.x &&
					other.getTop() <= this->p1.y &&
					other.getBottom() >= this->p2.y) ||
					(other.getLeft() <= this->p1.x &&
						other.getRight() >= this->p2.x &&
						other.getTop() <= this->p1.y &&
						other.getBottom() >= this->p2.y) ||
						(other.getLeft() <= this->p2.x &&
							other.getRight() >= this->p1.x &&
							other.getTop() <= this->p2.y &&
							other.getBottom() >= this->p1.y);
	}
	const inline Vector2 getP1() const {
		return p1;
	}
	const inline Vector2 getP2() const {
		return p2;
	}
private:
	Vector2 p1;
	Vector2 p2;
	float slope;
};

#endif SLOPE_H