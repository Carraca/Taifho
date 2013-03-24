#include "Material_components.h"

class Player_info{
public:
	static void paint(int player){

		switch (player)
		{
		case 1:
			Material_components(0.5,0.0,0.0,1,  0.8,0.0,0.0,1,  0.5,0.0,0.0,1.0,  32).act();
			break;

		case 2:
			glRotated(180,0,1,0);
			Material_components(0.4,0.4,0.4,1,  0.1,0.1,0.1,1,  0.1,0.1,0.1,1.0,  32).act();
			break;

		case 3:
			glRotated(-90,0,1,0);
			Material_components(0.0,0.5,0.0,1,  0.0,0.4,0.0,1,  0.0,0.5,0.0,1.0,  32).act();
			break;

		case 4:
			glRotated(90,0,1,0);
			Material_components(0.1,0.1,0.1,1,  0.96,0.92,0.22,1,  0.1,0.1,0.1,1.0,  32).act();
			break;

		}


	}

};