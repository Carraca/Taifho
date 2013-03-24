#pragma once
#include "BoardEvent.h"
#include "vector_2d.h"

class PassEvent : public BoardEvent {
public:
	PassEvent();
	PassEvent(int player);

	bool isPass();

private:
	int player;

};

