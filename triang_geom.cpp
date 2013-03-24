#include "triang_geom.h"
#include "Player_info.h"
#include "vertex_struct.h"

namespace triang{

struct vertex_struct hvertexs[]=
{
	{0.000003, -1.500524, 0.029311, 0.000000, -0.000000, -1.000000, 0.0, 0.0},
	{-1.187940, 0.568910, 0.030014, 0.000000, -0.000000, -1.000000, 0.0, 0.0},
	{-0.000001, 0.578292, 0.029311, 0.000000, -0.000000, -1.000000, 0.0, 0.0},
	{1.187938, 0.568913, 0.030014, 0.000000, -0.000000, -1.000000, 0.0, 0.0},
	{0.000002, -1.500524, 1.230717, -0.000000, 0.000000, 1.000000, 0.0, 0.0},
	{1.187938, 0.568914, 1.230014, -0.000000, 0.000000, 1.000000, 0.0, 0.0},
	{-0.000001, 0.578292, 1.230717, -0.000000, 0.000000, 1.000000, 0.0, 0.0},
	{-1.187940, 0.568910, 1.230014, -0.000000, 0.000000, 1.000000, 0.0, 0.0},
	{0.000003, -1.500524, 0.029311, -0.867265, -0.497847, -0.000000, 0.0, 0.0},
	{0.000002, -1.500524, 1.230717, -0.867265, -0.497847, -0.000000, 0.0, 0.0},
	{-1.187940, 0.568910, 1.230014, -0.867265, -0.497847, -0.000000, 0.0, 0.0},
	{-1.187940, 0.568910, 0.030014, -0.867265, -0.497847, -0.000000, 0.0, 0.0},
	{-1.187940, 0.568910, 0.030014, -0.007898, 0.999969, -0.000000, 0.0, 0.0},
	{-1.187940, 0.568910, 1.230014, -0.007898, 0.999969, -0.000000, 0.0, 0.0},
	{-0.000001, 0.578292, 1.230717, -0.007898, 0.999969, -0.000000, 0.0, 0.0},
	{-0.000001, 0.578292, 0.029311, -0.007898, 0.999969, -0.000000, 0.0, 0.0},
	{-0.000001, 0.578292, 0.029311, 0.007895, 0.999969, -0.000000, 0.0, 0.0},
	{-0.000001, 0.578292, 1.230717, 0.007895, 0.999969, -0.000000, 0.0, 0.0},
	{1.187938, 0.568914, 1.230014, 0.007895, 0.999969, -0.000000, 0.0, 0.0},
	{1.187938, 0.568913, 0.030014, 0.007895, 0.999969, -0.000000, 0.0, 0.0},
	{0.000002, -1.500524, 1.230717, 0.867266, -0.497844, 0.000001, 0.0, 0.0},
	{0.000003, -1.500524, 0.029311, 0.867266, -0.497844, 0.000001, 0.0, 0.0},
	{1.187938, 0.568913, 0.030014, 0.867266, -0.497844, 0.000001, 0.0, 0.0},
	{1.187938, 0.568914, 1.230014, 0.867266, -0.497844, 0.000001, 0.0, 0.0}
};

unsigned short hindexes[]={0, 1, 2,0, 2, 3,4, 5, 6,4, 6, 7,
	8, 9, 10,8, 10, 11,12, 13, 14,12, 14, 15,
	16, 17, 18,16, 18, 19,20, 21, 22,20, 22, 23
};
}

trian_geom::trian_geom( int ownership, int x, int y ) : Piece(x,y)
{
	owner=ownership;
}

void trian_geom::render( GLenum mode )
{
	glPushMatrix();
	Player_info::paint(owner);
	glCallList(3);
	glPopMatrix();
}

void trian_geom::create_geometry( float scale )
{
	glNewList(3,GL_COMPILE);
	glEnable(GL_NORMALIZE);
	glPushMatrix();

	int H_VERTEX_COUNT = 24;
	int H_FACES_COUNT = 12;

	glRotated(-90,1,0,0);
	glScaled(scale*0.4,scale*0.4,scale*0.4);

	for(int i=0; i< H_FACES_COUNT*3; i+=3){
		glBegin(GL_TRIANGLES);
		glNormal3f(triang::hvertexs[triang::hindexes[i]].nx,triang::hvertexs[triang::hindexes[i]].ny,triang::hvertexs[triang::hindexes[i]].nz);
		glTexCoord2f(triang::hvertexs[triang::hindexes[i]].u,triang::hvertexs[triang::hindexes[i]].v);
		glVertex3f(triang::hvertexs[triang::hindexes[i]].x,triang::hvertexs[triang::hindexes[i]].y,triang::hvertexs[triang::hindexes[i]].z);

		glNormal3f(triang::hvertexs[triang::hindexes[i+1]].nx,triang::hvertexs[triang::hindexes[i+1]].ny,triang::hvertexs[triang::hindexes[i+1]].nz);
		glTexCoord2f(triang::hvertexs[triang::hindexes[i+1]].u,triang::hvertexs[triang::hindexes[i+1]].v);
		glVertex3f(triang::hvertexs[triang::hindexes[i+1]].x,triang::hvertexs[triang::hindexes[i+1]].y,triang::hvertexs[triang::hindexes[i+1]].z);

		glNormal3f(triang::hvertexs[triang::hindexes[i+2]].nx,triang::hvertexs[triang::hindexes[i+2]].ny,triang::hvertexs[triang::hindexes[i+2]].nz);
		glTexCoord2f(triang::hvertexs[triang::hindexes[i+2]].u,triang::hvertexs[triang::hindexes[i+2]].v);
		glVertex3f(triang::hvertexs[triang::hindexes[i+2]].x,triang::hvertexs[triang::hindexes[i+2]].y,triang::hvertexs[triang::hindexes[i+2]].z);
		glEnd();
	}
	glPopMatrix();
	glDisable(GL_NORMALIZE);
	glEndList();
}
