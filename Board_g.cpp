#include "Board_g.h"
#include "board_geom.h"
#include "square_geom.h"
#include "triang_geom.h"
#include "circle_geom.h"
#include "diamond_geom.h"


const float Board_g::K_BOARD_RENDER_SIZE(8.0);

Board_g::Board_g(int n){

	std::vector<Cell_g> row;
	if(n==1)
	{
		
		row.push_back(Cell_g());
		row.push_back(Cell_g(new trian_geom(1,1,0)));
		row.push_back(Cell_g(new trian_geom(1,2,0)));
		row.push_back(Cell_g(new circle_geom(1,3,0)));
		row.push_back(Cell_g(new circle_geom(1,4,0)));
		row.push_back(Cell_g(new square_geom(1,5,0)));
		row.push_back(Cell_g(new square_geom(1,6,0)));
		row.push_back(Cell_g(new diamond_geom(1,7,0)));
		row.push_back(Cell_g(new diamond_geom(1,8,0)));
		row.push_back(Cell_g());

		this->m_board_cells.push_back(row);
		row.clear();
		
		for(int i=1; i<9; ++i){
			for(int j=0; j<10; ++j)
				row.push_back(Cell_g());
			this->m_board_cells.push_back(row);
			row.clear();
		}
		
		row.push_back(Cell_g());
		row.push_back(Cell_g(new diamond_geom(2,1,9)));
		row.push_back(Cell_g(new diamond_geom(2,2,9)));
		row.push_back(Cell_g(new square_geom(2,3,9)));
		row.push_back(Cell_g(new square_geom(2,4,9)));
		row.push_back(Cell_g(new circle_geom(2,5,9)));
		row.push_back(Cell_g(new circle_geom(2,6,9)));
		row.push_back(Cell_g(new trian_geom(2,7,9)));
		row.push_back(Cell_g(new trian_geom(2,8,9)));
		row.push_back(Cell_g());
		this->m_board_cells.push_back(row);
		
	}
	else
	{
		row.push_back(Cell_g());
		row.push_back(Cell_g(new trian_geom(1,1,0)));
		row.push_back(Cell_g(new trian_geom(1,2,0)));
		row.push_back(Cell_g(new circle_geom(1,3,0)));
		row.push_back(Cell_g(new circle_geom(1,4,0)));
		row.push_back(Cell_g(new square_geom(1,5,0)));
		row.push_back(Cell_g(new square_geom(1,6,0)));
		row.push_back(Cell_g(new diamond_geom(1,7,0)));
		row.push_back(Cell_g(new diamond_geom(1,8,0)));
		row.push_back(Cell_g());

		this->m_board_cells.push_back(row);
		row.clear();

		
		row.push_back(Cell_g(new diamond_geom(4,0,1)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new trian_geom(3,9,1)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new diamond_geom(4,0,2)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new trian_geom(3,9,2)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new square_geom(4,0,3)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new circle_geom(3,9,3)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new square_geom(4,0,4)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new circle_geom(3,9,4)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new circle_geom(4,0,5)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new square_geom(3,9,5)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new circle_geom(4,0,6)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new square_geom(3,9,6)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new trian_geom(4,0,7)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new diamond_geom(3,9,7)));
		this->m_board_cells.push_back(row);
		row.clear();

		row.push_back(Cell_g(new trian_geom(4,0,8)));
		for(int j=1; j<9; ++j)
			row.push_back(Cell_g());
		row.push_back(Cell_g(new diamond_geom(3,9,8)));
		this->m_board_cells.push_back(row);
		row.clear();
		

		row.push_back(Cell_g());
		row.push_back(Cell_g(new diamond_geom(2,1,9)));
		row.push_back(Cell_g(new diamond_geom(2,2,9)));
		row.push_back(Cell_g(new square_geom(2,3,9)));
		row.push_back(Cell_g(new square_geom(2,4,9)));
		row.push_back(Cell_g(new circle_geom(2,5,9)));
		row.push_back(Cell_g(new circle_geom(2,6,9)));
		row.push_back(Cell_g(new trian_geom(2,7,9)));
		row.push_back(Cell_g(new trian_geom(2,8,9)));
		row.push_back(Cell_g());
		this->m_board_cells.push_back(row);
	}


	anim_xi=anim_xf=anim_yf=anim_yi=selec_x=selec_y=cursor_x=cursor_y=-1;
	m_one_graveyard=m_two_graveyard=0;
	m_board_next=m_board_cells;
	m_player_turn=1;
}

