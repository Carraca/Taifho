#ifndef BOARD_H_
#define BOARD_H_

#include <vector>
#include <iostream>
#include <boost/shared_ptr.hpp>

class Vector_2D;
class Cell;

#include "cell.h"
#include "player_id.h"
#include "vector_2d.h"

class Board {
public:
	Board();

	const Cell& get_cell(Vector_2D position) const;
	Player_ID get_piece_ownership(Vector_2D position);
	boost::shared_ptr<Game_piece> get_cell_contents(Vector_2D position);
	void set_cell(Vector_2D position) const;

	void set_cell_contents(Vector_2D position, boost::shared_ptr<Game_piece> piece);

	void move_piece(Vector_2D initial, Vector_2D final);

	unsigned int get_x_size() const;
	unsigned int get_y_size() const;

	void print_board();
	Board clone();

	int num_of_pieces(Player_ID player);

private:
	std::vector<Cell> m_cells;

	static const unsigned int K_BOARD_X_SIZE;
	static const unsigned int K_BOARD_Y_SIZE;
};


#endif /* BOARD_H_ */
