#ifndef BALL_H
#define BALL_H

#include <allegro.h>
#include "plataforma.h"
#include "ambiente.h"

// Velocidade maxima do Sonic
#define SONIC_VEL_MAX 12 //12(facil),20(medio),30(dificil)

// Velocidade minima do Sonic
#define SONIC_VEL_MIN 8 //8(facil),16(medio),24(dificil)																

class Sonic
{	
	public:
		//Funcoes-membro
		Sonic();
		~Sonic();
		void init();
		bool atualizar(Plataforma &paddle, Ambiente &game_field); //mod
		void renderizar(BITMAP * bmp, Plataforma &paddle);							

		//Atributos
		
		// posição
		float x;
		float y;
		
		// direção (velocidade em x,y)
		float dx;
		float dy;
		
		// raio
		int r;
		
		// tempo para que a bola fique pregada na Plataforma. Depois disso, a bola é lancada
		int sticky_time; 
			
	private:
		void lancar_x();
		void lancar_y();
		clock_t tempo;	//tempo utilizado para o contador de vidas														
};

#endif