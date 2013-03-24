#define GL_GLEXT_PROTOTYPES
#include <GL/glui.h>
#include <math.h>
#include <ctime>
#include <stack>
#include "pick.h"
#include "Board_g.h"
#include "RGBpixmap.h"
#include "my_time.h"
#define getCurrentTime GetTickCount
#include "logic_interface.h"
#include "ProcessingEvent.h"
#include <boost/thread.hpp>
#include "Mqueue.h"
#include "MoveEvent.h"
#include "AvailableMovesEvent.h"
#include "WinEvent.h"
#include "PassEvent.h"
#include "vector_2d.h"
#include <iosfwd>
#include "turnEvent.h"

#ifdef _WIN32

#include <windows.h>
#include "ProcessingEvent.h"


#else

double GetTickCount(void) {
	timespec now;
  	if (clock_gettime(CLOCK_MONOTONIC, &now))
  		return 0;
  	return now.tv_sec * 1000.0 + now.tv_nsec / 1000000.0;
}
#endif

logic_interface *logic;

GLUI_Button* play_btn;
GLUI_Checkbox* n_players_checkbox;
GLUI_Panel *j1_panel;
GLUI_Panel *j1_type_panel;
GLUI_RadioGroup* j1_type;
GLUI_Listbox* j1_heuristic;
GLUI_Listbox* j1_algorithm;
GLUI_Listbox* j1_reordering;
GLUI_Listbox* j1_difficulty;
GLUI_Panel *j2_panel;
GLUI_Panel *j2_type_panel;
GLUI_RadioGroup* j2_type;
GLUI_Listbox* j2_heuristic;
GLUI_Listbox* j2_algorithm;
GLUI_Listbox* j2_reordering;
GLUI_Listbox* j2_difficulty;
GLUI_Panel *j3_panel;
GLUI_Panel *j3_type_panel;
GLUI_RadioGroup* j3_type;
GLUI_Listbox* j3_heuristic;
GLUI_Listbox* j3_algorithm;
GLUI_Listbox* j3_reordering;
GLUI_Listbox* j3_difficulty;
GLUI_Panel *j4_panel;
GLUI_Panel *j4_type_panel;
GLUI_RadioGroup* j4_type;
GLUI_Listbox* j4_heuristic;
GLUI_Listbox* j4_algorithm;
GLUI_Listbox* j4_reordering;
GLUI_Listbox* j4_difficulty;

int n_players=0;
int j1_type_var=0;
int j2_type_var=0;
int j3_type_var=0;
int j4_type_var=0;

bool STARTED=0;
Vector_2D o, f;
int moves[4];
int m_p=0;
const int DIMX = 500;
const int DIMY = 500;
const int INITIALPOS_X = 200;
const int INITIALPOS_Y = 200;
// picking
#define BUFSIZE 512
GLuint selectBuf[BUFSIZE];
GLuint selectBuf2[BUFSIZE];
picking *pk;
float dx=0.0, dy=0.0, dz=0.0, dxAc=0.0, dzAc=0.0;	// variaveis auxiliares de posicao
picking *pk2;
float dx2=0.0, dy2=0.0, dz2=0.0, dxAc2=0.0, dzAc2=0.0;	// variaveis auxiliares de posicao
float Xini=0, Yini=0;
int mouse_x=0,mouse_y=0;
int cursor_pos[]= {-1,-1};
int window_w=DIMX;
int window_h=DIMY;
bool NO_DSX = true;
float xy_aspect;
float def_view_rotate[16] = { 1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
						      0,0,0,1 };
	float view_rotate[16] = { 1,0,0,0,
							  0,1,0,0,
							  0,0,1,0,
							  0,0,0,1 };
float obj_pos[] = { 0.0, 0.0, 0.0 };
float obj_pan[] = { 0.0, 0.0, 0.0 };
double axis_radius_begin =  0.05;
double axis_radius_end   =  0.0;
double axis_lenght       = 4.0;
int axis_nslices = 8;
int axis_nstacks = 1;

float light0_position[]  = {5.0, 5.0, 5.0, 0.0};
float light0_ambient[] =   {0.1, 0.1, 0.1, 1.0};
float light0_diffuse[] =   {0.8, 0.8, 0.8, 1.0};
float light0_specular[] =  {1.0, 1.0, 1.0, 1.0};
float light0_kc = 0.0;
float light0_kl = 1.0;
float light0_kq = 0.0;
double light0x = 5.0;
double light0y = 3.0;
double light0z = 5.0;
double symb_light0_radius = 0.2;
int symb_light0_slices = 8;
int symb_light0_stacks =8;

float light1_position[]  = {-5.0, 3.0, -5.0, 0.0};
float light1_ambient[] =   {0.1, 0.1, 0.1, 1.0};
float light1_diffuse[] =   {0.8, 0.8, 0.8, 1.0};
float light1_specular[] =  {1.0, 1.0, 1.0, 1.0};
float light1_kc = 0.0;
float light1_kl = 1.0;
float light1_kq = 0.0;
double light1x = -5.0;
double light1y = 3.0;
double light1z = -5.0;
double symb_light1_radius = 0.2;
int symb_light1_slices = 8;
int symb_light1_stacks =8;

float light_ambient[] = {0.5, 0.5, 0.5, 1.0};

int main_window;
GLUquadric* glQ;
GLUI  *glui;
void camCB(int d);
GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
float mat_shininess[] = {50.0};

static float value = 3.14/2;

struct anim_time{
	float time_init;
	float time_final;
};

int game_type;
int p1=0,p2=0; //0 - human

int cur_dsx=0;
std::string dsx_names[] = {"theme1.dsx","theme2.dsx"};

typedef void (*menufunc) (GLenum mode);

int animSpeed=1;
int anim_speeds[] = {3000,1500,500,100};
int next_cam=1;
int prev_cam=1;
float DELTA_T = 10;
int PAWN_PIECE_ANIM_INTERVAL = anim_speeds[animSpeed]; 
int PAWN_PIECE_ANIM_BACK_INTERVAL = 300;
int BOARD_ROTATING_SPEED = 1500;
double VIEW_1_2_RADIUS = 6,
	   VIEW_1_2_HEIGHT=15.8;
double VIEW_3_RADIUS= sqrt(pow(VIEW_1_2_HEIGHT,2)+pow(VIEW_1_2_RADIUS,2));
double VIEW_4_X=15.6,VIEW_4_Y=10.4,VIEW_4_Z=7.8;

// -- GLOBAL GAME VARS ------------------------------
Board_g board;
std::stack<Board_g> board_states;
float t=0;
anim_time anim_t,view_t;
Vector_2D pos_i,pos_f;
double view_x=VIEW_4_X, view_y=VIEW_4_Y, view_z=VIEW_4_Z;
double cam_up_vec[] = { 0 , 1 , 0};
bool ANIMATING=0, VIEW_ANIMATING=0, ALLOW_USER_INPUT=0;
timer game_time,turn_time;
int COUGHT_ANIMATION_MOV = 0;
int winner=0;
int drawTurn=0;
int curTurn=1;
bool ROTATE_AFTER_MOVE = 1;
bool MENU_MODE= 0;
bool REPLAY = 0;
int moves_history, current_moves_history;
int one_wins=0, two_wins=0;
int TURN_TIMEOUT = 100;
int CPU_COUNT = 2;
bool REQUEST_SENT = false;
std::string win_message, turn_message;
std::vector<int> players;
bool PROCESSING=0;
// -- ---------------- ------------------------------

/// MENU ///
void draw_start_menu(GLenum mode);
void draw_type_menu(GLenum mode);
void draw_dif_menu(GLenum mode);
void draw_info_menu(GLenum mode);
void draw_final_menu(GLenum mode);
menufunc menu_window[] = {draw_start_menu,draw_type_menu,draw_dif_menu,draw_info_menu,draw_final_menu};
int current_menu_window=0;
///
GLUI_RadioGroup *radioGroup;
GLUI_Listbox *listbox;




void animate(int d){
		if(board.animate_obj_at(pos_i.x(),pos_i.y(),pos_f.x(),pos_f.y(),
			(GetTickCount()-anim_t.time_init)/(anim_t.time_final-anim_t.time_init)))
		{
		
			glutTimerFunc(DELTA_T, animate, 0);
		}
		else
		{
			board.update_board(pos_i.x(),pos_i.y(),pos_f.x(), pos_f.y());
			ANIMATING=false;
			
		}
}

void animate_back(int d){
	if(board.animate_obj_at(pos_i.x(),pos_i.y(),pos_f.x(),pos_f.y(),0.98-
		((GetTickCount()-anim_t.time_init)/(anim_t.time_final-anim_t.time_init))))
	{
		glutTimerFunc(DELTA_T, animate_back, 0);
	}
	else
	{
		//board.load_previous_state();
		ANIMATING=false;
	}
} 

