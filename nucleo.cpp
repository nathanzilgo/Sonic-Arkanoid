#include "gerror.h"
#include "nucleo.h"

Nucleo::Nucleo()
{
	double_buffer = NULL;
	vida = 4;							
}

Nucleo::~Nucleo()
{
	shutdown(); 
}


void Nucleo::init()
{
	
	double_buffer = create_bitmap(SCREEN_W,SCREEN_H);
	if (!double_buffer)
		raise_error("Nucleo::init() - Impossivel criar um double buffer!");
	clear_bitmap(double_buffer);
	
}

void Nucleo::play(int nivel)
{
	int ret = NUCLEO_UDP_OK; // estado do jogo, ok
	int level = 1 ; // nível atual

	_start_global_timer(); // começamos um tempo global, configurações no mtimer.h
	
	time_counter = speed_counter = fps_counter = fps_real = 0; // zeramos os parâmetros de tempo global
	
	clear_keybuf();
	
	init_game(); // incializa o jogo
	
	ambiente.do_new_random_level(9,2,1); // cria o primeiro nível
	
	show_mouse(NULL); // esconde mouse
	
	// Esse é o loop principal do jogo, onde tudo acontece 
	while (ret != NUCLEO_UDP_EXIT && ret != NUCLEO_UDP_QUIT)
	{
						
        if (speed_counter > 0) 
		{
			ret = atualizar(); // atualiza o estado do jogo
			
			if (ret == NUCLEO_UDP_LOST_LIFE) // perde uma vida!
			{
				init_game(); // inicia novamente a fase de onde paramos enquanto temos vidas
			}
			if(vida == 0){
				BITMAP *derrota = load_bitmap("derrota.bmp", NULL);				
				blit(derrota, screen, 0,0,0,0,SCREEN_W, SCREEN_H);				
				rest(2000);	
				destroy_bitmap(derrota);
				exit(-1);					//sai do jogo												
			}
			if (ret == NUCLEO_UDP_NEXT_LEVEL || key[KEY_S]) // SE APARTAR A TECLA S(SKIP), PASSA PARA OUTRA FASE
			{
				// próximo nível

				if(level < 3) {
                    level++; /// próximo nível
                    clear(screen);
                    BITMAP *DrIvo;
                    SAMPLE *risada;
                    //SAMPLE *thrash = load_sample("thrash_metal.wav");
					if(level == 2){                                             
						DrIvo = load_bitmap("nivel2_24bits.bmp", NULL);			
						blit(DrIvo, screen, 0,0,0,0,SCREEN_W, SCREEN_H);		
						risada = load_sample("evil_laugh2.wav");				
						play_sample(risada, 255, 0, 1000, FALSE);				
						rest(4000);	
						destroy_sample(risada);	
						destroy_bitmap(DrIvo);														
					}	
					else if (level == 3){
						DrIvo = load_bitmap("nivel3_24bits.bmp", NULL);			
						blit(DrIvo, screen, 0,0,0,0,SCREEN_W, SCREEN_H);		
						risada = load_sample("evil_laugh2_def~1.wav");			
						play_sample(risada, 255, 0, 1000, FALSE);				
						rest(6000);	
						//play_sample(thrash,255, 0, 1000, FALSE);					
						destroy_sample(risada);
						destroy_bitmap(DrIvo);					
					}					
					
    				// parâmetros do novo nível
    				nivel = level;
    				int w = 9;
    				int h = 3;
    
                    ambiente.do_new_random_level(w,h,nivel); // Novo nivel
    				init_game();
                }
    
			}
			
			speed_counter--; 
		}
		else
		{
			renderizar(); // renderiza o jogo
			fps_counter++; // conta frames por segundo (FPS)
		}
	}

	clear_keybuf();	
	_stop_global_timer(); // para o timer global
	time_counter = speed_counter = fps_counter = fps_real = 0; // só para ter certeza
}

void Nucleo::shutdown()
{
	if (double_buffer)
		destroy_bitmap(double_buffer);
	double_buffer = NULL;
}

// atualiza o jogo
int Nucleo::atualizar()
{
	int ret = NUCLEO_UDP_OK; // tudo é OK por default
	
	plataforma.atualizar(); // atualiza a plataforma
	
	if (sonic.atualizar(plataforma, ambiente)){
		ret = NUCLEO_UDP_LOST_LIFE; 
		vida--; //perde um vida para cada vez que cair								
	}
	
	if (ambiente.atualizar())
		ret = NUCLEO_UDP_NEXT_LEVEL;  // vai para o próximo nível quando não restarem mais blocos

	
	if (key[KEY_ESC]) // sai do jogo
		ret = NUCLEO_UDP_EXIT;
	
	return ret;
}

// renderiza o jogo
void Nucleo::renderizar()
{	
	clear_bitmap(double_buffer); // debug
	
	// primeiramente tudo é renderizado para o buffer duplo de bitmap
	ambiente.renderizar(double_buffer);  //mod
	plataforma.renderizar(double_buffer);  //mod
	sonic.renderizar(double_buffer, plataforma); //mod
	// depois nós renderizamos o buffer duplo na tela
	blit(double_buffer, screen, 0,0,0,0,SCREEN_W, SCREEN_H);	
	// renderizamos a pontuação e as vidas restantes
	textprintf_right_ex(screen, font, SCREEN_W - 10, 380, makecol(255, 0, 255), -1, "%d pontos", ambiente.bdc);
	textprintf_centre_ex(screen, font, 620, 410, makecol(255, 255, 255), 0,"%d", vida); 	
}

void Nucleo::init_game()
{
	plataforma.init(); // inicializa a plataforma
	
	sonic.init(); // inicializa a bola 
	
	sonic.sticky_time = BPS_OF_TIMER_MANAGER * 1000; // 1000 segundos antes do lançamento da bola
	
	position_mouse((int)plataforma.x , (int)plataforma.y ); 

	clear_keybuf();	 // limpa o buffer o teclado
}

