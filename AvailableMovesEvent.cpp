#include "AvailableMovesEvent.h"

AvailableMovesEvent::AvailableMovesEvent()
{

}

AvailableMovesEvent::AvailableMovesEvent( std::vector<Vector_2D> m, Vector_2D own)
{
	moves = m;
	this->own=own;
}

bool AvailableMovesEvent::isAvailableMoves()
{
	return true;
}


std::vector<Vector_2D> AvailableMovesEvent::getMoves()
{
	return moves;
}

Vector_2D AvailableMovesEvent::getOwn()
{
	return own;
}

