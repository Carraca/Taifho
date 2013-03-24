/*
 * emptypiece.h
 *
 *  Created on: Apr 30, 2012
 *      Author: ei10001
 */

#ifndef EMPTY_PIECE_H_
#define EMPTY_PIECE_H_

#include "game_piece.h"

class Empty_piece: public Game_piece {
public:
	Empty_piece(Vector_2D pos);
	virtual ~Empty_piece();
	std::string get_textual_representation() const;

	std::vector<Vector_2D> valid_moves(Board& board) const;

	std::vector<Vector_2D> generate_moves(Board& board) const;
	std::vector<Vector_2D> validate_moves(Board& board, std::vector<Vector_2D> moves) const;
	std::vector<Vector_2D> generate_jumps(Board& board) const;
	std::vector<Vector_2D> validate_jumps(Board& board, std::vector<Vector_2D> jumps) const;

	bool valid_move(Vector_2D move, Board& board);

	virtual Empty_piece* clone() {
		return new Empty_piece(*this);
	}

	virtual int worth() {
		return 0;
	}
};

#endif /* EMPTY_PIECE_H_ */