void animate_piece(int xi, int yi, int xf, int yf)
{
	if(!ANIMATING){
		anim_t.time_init= GetTickCount();
		anim_t.time_final= GetTickCount()+PAWN_PIECE_ANIM_INTERVAL; 
		pos_i = Vector_2D(xi,yi);
		pos_f = Vector_2D(xf,yf);
		ANIMATING=true;
		board.move_piece(pos_i.x(),pos_i.y(),pos_f.x(), pos_f.y());
		animate(0);
		//turn_time.set(TURN_TIMEOUT);
	}
}

void animate_view_1_to_2(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		view_z=-VIEW_1_2_RADIUS*(2*t -1);
		view_x= sqrt(pow(VIEW_1_2_RADIUS,2) - pow(view_z,2)); 
		
		glutTimerFunc(DELTA_T, animate_view_1_to_2, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=-VIEW_1_2_RADIUS;
		VIEW_ANIMATING=false;
		radioGroup->enable();
	}
}
void start_view_1_to_2()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=VIEW_1_2_RADIUS;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_1_to_2(0);
	}
}

void animate_view_2_to_1(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		view_z=VIEW_1_2_RADIUS*(2*t -1);
		view_x= -sqrt(pow(VIEW_1_2_RADIUS,2) - pow(view_z,2)); 

		glutTimerFunc(DELTA_T, animate_view_2_to_1, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=VIEW_1_2_RADIUS;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_2_to_1()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=-VIEW_1_2_RADIUS;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_2_to_1(0);
	}
}

void animate_view_1_to_3(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		
		view_z=VIEW_1_2_RADIUS-VIEW_1_2_RADIUS*t;
		view_y= sqrt(pow(VIEW_3_RADIUS,2) - pow(view_z,2)); 

		glutTimerFunc(DELTA_T, animate_view_1_to_3, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_3_RADIUS;
		view_z=0;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_1_to_3()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=VIEW_1_2_RADIUS;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[1]=0;
		cam_up_vec[2]=-1;
		animate_view_1_to_3(0);
	}
}

void animate_view_3_to_1(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);


		view_z=VIEW_1_2_RADIUS*t;
		view_y= sqrt(pow(VIEW_3_RADIUS,2) - pow(view_z,2)); 

		glutTimerFunc(DELTA_T, animate_view_3_to_1, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=VIEW_1_2_RADIUS;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_3_to_1()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_3_RADIUS;
		view_z=0;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[1]=0;
		cam_up_vec[2]=-1;
		animate_view_3_to_1(0);
	}
}

void animate_view_2_to_3(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);


		view_z=-VIEW_1_2_RADIUS+VIEW_1_2_RADIUS*t;
		view_y= sqrt(pow(VIEW_3_RADIUS,2) - pow(view_z,2)); 

		glutTimerFunc(DELTA_T, animate_view_2_to_3, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_3_RADIUS;
		view_z=0;
		VIEW_ANIMATING=false; radioGroup->enable();
	}

}
void start_view_2_to_3()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=-VIEW_1_2_RADIUS;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[1]=0;
		cam_up_vec[2]=1;
		animate_view_2_to_3(0);
	}
}

void animate_view_3_to_2(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);


		view_z=-VIEW_1_2_RADIUS*t;
		view_y= sqrt(pow(VIEW_3_RADIUS,2) - pow(view_z,2)); 

		glutTimerFunc(DELTA_T, animate_view_3_to_2, 0);
	}
	else
	{

		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=-VIEW_1_2_RADIUS;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_3_to_2()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_3_RADIUS;
		view_z=0;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[1]=0;
		cam_up_vec[2]=1;
		animate_view_3_to_2(0);
	}
}

void animate_view_1_to_4(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		view_x=VIEW_4_X*t;
		view_y=VIEW_1_2_HEIGHT+(VIEW_4_Y-VIEW_1_2_HEIGHT)*t;
		view_z=VIEW_1_2_RADIUS+(VIEW_4_Z-VIEW_1_2_RADIUS)*t;

		glutTimerFunc(DELTA_T, animate_view_1_to_4, 0);
	}
	else
	{

		view_x=VIEW_4_X;
		view_y=VIEW_4_Y;
		view_z=VIEW_4_Z;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_1_to_4()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=VIEW_1_2_RADIUS;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_1_to_4(0);
	}
}

void animate_view_4_to_1(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		view_x=VIEW_4_X*(1-t);
		view_y=VIEW_1_2_HEIGHT+(VIEW_4_Y-VIEW_1_2_HEIGHT)*(1-t);
		view_z=VIEW_1_2_RADIUS+(VIEW_4_Z-VIEW_1_2_RADIUS)*(1-t);

		glutTimerFunc(DELTA_T, animate_view_4_to_1, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=VIEW_1_2_RADIUS;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_4_to_1()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=VIEW_4_X;
		view_y=VIEW_4_Y;
		view_z=VIEW_4_Z;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_4_to_1(0);
	}
}

void animate_view_2_to_4(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		view_x=VIEW_4_X*t;
		view_y=VIEW_1_2_HEIGHT+(VIEW_4_Y-VIEW_1_2_HEIGHT)*t;
		view_z=-VIEW_1_2_RADIUS+(VIEW_4_Z+VIEW_1_2_RADIUS)*t;

		glutTimerFunc(DELTA_T, animate_view_2_to_4, 0);
	}
	else
	{

		view_x=VIEW_4_X;
		view_y=VIEW_4_Y;
		view_z=VIEW_4_Z;
		VIEW_ANIMATING=false; //radioGroup->enable();
	}
}
void start_view_2_to_4()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=-VIEW_1_2_RADIUS;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_2_to_4(0);
	}
}

void parseTurn(TurnEvent e);


void animate_view_4_to_2(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);
		
		view_x=VIEW_4_X*(1-t);
		view_y=VIEW_1_2_HEIGHT+(VIEW_4_Y-VIEW_1_2_HEIGHT)*(1-t);
		view_z=-VIEW_1_2_RADIUS+(VIEW_4_Z+VIEW_1_2_RADIUS)*(1-t);
		glutTimerFunc(DELTA_T, animate_view_4_to_2, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_1_2_HEIGHT;
		view_z=-VIEW_1_2_RADIUS;
		
		VIEW_ANIMATING=false; //radioGroup->enable();
		parseTurn(TurnEvent(1));
		if(players.at(0)==0){
			logic->generateAIMove(1);
		}
	}
}
void start_view_4_to_2()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=VIEW_4_X;
		view_y=VIEW_4_Y;
		view_z=VIEW_4_Z;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_4_to_2(0);
	}
}

void animate_view_3_to_4(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if(cam_up_vec[2]<0)
			cam_up_vec[2]=t-1;
		else
			cam_up_vec[2]=1-t;
		cam_up_vec[1]=sqrt(1-pow(cam_up_vec[2],2));

		view_x=VIEW_4_X*t;
		view_y=VIEW_3_RADIUS+(VIEW_4_Y-VIEW_3_RADIUS)*t;
		view_z=VIEW_4_Z*t;
		glutTimerFunc(DELTA_T, animate_view_3_to_4, 0);
	}
	else
	{
		view_x=VIEW_4_X;
		view_y=VIEW_4_Y;
		view_z=VIEW_4_Z;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_3_to_4()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=0;
		view_y=VIEW_3_RADIUS;
		view_z=0;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		//cam_up_vec[0]=cam_up_vec[2]=0;
		//cam_up_vec[1]=1;
		//SET FROM PRIOR CAMERA
		animate_view_3_to_4(0);
	}
}

void animate_view_4_to_3(int d)
{
	float t = (GetTickCount()-view_t.time_init)/(view_t.time_final-view_t.time_init);
	if( t <= 1 )
	{
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		if(board.get_turn()==1)
			cam_up_vec[2]=-t;
		else
			cam_up_vec[2]=t;
		cam_up_vec[1]=sqrt(1-pow(cam_up_vec[2],2));

		view_x=VIEW_4_X*(1-t);
		view_y=VIEW_3_RADIUS+(VIEW_4_Y-VIEW_3_RADIUS)*(1-t);
		view_z=VIEW_4_Z*(1-t);
		glutTimerFunc(DELTA_T, animate_view_4_to_3, 0);
	}
	else
	{
		view_x=0;
		view_y=VIEW_3_RADIUS;
		view_z=0;
		
		VIEW_ANIMATING=false; radioGroup->enable();
	}
}
void start_view_4_to_3()
{
	if(!VIEW_ANIMATING)
	{
		view_t.time_init= GetTickCount();
		view_t.time_final= GetTickCount()+BOARD_ROTATING_SPEED;
		view_x=VIEW_4_X;
		view_y=VIEW_4_Y;
		view_z=VIEW_4_Z;
		cursor_pos[0]=cursor_pos[1]=-1;
		VIEW_ANIMATING=true;
		cam_up_vec[0]=cam_up_vec[2]=0;
		cam_up_vec[1]=1;
		animate_view_4_to_3(0);
	}
}


void process_view() {
	glFrustum( -xy_aspect*.04, xy_aspect*.04, -.04, .04, .1, 200.0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
		
	gluLookAt(view_x,view_y,view_z,0,0,0,cam_up_vec[0],cam_up_vec[1],cam_up_vec[2]);
	
	glMultMatrixf( view_rotate );
	glTranslatef( obj_pan[0], obj_pan[1], obj_pan[2] );
	glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2]);
}

