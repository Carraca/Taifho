#include "game_piece.h"

Vector_2D Game_piece::generate_north_movement(Board& board) const {
	return Vector_2D(get_position().x(), get_position().y() - 1);
}

Vector_2D Game_piece::generate_northeast_movement(Board& board) const {
	return Vector_2D(get_position().x() + 1, get_position().y() - 1);
}

Vector_2D Game_piece::generate_east_movement(Board& board) const {
	return Vector_2D(get_position().x() + 1, get_position().y());
}

Vector_2D Game_piece::generate_southeast_movement(Board& board) const {
	return Vector_2D(get_position().x() + 1, get_position().y() + 1);
}

Vector_2D Game_piece::generate_south_movement(Board& board) const {
	return Vector_2D(get_position().x(), get_position().y() + 1);
}

Vector_2D Game_piece::generate_southwest_movement(Board& board) const {
	return Vector_2D(get_position().x() - 1, get_position().y() + 1);
}

Vector_2D Game_piece::generate_west_movement(Board& board) const {
	return Vector_2D(get_position().x() - 1, get_position().y());
}

Vector_2D Game_piece::generate_northwest_movement(Board& board) const {
	return Vector_2D(get_position().x() - 1, get_position().y() - 1);
}

Vector_2D Game_piece::generate_north_jump(Board& board) const {
	return Vector_2D(get_position().x(), get_position().y() - 2);
}

Vector_2D Game_piece::generate_northeast_jump(Board& board) const {
	return Vector_2D(get_position().x() + 2, get_position().y() - 2);
}

Vector_2D Game_piece::generate_east_jump(Board& board) const {
	return Vector_2D(get_position().x() + 2, get_position().y());
}

Vector_2D Game_piece::generate_southeast_jump(Board& board) const {
	return Vector_2D(get_position().x() + 2, get_position().y() + 2);
}

Vector_2D Game_piece::generate_south_jump(Board& board) const {
	return Vector_2D(get_position().x(), get_position().y() + 2);
}

Vector_2D Game_piece::generate_southwest_jump(Board& board) const {
	return Vector_2D(get_position().x() - 2, get_position().y() + 2);
}

Vector_2D Game_piece::generate_west_jump(Board& board) const {
	return Vector_2D(get_position().x() - 2, get_position().y());
}

Vector_2D Game_piece::generate_northwest_jump(Board& board) const {
	return Vector_2D(get_position().x() - 2, get_position().y() - 2);
}

bool Game_piece::valid_movement_destination_cell(Vector_2D move, Board& board) const {

	bool borders=false;
	

	if(ownership==1){
		if(move.x()>=board.get_x_size()-1 || move.x()<=0 || (move.y() == 0 && position.y() != 0))
			borders=true;
		
	}
	else if(ownership==2){
		if(move.x()>=board.get_x_size()-1 || move.x()<=0 || (move.y() == board.get_y_size()-1 && position.y() != board.get_y_size()-1))
			borders=true;
		
	}
	else if(ownership==3){
		if((move.x()==board.get_x_size()-1 && position.x()!=board.get_x_size()-1) || move.y() == board.get_y_size()-1 || move.y() == 0)
			borders=true;
		
	}
	else if(ownership==4){
		if((move.x()==0 && position.x()!=0) || move.y() == board.get_y_size()-1 || move.y() == 0)
			borders=true;
		
	}

	return board.get_piece_ownership(move) == NO_PLAYER && !borders;
}

bool Game_piece::valid_jump_destination_cell(Vector_2D move, Board& board) const {

	Player_ID middleship = board.get_piece_ownership(Vector_2D((position.x() + move.x())/2, (position.y() + move.y())/2));

	bool borders=false;

	if(ownership==1){
		if(move.x()>=board.get_x_size()-1 || move.x()<=0 || (move.y() == 0 && position.y() != 0))
			borders=true;
		
	}
	else if(ownership==2){
		if(move.x()>=board.get_x_size()-1 || move.x()<=0 || (move.y() == board.get_y_size()-1 && position.y() != board.get_y_size()-1))
			borders=true;
		
	}
	else if(ownership==3){
		if((move.x()==board.get_x_size()-1 && position.x()!=board.get_x_size()-1) || move.y() == board.get_y_size()-1 || move.y() == 0)
			borders=true;
		
	}
	else if(ownership==4){
		if((move.x()==0 && position.x()!=0) || move.y() == board.get_y_size()-1 || move.y() == 0)
			borders=true;
		
	}

	return board.get_piece_ownership(move) == NO_PLAYER && middleship != ownership && middleship != NO_PLAYER && !borders;
}

bool Game_piece::valid_limits(Vector_2D move, Board& board) const {
	return move.x() < board.get_x_size() && move.x() >= 0 && move.y() < board.get_y_size() && move.y() >= 0;
}

bool Game_piece::valid_movement_destination_and_limits(Vector_2D move, Board& board) const {
	return valid_limits(move, board) && valid_movement_destination_cell(move, board);
}

bool Game_piece::valid_jump_destination_and_limits(Vector_2D move, Board& board) const {
	return valid_limits(move, board) && valid_jump_destination_cell(move, board);
}

Player_ID Game_piece::get_ownership() const {
	return ownership;
}

void Game_piece::set_ownership(Player_ID owner) {
	ownership = owner;
}

Vector_2D Game_piece::get_position() const {
	return position;
}

void Game_piece::set_position(Vector_2D pos) {
	position = pos;
}

bool Game_piece::member_of(Vector_2D move, std::vector<Vector_2D> moves) {
	for (unsigned int i = 0; i < moves.size(); i++) {
		if (moves.at(i) == move) {
			return true;
		}
	}
	return false;
}
