
#ifndef RGBpixmap_h__
#define RGBpixmap_h__

#include <GL/glui.h>
#include <fstream>

class RGBmap{
public:
	unsigned char r,g,b;
};

class RGBpixmap{
	public:
		int nRows, nCols;
		RGBmap *pixel;
	int readBMPFile(const char * fname);
	void setTexture(GLuint textureName,int mipmap=0);
	
	
};
#endif // RGBpixmap_h__
