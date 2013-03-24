
#include "game.h"
#include "empty_piece.h"
#include "triangle_piece.h"
#include "square_piece.h"
#include "diamond_piece.h"


int Game::go() {
	//Board board;
	/*
	board.set_cell_contents(Vector_2D(3, 3), boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(3, 3), 1)));
	board.set_cell_contents(Vector_2D(4, 4), boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(4, 4), 1)));
	board.set_cell_contents(Vector_2D(2, 2), boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(2, 2), 1)));

	board.print_board();
	std::cout << "\n";

	if (board.get_cell_contents(Vector_2D(3, 3))->valid_move(Vector_2D(5, 5), board) &&
			board.get_cell_contents(Vector_2D(2, 2))->valid_move(Vector_2D(1, 1), board)) {
		board.move_piece(Vector_2D(3, 3), Vector_2D(5, 5));
		board.move_piece(Vector_2D(2, 2), Vector_2D(1, 1));
		board.print_board();
	}
	*/

	board.set_cell_contents(Vector_2D(1, 1), boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(1, 1), 1)));
	board.set_cell_contents(Vector_2D(2, 2), boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(2, 2), 2)));
	board.set_cell_contents(Vector_2D(3, 4), boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(3, 4), 2)));
	board.print_board();

	std::vector<Vector_2D> a = board.get_cell_contents(Vector_2D(1, 1))->valid_moves(board);

	for(int i=0; i< a.size(); ++i){
		std::cout << a[i] << "\n";
	}

	return 0;
}

Game::Game( std::vector<int> players, std::vector<AI_details> ai_details)
{
	this->players=players;
	this->ai_details = ai_details;
	int n = players.size()/2;
	turn = 1;

	//if(n==1)
	//{
		board.set_cell_contents(Vector_2D(1,0),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(1, 0),1)));
		board.set_cell_contents(Vector_2D(2,0),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(2, 0),1)));
		board.set_cell_contents(Vector_2D(3,0),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(3, 0),1)));
		board.set_cell_contents(Vector_2D(4,0),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(4, 0),1)));
		board.set_cell_contents(Vector_2D(5,0),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(5, 0),1)));
		board.set_cell_contents(Vector_2D(6,0),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(6, 0),1)));
		board.set_cell_contents(Vector_2D(7,0),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(7, 0),1)));
		board.set_cell_contents(Vector_2D(8,0),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(8, 0),1)));

		board.set_cell_contents(Vector_2D(8,9),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(8, 9),2)));
		board.set_cell_contents(Vector_2D(7,9),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(7, 9),2)));
		board.set_cell_contents(Vector_2D(6,9),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(6, 9),2)));
		board.set_cell_contents(Vector_2D(5,9),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(5, 9),2)));
		board.set_cell_contents(Vector_2D(4,9),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(4, 9),2)));
		board.set_cell_contents(Vector_2D(3,9),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(3, 9),2)));
		board.set_cell_contents(Vector_2D(2,9),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(2, 9),2)));
		board.set_cell_contents(Vector_2D(1,9),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(1, 9),2)));
	//}
	//else
	if(n==2)
	{
		board.set_cell_contents(Vector_2D(9,1),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(9, 1),3)));
		board.set_cell_contents(Vector_2D(9,2),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(9, 2),3)));
		board.set_cell_contents(Vector_2D(9,3),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(9, 3),3)));
		board.set_cell_contents(Vector_2D(9,4),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(9, 4),3)));
		board.set_cell_contents(Vector_2D(9,5),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(9, 5),3)));
		board.set_cell_contents(Vector_2D(9,6),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(9, 6),3)));
		board.set_cell_contents(Vector_2D(9,7),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(9, 7),3)));
		board.set_cell_contents(Vector_2D(9,8),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(9, 8),3)));

		board.set_cell_contents(Vector_2D(0,8),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(0, 8),4)));
		board.set_cell_contents(Vector_2D(0,7),boost::shared_ptr<Game_piece>(new Triangle_piece(Vector_2D(0, 7),4)));
		board.set_cell_contents(Vector_2D(0,6),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(0, 6),4)));
		board.set_cell_contents(Vector_2D(0,5),boost::shared_ptr<Game_piece>(new Circle_piece(Vector_2D(0, 5),4)));
		board.set_cell_contents(Vector_2D(0,4),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(0, 4),4)));
		board.set_cell_contents(Vector_2D(0,3),boost::shared_ptr<Game_piece>(new Square_piece(Vector_2D(0, 3),4)));
		board.set_cell_contents(Vector_2D(0,2),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(0, 2),4)));
		board.set_cell_contents(Vector_2D(0,1),boost::shared_ptr<Game_piece>(new Diamond_piece(Vector_2D(0, 1),4)));
	}

	//board.print_board();
}

