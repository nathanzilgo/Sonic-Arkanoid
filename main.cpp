#include <allegro.h>
#include <string.h>
#include <iostream>

#include "nucleo.h"
#include "gerror.h"

void init();
void deinit();

int main() {
	init(); //inicializa a função void init()
      SAMPLE *musica;
      musica = load_sample("electric.wav");
      play_sample(musica, 255, 128, 1000, TRUE);
      
      BITMAP *vitoria = load_bitmap("final.bmp", NULL);						
      SAMPLE *thrash = load_sample("thrash_metal.wav"); 			
      
	while(!key[KEY_ENTER]){
        set_window_title("Sonic Breakout");
        
		BITMAP *menu;                           
		menu = load_bitmap("sonic_breakout.bmp", NULL);
		blit(menu, screen, 0,0,0,0,SCREEN_W, SCREEN_H);
		
		rest(100);
		if(key[KEY_ESC]){
			deinit();
			destroy_bitmap(menu);
			destroy_sample(musica);								
			return 0;
		}

	}

	int nivel = 1;    
	
	while (!key[KEY_ESC] && nivel < 3) {	
	    stop_sample(musica);
		destroy_sample(musica);										
		// Rodar jogo
		Nucleo nucleo;
		nucleo.init();
		nucleo.play(nivel);
		nucleo.shutdown();
	}
		
	if(nivel == 3) {
		while(!key[KEY_ENTER]) {
			draw_sprite(vitoria, screen, 0, 0);
			play_sample(thrash, 255, 128, 1000, TRUE);
	     }
	}
	deinit();
	return 0;
}
END_OF_MAIN() //necessario

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth); // intensidade/profundidade das cores
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);	//modo de display e resolução da tela
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
    install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_timer();
	install_keyboard();
	install_mouse();
}

void deinit() {
	clear_keybuf(); //limpa o buffer do teclado 
	// pode adicionar outras deinicializacoes
}
