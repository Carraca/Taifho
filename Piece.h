#pragma once

#include "Game_object.h"

class Piece :
	public Game_object
{
public:
	Piece(int x, int y);
	~Piece(void);

	void static create_geometry(float scale);

	virtual void render(GLenum mode)=0;

	bool animate(int xi,int yi,int xf,int yf,float t);
	bool animate_capture(int xi, int yi, int xf, int yf, float t);
	bool animate_cought(int xi, int yi,int xf, int yf, float t,int one, int two);

	float get_inc_x();
	float get_inc_y();
	float get_inc_z();
	float get_rot_x();
	float get_rot_y();
	float get_rot_z();
	float get_rot_ang();
	float get_rot_axis();
	float rot_axis;

protected:
	float inc_x, inc_y, inc_z, rot_x, rot_y, rot_z, rot_ang;
	Material_components color;
	int geom_nr;
	int owner;
	
};