Player_ID Game::end(Board &board) {
	int counter = 0;

	for(int x = 1; x < board.get_x_size() - 1; ++x) {
		if (board.get_piece_ownership(Vector_2D(x, 0)) == 2)
			++counter;
	}

	if (counter == 8)
		return 2;
	counter = 0;

	for(int x = 1; x < board.get_x_size() - 1; ++x) {
		if (board.get_piece_ownership(Vector_2D(x, board.get_y_size() - 1)) == 1)
			++counter;
	}

	if (counter == 8)
		return 1;
	counter = 0;

	for(int y = 1; y < board.get_y_size() - 1; ++y) {
		if (board.get_piece_ownership(Vector_2D(0, y)) == 3)
			++counter;
	}

	if (counter == 8)
		return 3;
	counter = 0;

	for(int y = 1; y < board.get_y_size() - 1; ++y) {
		if (board.get_piece_ownership(Vector_2D(board.get_y_size() - 1, y)) == 4)
			++counter;
	}

	if (counter == 8)
		return 4;
	counter = 0;

	return NO_PLAYER;
}

Board* Game::getBoard()
{
	return &board;
}

bool Game::move( Vector_2D init, Vector_2D final )
{
	boost::shared_ptr<Game_piece> i = board.get_cell_contents(init);
	boost::shared_ptr<Game_piece> f = board.get_cell_contents(final);

	i->set_position(final);
	f->set_position(init);

	board.set_cell_contents(final,i);
	board.set_cell_contents(init,f);
	//board.print_board();
	return true;
}

Player_ID Game::getTurn()
{
	return turn;
}

Player_ID Game::end_from_move( Vector_2D mv )
{
	if(getTurn()==PLAYER_RED)
	{
		if(mv.y() == board.get_x_size()-1){
			for(int i=1; i<board.get_x_size()-1;++i){
				if(board.get_piece_ownership(Vector_2D(i,board.get_x_size()-1)) != PLAYER_RED){
					return NO_PLAYER;
				}
			}
			return PLAYER_RED;
		}
	}
	else if(getTurn()==PLAYER_BLUE)
	{
		if(mv.y() == 0){
			for(int i=1; i<board.get_x_size()-1;++i){
				if(board.get_piece_ownership(Vector_2D(i,0)) != PLAYER_BLUE){
					return NO_PLAYER;
				}
			}
			return PLAYER_BLUE;
		}
	}
	else if(getTurn()==PLAYER_GREEN)
	{
		if(mv.x() == 0){
			for(int i=1; i<board.get_x_size()-1;++i){
				if(board.get_piece_ownership(Vector_2D(0,i)) != PLAYER_GREEN){
					return NO_PLAYER;
				}
			}
			return PLAYER_GREEN;
		}
	}
	else if(getTurn()==PLAYER_YELLOW)
	{
		if(mv.x() == board.get_x_size()-1){
			for(int i=1; i<board.get_x_size()-1;++i){
				if(board.get_piece_ownership(Vector_2D(board.get_x_size()-1,i)) != PLAYER_YELLOW){
					return NO_PLAYER;
				}
			}
			return PLAYER_YELLOW;
		}
	}

	return NO_PLAYER;
}