Board_g::Board_g() {
	std::vector<Cell_g> row;
	Cell_g cell;

	for (int y = 0; y < 10 ; y++) {
		for (int x = 0; x < 10 ; x++) {
			if (x >0 && x < 9) {
				if(y==0){
					row.push_back(Cell_g(new trian_geom(1,x,y)));
				}
				else if(y==9){
					row.push_back(Cell_g(new trian_geom(2,x,y)));
				}
				else
					row.push_back(Cell_g());
			} else 	if(x==0 && y > 0 && y<9){
				row.push_back(Cell_g(new trian_geom(4,x,y)));
			}else if(x==9 && y > 0 && y<9){
					row.push_back(Cell_g(new trian_geom(3,x,y)));
			}else {
				row.push_back(Cell_g());
			}
		}

		this->m_board_cells.push_back(row);
		row.clear();
	}
	
	//get_board_cell(Vector2D(1,2)) = Cell(new Player_two_pawn(1,2)); // TO DELETE
	anim_xi=anim_xf=anim_yf=anim_yi=selec_x=selec_y=cursor_x=cursor_y=-1;
	m_one_graveyard=m_two_graveyard=0;
	m_board_next=m_board_cells;
	m_player_turn=1;
	//save_board_state();
}

Board_g::~Board_g() {
}

void Board_g::draw_s_content(float separation_width, Vector_2D v){
	if(get_board_cell(Vector_2D(v.x(), v.y())).has_pawn()){
		glPushMatrix();

		glTranslatef(separation_width*(v.x() + 1  +get_board_cell(v).get_game_object()->get_inc_x()),
					get_board_cell(v).get_game_object()->get_inc_z(),
					separation_width*(v.y() + 1  +get_board_cell(v).get_game_object()->get_inc_y()));	

		glTranslatef(0,get_board_cell(v).get_game_object()->get_rot_axis(),0);
		glRotatef(get_board_cell(v).get_game_object()->get_rot_ang(),
			get_board_cell(v).get_game_object()->get_rot_x(),
			get_board_cell(v).get_game_object()->get_rot_y(),
			get_board_cell(v).get_game_object()->get_rot_z());
		glTranslatef(0,-get_board_cell(v).get_game_object()->get_rot_axis(),0);

		get_board_cell(v).render_contents(GL_RENDER);
		glPopMatrix();
	}
}

void draw_square(int x, int y, float s){
	glPushMatrix();
	glTranslatef(s*(x+1),0,s*(y+1));
	s/=2.0;
	float l=0.0;	
	glBegin(GL_POLYGON);
	glNormal3f(0,1,0);
	glVertex3f(-s,l,-s);
	glVertex3f(-s,l,s);
	glVertex3f(s,l,s);
	glVertex3f(s,l,-s);
	glEnd();
	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}

void Board_g::draw_option_square(int x, int y, float s, int own){
	if(x<0 || y<0 || x>9 || y>9)
		return;

	glPushMatrix();
	glTranslatef(s*(x+1),0,s*(y+1));
	s/=2.0;

	float opa= 0.5;
	if(own==1)
		Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.05,0.73,0.95,opa,  32).act();
	else if(own==0)
		if(get_board_cell(Vector_2D(x,y)).has_pawn())
			Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.85,0.08,0.08,opa,  32).act();
		else
			Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.95,0.83,0.08,opa,  32).act();
	else
		Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.15,0.83,0.08,opa,  32).act();

	glPolygonMode(GL_FRONT, GL_FILL);
	float h=0.07;
	glBegin(GL_POLYGON);
	glNormal3f(0,1,0);
	glVertex3f(-s,h,-s);
	glVertex3f(-s,h,s);
	glVertex3f(s,h,s);
	glVertex3f(s,h,-s);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(s*2*(x+1),0,s*2*(y+1));

	opa= 1;
	if(own==1)
		Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.05,0.73,0.95,opa,  32).act();
	else if(own==0)
		if(get_board_cell(Vector_2D(x,y)).has_pawn())
			Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.85,0.08,0.08,opa,  32).act();
		else
			Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.95,0.83,0.08,opa,  32).act();
	else
		Material_components (0.0,0.0,0.0,opa,  0.0,0.0,0.0,opa,  0.15,0.83,0.08,opa,  32).act();

	glPolygonMode(GL_FRONT, GL_LINE);
	glBegin(GL_POLYGON);
	glNormal3f(0,1,0);
	glVertex3f(-s,h,-s);
	glVertex3f(-s,h,s);
	glVertex3f(s,h,s);
	glVertex3f(s,h,-s);
	glEnd();
	glPopMatrix();

	glPolygonMode(GL_FRONT, GL_FILL);
	glDisable(GL_COLOR_MATERIAL);
	
}

