#pragma once

#include <GL/glui.h>
#include "vector_2d.h"
#include "Material_components.h"

class Game_object
{
public:
	Game_object(void);
	~Game_object(void);

	virtual void render(GLenum mode) = 0;
	virtual float get_inc_x()= 0;
	virtual float get_inc_y()= 0;
	virtual float get_inc_z()= 0;
	virtual float get_rot_x()= 0;
	virtual float get_rot_y()= 0;
	virtual float get_rot_z()= 0;
	virtual float get_rot_ang()= 0;
	virtual float get_rot_axis() = 0;

	Material_components& get_material(){
		return K_COLOR;
	}

	virtual bool animate(int xi,int yi,int xf,int yf,float t)= 0;
	virtual bool animate_capture(int xi, int yi, int xf, int yf, float t)= 0;
	virtual bool animate_cought(int xi, int yi,int xf, int yf, float t, int one, int two)= 0;
	
	void set_ownership(int p);
	int get_ownership();
protected:
	Material_components K_COLOR;
	int m_ownership;
};