Player_ID Game::getNextTurn()
{
	if(++turn>players.size())
		turn=1;

	return players[turn-1];
}

int Game::heuristic_distance(Player_ID player, Board &b, bool value = false) {
	++curval;
	int result;
	int distance;
	std::vector<int> scores(4,0);
	float tmp_score;
	int index;

	Player_ID winner = end(b);

	if(winner != NO_PLAYER) {
		std::cout << "Heuristic end board\n";
		if(winner == player) {
			std::cout << "WIN\n";
			return 1000000;
		} else {
			std::cout << "LOSE\n";
			return -1000000;
		}
	}

	for(int y = 0; y < b.get_y_size(); ++y) {
		for(int x = 0; x < b.get_x_size(); ++x) {
			tmp_score = 0;
			switch (b.get_piece_ownership(Vector_2D(x, y))) {
				case 1:
					index = 0;
					distance = y;
				break;
				case 2:
					index = 1;
					distance = (b.get_y_size() - 1) - y;
				break;
				case 3:
					index = 2;
					distance = (b.get_x_size() - 1) - x;
				break;
				case 4:
					index = 3;
					distance = x;
				break;
				default:
					continue;
				break;
			}

			tmp_score -= (float) distance * 3000.0/90.0;
			if(value) {
				tmp_score *= 1.0 - ((float) b.get_cell_contents(Vector_2D(x, y))->worth() - 1.0) * 0.075;
			}

			scores[index] += tmp_score;
		}
	}

	scores[player - 1] *= -1;

	return scores[0] + scores[1] + scores[2] + scores[3];
}

int Game::heuristic_distance_value(Player_ID player, Board &b) {
	return heuristic_distance(player, b, true);
}

std::vector<int> Game::eval_board_n_player(Board &board, Heuristic heur) {
	std::vector<int> result(4, -1000000);
	Player_ID winner = end(board);

	if(winner != NO_PLAYER) {
		result[winner - 1] = 1000000;;
		return result;
	}

	switch(heur) {
	case N_PIECES_DISTANCE_WEIGHTED:
		result[0] = heuristic_distance(1, board);
		result[1] = heuristic_distance(2, board);
		result[2] = heuristic_distance(3, board);
		result[3] = heuristic_distance(4, board);
		break;

	case N_PIECES_DISTANCE_AND_VALUE_WEIGHTED:
		result[0] = heuristic_distance_value(1, board);
		result[2] = heuristic_distance_value(3, board);
		result[3] = heuristic_distance_value(4, board);
		break;
	}

	return result;
}

AI_move_result Game::ai_move() {
	Player_ID player = getTurn();
	int n_players = players.size();
	AI_details ai = ai_details[player-1];
	curval = 0;

	AI_move_result result, temp;

	clock_t start = clock(), diff;

	Difficulty difficulty = ai.difficulty;

	int n_moves = get_moves_for_player(board, player).size();

	int depth = 4; //depois fazer um calculo em funcao de dificuldade e n_moves

	Board b = board.clone();
	switch(n_players) {
		case 2:
			switch(ai.algo) {
				case MINIMAX:
					temp = minimax(player, b, depth);
				break;

				case MINIMAX_AB:
					temp = minimax_ab(player, b, depth, -1000000, 1000000, 1);
				break;

				case NEGASCOUT:
					temp = negascout(player, b, depth, -1000000, 1000000);
				break;

				case GREEDY:
					temp = minimax(player, b, 1);
				break;
			}
		break;

		case 4:
			temp = n_player_minimax(player, b, depth);
		break;
	}

	diff = clock() - start;
	result.time = diff * 1000 / CLOCKS_PER_SEC;
	result.nodes_evaluated = curval;
	result.move = temp.move;
	result.value = temp.value;
	result.pvalue = temp.pvalue;

	return result;
}