void Board_g::draw_select_content(float separation_width, Vector_2D v){
	if(get_board_cell(Vector_2D(v.x(), v.y())).has_pawn()){

		//glBlendFunc(GL_ONE, GL_ONE);
		
		glPushMatrix();
			glTranslatef(separation_width*(v.x() + 1), 0,	separation_width*(v.y() + 1));	
			get_board_cell(v).render_contents(GL_RENDER);
		glPopMatrix();
		
		draw_option_square(v.x(),v.y(),separation_width,1);

		get_board_cell(v).get_game_object().get()->get_material().reset();
		get_board_cell(v).get_game_object().get()->get_material().set_opac(1);
	}
}


void Board_g::render( GLenum mode ) {
	static const float separation_width = K_BOARD_RENDER_SIZE/(K_BOARD_RENDER_SIZE+1.0);
	
	glPushMatrix();

	glTranslatef(0.4-0.7,0.7,0.4);
		
	if(mode == GL_RENDER)
		render_board();
	
	glTranslatef(-5*separation_width,-1*separation_width,-5*separation_width);

	if (mode == GL_SELECT)
		glPushName(0);

	for (int x = 0; x < get_board().size(); ++x) {
		for (int y = 0; y < get_board_row(0).size(); ++y) {

			if(mode == GL_SELECT){
				
				glLoadName(x);
				glPushName(y);
				draw_square(x,y,separation_width);
			}
				
			if(get_board_cell(Vector_2D(x, y)).has_pawn() && !((x == anim_xi && y==anim_yi) || (x == anim_xf && y==anim_yf) || (x == selec_x && y==selec_y))){
				glPushMatrix();

					glTranslatef(separation_width*(x + 1  +get_board_cell(Vector_2D(x, y)).get_game_object()->get_inc_x()),
														   get_board_cell(Vector_2D(x, y)).get_game_object()->get_inc_z(),
								 separation_width*(y + 1  +get_board_cell(Vector_2D(x, y)).get_game_object()->get_inc_y()));	

					get_board_cell(Vector_2D(x, y)).render_contents(mode);
				glPopMatrix();
			}	

			if(mode == GL_SELECT)
				glPopName();	

		}
	}

	if(mode == GL_SELECT)
		glPopName();	

	if(mode == GL_RENDER){
		if(anim_xi != -1) 
			draw_s_content(separation_width,Vector_2D(anim_xi,anim_yi));
			
		if(anim_xf != -1) 
			draw_s_content(separation_width,Vector_2D(anim_xf,anim_yf));
			
		if(selec_x != -1)
			draw_select_content(separation_width,Vector_2D(selec_x,selec_y));

		draw_valid_squares(separation_width);

		if(cursor_x != -1)
			draw_option_square(cursor_x,cursor_y,separation_width,2);
	}

	glPopMatrix();
}