void draw_axii() {
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(1.0,0.0,0.0);
	glPushMatrix();
	glRotated(90.0, 0.0,1.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		axis_lenght, axis_nslices, axis_nstacks);   
	glPopMatrix();


	glColor3f(0.0,1.0,0.0);
	glPushMatrix();
	glRotated(-90.0, 1.0,0.0,0.0 );
	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		axis_lenght, axis_nslices, axis_nstacks);   
	glPopMatrix();


	glColor3f(0.0,0.0,1.0);
	glPushMatrix();

	gluCylinder(glQ, axis_radius_begin, axis_radius_end,
		axis_lenght, axis_nslices, axis_nstacks);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void configure_quadrics() 
{
	gluQuadricOrientation( glQ, GLU_OUTSIDE);

	gluQuadricDrawStyle(glQ, GLU_FILL);
	gluQuadricNormals(glQ, GLU_SMOOTH);
	gluQuadricOrientation(glQ, GLU_OUTSIDE);
	gluQuadricTexture(glQ, GL_FALSE);
}

void update_light(bool drawLightBulb = false) {	
	light0_position[0] = light0x;
	light0_position[1] = light0y;
	light0_position[2] = light0z;

	light1_position[0] = light1x;
	light1_position[1] = light1y;
	light1_position[2] = light1z;

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	if (drawLightBulb)
	{
		//glEnable(GL_COLOR_MATERIAL);
		glColor3f(1.0,1.0,0.0);
		gluQuadricOrientation( glQ, GLU_INSIDE);
		glPushMatrix();
		glTranslated(light0x,light0y,light0z);
		gluSphere(glQ, symb_light0_radius, symb_light0_slices, symb_light0_stacks);
		glPopMatrix();
		
		glColor3f(1.0,1.0,0.0);
		gluQuadricOrientation( glQ, GLU_INSIDE);
		glPushMatrix();
		glTranslated(light1x,light1y,light1z);
		gluSphere(glQ, symb_light1_radius, symb_light1_slices, symb_light1_stacks);
		glPopMatrix();
		glDisable(GL_COLOR_MATERIAL);
	}
}

void drawHUD() {

	std::string text=game_time.get();
	std::string text2=turn_time.get();

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,window_w,0,window_h,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glColor4f(0.6,0.6,0.6,0.9);
	glBegin(GL_POLYGON);
		glVertex2d(0,window_h);
		glVertex2d(0,window_h-40);
		glVertex2d(65,window_h-40);
		glVertex2d(65,window_h);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2d(window_w-65,window_h);
	glVertex2d(window_w-65,window_h-40);
	glVertex2d(window_w,window_h-40);
	glVertex2d(window_w,window_h);
	glEnd();
	
	glPushMatrix();
	glColor3f(50, 50,50);		
	glRasterPos3f(10, window_h-30, 0);

	for (unsigned i = 0; i < text.size(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}
	glPopMatrix();


	if(!REPLAY){
		glPushMatrix();

		glRasterPos3f(window_w*0.5-10, window_h-30, 0);

		for (unsigned i = 0; i < text.size(); ++i) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
		}

		glPopMatrix();
	}

	glPushMatrix();
	glRasterPos3f(window_w-45, window_h-30, 0);

		
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, one_wins+'0');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, '-');
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, two_wins+'0');
	

	glPopMatrix();


	
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_text(double r, double g, double b, double a, double x, double y, std::string text){
	glPushMatrix();
	glColor3f(r, g, b);		
	glRasterPos3f(x, y, 0);
	
	for (unsigned i = 0; i < text.size(); ++i) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
	}

	glPopMatrix();
}