std::vector<Move> Game::get_moves_for_player(Board &board, Player_ID player) {
	std::vector<Move> all_moves;
	std::vector<Vector_2D> piece_moves;
	Vector_2D pos;
	for(int y = 0; y < board.get_y_size(); ++y) {
		for(int x = 0; x < board.get_y_size(); ++x) {
			pos.x(x);
			pos.y(y);
			if(board.get_piece_ownership(pos) == player) {
				piece_moves = board.get_cell_contents(pos)->valid_moves(board);
				for(int i = 0; i < piece_moves.size(); ++i) {
					all_moves.push_back(Move(pos, piece_moves[i]));
				}
			}
		}
	}

	return all_moves;
}

AI_move_result Game::n_player_minimax(Player_ID current_player, Board &board, int depth) {
	AI_details ai = ai_details[current_player-1];
	std::vector<int> board_value = eval_board_n_player(board, ai.heuristic);
	std::vector<Move> moves = get_moves_for_player(board, current_player);
	AI_move_result result;

	if(depth == 0 || moves.size() == 0) {
		result.value = board_value;
		return result;
	}

	result.value = std::vector<int>(4, -1000000);
	Move final_move;
	AI_move_result temp_res;
	Board temp_board = board;

	int next_player = current_player + 1;
	if(next_player > players.size()) {
		next_player = 1;
	}


	for(int i = 0; i < moves.size(); ++i) {

		board.move_piece(moves[i].initial(), moves[i].final());
		temp_res = n_player_minimax(next_player, board, depth - 1);
		if(result.value[current_player-1] < temp_res.value[current_player-1]) {
			result.move = moves[i];
			result.value = temp_res.value;
		}
		board.move_piece(moves[i].final(), moves[i].initial());
	}

	return result;
}

AI_move_result Game::minimax(Player_ID current_player, Board &board, int depth) {
	AI_details ai = ai_details[current_player-1];
	std::vector<int> board_value;
	std::vector<Move> moves = get_moves_for_player(board, current_player);
	AI_move_result result;
	int sp_val;

	switch(ai.heuristic) {
		case Heuristic::N_PIECES_DISTANCE_WEIGHTED:
			sp_val = heuristic_distance(current_player, board);
		break;

		case Heuristic::N_PIECES_DISTANCE_AND_VALUE_WEIGHTED:
			sp_val = heuristic_distance_value(current_player, board);
		break;
	}

	if(depth == 0 || end(board) != NO_PLAYER) {
		result.pvalue = sp_val;
		return result;
	}

	result.pvalue = -1000000;;
	Move final_move;
	AI_move_result temp_res;
	Board temp_board = board;

	int next_player = current_player + 1;
	if(next_player > players.size()) {
		next_player = 1;
	}

	for(int i = 0; i < moves.size(); ++i) {
		board.move_piece(moves[i].initial(), moves[i].final());
		temp_res = minimax(next_player, board, depth - 1);
		temp_res.pvalue *= -1;

		if(result.pvalue < temp_res.pvalue) {
			result.move = moves[i];
			result.pvalue = temp_res.pvalue;
		}

		board.move_piece(moves[i].final(), moves[i].initial());
	}


	return result;
}

