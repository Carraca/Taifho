#ifndef TRIANGLE_PIECE_H_
#define TRIANGLE_PIECE_H_

#include <vector>
#include <stack>
#include <string>

class Board;
class Cell;

#include "board.h"

class Triangle_piece: public Game_piece {
public:
	Triangle_piece(Vector_2D pos, Player_ID ownership);
	virtual ~Triangle_piece();
	std::string get_textual_representation() const;
	bool valid_move( Vector_2D move, Board& board);
	std::vector<Vector_2D> valid_moves(Board& board) const;
	std::vector<Vector_2D> generate_moves(Board& board) const;
	std::vector<Vector_2D> validate_moves(Board& board, std::vector<Vector_2D> moves) const;
	std::vector<Vector_2D> generate_jumps(Board& board) const;
	std::vector<Vector_2D> validate_jumps(Board& board, std::vector<Vector_2D> jumps) const;

	virtual Triangle_piece* clone() {
		return new Triangle_piece(*this);
	}

	virtual int worth() {
	  return 2;
	}
};

#endif /* TRIANGLE_PIECE_H_ */
