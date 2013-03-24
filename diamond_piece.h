/*
 * diamond_piece.h
 *
 *  Created on: Apr 5, 2012
 *      Author: brode
 */

#ifndef DIAMOND_PIECE_H_
#define DIAMOND_PIECE_H_

#include "game_piece.h"
#include <vector>

class Diamond_piece: public Game_piece {
public:
  Diamond_piece(Vector_2D pos, Player_ID owner);
  virtual ~Diamond_piece();
  bool valid_move(Vector_2D move, Board& board);
  std::vector<Vector_2D> valid_moves(Board& board) const;
  std::vector<Vector_2D> generate_moves(Board& board) const;
  std::vector<Vector_2D> validate_moves(Board& board, std::vector<Vector_2D> moves) const;
  std::vector<Vector_2D> generate_jumps(Board& board) const;
  std::vector<Vector_2D> validate_jumps(Board& board, std::vector<Vector_2D> jumps) const;
  std::string get_textual_representation() const;

  virtual Diamond_piece* clone() {
  	return new Diamond_piece(*this);
  }

  virtual int worth() {
	return 3;
  }
};

#endif /* DIAMOND_PIECE_H_ */
