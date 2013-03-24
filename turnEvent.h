#pragma once
#include "BoardEvent.h"

class TurnEvent : public BoardEvent {
public:

	TurnEvent();
	TurnEvent(int p);

	bool isTurn();

	int getPlayer();

private:
	int player;
};