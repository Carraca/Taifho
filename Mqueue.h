#pragma once
#include <queue>
#include "BoardEvent.h"
#include <boost/thread.hpp>

class Mqueue{
public:
	void push(BoardEvent* e);
	bool empty();
	BoardEvent* pop();

private:
	std::queue<BoardEvent*> events;
	boost::mutex mut;
};