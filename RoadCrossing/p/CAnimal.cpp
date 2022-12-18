#include "CAnimal.h"

CAnimal::CAnimal()
{
	pos.x = 0;
	pos.y = 0;
	direction = 0;
}
CAnimal::CAnimal(int x, int y)
{
	pos.x = x;
	pos.y = y;
	direction = 0;
}
Point CAnimal::getPos() const
{
	return pos;
}
void CAnimal::setPos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
}
bool CAnimal::getDirection() const
{
	return direction;
}
void CAnimal::setDirection(bool direction)
{
	this->direction = direction;
}
void CAnimal::Move()
{
	pos.x--;
}
void CAnimal::deleteAnimal(ConsoleHandle& handle)
{
	if (pos.x == 20)
	{
		handle.eraseGraphic(pos.x, pos.y, getHeight(), getLength() + 1, 0, 33, 162);
		return;
	}
	handle.eraseGraphic(pos.x + getLength(), pos.y, getHeight(), 1, 0, 33, 162);
}