AI_move_result Game::minimax_ab(Player_ID current_player, Board &board, int depth, int alpha, int beta, int color) {
	//std::cout << "alpha: " << alpha << " beta: " << beta << '\n';
	AI_details ai = ai_details[current_player-1];
	std::vector<int> board_value;
	std::vector<Move> moves = get_moves_for_player(board, current_player);
	AI_move_result result;
	int sp_val;

	switch(ai.heuristic) {
		case Heuristic::N_PIECES_DISTANCE_WEIGHTED:
			sp_val = heuristic_distance(current_player, board);
		break;

		case Heuristic::N_PIECES_DISTANCE_AND_VALUE_WEIGHTED:
			sp_val = heuristic_distance_value(current_player, board);
		break;

		default:
			std::cout << "BORKED\n";
		break;
	}

	Player_ID winner = end(board);
	if(depth == 0 || winner != NO_PLAYER) {
		result.pvalue = sp_val;
		//std::cout << "pvalue " << sp_val << '\n';
		if(winner != NO_PLAYER) {
			std::cout << "END BOARD\n";
			std::cout << "Winner " << winner << '\n';
			for(int i = 0; i < moves.size(); ++i) {
				std::cout << moves[i].initial().x() << ", " << moves[i].initial().y()
						<< moves[i].final().x() << ", " << moves[i].final().y() << '\n';
			}
		}
		//std::cout << sp_val << '\n';
		return result;
	}

	result.pvalue = -1000000;;
	Move final_move;
	AI_move_result temp_res;
	Board temp_board = board;

	int next_player = current_player + 1;
	if(next_player > 2) {
		next_player = 1;
	}

//    if  Player = MaxPlayer
//        for each child of node
//            α := max(α, alphabeta(child, depth-1, α, β, not(Player) ))
//            if β ≤ α
//                break                             (* Beta cut-off *)
//        return α
//    else
//        for each child of node
//            β := min(β, alphabeta(child, depth-1, α, β, not(Player) ))
//            if β ≤ α
//                break                             (* Alpha cut-off *)
//        return β

	if(color == 1) {
		for(int i = 0; i < moves.size(); ++i) {
			board.move_piece(moves[i].initial(), moves[i].final());
			temp_res = minimax_ab(next_player, board, depth - 1, alpha, beta, color*-1);

			if(temp_res.pvalue > alpha) {
				alpha = temp_res.pvalue;
				result.move = moves[i];
			}

			board.move_piece(moves[i].final(), moves[i].initial());

			if(beta <= alpha) {
				break;
			}
		}
		result.pvalue = alpha;
	} else {
		for(int i = 0; i < moves.size(); ++i) {
			board.move_piece(moves[i].initial(), moves[i].final());
			temp_res = minimax_ab(next_player, board, depth - 1, alpha, beta, color*-1);

			if(temp_res.pvalue < beta) {
				beta = temp_res.pvalue;
				result.move = moves[i];
			}

			board.move_piece(moves[i].final(), moves[i].initial());

			if(beta <= alpha) {
				break;
			}
		}
		result.pvalue = beta;
	}

	return result;
}

AI_move_result Game::negascout(Player_ID current_player, Board &board, int depth, int alpha, int beta) {
	AI_details ai = ai_details[current_player-1];

	std::vector<int> board_value;
	std::vector<Move> moves = get_moves_for_player(board, current_player);
	AI_move_result result;
	int sp_val;

	switch(ai.heuristic) {
		case Heuristic::N_PIECES_DISTANCE_WEIGHTED:
			sp_val = heuristic_distance(current_player, board);
		break;

		case Heuristic::N_PIECES_DISTANCE_AND_VALUE_WEIGHTED:
			sp_val = heuristic_distance_value(current_player, board);
		break;
	}

	if(depth == 0 || end(board) != NO_PLAYER) {
		result.pvalue = sp_val;
		return result;
	}

	result.pvalue = -1000000;
	Move final_move;
	AI_move_result temp_res;
	Board temp_board = board;

	int next_player = current_player + 1;
	if(next_player > players.size()) {
		next_player = 1;
	}

	int b = beta;

	int i;
	for(i = 0; i < moves.size(); ++i) {
		board.move_piece(moves[i].initial(), moves[i].final());
		temp_res = negascout(current_player, board, depth - 1, -b, -alpha);
		temp_res.pvalue *= -1;

		if(alpha < temp_res.pvalue && temp_res.pvalue < beta && i != 0) {
			temp_res = negascout(current_player, board, depth - 1, -beta, -alpha);
			temp_res.pvalue *= -1;
			result.move = moves[i];
			result.pvalue = temp_res.pvalue;
		}

		if(temp_res.pvalue > alpha) {
			alpha = temp_res.pvalue;
		}

		board.move_piece(moves[i].final(), moves[i].initial());

		if (alpha >= beta) {
			return result;
		}

		b = alpha + 1;
	}

	result.pvalue = alpha;
	return result;
}

