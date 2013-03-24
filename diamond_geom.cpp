#include "diamond_geom.h"
#include "Player_info.h"
#include "vertex_struct.h"


namespace diamond{
struct vertex_struct hvertexs[]=
{
	{-0.000001, 1.478168, 0.029311, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{0.848528, 0.000000, 0.030014, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{0.000000, -1.478168, 0.029311, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{-0.848528, 0.000000, 0.030014, 0.000000, 0.000000, -1.000000, 0.0, 0.0},
	{0.000000, 1.478168, 1.230717, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{-0.848528, -0.000000, 1.230014, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{-0.000000, -1.478168, 1.230717, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{0.848528, -0.000000, 1.230014, 0.000000, -0.000000, 1.000000, 0.0, 0.0},
	{-0.000001, 1.478168, 0.029311, 0.867266, 0.497846, -0.000000, 0.0, 0.0},
	{0.000000, 1.478168, 1.230717, 0.867266, 0.497846, -0.000000, 0.0, 0.0},
	{0.848528, -0.000000, 1.230014, 0.867266, 0.497846, -0.000000, 0.0, 0.0},
	{0.848528, 0.000000, 0.030014, 0.867266, 0.497846, -0.000000, 0.0, 0.0},
	{0.848528, 0.000000, 0.030014, 0.867266, -0.497845, 0.000000, 0.0, 0.0},
	{0.848528, -0.000000, 1.230014, 0.867266, -0.497845, 0.000000, 0.0, 0.0},
	{-0.000000, -1.478168, 1.230717, 0.867266, -0.497845, 0.000000, 0.0, 0.0},
	{0.000000, -1.478168, 0.029311, 0.867266, -0.497845, 0.000000, 0.0, 0.0},
	{0.000000, -1.478168, 0.029311, -0.867266, -0.497846, -0.000000, 0.0, 0.0},
	{-0.000000, -1.478168, 1.230717, -0.867266, -0.497846, -0.000000, 0.0, 0.0},
	{-0.848528, -0.000000, 1.230014, -0.867266, -0.497846, -0.000000, 0.0, 0.0},
	{-0.848528, 0.000000, 0.030014, -0.867266, -0.497846, -0.000000, 0.0, 0.0},
	{0.000000, 1.478168, 1.230717, -0.867266, 0.497845, 0.000000, 0.0, 0.0},
	{-0.000001, 1.478168, 0.029311, -0.867266, 0.497845, 0.000000, 0.0, 0.0},
	{-0.848528, 0.000000, 0.030014, -0.867266, 0.497845, 0.000000, 0.0, 0.0},
	{-0.848528, -0.000000, 1.230014, -0.867266, 0.497845, 0.000000, 0.0, 0.0}
};

unsigned short hindexes[]={0, 1, 2,0, 2, 3,4, 5, 6,4, 6, 7,
	8, 9, 10,8, 10, 11,12, 13, 14,12, 14, 15,
	16, 17, 18,16, 18, 19,20, 21, 22,20, 22, 23
};
}


diamond_geom::diamond_geom( int ownership, int x,int y ) : Piece(x,y)
{
	owner=ownership;
}


void diamond_geom::render( GLenum mode )
{
	glPushMatrix();
	Player_info::paint(owner);
	glCallList(5);
	glPopMatrix();
}

void diamond_geom::create_geometry( float scale )
{
	glNewList(5,GL_COMPILE);
	glEnable(GL_NORMALIZE);
	glPushMatrix();

	const int H_VERTEX_COUNT = 24;
	const int H_FACES_COUNT = 12;

	glRotated(-90,1,0,0);
	glScaled(scale*0.4,scale*0.4,scale*0.4);

	for(int i=0; i< H_FACES_COUNT*3; i+=3){
		glBegin(GL_TRIANGLES);
		glNormal3f(diamond::hvertexs[diamond::hindexes[i]].nx,diamond::hvertexs[diamond::hindexes[i]].ny,diamond::hvertexs[diamond::hindexes[i]].nz);
		glTexCoord2f(diamond::hvertexs[diamond::hindexes[i]].u,diamond::hvertexs[diamond::hindexes[i]].v);
		glVertex3f(diamond::hvertexs[diamond::hindexes[i]].x,diamond::hvertexs[diamond::hindexes[i]].y,diamond::hvertexs[diamond::hindexes[i]].z);

		glNormal3f(diamond::hvertexs[diamond::hindexes[i+1]].nx,diamond::hvertexs[diamond::hindexes[i+1]].ny,diamond::hvertexs[diamond::hindexes[i+1]].nz);
		glTexCoord2f(diamond::hvertexs[diamond::hindexes[i+1]].u,diamond::hvertexs[diamond::hindexes[i+1]].v);
		glVertex3f(diamond::hvertexs[diamond::hindexes[i+1]].x,diamond::hvertexs[diamond::hindexes[i+1]].y,diamond::hvertexs[diamond::hindexes[i+1]].z);

		glNormal3f(diamond::hvertexs[diamond::hindexes[i+2]].nx,diamond::hvertexs[diamond::hindexes[i+2]].ny,diamond::hvertexs[diamond::hindexes[i+2]].nz);
		glTexCoord2f(diamond::hvertexs[diamond::hindexes[i+2]].u,diamond::hvertexs[diamond::hindexes[i+2]].v);
		glVertex3f(diamond::hvertexs[diamond::hindexes[i+2]].x,diamond::hvertexs[diamond::hindexes[i+2]].y,diamond::hvertexs[diamond::hindexes[i+2]].z);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_NORMALIZE);
	glEndList();
}

