#include "square_geom.h"
#include "Player_info.h"
#include "vertex_struct.h"

namespace square{
struct vertex_struct hvertexs[]=
{
	{1.320000, 1.320000, -0.029986, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{1.320000, -1.320000, -0.029986, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{-1.320000, -1.319999, -0.029986, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{-1.319999, 1.320000, -0.029986, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{1.320000, 1.319999, 1.290014, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{-1.320000, 1.320000, 1.290014, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{-1.320000, -1.319999, 1.290014, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{1.319999, -1.320000, 1.290014, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{1.320000, 1.320000, -0.029986, 1.000000, -0.000000, 0.000000, 0.0, 0.0},
	{1.320000, 1.319999, 1.290014, 1.000000, -0.000000, 0.000000, 0.0, 0.0},
	{1.319999, -1.320000, 1.290014, 1.000000, -0.000000, 0.000000, 0.0, 0.0},
	{1.320000, -1.320000, -0.029986, 1.000000, -0.000000, 0.000000, 0.0, 0.0},
	{1.320000, -1.320000, -0.029986, -0.000000, -1.000000, -0.000000, 0.0, 0.0},
	{1.319999, -1.320000, 1.290014, -0.000000, -1.000000, -0.000000, 0.0, 0.0},
	{-1.320000, -1.319999, 1.290014, -0.000000, -1.000000, -0.000000, 0.0, 0.0},
	{-1.320000, -1.319999, -0.029986, -0.000000, -1.000000, -0.000000, 0.0, 0.0},
	{-1.320000, -1.319999, -0.029986, -1.000000, 0.000000, -0.000000, 0.0, 0.0},
	{-1.320000, -1.319999, 1.290014, -1.000000, 0.000000, -0.000000, 0.0, 0.0},
	{-1.320000, 1.320000, 1.290014, -1.000000, 0.000000, -0.000000, 0.0, 0.0},
	{-1.319999, 1.320000, -0.029986, -1.000000, 0.000000, -0.000000, 0.0, 0.0},
	{1.320000, 1.319999, 1.290014, 0.000000, 1.000000, 0.000000, 0.0, 0.0},
	{1.320000, 1.320000, -0.029986, 0.000000, 1.000000, 0.000000, 0.0, 0.0},
	{-1.319999, 1.320000, -0.029986, 0.000000, 1.000000, 0.000000, 0.0, 0.0},
	{-1.320000, 1.320000, 1.290014, 0.000000, 1.000000, 0.000000, 0.0, 0.0}
};

unsigned short hindexes[]={0, 1, 2,0, 2, 3,4, 5, 6,4, 6, 7,
	8, 9, 10,8, 10, 11,12, 13, 14,12, 14, 15,
	16, 17, 18,16, 18, 19,20, 21, 22,20, 22, 23
};
}
square_geom::square_geom( int ownership, int x,int y ) : Piece(x,y)
{
	owner=ownership;
}


void square_geom::render( GLenum mode )
{
	glPushMatrix();
	Player_info::paint(owner);
	glCallList(2);
	glPopMatrix();
}

void square_geom::create_geometry( float scale )
{
	glNewList(2,GL_COMPILE);
	glEnable(GL_NORMALIZE);
	glPushMatrix();

	const int H_VERTEX_COUNT = 24;
	const int H_FACES_COUNT = 12;

	glRotated(-90,1,0,0);
	glScaled(scale*0.4,scale*0.4,scale*0.4);

	for(int i=0; i< H_FACES_COUNT*3; i+=3){
		glBegin(GL_TRIANGLES);
		glNormal3f(square::hvertexs[square::hindexes[i]].nx,square::hvertexs[square::hindexes[i]].ny,square::hvertexs[square::hindexes[i]].nz);
		glTexCoord2f(square::hvertexs[square::hindexes[i]].u,square::hvertexs[square::hindexes[i]].v);
		glVertex3f(square::hvertexs[square::hindexes[i]].x,square::hvertexs[square::hindexes[i]].y,square::hvertexs[square::hindexes[i]].z);

		glNormal3f(square::hvertexs[square::hindexes[i+1]].nx,square::hvertexs[square::hindexes[i+1]].ny,square::hvertexs[square::hindexes[i+1]].nz);
		glTexCoord2f(square::hvertexs[square::hindexes[i+1]].u,square::hvertexs[square::hindexes[i+1]].v);
		glVertex3f(square::hvertexs[square::hindexes[i+1]].x,square::hvertexs[square::hindexes[i+1]].y,square::hvertexs[square::hindexes[i+1]].z);

		glNormal3f(square::hvertexs[square::hindexes[i+2]].nx,square::hvertexs[square::hindexes[i+2]].ny,square::hvertexs[square::hindexes[i+2]].nz);
		glTexCoord2f(square::hvertexs[square::hindexes[i+2]].u,square::hvertexs[square::hindexes[i+2]].v);
		glVertex3f(square::hvertexs[square::hindexes[i+2]].x,square::hvertexs[square::hindexes[i+2]].y,square::hvertexs[square::hindexes[i+2]].z);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_NORMALIZE);
	glEndList();
}

