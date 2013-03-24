#pragma once
#include "BoardEvent.h"
#include <vector>
#include "vector_2d.h"

class AvailableMovesEvent : public BoardEvent {
public:

	AvailableMovesEvent();
	AvailableMovesEvent(std::vector<Vector_2D> m, Vector_2D own);

	bool isAvailableMoves();
	
	std::vector<Vector_2D> getMoves();
	Vector_2D getOwn();

private:
	std::vector<Vector_2D> moves;
	Vector_2D own;
};