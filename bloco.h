#ifndef BLOCO_H
#define BLOCO_H

#include <allegro.h>

class Bloco
{
	public:
		// Fun��es-membro
		Bloco();
		~Bloco();
	
		void atualizar();
		void renderizar(BITMAP * bmp);
	
		// Atributos
		int vida; // "vida" dos blocos
	
		int x; // posi��o
		int y;
	
		int w; // tamanho em, pixels, w = largura e h = altura
		int h;
	
};

#endif