void process_menu_view(){
	glOrtho(0,window_w,0,window_h,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void draw_start_menu(GLenum mode){

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslated((window_w-window_h)/2.0,0,0);

	if(mode == GL_RENDER){

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,3);

		glColor4f(0.6,0.6,0.6,0.9);
		glBegin(GL_POLYGON);
		
		glVertex2d(window_h*0.1,window_h*0.3);
		
		glVertex2d(window_h*0.9,window_h*0.3);
		
		glVertex2d(window_h*0.9,window_h*0.9);
		
		glVertex2d(window_h*0.1,window_h*0.9);
		glEnd();
	
		glColor4f(0.6,0.6,0.6,1);
		glBegin(GL_POLYGON);
		glTexCoord2f(0,0.1104);
		glVertex2d(window_h*0.2,window_h*0.73);
		glTexCoord2f(0.5996,0.1104);
		glVertex2d(window_h*0.8,window_h*0.73);
		glTexCoord2f(0.5996,0);
		glVertex2d(window_h*0.8,window_h*0.85);
		glTexCoord2f(0,0);
		glVertex2d(window_h*0.2,window_h*0.85);
		glEnd();
	}

	if (mode == GL_SELECT)
		glPushName(0);

	if(mode == GL_SELECT)
		glLoadName(1);

	glBegin(GL_POLYGON);
		glTexCoord2f(0,0.1955);
		glVertex2d(window_h*0.4,window_h*0.6);
		glTexCoord2f(0.2,0.1955);
		glVertex2d(window_h*0.6,window_h*0.6);
		glTexCoord2f(0.2,0.1104);
		glVertex2d(window_h*0.6,window_h*0.7);
		glTexCoord2f(0,0.1104);
		glVertex2d(window_h*0.4,window_h*0.7);
	glEnd();

	/*
	if(mode == GL_SELECT)
		glLoadName(2);

	glBegin(GL_POLYGON);
	glTexCoord2f(0,0.2806);
	glVertex2d(window_h*0.4,window_h*0.48);
	glTexCoord2f(0.2,0.2806);
	glVertex2d(window_h*0.6,window_h*0.48);
	glTexCoord2f(0.2,0.1955);
	glVertex2d(window_h*0.6,window_h*0.58);
	glTexCoord2f(0,0.1955);
	glVertex2d(window_h*0.4,window_h*0.58);
	glEnd();
	*/
	if(mode == GL_SELECT)
		glLoadName(3);

	glBegin(GL_POLYGON);
	glTexCoord2f(0,0.3657);
	glVertex2d(window_h*0.4,window_h*0.36);
	glTexCoord2f(0.2,0.3657);
	glVertex2d(window_h*0.6,window_h*0.36);
	glTexCoord2f(0.2,0.2806);
	glVertex2d(window_h*0.6,window_h*0.46);
	glTexCoord2f(0,0.2806);
	glVertex2d(window_h*0.4,window_h*0.46);
	glEnd();

	if(mode == GL_SELECT)
		glPopName();	

	glPopMatrix();

	if(mode == GL_RENDER)
		glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_type_menu(GLenum mode){

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslated((window_w-window_h)/2.0,0,0);

	if(mode == GL_RENDER){

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,3);

		glColor4f(0.6,0.6,0.6,0.9);
		glBegin(GL_POLYGON);

		glVertex2d(window_h*0.1,window_h*0.3);

		glVertex2d(window_h*0.9,window_h*0.3);

		glVertex2d(window_h*0.9,window_h*0.9);

		glVertex2d(window_h*0.1,window_h*0.9);
		glEnd();

		glColor4f(0.6,0.6,0.6,1);
		glBegin(GL_POLYGON);
		glTexCoord2f(0,0.4873);
		glVertex2d(window_h*0.2,window_h*0.73);
		glTexCoord2f(0.5996,0.4873);
		glVertex2d(window_h*0.8,window_h*0.73);
		glTexCoord2f(0.5996,0.377);
		glVertex2d(window_h*0.8,window_h*0.85);
		glTexCoord2f(0,0.377);
		glVertex2d(window_h*0.2,window_h*0.85);
		glEnd();
	}

	if (mode == GL_SELECT)
		glPushName(0);

	if(mode == GL_SELECT)
		glLoadName(4);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.2,0.1955);
	glVertex2d(window_h*0.4,window_h*0.6);
	glTexCoord2f(0.4,0.1955);
	glVertex2d(window_h*0.6,window_h*0.6);
	glTexCoord2f(0.4,0.1104);
	glVertex2d(window_h*0.6,window_h*0.7);
	glTexCoord2f(0.2,0.1104);
	glVertex2d(window_h*0.4,window_h*0.7);
	glEnd();

	if(mode == GL_SELECT)
		glLoadName(5);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.2,0.2806);
	glVertex2d(window_h*0.4,window_h*0.48);
	glTexCoord2f(0.4,0.2806);
	glVertex2d(window_h*0.6,window_h*0.48);
	glTexCoord2f(0.4,0.1955);
	glVertex2d(window_h*0.6,window_h*0.58);
	glTexCoord2f(0.2,0.1955);
	glVertex2d(window_h*0.4,window_h*0.58);
	glEnd();

	if(mode == GL_SELECT)
		glLoadName(6);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.2,0.3657);
	glVertex2d(window_h*0.4,window_h*0.36);
	glTexCoord2f(0.4,0.3657);
	glVertex2d(window_h*0.6,window_h*0.36);
	glTexCoord2f(0.4,0.2806);
	glVertex2d(window_h*0.6,window_h*0.46);
	glTexCoord2f(0.2,0.2806);
	glVertex2d(window_h*0.4,window_h*0.46);
	glEnd();

	if(mode == GL_SELECT)
		glLoadName(13);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.6,0.1104);
	glVertex2d(window_h*0.78,window_h*0.31);
	glTexCoord2f(0.72,0.1140);
	glVertex2d(window_h*0.88,window_h*0.31);
	glTexCoord2f(0.72,0);
	glVertex2d(window_h*0.88,window_h*0.41);
	glTexCoord2f(0.6,0);
	glVertex2d(window_h*0.78,window_h*0.41);
	glEnd();

	if(mode == GL_SELECT)
		glPopName();	

	glPopMatrix();

	if(mode == GL_RENDER)
		glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_dif_menu(GLenum mode){

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslated((window_w-window_h)/2.0,0,0);

	if(mode == GL_RENDER){

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,3);

		glColor4f(0.6,0.6,0.6,0.9);
		glBegin(GL_POLYGON);

		glVertex2d(window_h*0.1,window_h*0.3);

		glVertex2d(window_h*0.9,window_h*0.3);

		glVertex2d(window_h*0.9,window_h*0.9);

		glVertex2d(window_h*0.1,window_h*0.9);
		glEnd();

		glColor4f(0.6,0.6,0.6,1);
		glBegin(GL_POLYGON);
		glTexCoord2f(0,0.595);
		glVertex2d(window_h*0.2,window_h*0.73);
		glTexCoord2f(0.5996,0.595);
		glVertex2d(window_h*0.8,window_h*0.73);
		glTexCoord2f(0.5996,0.4873);
		glVertex2d(window_h*0.8,window_h*0.85);
		glTexCoord2f(0,0.4873);
		glVertex2d(window_h*0.2,window_h*0.85);
		glEnd();
	}

	if (mode == GL_SELECT)
		glPushName(0);

	
	for(int i=0; i< CPU_COUNT; ++i){

	if(mode == GL_SELECT)
		glLoadName(7);

	if(CPU_COUNT == 2){
		if(mode == GL_SELECT && i==1)
			glLoadName(10);

		glPushMatrix();
		if(i==0)
			glTranslatef(-window_h*0.15,0,0);
		else
			glTranslatef(window_h*0.15,0,0);
	}

	glBegin(GL_POLYGON);
	glTexCoord2f(0.4,0.1955);
	glVertex2d(window_h*0.4,window_h*0.6);
	glTexCoord2f(0.6,0.1955);
	glVertex2d(window_h*0.6,window_h*0.6);
	glTexCoord2f(0.6,0.1104);
	glVertex2d(window_h*0.6,window_h*0.7);
	glTexCoord2f(0.4,0.1104);
	glVertex2d(window_h*0.4,window_h*0.7);
	glEnd();

	if(CPU_COUNT == 2)
		glPopMatrix();

	if(mode == GL_SELECT)
		glLoadName(8);

	if(CPU_COUNT == 2){
		if(mode == GL_SELECT && i==1)
			glLoadName(11);

		glPushMatrix();
		if(i==0)
			glTranslatef(-window_h*0.15,0,0);
		else
			glTranslatef(window_h*0.15,0,0);
	}

	glBegin(GL_POLYGON);
	glTexCoord2f(0.4,0.2806);
	glVertex2d(window_h*0.4,window_h*0.48);
	glTexCoord2f(0.6,0.2806);
	glVertex2d(window_h*0.6,window_h*0.48);
	glTexCoord2f(0.6,0.1955);
	glVertex2d(window_h*0.6,window_h*0.58);
	glTexCoord2f(0.4,0.1955);
	glVertex2d(window_h*0.4,window_h*0.58);
	glEnd();

	if(CPU_COUNT == 2)
		glPopMatrix();

	if(mode == GL_SELECT)
		glLoadName(9);

	if(CPU_COUNT == 2){
		if(mode == GL_SELECT && i==1)
			glLoadName(12);

		glPushMatrix();
		if(i==0)
			glTranslatef(-window_h*0.15,0,0);
		else
			glTranslatef(window_h*0.15,0,0);
	}

	glBegin(GL_POLYGON);
	glTexCoord2f(0.4,0.3657);
	glVertex2d(window_h*0.4,window_h*0.36);
	glTexCoord2f(0.6,0.3657);
	glVertex2d(window_h*0.6,window_h*0.36);
	glTexCoord2f(0.6,0.2806);
	glVertex2d(window_h*0.6,window_h*0.46);
	glTexCoord2f(0.4,0.2806);
	glVertex2d(window_h*0.4,window_h*0.46);
	glEnd();

	if(CPU_COUNT == 2)
		glPopMatrix();

	}

	if(mode == GL_SELECT)
		glLoadName(13);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.6,0.1104);
	glVertex2d(window_h*0.78,window_h*0.31);
	glTexCoord2f(0.72,0.1140);
	glVertex2d(window_h*0.88,window_h*0.31);
	glTexCoord2f(0.72,0);
	glVertex2d(window_h*0.88,window_h*0.41);
	glTexCoord2f(0.6,0);
	glVertex2d(window_h*0.78,window_h*0.41);
	glEnd();

	if(mode == GL_SELECT)
		glPopName();	

	glPopMatrix();

	if(mode == GL_RENDER)
		glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_info_menu(GLenum mode){

}

void draw_final_menu(GLenum mode){

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glTranslated((window_w-window_h)/2.0,0,0);

	if(mode == GL_RENDER){

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,3);

		glColor4f(0.6,0.6,0.6,0.9);
		glBegin(GL_POLYGON);

		glVertex2d(window_h*0.1,window_h*0.3);

		glVertex2d(window_h*0.9,window_h*0.3);

		glVertex2d(window_h*0.9,window_h*0.9);

		glVertex2d(window_h*0.1,window_h*0.9);
		glEnd();

		if(winner==1){
			glColor4f(0.6,0.6,0.6,1);
			glBegin(GL_POLYGON);
			glTexCoord2f(0,0.7);
			glVertex2d(window_h*0.2,window_h*0.73);
			glTexCoord2f(0.5996,0.7);
			glVertex2d(window_h*0.8,window_h*0.73);
			glTexCoord2f(0.5996,0.595);
			glVertex2d(window_h*0.8,window_h*0.85);
			glTexCoord2f(0,0.595);
			glVertex2d(window_h*0.2,window_h*0.85);
			glEnd();
		} else {
			glColor4f(0.6,0.6,0.6,1);
			glBegin(GL_POLYGON);
			glTexCoord2f(0,0.814);
			glVertex2d(window_h*0.2,window_h*0.73);
			glTexCoord2f(0.5996,0.814);
			glVertex2d(window_h*0.8,window_h*0.73);
			glTexCoord2f(0.5996,0.7);
			glVertex2d(window_h*0.8,window_h*0.85);
			glTexCoord2f(0,0.7);
			glVertex2d(window_h*0.2,window_h*0.85);
			glEnd();
		}
	}

	if (mode == GL_SELECT)
		glPushName(0);

	if(mode == GL_SELECT)
		glLoadName(1);

	glBegin(GL_POLYGON);
	glTexCoord2f(0,0.1955);
	glVertex2d(window_h*0.4,window_h*0.6);
	glTexCoord2f(0.2,0.1955);
	glVertex2d(window_h*0.6,window_h*0.6);
	glTexCoord2f(0.2,0.1104);
	glVertex2d(window_h*0.6,window_h*0.7);
	glTexCoord2f(0,0.1104);
	glVertex2d(window_h*0.4,window_h*0.7);
	glEnd();

	if(mode == GL_SELECT)
		glLoadName(14);

	glBegin(GL_POLYGON);
	glTexCoord2f(0.6,0.1955);
	glVertex2d(window_h*0.4,window_h*0.48);
	glTexCoord2f(0.8,0.1955);
	glVertex2d(window_h*0.6,window_h*0.48);
	glTexCoord2f(0.8,0.1104);
	glVertex2d(window_h*0.6,window_h*0.58);
	glTexCoord2f(0.6,0.1104);
	glVertex2d(window_h*0.4,window_h*0.58);
	glEnd();

	if(mode == GL_SELECT)
		glLoadName(3);

	glBegin(GL_POLYGON);
	glTexCoord2f(0,0.3657);
	glVertex2d(window_h*0.4,window_h*0.36);
	glTexCoord2f(0.2,0.3657);
	glVertex2d(window_h*0.6,window_h*0.36);
	glTexCoord2f(0.2,0.2806);
	glVertex2d(window_h*0.6,window_h*0.46);
	glTexCoord2f(0,0.2806);
	glVertex2d(window_h*0.4,window_h*0.46);
	glEnd();

	if(mode == GL_SELECT)
		glPopName();	

	glPopMatrix();

	if(mode == GL_RENDER)
		glDisable(GL_TEXTURE_2D);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_menu(){
	if(MENU_MODE){
		glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		process_menu_view();
		menu_window[current_menu_window](GL_RENDER);
	}
}

