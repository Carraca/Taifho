#pragma once
#include "BoardEvent.h"

class WinEvent : public BoardEvent {
public:

	WinEvent();
	WinEvent(int p);

	bool isWin();

	int getPlayer();

private:
	int player;
};