/*
 * game.h
 */

#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include <ctime>
#include <limits>

#include "circle_piece.h"
#include "board.h"
#include "move.h"
#include <algorithm>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/undirected_graph.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

enum Reordering {
	NO_REORDERING,
	KILLER
};

enum Algorithm {
	MINIMAX,
	MINIMAX_AB,
	NEGASCOUT,
	GREEDY
};

enum Heuristic {
	N_PIECES_DISTANCE_WEIGHTED,
	N_PIECES_DISTANCE_AND_VALUE_WEIGHTED
};

enum Difficulty {
	EASY,
	MEDIUM,
	HARD
};

struct AI_move_result {
	Move move;
	unsigned int time;
	unsigned int nodes_evaluated;
	std::vector<int> value;
	int pvalue;
};

struct AI_details {
	Heuristic heuristic;
	Algorithm algo;
	Reordering reordering;
	Difficulty difficulty;
};

class Game {
public:
	Game(std::vector<int> players, std::vector<AI_details> ai_details);
	int go(); //TODO stub
	Player_ID end(Board &board);
	Player_ID end_from_move(Vector_2D mv);
	Board* getBoard();
	bool move(Vector_2D init, Vector_2D final);
	Player_ID getTurn();
	Player_ID getNextTurn();
	std::vector<Vector_2D> path(Vector_2D init, Vector_2D final);

	AI_move_result ai_move();
	bool has_moves();
private:
	AI_move_result n_player_minimax(Player_ID current_player, Board &board, int depth);
	AI_move_result minimax(Player_ID current_player, Board &board, int depth);
	AI_move_result minimax_ab(Player_ID current_player, Board &board, int depth, int alpha, int beta, int color);
	AI_move_result negascout(Player_ID current_player, Board &board, int depth, int alpha, int beta);

	std::vector<Move> get_moves_for_player(Board &board, Player_ID player);

	int heuristic_distance(Player_ID player, Board &b, bool value);
	int heuristic_distance_value(Player_ID player, Board &b);
	std::vector<int> eval_board_n_player(Board &board, Heuristic heur);

	int vector_max(std::vector<int> v, int index);

	Board board;
	Player_ID turn;
	std::vector<int> players;
	std::vector<AI_details> ai_details;
	int curval;
};

#endif /* GAME_H_ */