void start_game_logic(int d){

	if(winner!=0)
	{
		if(winner==1)
			one_wins++;
		else
			two_wins++;
		next_cam=3;
		camCB(0);
		cursor_pos[0]=cursor_pos[1]=-1;
		ALLOW_USER_INPUT=0;
		MENU_MODE=1;
		current_menu_window=4;
		//listbox->enable();
		//radioGroup->disable();
		return;
	}

	if(!ANIMATING)
		if(true/*board.is_human()*/){

		}else{
			/*
			if(!REQUEST_SENT){
				li.request_ai_move(board.to_string(),board.get_turn(),board.get_player_type(board.get_turn()));
				REQUEST_SENT=true;
			}
			else{
				if(li.parse_ai_move(pos_i,pos_f) == Logic_interface::get_code_success()){
					REQUEST_SENT=false;

					if(pos_i.valid()){

						bool is_n_human = board.is_next_human();
						animate_piece(pos_i.x,pos_i.y,pos_f.x,pos_f.y);

						if(!REQUEST_SENT)
						{
							REQUEST_SENT=true;
							li.request_winner_verification(board.to_string(),board.get_next_turn());
							while(1){
								bool won;
								int code = li.parse_winner_verification(won);
								if(code != Logic_interface::get_code_error_no_data_available()){
									REQUEST_SENT=false;
									if(code==Logic_interface::get_code_success())
										if(won)
											winner=board.get_next_turn();
									break;
								}
							}
						}

						if(!is_n_human){
							if(!REQUEST_SENT){
								li.request_ai_move(board.to_string(),board.get_next_turn(),board.get_player_type(board.get_next_turn()));
								REQUEST_SENT=true;
							}
						}

					}

				} 
				else if(li.parse_ai_move(pos_i,pos_f) == Logic_interface::get_code_error_server_disconnect())
				{

				}
			}
			*/
		}

		
		glutTimerFunc(DELTA_T,start_game_logic,0);
}

void removeTurn(int d){
	if(d==curTurn)
		drawTurn=0;
}

void displayTurn(int d){

	drawTurn=1;
	curTurn=d;

	std::stringstream ss;
	ss << "Turno do jogador " << d;
	turn_message=ss.str();

	glutTimerFunc(2000,removeTurn,d);
}

void game_cb_thread();

void start_game(int d){

	winner=0;

	std::vector<AI_details> ai;
	AI_details p1_dets,p2_dets;

	
	p1_dets.algo       = (Algorithm)j1_algorithm->get_int_val();
	p1_dets.difficulty = (Difficulty)j1_difficulty->get_int_val();
	p1_dets.heuristic  = (Heuristic)j1_heuristic->get_int_val();
	p1_dets.reordering = (Reordering)j1_reordering->get_int_val();

	p2_dets.algo       = (Algorithm)j2_algorithm->get_int_val();
	p2_dets.difficulty = (Difficulty)j2_difficulty->get_int_val();
	p2_dets.heuristic  = (Heuristic)j2_heuristic->get_int_val();
	p2_dets.reordering = (Reordering)j2_reordering->get_int_val();

	ai.push_back(p1_dets);
	ai.push_back(p2_dets);

	players.push_back(!j1_type_var);
	players.push_back(!j2_type_var);

	if(n_players==1){
		AI_details p3_dets,p4_dets;

		p3_dets.algo       = (Algorithm)j3_algorithm->get_int_val();
		p3_dets.difficulty = (Difficulty)j3_difficulty->get_int_val();
		p3_dets.heuristic  = (Heuristic)j3_heuristic->get_int_val();
		p3_dets.reordering = (Reordering)j3_reordering->get_int_val();

		p4_dets.algo       = (Algorithm)j4_algorithm->get_int_val();
		p4_dets.difficulty = (Difficulty)j4_difficulty->get_int_val();
		p4_dets.heuristic  = (Heuristic)j4_heuristic->get_int_val();
		p4_dets.reordering = (Reordering)j4_reordering->get_int_val();

		ai.push_back(p3_dets);
		ai.push_back(p4_dets);

		players.push_back(!j3_type_var);
		players.push_back(!j4_type_var);

	}
	
	board = Board_g(players.size()/2);
	Game* game = new Game(players, ai);
	logic = new logic_interface(game);
	
	//board=Board(b);
	
	STARTED=1;
	MENU_MODE=0;
	ALLOW_USER_INPUT=0;
	prev_cam=1;
	
	
	glui->hide();

	start_view_4_to_2();
	boost::thread t(&game_cb_thread);
	
}

void switch_menus(int v){

	switch (v)
	{
	case 1:
		current_menu_window = 1;
		break;
	case 2:
		current_menu_window=3;
		break;
	case 3:
		exit(0);
		break;
	case 4:
		p1=p2=0;
		CPU_COUNT=1;
		start_game(0);
		break;
	case 5:
		p1=0;
		p2=-1;
		current_menu_window=2;
		CPU_COUNT=1;
		break;
	case 6:
		p1=p2=-1;
		current_menu_window=2;
		CPU_COUNT=2;
		break;
	case 7:
		if(CPU_COUNT==2)
			p1=1;
		else
			p2=1;
		if(p2!=-1)
			start_game(0);
		break;
	case 8:
		if(CPU_COUNT==2)
			p1=2;
		else
			p2=2;
		if(p2!=-1)
			start_game(0);
		break;
	case 9:
		if(CPU_COUNT==2)
			p1=3;
		else
			p2=3;
		if(p2!=-1)
			start_game(0);
		break;
	case 10:
		p2=1;
		if(p1!=-1)
			start_game(0);
		break;
	case 11:
		p2=2;
		if(p1!=-1)
			start_game(0);
		break;
	case 12:
		p2=3;
		if(p1!=-1)
			start_game(0);
		break;
	case 13:
		p1=p2=-1;
		if(current_menu_window==2)
			current_menu_window=1;
		else if(current_menu_window==1)
			current_menu_window=0;
		break;
	case 14:
		//RePLAY
		current_moves_history = 0;
		//moves_history = board.get_move_history_count();
		REPLAY=1;
		ALLOW_USER_INPUT=0;
		MENU_MODE=0;
		board.reset();
		prev_cam=1;
		start_view_4_to_2();
		//play_movie(0);
		break;
	}
}

void drawFloor(){
	double h=-1.5,rep=25;

	
	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	Material_components (0.0,0.0,0.0,1,  0.0,0.0,0.0,1,  0.8,0.8,0.8,1,  32).act();
	glBindTexture(GL_TEXTURE_2D,1);	

	glBegin(GL_POLYGON);
		glNormal3d(0,1,0);
		glTexCoord2f(rep,rep);glVertex3d(50,h,50);
		glTexCoord2f(rep,0);glVertex3d(50,h,-50);
		glTexCoord2f(0,0);glVertex3d(-50,h,-50);
		glTexCoord2f(0,rep);glVertex3d(-50,h,50);
	glEnd();

	//glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);
	
}

void draw_win(){

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,window_w,0,window_h,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	glColor3f(50, 50,50);		
	glRasterPos3f(10, window_h-30, 0);
	//glRasterPos3f(50, 5, 0);
	
	for(int i=0; i<win_message.size(); ++i)
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char)win_message[i]);
	glPopMatrix();



	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_turn(){

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,window_w,0,window_h,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();

	switch (curTurn)
	{
	case 1:glColor3f(80, 0,0);
		break;
	case 2:glColor3f(0, 0,0);
		break;
	case 3:glColor3f(0, 40,0);
		break;
	case 4:glColor3f(0.96, 0.92,0.22);
		break;
	}
			
	glRasterPos3f(10, window_h-50, 0);
	//glRasterPos3f(50, 5, 0);

	for(int i=0; i<turn_message.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char)turn_message[i]);
	glPopMatrix();



	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void draw_processing(){

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,window_w,0,window_h,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();

	
	glColor3f(30, 30,30);
	

	glRasterPos3f(window_w/2.5, window_h-50, 0);
	//glRasterPos3f(50, 5, 0);

	std::string msg="A processar...";

	for(int i=0; i<msg.size(); ++i)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (char)msg[i]);
	glPopMatrix();



	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void drawLogo(){

	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	process_menu_view();
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glPushMatrix();
	//glTranslated((window_w-window_h)/2.0,0,0);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,3);

	//glColor4f(0.6,0.6,0.6,0.9);
	glBegin(GL_POLYGON);

	glTexCoord2f(0,0); glVertex2d(0,0);
	glTexCoord2f(1,0); glVertex2d(window_w,0);
	glTexCoord2f(1,1); glVertex2d(window_w,window_h);
	glTexCoord2f(0,1); glVertex2d(0,window_h);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	board.set_cursor(cursor_pos[0],cursor_pos[1]);

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();	
	process_view();

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	
	//draw_axii();
	
	configure_quadrics();
	update_light();
	
	if(STARTED){
		board.render(GL_RENDER);
		drawFloor();
	}
	else{
		drawLogo();
	}
	
	
	
	if(PROCESSING)
		draw_processing();

	if(drawTurn)
		draw_turn();

	if(winner)
		draw_win();

	glutSwapBuffers();
	glFlush();
	boost::this_thread::sleep(boost::posix_time::milliseconds(20));
}

