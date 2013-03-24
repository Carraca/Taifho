#include "logic_interface.h"
#include "AvailableMovesEvent.h"
#include "MoveEvent.h"
#include "WinEvent.h"
#include "turnEvent.h"
#include "ProcessingEvent.h"

logic_interface::logic_interface() {

}

logic_interface::logic_interface(Game *g) {
	this->game = g;
	threaded = 1;

}

void select_t(int player, Vector_2D pos, Game* g, Mqueue* q, int* t) {

	if (/*g->getTurn()==player &&*/g->getBoard()->get_piece_ownership(pos)
			== g->getTurn()) {

		std::vector<Vector_2D> moves;
		moves = g->getBoard()->get_cell_contents(pos)->valid_moves(
				*g->getBoard());
		BoardEvent *e = new AvailableMovesEvent(moves, pos);
		q->push(e);
	}
	++*t;
}

void generateAIMove_t(int player, Game* g, Mqueue* q, int* t) {

	bool next_is_cpu;
	do {
		next_is_cpu = false;

		BoardEvent *e2 = new TurnEvent(g->getTurn());
		q->push(e2);

		if (g->has_moves()) {

			BoardEvent *e4 = new ProcessingEvent();
			q->push(e4);

			AI_move_result result = g->ai_move();

			std::cout << "Time elapsed: " << result.time << '\n';
			std::cout << "Nodes evaluated: " << result.nodes_evaluated << '\n';
			std::cout << "Move: " << result.move.initial().x() << ", "
					<< result.move.initial().y() << " to "
					<< result.move.final().x() << ", "
					<< result.move.final().y() << '\n';

			std::cout << "Value:\n";
			if (result.value.size() == 4) {
				std::cout << "\t1: " << result.value[0] << '\n';
				std::cout << "\t2: " << result.value[1] << '\n';
				std::cout << "\t3: " << result.value[2] << '\n';
				std::cout << "\t4: " << result.value[3] << '\n';
			} else {
				std::cout << "\tpval: " << result.pvalue << '\n';
			}

			std::vector<Vector_2D> moves = g->path(result.move.initial(),
					result.move.final());
			g->move(result.move.initial(), result.move.final());
			g->getBoard()->print_board();
			if (moves.size() < 3) {
				BoardEvent *e = new MoveEvent(result.move.initial(),
						result.move.final());
				q->push(e);
			} else
				for (int i = 0; i < moves.size() - 1; ++i) {
					BoardEvent *e = new MoveEvent(moves.at(i), moves.at(i + 1));
					q->push(e);
				}

			int winner = g->end_from_move(result.move.final());
			if (winner != NO_PLAYER) {
				BoardEvent *e2 = new WinEvent(winner);
				q->push(e2);
				++*t;
				return;
			}
		}

		do {

			if (g->getNextTurn() == 0) {
				next_is_cpu = true;
				player = g->getTurn();
			} else {

				BoardEvent *e3 = new TurnEvent(g->getTurn());
				q->push(e3);

			}
		} while (!g->has_moves());

	} while (next_is_cpu);
	++*t;
}

void move_t(Vector_2D init, Vector_2D final, Game* g, Mqueue* q, int* t) {
	std::vector<Vector_2D> moves = g->path(init, final);
	if (g->move(init, final)) {

		//BoardEvent *e =  new MoveEvent(init,final);
		//q->push(e);

		if (moves.size() < 3) {
			BoardEvent *e = new MoveEvent(init, final);
			q->push(e);
		} else
			for (int i = 0; i < moves.size() - 1; ++i) {
				BoardEvent *e = new MoveEvent(moves.at(i), moves.at(i + 1));
				q->push(e);
			}

		int winner = g->end_from_move(final);
		if (winner != NO_PLAYER) {
			BoardEvent *e2 = new WinEvent(winner);
			q->push(e2);
			++*t;
			return;
		}

		do {
			int p = g->getNextTurn();

			if (p == 1) //human
					{
				BoardEvent *e3 = new TurnEvent(g->getTurn());
				q->push(e3);
			} else {
				generateAIMove_t(g->getTurn(), g, q, t);
				break;
			}
		} while (!g->has_moves());
	}
	++*t;
}

void pass_t(int player, Game* g, Mqueue* q, int* t) {
	++*t;
}

void logic_interface::select(int player, Vector_2D pos) {
	if (threaded != 0) {
		--threaded;

		boost::thread(&select_t, player, pos, game, &action_queue, &threaded);
	}
}

void logic_interface::generateAIMove(int player) {
	if (threaded != 0) {
		--threaded;

		boost::thread(&generateAIMove_t, player, game, &action_queue,
				&threaded);
	}
}

void logic_interface::move(Vector_2D init, Vector_2D final) {
	if (threaded != 0) {
		--threaded;

		boost::thread(&move_t, init, final, game, &action_queue, &threaded);
	}
}

void logic_interface::pass(int player) {

}

Mqueue* logic_interface::queue() {
	return &action_queue;
}

