#include "Piece.h"
#include "square_geom.h"

#define LOWER_BOUND -0.06

Piece::Piece(int x, int y) {
	inc_x=inc_y=inc_z=rot_x=rot_y=rot_z=rot_ang=rot_axis=0;
}


Piece::~Piece(void) {
}

bool Piece::animate(int xi,int yi,int xf,int yf,float t)
{
	if(t < 1 && t >= LOWER_BOUND) 
	{
		//EASEinOUT
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);
	
		inc_x= ((float)(xf-xi))*t;
		inc_y= ((float)(yf-yi))*t;
		inc_z= 0.5-((1.405*(t-0.5))*(1.405*(t-0.5)));
		return true;
	}
	else
	{
		inc_x=inc_y=inc_z=0;
		return false;
	}
}

bool Piece::animate_capture(int xi, int yi, int xf, int yf, float t)
{
	if(t < 1 && t >= LOWER_BOUND) 
	{
		rot_axis=0.7;
		rot_ang=0;
		if(t >= 0.1 && t < 0.2)
		{
			rot_ang= -(-750*(t*t*t)+1100*(t*t) - 377.5*t +27.5);
			
		}
		else if( t >= 0.2 && t<0.75)
		{
			rot_ang = -(-400*(t*t) + 402.5*t - (155/2));
		}
		else
			rot_ang=0;
		

		rot_x=1;
		if(xi>xf)
			rot_z=1;
		else if(xi<xf)
			rot_z=-1;
		
		//EASEinOUT
		if((t*=2)<1)
			t= 0.5*t*t;
		else
			t=-0.5*(--t*(t-2)-1);

		inc_x= ((float)(xf-xi))*t;
		inc_y= ((float)(yf-yi))*t;
		inc_z= 0.7-((1.7*(t-0.5))*(1.7*(t-0.5)));

		if(yi>yf){
			rot_ang=-rot_ang;
			rot_z=-rot_z;
		}

		return true;
	}
	else
	{
		inc_x=inc_y=inc_z=0;
		rot_x=rot_y=rot_z=rot_axis=0;
		return false;
	}
}

bool Piece::animate_cought(int xi, int yi,int xf, int yf, float t,int one, int two)
{

	if(t < 1 && t >= LOWER_BOUND) 
	{
		extern int COUGHT_ANIMATION_MOV;
		if(COUGHT_ANIMATION_MOV==1){

			rot_ang=0;
			if(t > 0.3)
			{

				rot_ang=50*t-15;
				rot_x=1;
				if(xf>xi)
					rot_z=-1;
				else if(xf<xi)
					rot_z=1;


				inc_y=0.5*(t-0.4);
				inc_z=0.5*(t-0.4);
				K_COLOR.set_opac( 1-((t-0.3)*2.86666) );
				if(t >= 0.620)
					inc_z=10;
			}

			if(yf<yi){
				rot_ang=-rot_ang;
				rot_z=-rot_z;
				inc_y=-inc_y;
			}
		}
		else
		{

			if(t > 0.3)
			{

				t= (t-0.3)*(1.0/0.7);
				
				static const float separation_width = 8.0/9.0;
				float amount,pos=-4.6,vpos=4.3,shift=0.5,s=0.58;
				float fx,fy,fz;

				float sw=-1;
				if(this->get_ownership()==1)
				{
					shift*=-1;
					pos*=-1;
					amount=one;
					sw*=-1;
				}else
					amount=two;

				if((int)amount%2!=0)
					shift=0;

				fx=pos+shift;
				fy=0;
				fz=amount*s-vpos;

				
				if((t*=2)<1)
					t= 0.5*t*t;
				else
					t=-0.5*(--t*(t-2)-1);
					
				
				float xx = (-5.0*separation_width)+0.4+(separation_width*(float)(xf+1.0));
				float yy = (-5.0*separation_width)+0.4+(separation_width*(float)(yf+1.0));

				inc_x=(((float)(fx-xx))*t)/separation_width;
				inc_y= (((float)(sw*fz-yy))*t)/separation_width;
				float vertical_arc=16.0;
				inc_z= -vertical_arc*(t*t)+vertical_arc*t;	
			}

		}

		return true;
	}
	else
	{
		
		rot_x=rot_y=rot_z=inc_x=inc_z=inc_y=0;
		K_COLOR.set_opac(1);
		return false;
	}
}

float Piece::get_inc_x()
{
	return inc_x;
}

float Piece::get_inc_y()
{
	return inc_y;
}

float Piece::get_inc_z()
{
	return inc_z;
}

float Piece::get_rot_x()
{
	return rot_x;
}

float Piece::get_rot_y()
{
	return rot_y;
}

float Piece::get_rot_z()
{
	return rot_z;
}

float Piece::get_rot_ang()
{
	return rot_ang;
}

float Piece::get_rot_axis()
{
	return rot_axis;
}




