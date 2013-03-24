#include "circle_piece.h"

Circle_piece::Circle_piece(Vector_2D pos,Player_ID owner) {
	set_position(pos);
	set_ownership(owner);
}

Circle_piece::~Circle_piece() {
	// TODO Auto-generated destructor stub
}

std::string Circle_piece::get_textual_representation() const {
	return "o";
}

bool Circle_piece::valid_move(Vector_2D move, Board& board) {
	return member_of(move, valid_moves(board));
}

std::vector<Vector_2D> Circle_piece::generate_moves(Board& board) const {
	std::vector<Vector_2D> moves;
	moves.push_back(generate_north_movement(board));
	moves.push_back(generate_northeast_movement(board));
	moves.push_back(generate_east_movement(board));
	moves.push_back(generate_southeast_movement(board));
	moves.push_back(generate_south_movement(board));
	moves.push_back(generate_southwest_movement(board));
	moves.push_back(generate_west_movement(board));
	moves.push_back(generate_northwest_movement(board));
	return moves;
}

std::vector<Vector_2D> Circle_piece::validate_moves(Board& board, std::vector<Vector_2D> moves) const{
	for (unsigned int i = 0; i < moves.size(); i++) {
		if (!valid_movement_destination_and_limits(moves.at(i), board)) {
			moves.erase(moves.begin() + i--);
		}
	}
	return moves;
}

std::vector<Vector_2D> Circle_piece::generate_jumps(Board& board) const{
	std::vector<Vector_2D> jumps;
	jumps.push_back(generate_north_jump(board));
	jumps.push_back(generate_northeast_jump(board));
	jumps.push_back(generate_east_jump(board));
	jumps.push_back(generate_southeast_jump(board));
	jumps.push_back(generate_south_jump(board));
	jumps.push_back(generate_southwest_jump(board));
	jumps.push_back(generate_west_jump(board));
	jumps.push_back(generate_northwest_jump(board));
	return jumps;
}

std::vector<Vector_2D> Circle_piece::validate_jumps(Board& board, std::vector<Vector_2D> jumps) const{
	for (unsigned int i = 0; i < jumps.size(); i++) {
		if (!valid_jump_destination_and_limits(jumps.at(i), board))
			jumps.erase(jumps.begin() + i--);
	}
	return jumps;
}

std::vector<Vector_2D> Circle_piece::valid_moves(Board& board) const {
	std::vector<Vector_2D> moves = generate_moves(board);
	std::vector<Vector_2D> valid_moves = validate_moves(board, moves);
	std::vector<Vector_2D> jumps = generate_jumps(board);
	std::vector<Vector_2D> visited;
	std::vector<Vector_2D> to_visit = validate_jumps(board, jumps);
	std::vector<Vector_2D> possible_jumps;

	Circle_piece p = Circle_piece(*this);
	while (!to_visit.empty()) {
		Vector_2D pos = to_visit.back();
		to_visit.pop_back();
		visited.push_back(pos);
		p.set_position(pos);
		visited.push_back(pos);
		jumps = p.generate_jumps(board);
		possible_jumps = p.validate_jumps(board, jumps);

		for(int i=0; i<possible_jumps.size(); ++i){
			if (find(visited.begin(), visited.end(), possible_jumps.at(i)) == visited.end())
				to_visit.push_back(possible_jumps.at(i));
		}
	}
	valid_moves.insert( valid_moves.end(), visited.begin(), visited.end() );
	return valid_moves;
}
