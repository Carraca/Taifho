#pragma once
#include "Mqueue.h"
#include "BoardEvent.h"
#include "game.h"
#include "vector_2d.h"


class logic_interface {
public:
	logic_interface();
	logic_interface(Game *g);

	void select(int player, Vector_2D pos);
	void generateAIMove(int player);
	void move(Vector_2D init, Vector_2D final);
	void pass(int player);

	Mqueue* queue();


private:
	Mqueue action_queue;
	boost::thread t;
	Game *game;

	int threaded;
};