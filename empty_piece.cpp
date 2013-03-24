/*
 * emptypiece.cpp
 *
 *  Created on: Apr 30, 2012
 *      Author: ei10001
 */

#include "empty_piece.h"

Empty_piece::Empty_piece(Vector_2D pos) {
	set_position(pos);
	set_ownership(NO_PLAYER);
}

Empty_piece::~Empty_piece() {
	// TODO Auto-generated destructor stub
}

std::string Empty_piece::get_textual_representation() const {
	return "_";
}

std::vector<Vector_2D> Empty_piece::generate_moves(Board& board) const {
	return std::vector<Vector_2D>();
}
std::vector<Vector_2D> Empty_piece::validate_moves(Board& board, std::vector<Vector_2D> moves) const {
	return std::vector<Vector_2D>();
}
std::vector<Vector_2D> Empty_piece::generate_jumps(Board& board) const {
	return std::vector<Vector_2D>();
}
std::vector<Vector_2D> Empty_piece::validate_jumps(Board& board, std::vector<Vector_2D> jumps) const {
	return std::vector<Vector_2D>();
}

bool Empty_piece::valid_move(Vector_2D move, Board& board) {
	return false;
}

std::vector<Vector_2D> Empty_piece::valid_moves(Board& board) const {
	return std::vector<Vector_2D>();
}
