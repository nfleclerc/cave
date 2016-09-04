#include "player.h"
#include "graphics.h"

namespace player_constants {
	const float WALK_SPEED = 0.2f;
	const float GRAVITY = 0.002f;
	const float GRAVITY_CAP = 0.8f;
}

Player::Player() {}

Player::Player(Graphics &graphics, Vector2 spawnPoint) :
	AnimatedSprite(graphics, "MyChar.png", 0, 0, 16, 16, spawnPoint.x, spawnPoint.y, 100),
	dx(0),
	dy(0),
	facing(RIGHT),
	grounded(false)
{
	graphics.loadImage("MyChar.png");
	setupAnimations();
	playAnimation("RunRight");
}

void Player::draw(Graphics &graphics)
{
	AnimatedSprite::draw(graphics, x, y);
}

void Player::setupAnimations() {
	addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2());
	addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2());
	addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2());
	addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2());
}

const float Player::getX() const
{
	return x;
}

const float Player::getY() const
{
	return y;
}

void Player::handleTileCollisions(std::vector<Rectangle>& others)
{
	for (int i = 0; i < others.size(); i++)
	{
		sides::Side collisionSide = Sprite::getCollisionSide(others.at(i));
		if (collisionSide != sides::NONE) {
			switch (collisionSide)
			{
			case sides::TOP:
				y = others.at(i).getBottom() + 1;
				dy = 0;
				break;
			case sides::BOTTOM:
				y = others.at(i).getTop() - boundingBox.getHeight() - 1;
				dy = 0;
				grounded = true;
				break;
			case sides::LEFT:
				x = others.at(i).getRight() + 1;
				break;
			case sides::RIGHT:
				x = others.at(i).getLeft() - boundingBox.getWidth() - 1;
				break;
			default:
				break;
			}
		}
	}
}

void Player::animationDone(std::string currentAnimation) {
}

void Player::update(float elapsedTime) {

	//apply gravity
	if (dy <= player_constants::GRAVITY_CAP) {
		dy += player_constants::GRAVITY * elapsedTime;
	}

	x += dx * elapsedTime;
	y += dy * elapsedTime;
	AnimatedSprite::update(elapsedTime);
}

void Player::moveLeft()
{
	dx = -player_constants::WALK_SPEED;
	playAnimation("RunLeft");
	facing = LEFT;
}

void Player::moveRight()
{
	dx = player_constants::WALK_SPEED;
	playAnimation("RunRight");
	facing = RIGHT;
}

void Player::stopMoving()
{
	dx = 0;
	playAnimation(facing == RIGHT ? "IdleRight" : "IdleLeft");
}


