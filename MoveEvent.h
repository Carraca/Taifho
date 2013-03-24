#pragma once
#include "BoardEvent.h"
#include "vector_2d.h"

class MoveEvent : public BoardEvent {
public:
	MoveEvent();
	MoveEvent(Vector_2D i, Vector_2D f);

	bool isMove();
	
	
	Vector_2D getInit();
	Vector_2D getFinal();

private:
	Vector_2D init,final;
	
};

