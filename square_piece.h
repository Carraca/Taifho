/*
 * Squarepiece.h
 *
 *  Created on: Apr 5, 2012
 *      Author: brode
 */

#ifndef SQUAREPIECE_H_
#define SQUAREPIECE_H_

#include "game_piece.h"

class Square_piece: public Game_piece {
public:
  Square_piece(Vector_2D pos, Player_ID owner);
  virtual ~Square_piece();
  std::string get_textual_representation() const ;
  bool valid_move(Vector_2D move, Board& board);
  std::vector<Vector_2D> generate_moves(Board& board) const;
  std::vector<Vector_2D> validate_moves(Board& board, std::vector<Vector_2D> moves) const;
  std::vector<Vector_2D> generate_jumps(Board& board) const;
  std::vector<Vector_2D> validate_jumps(Board& board, std::vector<Vector_2D> jumps) const;
  std::vector<Vector_2D> valid_moves(Board& board) const;

  virtual Game_piece* clone() {
  	return new Square_piece(*this);
  }

  virtual int worth() {
	  return 1;
  }
};

#endif /* SQUAREPIECE_H_ */
