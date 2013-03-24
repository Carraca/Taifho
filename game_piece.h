/*
 * game_piece.h
 */

#ifndef GAME_PIECE_H_
#define GAME_PIECE_H_

#include <string>
#include <vector>

class Vector_2D;
class Board;

#include "cell.h"
#include "vector_2d.h"
#include "player_id.h"
#include "board.h"

class Game_piece {
public:
	virtual std::string get_textual_representation() const = 0 ;

	Player_ID get_ownership() const;
	void set_ownership(Player_ID owner);
	Vector_2D get_position() const;
	void set_position(Vector_2D move);

	virtual Game_piece* clone() = 0;
	virtual int worth() = 0;

	virtual std::vector<Vector_2D> generate_moves(Board& board) const = 0;
	virtual std::vector<Vector_2D> validate_moves(Board& board, std::vector<Vector_2D> moves) const = 0;
	virtual std::vector<Vector_2D> generate_jumps(Board& board) const = 0;
	virtual std::vector<Vector_2D> validate_jumps(Board& board, std::vector<Vector_2D> jumps) const = 0;
	virtual std::vector<Vector_2D> valid_moves(Board& board) const = 0;

	virtual bool valid_move(Vector_2D move, Board& board) = 0;

	Vector_2D generate_north_movement(Board& board) const;
	Vector_2D generate_north_jump(Board& board) const;

	Vector_2D generate_northeast_movement(Board& board) const;
	Vector_2D generate_northeast_jump(Board& board) const;

	Vector_2D generate_east_movement(Board& board) const;
	Vector_2D generate_east_jump(Board& board) const;

	Vector_2D generate_southeast_movement(Board& board) const;
	Vector_2D generate_southeast_jump(Board& board) const;

	Vector_2D generate_south_movement(Board& board) const;
	Vector_2D generate_south_jump(Board& board) const;

	Vector_2D generate_southwest_movement(Board& board) const;
	Vector_2D generate_southwest_jump(Board& board) const;

	Vector_2D generate_west_movement(Board& board) const;
	Vector_2D generate_west_jump(Board& board) const;

	Vector_2D generate_northwest_movement(Board& board) const;
	Vector_2D generate_northwest_jump(Board& board) const;

	bool valid_limits(Vector_2D move, Board& board) const;

	bool valid_movement_destination_cell(Vector_2D move, Board& board) const;
	bool valid_jump_destination_cell(Vector_2D move, Board& board) const;

	bool valid_movement_destination_and_limits(Vector_2D move, Board& board) const;
	bool valid_jump_destination_and_limits(Vector_2D move, Board& board) const;

	bool member_of(Vector_2D move, std::vector<Vector_2D> moves);

private:
	Vector_2D position;
	Player_ID ownership;
};

#endif /* GAME_PIECE_H_ */
