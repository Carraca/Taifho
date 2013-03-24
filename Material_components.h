#pragma once

class Material_components {
public:
	Material_components(){}
	Material_components(float sr, float sg, float sb, float sa, float dr, float dg, float db, float da, float ar, float ag, float ab, float aa, float s) {
		
		this->specular[0]=old_specular[0] = sr;
		this->specular[1]=old_specular[1] = sg;
		this->specular[2]=old_specular[2] = sb;
		this->specular[3]=old_specular[3] = sa;

		this->diffuse[0]=old_diffuse[0] = dr;
		this->diffuse[1]=old_diffuse[1] = dg;
		this->diffuse[2]=old_diffuse[2] = db;
		this->diffuse[3]=old_diffuse[3] = da;

		this->ambient[0]=old_ambient[0] = ar;
		this->ambient[1]=old_ambient[1] = ag;
		this->ambient[2]=old_ambient[2] = ab;
		this->ambient[3]=old_ambient[3] = aa;
		
		this->shininess[0] = s;

		for(int i=0; i<4; ++i) emission[i]=old_emission[i]=0;
	}

	void act(){
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
		glMaterialfv(GL_FRONT, GL_SPECULAR,  specular);
		glMaterialfv(GL_FRONT, GL_DIFFUSE,   diffuse);
		glMaterialfv(GL_FRONT, GL_AMBIENT,   ambient);
		glMaterialfv(GL_FRONT, GL_EMISSION,  emission);
	}

	void set_opac(float a)
	{
		specular[3]=diffuse[3]=ambient[3]=a;
	}

	void set_emission(float r,float g,float b)
	{
		emission[0]=r;
		emission[1]=g;
		emission[2]=b;
		
	}

	void set_diffuse(float r,float g,float b)
	{
		diffuse[0]=r;
		diffuse[1]=g;
		diffuse[2]=b;
	
	}

	void set_specular(float r,float g,float b)
	{
		specular[0]=r;
		specular[1]=g;
		specular[2]=b;
		
	}
	void set_ambient(float r,float g,float b)
	{
		ambient[0]=r;
		ambient[1]=g;
		ambient[2]=b;
		
	}

	void reset(){
		for(int i=0; i< 3; ++i){
			specular[i]=old_specular[i];
			diffuse[i]=old_diffuse[i];
			ambient[i]=old_ambient[i];
			emission[i]=old_emission[i];
		}

	}
	
private:
	float specular[4], diffuse[4],  ambient[4],  shininess[1], emission[4];
	float old_specular[4], old_diffuse[4],  old_ambient[4],  old_shininess[1], old_emission[4];
};