void processHitsPassive (GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
	GLuint nnames, *ptr;
	GLuint selected_nnames, *selected_ptr;
	unsigned int z1=0, z2=0;
	unsigned int selected_z1, selected_z2;

	pk2->resetEstados();
	if (hits == 0){
		cursor_pos[0]=cursor_pos[1]=-1;
		return;
	}

	ptr = (GLuint *) buffer;

	for (i = 0; i < hits; i++) 
	{	
		nnames = *ptr; ptr++;
		for(int a=0; a<2; ++a) ptr++;
		selected_ptr=ptr;
		for (j = 0; j < nnames; j++) ptr++;

	}

	for (j = 0; j < nnames; j++)
	{
		if(j<2)
		cursor_pos[j] =*selected_ptr;
		selected_ptr++;
	}
	
	
	selected_ptr--;
	pk2->setEstado(*selected_ptr);
	dx2 = dxAc2 = pk2->getDx(*selected_ptr);
	dz2 = dzAc2 = pk2->getDz(*selected_ptr);

}

void processHits (GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
    GLuint nnames, *ptr;
	GLuint selected_nnames, *selected_ptr;
	unsigned int z1=0, z2=0;
	unsigned int selected_z1, selected_z2;

	pk->resetEstados();
	if (hits == 0){
		m_p=0;
		board.deselect(); //////MINE
		return;
	}

    ptr = (GLuint *) buffer;

    for (i = 0; i < hits; i++) 
	{	
		
		nnames = *ptr; ptr++;
		for(int a=0; a<2; ++a) ptr++;
		selected_ptr=ptr;
		for (j = 0; j < nnames; j++) ptr++;
			
	}

	for (j = 0; j < nnames; j++)
		{
			
			moves[m_p] =*selected_ptr;
			selected_ptr++;

			if(++m_p == 4){
				m_p=0;

				
				if(board.is_valid_cell(moves[2],moves[3])){
					int turn = board.get_turn();

					logic->move(Vector_2D(moves[0],moves[1]),Vector_2D(moves[2],moves[3]));
						
				}
				else
				{
					m_p=2;
					moves[0]=moves[2];
					moves[1]=moves[3];
				}
				board.deselect();
				//printf("%d %d %d %d",moves[0],moves[1],moves[2],moves[3]);
				
			}
			if(m_p == 2){

				logic->select(1,Vector_2D(moves[0],moves[1]));

			}

		}
		//printf ("\n\n");

	selected_ptr--;
	pk->setEstado(*selected_ptr);
	dx = dxAc = pk->getDx(*selected_ptr);		// obtem dados da posicao actual do objecto
	dz = dzAc = pk->getDz(*selected_ptr);

}

void processHitsMenu (GLint hits, GLuint buffer[])
{
	int i;
	unsigned int j;
	GLuint nnames, *ptr;
	GLuint selected_nnames, *selected_ptr;
	unsigned int z1=0, z2=0;
	unsigned int selected_z1, selected_z2;

	pk->resetEstados();
	if (hits == 0){
		return;
	}

	ptr = (GLuint *) buffer;

	for (i = 0; i < hits; i++) 
	{	
		nnames = *ptr; ptr++;
		for(int a=0; a<2; ++a) ptr++;
		selected_ptr=ptr;
		for (j = 0; j < nnames; j++) ptr++;
	}

	for (j = 0; j < nnames; j++)
	{
		int value = *selected_ptr;
		selected_ptr++;

		switch_menus(value);
	}

	selected_ptr--;
	pk->setEstado(*selected_ptr);
	dx = dxAc = pk->getDx(*selected_ptr);		// obtem dados da posicao actual do objecto
	dz = dzAc = pk->getDz(*selected_ptr);
}

struct g_mouseState{
	bool leftButton;
	bool rightButton;
	bool middleButton;
	int x;
	int y;
} MouseState;

/* Mouse handling */
void processMouse(int button, int state, int x, int y) {

	if((!REQUEST_SENT && ALLOW_USER_INPUT) || MENU_MODE){
		GLint hits;
		GLint viewport[4];

		// update our button state
		if(button == GLUT_LEFT_BUTTON) {
			if(state == GLUT_DOWN)
				MouseState.leftButton = true;
			else
				MouseState.leftButton = false;
		}
		if(button == GLUT_RIGHT_BUTTON) {
			if(state == GLUT_DOWN)
				MouseState.rightButton = true;
			else
				MouseState.rightButton = false;
		}
		if(button == GLUT_MIDDLE_BUTTON) {
			if(state == GLUT_DOWN)
				MouseState.middleButton = true;
			else
				MouseState.middleButton = false;
		}

		// update our position so we know a delta when the mouse is moved
		MouseState.x = x;
		MouseState.y = y;

		if (MouseState.leftButton && !MouseState.rightButton && !MouseState.middleButton && !MENU_MODE && !ANIMATING) {

			glGetIntegerv(GL_VIEWPORT, viewport);

			glSelectBuffer (BUFSIZE, selectBuf);
			glRenderMode (GL_SELECT);

			// inicia processo de picking
			glInitNames();
			glMatrixMode (GL_PROJECTION);
			glPushMatrix ();

			glLoadIdentity ();
			gluPickMatrix ((GLdouble) x, (GLdouble) (window_h - y), 1.0, 1.0, viewport);

			process_view();
			board.render(GL_SELECT);

			glMatrixMode (GL_PROJECTION);
			glPopMatrix ();
			glFlush ();

			hits = glRenderMode(GL_RENDER);
			processHits(hits, selectBuf);
		}

		if (MouseState.leftButton && !MouseState.rightButton && !MouseState.middleButton && MENU_MODE){
			glGetIntegerv(GL_VIEWPORT, viewport);

			glSelectBuffer (BUFSIZE, selectBuf);
			glRenderMode (GL_SELECT);

			// inicia processo de picking
			glInitNames();
			glMatrixMode (GL_PROJECTION);
			glPushMatrix ();

			glLoadIdentity ();
			gluPickMatrix ((GLdouble) x, (GLdouble) (window_h - y), 1.0, 1.0, viewport);

			process_menu_view();
			menu_window[current_menu_window](GL_SELECT);

			glMatrixMode (GL_PROJECTION);
			glPopMatrix ();
			glFlush ();

			hits = glRenderMode(GL_RENDER);
			processHitsMenu(hits, selectBuf);
		}
	}
}

void processMouseMoved(int x, int y)
{
	// pedido de refrescamento da janela
	glutPostRedisplay();				
}

long int MOUSE_LAST_MOVED=0;

void processPassiveMouseMoved(int x, int y)
{
	
	if(MOUSE_LAST_MOVED+50 < GetTickCount() && !VIEW_ANIMATING && ALLOW_USER_INPUT){
		MOUSE_LAST_MOVED=GetTickCount();
		GLint hits;
		GLint viewport[4];

		glGetIntegerv(GL_VIEWPORT, viewport);

		glSelectBuffer (BUFSIZE, selectBuf2);
		glRenderMode (GL_SELECT);

		// inicia processo de picking
		glInitNames();
		glMatrixMode (GL_PROJECTION);
		glPushMatrix ();

		glLoadIdentity ();
		gluPickMatrix ((GLdouble) x, (GLdouble) (window_h - y), 1.0, 1.0, viewport);

		process_view();
		board.render_only_board();

		glMatrixMode (GL_PROJECTION);
		glPopMatrix ();
		glFlush ();

		hits = glRenderMode(GL_RENDER);
		processHitsPassive(hits, selectBuf2);
		
	}
	
		//glutPostRedisplay();
}

void reshape(int w, int h)
{
	int tx, ty, tw, th;

	window_w = w;	//variaveis globais; window_h e' usado em processMouse()
	window_h = h;

	GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
	glViewport( tx, ty, tw, th );
	xy_aspect = (float)tw / (float)th;

	glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y)
{
	
   switch (key) {
      case 27:		// tecla de escape termina o programa
		  exit(0);
         break;
	  case 'l':
		  break;
	  case '1':
		  PAWN_PIECE_ANIM_INTERVAL=anim_speeds[0];
		  break;
	 case '2':
		  PAWN_PIECE_ANIM_INTERVAL=anim_speeds[1];
		  break;
	 case '3':
		  PAWN_PIECE_ANIM_INTERVAL=anim_speeds[2];
		  break;
	 case '4':
		  PAWN_PIECE_ANIM_INTERVAL=anim_speeds[3];
		  break;
	  /*case '1':
		  animate_piece(1,2 ,0,1);
		  break;
	  case '2':
		  animate_piece(1,2 ,1,1);
		  break;
	  case '3':
		  animate_piece(1,2 ,2,1);
		  break;
	  case '4':
		  animate_piece(0,1 ,1,2);
		  break;
	  case '5':
		  animate_piece(1,1 ,1,2);
		  break;
	  case '6':
		  animate_piece(2,1 ,1,2);
		  break;*/
   }
}


