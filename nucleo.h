#ifndef NUCLEO_H
#define NUCLEO_H

#include <allegro.h>


#include "plataforma.h"
#include "sonic.h"
#include "ambiente.h"
#include "mtimer.h"

// tudo certo
#define NUCLEO_UDP_OK 0

// vai para o pr�ximo n�vel
#define NUCLEO_UDP_NEXT_LEVEL 1

// perde uma vida
#define NUCLEO_UDP_LOST_LIFE 2

// pause
#define NUCLEO_UDP_PAUSE 100

// sair do jogo para o menu
#define NUCLEO_UDP_EXIT 101

// sair do jogo
#define NUCLEO_UDP_QUIT 102



class Nucleo 
{
	public:
		// Operations
		Nucleo(); // construtor
		~Nucleo(); // destrutor
		
		void init(); // inicia o jogo
		void play(int); // inicia o loop principal do jogo
		void shutdown(); // desliga o jogo
		
		// Attributes
  		BITMAP *double_buffer; // buffer duplo de bitmap
		Plataforma plataforma; // a plataforma
		Sonic sonic; // a bola (sonic)
		Ambiente ambiente; // os n�veis e a disposi��o dos blocos //mod
		
		int vida;
		
	private:
		void init_game(); // inicia o jogo sem zerar o n�vel, � usada quando perde-se uma vida ou passa de n�vel, etc
		int atualizar(); // atualiza o jogo
		void renderizar(); // atualiza os gr�ficos do jogo
	
};

#endif
