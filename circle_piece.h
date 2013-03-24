#ifndef CIRCLEPIECE_H_
#define CIRCLEPIECE_H_

#include <vector>
#include <stack>
#include <string>

class Board;
class Cell;

#include "board.h"

class Circle_piece: public Game_piece {
public:
	Circle_piece(Vector_2D pos, Player_ID owner);
	virtual ~Circle_piece();
	bool valid_move(Vector_2D move, Board& board);
	std::vector<Vector_2D> valid_moves(Board& board) const;
	std::vector<Vector_2D> generate_moves(Board& board) const;
	std::vector<Vector_2D> validate_moves(Board& board, std::vector<Vector_2D> moves) const;
	std::vector<Vector_2D> generate_jumps(Board& board) const;
	std::vector<Vector_2D> validate_jumps(Board& board, std::vector<Vector_2D> jumps) const;
	std::string get_textual_representation() const;

	virtual Circle_piece* clone() {
		return new Circle_piece(*this);
	}

	virtual int worth() {
		return 4;
	}
};

#endif /* CIRCLEPIECE_H_ */