void glut_idle( void )
{
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  

  glutPostRedisplay();

}

void render_init()
{
	glQ = gluNewQuadric();

	glFrontFace(GL_CCW);		// Front faces defined using a counterclockwise rotation
	glDepthFunc(GL_LEQUAL);		// Por defeito e GL_LESS
	glEnable(GL_DEPTH_TEST);	// Use a depth (z) buffer to draw only visible objects

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// Face Culling para aumentar a velocidade
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);		// GL_FRONT, GL_BACK, GL_FRONT_AND_BACK

	glDisable(GL_COLOR_MATERIAL);

	// Define que modelo de iluminacao utilizar; consultar o manual de referencia
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);  // define luz ambiente
	glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	glLightModeli (GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	
	// por defeito a cor de fundo e o preto
	// glClearColor(1.0,1.0,1.0,1.0);    // cor de fundo a branco


	// declaracoes para a fonte luz GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,  light0_kc);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION,    light0_kl);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light0_kq);

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION,  light1_kc);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION,    light1_kl);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, light1_kq);
	// NOTA: a direccao e a posicao de GL_LIGHT0 estao na rotina display(), pelo
	//       que as isntrucoes seguntes nao sao necessarias
	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glEnable(GL_NORMALIZE);	

	//glEnable(GL_MAP2_VERTEX_3);
	//glMapGrid2f(gridSize, 0.0, 1.0, gridSize, 0.0, 1.0);


	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT, GL_FILL);
	//glPolygonMode(GL_FRONT, GL_LINE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);

}

void do_nothing(int key, int x, int y) {}

void window_init( int argc, char* * argv ) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize (DIMX, DIMY);
	glutInitWindowPosition (INITIALPOS_X, INITIALPOS_Y);
	main_window = glutCreateWindow (argv[0]);
}


void animSpeedParse(int d)
{
	//PAWN_PIECE_ANIM_INTERVAL=anim_speeds[animSpeed];
	if(animSpeed==0)
		TURN_TIMEOUT=10;
	else if(animSpeed==1)
		TURN_TIMEOUT=30;
	else if(animSpeed==2)
		TURN_TIMEOUT=60;
}

void camCB(int d)
{
	++next_cam;
	for(int i=0; i<16; ++i)
		if(i==0 ||  i==5 ||  i==10  ||i==15)
			view_rotate[i]=1;
		else
			view_rotate[i]=0;
	obj_pan[0]=obj_pan[1]=obj_pan[2]=0;
	obj_pos[0]=obj_pos[1]=obj_pos[2]=0;
	//radioGroup->disable();
	if(prev_cam==1){
		if(next_cam==2){
			start_view_2_to_1();
		} else if(next_cam==3){
			start_view_2_to_3();
		} else if(next_cam==4){
			start_view_2_to_4();
		}
	} else if(prev_cam==2){
		if(next_cam==1){
			start_view_1_to_2();
		} else if(next_cam==3){
			start_view_1_to_3();
		} else if(next_cam==4){
			start_view_1_to_4();
		}
	}
	else if(prev_cam==3){
		if(next_cam==1){
			start_view_3_to_2();
		} else if(next_cam==2){
			start_view_3_to_1();
		} else if(next_cam==4){
			start_view_3_to_4();
		}
	}
	else if(prev_cam==4){
		if(next_cam==1){
			start_view_4_to_2();
		} else if(next_cam==2){
			start_view_4_to_1();
		} else if(next_cam==3){
			start_view_4_to_3();
		}
	}
	else
		radioGroup->enable();
	prev_cam=next_cam;
}

void always_disable(){
	j3_algorithm->disable();
	j4_algorithm->disable();
	j3_reordering->disable();
	j3_heuristic->disable();
	j4_reordering->disable();
	j4_heuristic->disable();
	if(n_players==1){
		j1_algorithm->set_int_val(0);
		j2_algorithm->set_int_val(0);
		j1_heuristic->set_int_val(0);
		j2_heuristic->set_int_val(0);
		j1_reordering->set_int_val(0);
		j2_reordering->set_int_val(0);
		j1_algorithm->disable();
		j2_algorithm->disable();
		j1_reordering->disable();
		j1_heuristic->disable();
		j2_reordering->disable();
		j2_heuristic->disable();
	}
}

void j_type(int d){
	switch (d)
	{
	case 1:
		if(j1_type_var==1){
			j1_difficulty->enable();
			if(n_players==1){
				always_disable();
			}
			else
			{
				j1_heuristic->enable();
				j1_reordering->enable();
				j1_algorithm->enable();
			}
		}
		else{
			j1_difficulty->disable();
			j1_heuristic->disable();
			j1_reordering->disable();
			j1_algorithm->disable();
		}
		break;
	case 2:
		if(j2_type_var==1){
			j2_difficulty->enable();
			if(n_players==1){
				always_disable();
			}
			else
			{
				j2_heuristic->enable();
				j2_reordering->enable();
				j2_algorithm->enable();
			}
		}
		else{
			j2_difficulty->disable();
			j2_heuristic->disable();
			j2_reordering->disable();
			j2_algorithm->disable();
		}
		break;
	case 3:
		if(j3_type_var==1){
			if(n_players==1)
				j3_difficulty->enable();
		}
		else{
			j3_difficulty->disable();
		}
		break;
	case 4:
		if(j4_type_var==1){
			if(n_players==1)
				j4_difficulty->enable();
		}
		else{
			j4_difficulty->disable();
		}
		break;
	}
}

void n_players_cb(int d){
	if(n_players==1){
		
		j3_panel->enable();
		j4_panel->enable();
		always_disable();
		j_type(3);
		j_type(4);
	}
	else
	{
		if(j1_type_var==1){
			j1_heuristic->enable();
			j1_algorithm->enable();
			j1_reordering->enable();
		}
		if(j2_type_var==1){
			j2_algorithm->enable();
			j2_reordering->enable();
			j2_heuristic->enable();
		}
		j3_panel->disable();
		j4_panel->disable();
	}
}

void start_game(int d);

