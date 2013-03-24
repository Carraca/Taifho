#pragma once

#include <vector>
#include <utility>
#include <sstream>
#include <memory>
#include "Cell_g.h"
#include "vector_2d.h"

class Board_g
{
public:
	// Test board
	Board_g();
	Board_g(int n);
	Board_g(std::string board);
	~Board_g(void);

	void render(GLenum mode);
	
	void save_board_state();
	bool load_previous_state();
	std::pair<Vector_2D,Vector_2D> load_previous_move();
	void save_move(int xi, int yi, int xf, int yf, int one_g, int two_g);

	static void create_board_geom(float scale);

	void move_piece(int xi, int yi, int xf, int yf);
	Cell_g& get_board_cell(Vector_2D pos);
	Cell_g& get_next_board_cell(Vector_2D pos);
	bool animate_obj_at(int xi, int yi, int xf, int yf, float t );

	static void init_geoms(float scale);

	void set_selected(int x, int y);
	void deselect();
	void set_cursor(int x, int y);

	void render_only_board();

	bool is_valid_cell(int x, int y);
	bool is_piece(int x, int y){
		return m_board_cells[y][x].has_pawn();
	}

	int change_turn();
	int get_turn();
	int get_next_turn();

	void set_player_type(int p, int t);
	int get_player_type(int p);
	bool is_human();
	bool is_next_human();
	void update_board(int xi, int yi, int xf, int yf);

	void set_valid_squares(std::vector<Vector_2D> vec);
	std::string to_string();

	int get_move_history_count();
	std::pair<Vector_2D,Vector_2D> get_move_history_at(int d);
	void reset();
private:
	void render_board();
	void draw_option_square(int x, int y, float s, int own=0);
	void clear_valid_squares();
	void draw_valid_squares(float s);
	void draw_select_content(float separation_width, Vector_2D v);
	std::vector<std::vector<Cell_g> > get_board() const;
	std::vector<Cell_g> get_board_row(unsigned int row_index) const;
	void set_board_cell(Vector_2D pos, Cell_g c);
	void draw_s_content(float separation_width, Vector_2D v);
	void set_board(std::vector<std::vector<Cell_g> > board);
	void clear_board();
	void draw_graveyard(int side);
	


	std::vector<std::vector<Cell_g> > m_board_cells;
	std::vector<std::vector<Cell_g> > m_board_next;
	std::vector< std::vector<std::vector<Cell_g> > > m_board_states;
	std::vector< std::pair<Vector_2D,Vector_2D> > m_move_history;
	std::vector< std::pair<int,int> > m_graveyard_history;
	std::vector<Vector_2D> valid_squares;
	int m_one_graveyard,m_two_graveyard;

	int m_player_turn;
	int m_one_type;
	int m_two_type;


	int cursor_x,cursor_y;
	int anim_xi,anim_xf,anim_yi,anim_yf,selec_x,selec_y;
	static const float K_BOARD_RENDER_SIZE;
};