void Board_g::render_only_board( )
{
	static const float separation_width = K_BOARD_RENDER_SIZE/(K_BOARD_RENDER_SIZE+1);

	glPushMatrix();
	glTranslatef(0.4-0.7,0.7,0.4);
	glTranslatef(-5*separation_width,-1*separation_width,-5*separation_width);

	glPushName(0);

	for (int x = 0; x < get_board().size(); ++x) {
		for (int y = 0; y < get_board_row(0).size(); ++y) {

			glLoadName(x);
			glPushName(y);	
			draw_square(x,y,separation_width);


			if(get_board_cell(Vector_2D(x, y)).has_pawn() && !((x == anim_xi && y==anim_yi) || (x == anim_xf && y==anim_yf) || (x == selec_x && y==selec_y))){
				glPushMatrix();
				glTranslatef(separation_width*(x + 1  +get_board_cell(Vector_2D(x, y)).get_game_object()->get_inc_x()),
					get_board_cell(Vector_2D(x, y)).get_game_object()->get_inc_z(),
					separation_width*(y + 1  +get_board_cell(Vector_2D(x, y)).get_game_object()->get_inc_y()));	

				get_board_cell(Vector_2D(x, y)).render_contents(GL_SELECT);
				glPopMatrix();
			}	

			glPopName();
		}
	}
	glPopName();
	glPopMatrix();
}

void Board_g::draw_valid_squares(float s)
{
	if(valid_squares.size() == 0)
		return;

	for(int i=0; i<valid_squares.size(); ++i){
	
		draw_option_square(valid_squares[i].x(),valid_squares[i].y(),s);
	}
}


void Board_g::render_board() {
	glDisable(GL_COLOR_MATERIAL);Material_components (0.4,0.4,0.4,1.0,  0.6,0.6,0.6,1.0,  0.4,0.4,0.4,1.0,  32).act();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,2);
	glCallList(1);
	glDisable(GL_TEXTURE_2D);
	//glEnable(GL_COLOR_MATERIAL);
}

std::vector<std::vector<Cell_g> > Board_g::get_board() const {
	return m_board_cells;
}

void Board_g::set_board( std::vector<std::vector<Cell_g> > board ) {
	m_board_cells = board;
}

void Board_g::clear_board() {
	m_board_cells.clear();
}

std::vector<Cell_g> Board_g::get_board_row(unsigned int row_index) const {
	return get_board()[row_index];
}

bool Board_g::animate_obj_at(int xi, int yi, int xf, int yf, float t )
{
	anim_xi=xi;
	anim_xf=xf;
	anim_yf=yf;
	anim_yi=yi;
	if(get_board_cell(Vector_2D(xi,yi)).has_pawn()){ /////CAN BE REMOVED
		if(get_board_cell(Vector_2D(xf,yf)).has_pawn())
		{
			bool v1 = get_board_cell(Vector_2D(xi,yi)).get_game_object()->animate_capture(xi,yi,xf,yf,t);
			bool v2 = get_board_cell(Vector_2D(xf,yf)).get_game_object()->animate_cought(xi,yi,xf,yf,t,m_one_graveyard,m_two_graveyard);
			
			if (v1 || v2)
				return true;
			else
			{
				anim_xi=anim_xf=anim_yf=anim_yi=-1;
				return false;
			}

		}
		else
		{
			return get_board_cell(Vector_2D(xi,yi)).get_game_object()->animate(xi,yi,xf,yf,t);
		}
	}										 /////CAN BE REMOVED
	else									 /////CAN BE REMOVED
		return false;						 /////CAN BE REMOVED
}


Cell_g& Board_g::get_board_cell( Vector_2D pos ) {
		return m_board_cells[pos.y()][pos.x()];
}

Cell_g& Board_g::get_next_board_cell(Vector_2D pos)
{
	return m_board_next[pos.y()][pos.x()];
}

void Board_g::set_board_cell(Vector_2D pos, Cell_g c)
{
	m_board_cells[pos.y()][pos.x()] = c;
}

void Board_g::move_piece( int xi, int yi, int xf, int yf )
{
	m_board_next=m_board_cells;
	if(get_next_board_cell(Vector_2D(xi,yi)).has_pawn()){

		get_next_board_cell(Vector_2D(xf,yf)).set_game_object( get_next_board_cell(Vector_2D(xi,yi)).get_game_object() );
		get_next_board_cell(Vector_2D(xi,yi)).set_game_object(nullptr);

	}
}