//int Game::vector_max(AI_move_result) {
//
//	int curmax = std::numeric_limits<int>::min();
//	int curmaxindex;
//
//	for(int i = 0; i < v.size(); ++i) {
//		if(v[i][index] > curmax) {
//			curmax = v[i][index];
//			curmaxindex = i;
//		}
//	}
//
//	return curmaxindex;
//}

std::vector<Vector_2D> Game::path( Vector_2D init, Vector_2D final )
{
	typedef boost::property<boost::edge_weight_t, float> EdgeWeightProperty;
	typedef boost::adjacency_list<     boost::listS,             
		boost::vecS,             
		boost::undirectedS,   
		boost::no_property,              
		EdgeWeightProperty,       
		boost::no_property,      
		boost::listS             
	> graph_t;

	typedef boost::graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
	typedef boost::graph_traits < graph_t >::edge_descriptor edge_descriptor;
	typedef std::pair<int, int> Edge;

	graph_t g;
	std::vector<std::pair<Vector_2D,vertex_descriptor> > nodes;
	std::vector<Vector_2D> result,already_added;
	vertex_descriptor current_vertex,next_vertex;

	already_added.push_back(init);
	nodes.push_back(std::pair<Vector_2D,vertex_descriptor>(init,boost::add_vertex(g)));
	current_vertex = nodes.back().second;

	Game_piece* p = board.get_cell_contents(init)->clone();
	std::vector<Vector_2D> cur_jumps = p->validate_jumps(*getBoard(),p->generate_jumps(*getBoard()));

	for(int i=0; i<cur_jumps.size(); ++i){
		if(find(already_added.begin(),already_added.end(),cur_jumps.at(i))==already_added.end()){
			next_vertex = boost::add_vertex(g);
			nodes.push_back(std::pair<Vector_2D,vertex_descriptor>(cur_jumps.at(i),next_vertex));
			boost::add_edge( current_vertex, next_vertex,1,g);
			already_added.push_back(cur_jumps.at(i));
		}
	}
	int j=0;
	while (!cur_jumps.empty()) {

		p->set_position(cur_jumps.at(0));
		current_vertex = nodes.at(j+1).second;
		cur_jumps.erase(cur_jumps.begin());
		++j;
		std::vector<Vector_2D> next_jumps = p->validate_jumps(*getBoard(),p->generate_jumps(*getBoard()));

		for(int i=0; i<next_jumps.size(); ++i){
			if(find(already_added.begin(),already_added.end(),next_jumps.at(i))==already_added.end()){
				next_vertex = boost::add_vertex(g);
				nodes.push_back(std::pair<Vector_2D,vertex_descriptor>(next_jumps.at(i),next_vertex));
				boost::add_edge( current_vertex, next_vertex,1,g);
				cur_jumps.push_back(next_jumps.at(i));
				already_added.push_back(next_jumps.at(i));
			}
		}       
	}

	std::vector<vertex_descriptor> pp(boost::num_vertices(g));
	std::vector<int> d( boost::num_vertices(g) );
	boost::dijkstra_shortest_paths(g, nodes[0].second , boost::predecessor_map(&pp[0]).distance_map(&d[0]) );
	delete p;

	int aa=0;
	for(int i=0; i<nodes.size(); ++i)
	{
		if(nodes.at(i).first==final){
			aa=nodes.at(i).second;
			break;
		}
	}

	result.push_back(final);
	int x;
	do{
		x = pp[aa];
		result.push_back(nodes.at(x).first);
		aa=x;
	}while(x!=0);

	std::reverse(result.begin(), result.end());
	
	return result;
}

bool Game::has_moves()
{
	return this->get_moves_for_player(*getBoard(),getTurn()).size()!=0;
}
