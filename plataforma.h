#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include <allegro.h>

class Plataforma
{
	public:
		// Operations
		Plataforma();
		~Plataforma();
		void init();
		void atualizar();
		void renderizar(BITMAP * bmp);
	
		// Attributes
		float x;
		float y;
		int w;
		int h;

};

#endif