void Board_g::update_board(int xi, int yi, int xf, int yf)
{
	if(get_board_cell(Vector_2D(xi,yi)).has_pawn()){
		if(get_board_cell(Vector_2D(xf,yf)).has_pawn()){
			if(get_board_cell(Vector_2D(xf,yf)).get_game_object().get()->get_ownership()==1)
				m_one_graveyard++;
			else
				m_two_graveyard++;
		}
	}

	m_board_cells=m_board_next;
	change_turn();
	//save_move(xi,yi,xf,yf,m_one_graveyard,m_two_graveyard);
	//save_board_state();
}


void Board_g::create_board_geom( float scale )
{
	glNewList(1,GL_COMPILE);
	glEnable(GL_NORMALIZE);
	glPushMatrix();

	float xx=0.88;//8/9;
	//glTranslatef(-0.89*scale+1.7,-4.12*scale,-0.89*scale+1.7);
	glTranslatef(-0.89*scale+xx,-4.12*scale,-0.89*scale+xx);
	glRotated(-45,0,1,0);
	glScaled(2.534*scale,2.534*scale,2.534*scale);

	for(int i=0; i< B_FACES_COUNT*3; i+=3){
		glBegin(GL_TRIANGLES);
		glNormal3f(bvertexs[bindexes[i]].nx,bvertexs[bindexes[i]].ny,bvertexs[bindexes[i]].nz);
		glTexCoord2f(bvertexs[bindexes[i]].u,bvertexs[bindexes[i]].v);
		glVertex3f(bvertexs[bindexes[i]].x,bvertexs[bindexes[i]].y,bvertexs[bindexes[i]].z);

		glNormal3f(bvertexs[bindexes[i+1]].nx,bvertexs[bindexes[i+1]].ny,bvertexs[bindexes[i+1]].nz);
		glTexCoord2f(bvertexs[bindexes[i+1]].u,bvertexs[bindexes[i+1]].v);
		glVertex3f(bvertexs[bindexes[i+1]].x,bvertexs[bindexes[i+1]].y,bvertexs[bindexes[i+1]].z);

		glNormal3f(bvertexs[bindexes[i+2]].nx,bvertexs[bindexes[i+2]].ny,bvertexs[bindexes[i+2]].nz);
		glTexCoord2f(bvertexs[bindexes[i+2]].u,bvertexs[bindexes[i+2]].v);
		glVertex3f(bvertexs[bindexes[i+2]].x,bvertexs[bindexes[i+2]].y,bvertexs[bindexes[i+2]].z);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_NORMALIZE);
	glEndList();
}

void Board_g::init_geoms( float scale )
{
	Board_g::create_board_geom(scale);
	//Piece::create_pawn_low_geometry(scale);
	//Piece::create_pawn_high_geometry(scale);
	square_geom::create_geometry(scale);
	trian_geom::create_geometry(scale);
	circle_geom::create_geometry(scale);
	diamond_geom::create_geometry(scale);
}

void Board_g::set_selected( int x, int y )
{
	selec_x=x;
	selec_y=y;
}

void Board_g::deselect()
{
	clear_valid_squares();
	selec_x=selec_y=-1;
}

void Board_g::set_valid_squares( std::vector<Vector_2D> vec )
{
	valid_squares = vec;
}

void Board_g::clear_valid_squares()
{
	valid_squares.clear();
}

void Board_g::set_cursor( int x, int y )
{
	cursor_x=x;
	cursor_y=y;
}

bool Board_g::is_valid_cell( int x, int y )
{
	for(int i=0; i<valid_squares.size(); ++i){
		printf("%d %d\n",valid_squares[i].x(),valid_squares[i].y());
		if(valid_squares[i].x()==x && valid_squares[i].y()==y)
			return true;}
	return false;
}

int Board_g::change_turn()
{
	if(m_player_turn==1)
		m_player_turn=2;
	else
		m_player_turn=1;
	return m_player_turn;
}

int Board_g::get_turn()
{
	return m_player_turn;
}

void Board_g::set_player_type( int p, int t )
{
	if(p==1)
		m_one_type=t;
	else
		m_two_type=t;
}


void Board_g::reset()
{
	m_board_cells=m_board_next=m_board_states[0];
	m_one_graveyard=m_two_graveyard=0;
}