void UI_init() 
{
	glutDisplayFunc(display);
	
	GLUI_Master.set_glutReshapeFunc(reshape);
	GLUI_Master.set_glutKeyboardFunc (keyboard);
	GLUI_Master.set_glutMouseFunc(processMouse);      
	glutMotionFunc(processMouseMoved);
	glutPassiveMotionFunc(processPassiveMouseMoved);
	GLUI_Master.set_glutSpecialFunc( do_nothing );
	glutReshapeWindow( 800, 600);
	/*** Create the bottom subwindow ***/

	glui = GLUI_Master.create_glui("CONFIGURACOES",0, glutGet(GLUT_WINDOW_X) + window_w/3.7 ,  glutGet(GLUT_WINDOW_Y)+window_h/2.8 ); 
	glui->set_main_gfx_window( main_window );

	//radioGroup = glui->add_radiogroup(0,-1,0);
	//glui->add_radiobutton_to_group(radioGroup,"2 Jogadores");
	//glui->add_radiobutton_to_group(radioGroup,"4 Jogadores");
	
	n_players_checkbox = glui->add_checkbox("4 Jogadores",&n_players,1,n_players_cb);

	j1_panel = glui->add_panel( "Jogador 1" );
	

	j1_type_panel = glui->add_panel_to_panel(j1_panel, "Tipo" );
	j1_type = glui->add_radiogroup_to_panel(j1_type_panel,&j1_type_var,1,j_type);
	glui->add_radiobutton_to_group(j1_type,"Humano");
	glui->add_radiobutton_to_group(j1_type,"Computador");

	j1_heuristic = glui->add_listbox_to_panel(j1_panel,"Heuristic   ",NULL,-1, (GLUI_Update_CB) 0);
	j1_heuristic->add_item(0,"DISTANCE");
	j1_heuristic->add_item(1,"DISTANCE_AND_VALUE");

	j1_algorithm = glui->add_listbox_to_panel(j1_panel,"Algorithm  ",NULL,-1,(GLUI_Update_CB) 0);
	j1_algorithm->add_item(0,"MINIMAX");
	j1_algorithm->add_item(1,"MINIMAX_AB");
	j1_algorithm->add_item(2,"NEGASCOUT");
	j1_algorithm->add_item(3,"GREEDY");
	

	j1_reordering = glui->add_listbox_to_panel(j1_panel,"Reordering",NULL,-1,(GLUI_Update_CB) 0);
	j1_reordering->add_item(0,"NO_REORDERING");
	j1_reordering->add_item(1,"KILLER");
	
	j1_difficulty = glui->add_listbox_to_panel(j1_panel,"Difficulty   ",NULL,-1,(GLUI_Update_CB) 0);
	j1_difficulty->add_item(0,"EASY");
	j1_difficulty->add_item(1,"MEDIUM");
	j1_difficulty->add_item(2,"HARD");
	
	j2_panel = glui->add_panel( "Jogador 2" );

	j2_type_panel = glui->add_panel_to_panel(j2_panel, "Tipo" );
	j2_type = glui->add_radiogroup_to_panel(j2_type_panel,&j2_type_var,2,j_type);
	glui->add_radiobutton_to_group(j2_type,"Humano");
	glui->add_radiobutton_to_group(j2_type,"Computador");

	j2_heuristic = glui->add_listbox_to_panel(j2_panel,"Heuristic   ",NULL,-1, (GLUI_Update_CB)0);
	j2_heuristic->add_item(0,"DISTANCE");
	j2_heuristic->add_item(1,"DISTANCE_AND_VALUE");

	j2_algorithm = glui->add_listbox_to_panel(j2_panel,"Algorithm  ",NULL,-1, (GLUI_Update_CB) 0);
	j2_algorithm->add_item(0,"MINIMAX");
	j2_algorithm->add_item(1,"MINIMAX_AB");
	j2_algorithm->add_item(2,"NEGASCOUT");
	j2_algorithm->add_item(3,"GREEDY");


	j2_reordering = glui->add_listbox_to_panel(j2_panel,"Reordering",NULL,-1, (GLUI_Update_CB) 0);
	j2_reordering->add_item(0,"NO_REORDERING");
	j2_reordering->add_item(1,"KILLER");

	j2_difficulty = glui->add_listbox_to_panel(j2_panel,"Difficulty   ",NULL,-1, (GLUI_Update_CB) 0);
	j2_difficulty->add_item(0,"EASY");
	j2_difficulty->add_item(1,"MEDIUM");
	j2_difficulty->add_item(2,"HARD");

	glui->add_column(false);

	play_btn = glui->add_button("Jogar",-1,start_game);

	j3_panel = glui->add_panel( "Jogador 3" );

	j3_type_panel = glui->add_panel_to_panel(j3_panel, "Tipo" );
	j3_type = glui->add_radiogroup_to_panel(j3_type_panel,&j3_type_var,3,j_type);
	glui->add_radiobutton_to_group(j3_type,"Humano");
	glui->add_radiobutton_to_group(j3_type,"Computador");

	j3_heuristic = glui->add_listbox_to_panel(j3_panel,"Heuristic   ",NULL,-1, (GLUI_Update_CB) 0);
	j3_heuristic->add_item(0,"DISTANCE");
	j3_heuristic->add_item(1,"DISTANCE_AND_VALUE");

	j3_algorithm = glui->add_listbox_to_panel(j3_panel,"Algorithm  ",NULL,-1, (GLUI_Update_CB) 0);
	j3_algorithm->add_item(0,"MINIMAX");
	j3_algorithm->add_item(1,"MINIMAX_AB");
	j3_algorithm->add_item(2,"NEGASCOUT");
	j3_algorithm->add_item(3,"GREEDY");


	j3_reordering = glui->add_listbox_to_panel(j3_panel,"Reordering",NULL,-1, (GLUI_Update_CB) 0);
	j3_reordering->add_item(0,"NO_REORDERING");
	j3_reordering->add_item(1,"KILLER");

	j3_difficulty = glui->add_listbox_to_panel(j3_panel,"Difficulty   ",NULL,-1, (GLUI_Update_CB) 0);
	j3_difficulty->add_item(0,"EASY");
	j3_difficulty->add_item(1,"MEDIUM");
	j3_difficulty->add_item(2,"HARD");

	j4_panel = glui->add_panel( "Jogador 4" );

	j4_type_panel = glui->add_panel_to_panel(j4_panel, "Tipo" );
	j4_type = glui->add_radiogroup_to_panel(j4_type_panel,&j4_type_var,4,j_type);
	glui->add_radiobutton_to_group(j4_type,"Humano");
	glui->add_radiobutton_to_group(j4_type,"Computador");

	j4_heuristic = glui->add_listbox_to_panel(j4_panel,"Heuristic   ",NULL,-1, (GLUI_Update_CB) 0);
	j4_heuristic->add_item(0,"DISTANCE");
	j4_heuristic->add_item(1,"DISTANCE_AND_VALUE");

	j4_algorithm = glui->add_listbox_to_panel(j4_panel,"Algorithm  ",NULL,-1, (GLUI_Update_CB) 0);
	j4_algorithm->add_item(0,"MINIMAX");
	j4_algorithm->add_item(1,"MINIMAX_AB");
	j4_algorithm->add_item(2,"NEGASCOUT");
	j4_algorithm->add_item(3,"GREEDY");


	j4_reordering = glui->add_listbox_to_panel(j4_panel,"Reordering",NULL,-1, (GLUI_Update_CB) 0);
	j4_reordering->add_item(0,"NO_REORDERING");
	j4_reordering->add_item(1,"KILLER");

	j4_difficulty = glui->add_listbox_to_panel(j4_panel,"Difficulty   ",NULL,-1,(GLUI_Update_CB) 0);
	j4_difficulty->add_item(0,"EASY");
	j4_difficulty->add_item(1,"MEDIUM");
	j4_difficulty->add_item(2,"HARD");

	j3_panel->disable();
	j4_panel->disable();
	
	j1_difficulty->set_int_val(1);
	j1_difficulty->disable();
	j1_heuristic->disable();
	j1_reordering->disable();
	j1_algorithm->disable();
	j2_difficulty->set_int_val(1);
	j2_difficulty->disable();
	j2_heuristic->disable();
	j2_reordering->disable();
	j2_algorithm->disable();
	j3_difficulty->set_int_val(1);
	j4_difficulty->set_int_val(1);
	GLUI_Master.set_glutIdleFunc( glut_idle );
}

void tick_game_time(int d){
	if(!ANIMATING && !REPLAY)
		turn_time.dec();
	if(turn_time.is_zero())
		winner = board.get_turn();

	game_time.inc();
	glutTimerFunc(1000, tick_game_time, 0);
}

void game_logic_loop(int d){





	glutTimerFunc(DELTA_T,game_logic_loop,0);
}

void anim_init()
{
	 glutTimerFunc(1000, tick_game_time, 0);
	
}

void texture_init(){

	RGBpixmap *pixmap = new RGBpixmap();
	pixmap->readBMPFile("textures/wood.bmp");
	pixmap->setTexture(1);

	pixmap->readBMPFile("textures/board_tex.bmp");
	pixmap->setTexture(2);

	pixmap->readBMPFile("textures/logo.bmp");
	pixmap->setTexture(3);

	//pixmap->readBMPFile("textures/menu-tex.bmp");
	//pixmap->setTexture(3);
}

void init( int argc, char* * argv ) 
{
	window_init(argc, argv);

	UI_init();

	//anim_init();

	render_init();

	texture_init();
}

void parseMove(MoveEvent e){
	while(ANIMATING){boost::this_thread::sleep(boost::posix_time::milliseconds(1));}
	PROCESSING=0;
	animate_piece(e.getInit().x(),e.getInit().y(),e.getFinal().x(),e.getFinal().y());
}

void parseAvailableMoves(AvailableMovesEvent e){

	board.set_selected(e.getOwn().x(), e.getOwn().y());
	board.set_valid_squares(e.getMoves());
}

void parseWin(WinEvent e){
	while(ANIMATING){boost::this_thread::sleep(boost::posix_time::milliseconds(1));
;}
	winner=1;
	std::stringstream ss;
	ss << "O jogador " << e.getPlayer() << " ganhou!";
	win_message=ss.str();
}

void parsePass(PassEvent e){

}

void parseProcessing(ProcessingEvent e){
	PROCESSING=1;
}

void parseTurn(TurnEvent e){
	ALLOW_USER_INPUT=0;
	board.deselect();
	cursor_pos[0]=cursor_pos[1]=-1;
	
	while(ANIMATING){boost::this_thread::sleep(boost::posix_time::milliseconds(1));}
	
	if(players[e.getPlayer()-1]==1)
		ALLOW_USER_INPUT=1;
	

	glutTimerFunc(0,displayTurn,e.getPlayer());
}

void game_cb_thread(){
	while(1){
		boost::this_thread::sleep(boost::posix_time::milliseconds(20));

		if(!logic->queue()->empty() && winner == 0){
			BoardEvent *e = logic->queue()->pop();

			if(e->isMove())
				parseMove(*((MoveEvent*)e));
			else if(e->isAvailableMoves())
				parseAvailableMoves(*((AvailableMovesEvent*)e));
			else if(e->isWin())
				parseWin(*((WinEvent*)e));
			else if(e->isPass())
				parsePass(*((PassEvent*)e));
			else if(e->isTurn())
				parseTurn(*((TurnEvent*)e));
			else if(e->isProcessing())
				parseProcessing(*((ProcessingEvent*)e));

			delete e;
		}
	}
}


int main(int argc, char* argv[])
{
	init(argc, argv);

	Board_g::init_geoms(0.5);

	pk = new picking(5);
	pk2 = new picking(5);
	
	glutMainLoop();
	

	return 0;
}
