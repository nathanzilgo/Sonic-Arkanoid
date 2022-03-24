#ifndef AMBIENTE_H
#define AMBIENTE_H

#include <allegro.h>

#include "bloco.h"
// dimensões máximas do nível
#define AMBIENTE_MAX_W 10	//mod
#define AMBIENTE_MAX_H 10	//mod

class Ambiente	//mod
{
	public:
		// Funçôes-membro
		Ambiente(); //mod
		~Ambiente();	//mod
	
		void do_new_random_level(int w, int h, int max_life); // cria um novo nível de tamanho w*h, com blocos de vida máxima max_life
	
		bool atualizar();	//mod
		void renderizar(BITMAP *bmp);	//mod
	
		bool sonic_hit_brick(int x_px , int y_px); // é usada para a colisão entre a bola e os blocos, returna true se um bloco for atingido
	
		// Atributos
	
		Bloco bricks[AMBIENTE_MAX_W][AMBIENTE_MAX_H];	//mod
		int w, h; // quantidade de colunas(w) e linhas(h) de blocos
		int bc; // contadores de blocos(anéis)
		int bdc; 
};

#endif
