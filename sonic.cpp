#include "sonic.h"
#include "krandom.h"
#include <iostream>
Sonic::Sonic()
{
}

Sonic::~Sonic()
{}


void Sonic::init()
{
	x = SCREEN_W / 2;
	y = SCREEN_H / 2;

	dx = rand_sign_switch(rand_ex_f(SONIC_VEL_MIN,SONIC_VEL_MAX ));
	dy = rand_ex_f(SONIC_VEL_MIN ,SONIC_VEL_MAX );

	r = 8;
	
	sticky_time = 0;

}

// Atualiza a posição do sonic, junto de seu sprite ... Retorna verdadeiro se abola estiver "perdida" (perde-se vida) 
bool Sonic::atualizar(Plataforma &plataforma, Ambiente &game_field)
{
	static float plataforma_last_y = 0; // usado para que o Sonic não atravese a Plataforma
	
	if (sticky_time > 0)
	{
		
		sticky_time--;
		// Faz com que a posição do Sonic fique em cima da Plataforma
		x = plataforma.x + plataforma.w / 2;
		y = plataforma.y - r;
		
		if (key[KEY_SPACE]){ // quando pressionar a barra de espaço a bola é lancada		/*victor*/
			sticky_time = 0;
		}
	
		if (sticky_time <= 0)  
		{
			// do the up release
			dy = -rand_ex_f(SONIC_VEL_MIN ,SONIC_VEL_MAX );
			dx = rand_sign_switch(rand_ex_f(SONIC_VEL_MIN,SONIC_VEL_MAX ));
			
		}
		return false; //O Sonic fica em cima da Plataforma. Tudo certo
	}
	else
		sticky_time = 0;
	
	//Atualliza a posição da bola em função de sua velocidade em x e em y
	x += dx;
	y += dy;

	// lanca o sonic no campo
	if (x < r)
	{
		x = r;
		lancar_x();
	}

	if (x > SCREEN_W - r)
	{
		x = SCREEN_W - r;
		lancar_x();
	}

	if (y < r)
	{
		y = r;
		lancar_y();
	}

	if (y > SCREEN_H - r)  // Caso Morre.
	{
		return true; 
	}

	// tratamento da colisão na plataforma
	if (x + r > plataforma.x && 
		x - r < plataforma.x + plataforma.w && 
		(y + r > plataforma.y  || y + r > plataforma_last_y  ) && 
		(y - r < plataforma.y + plataforma.h || y - r < plataforma_last_y + plataforma.h))
	{
			y = plataforma.y - r; 
		
			lancar_y();
	}
	
	// tratamento da colisão nos blocos
	if (game_field.sonic_hit_brick((int)x-r,(int)y) || game_field.sonic_hit_brick((int)x+r,(int)y))
		lancar_x();	

	if (game_field.sonic_hit_brick((int)x,(int)y-r) || game_field.sonic_hit_brick((int)x,(int)y+r))
		lancar_y();	

	
	//Garantia que a velocidade do Sonic não seja maior que o tamanho da Plataforma, se não da aguia
	if (dy > plataforma.h*0.25) 
		dy = plataforma.h*0.25;
	
	if (dy < -plataforma.h*0.25) 
		dy = -plataforma.h*0.25;

	if (dx > plataforma.w*0.25) 
		dx = plataforma.w*0.25;
	
	if (dx < -plataforma.w*0.25) 
		dx = -plataforma.w*0.25;
	

	plataforma_last_y = plataforma.y; ///Salva a ultima posição
	
	return false; 
}

void Sonic::renderizar(BITMAP * bmp, Plataforma &plataforma)									
{																				
	BITMAP *player;
	player = load_bitmap("sonic1.bmp", NULL);									//Carrega a imagem do sonic em pé
														   	   	   	   	   	   
  	if(x != plataforma.x + plataforma.w / 2 && y != plataforma.y - r){			//enquanto o sonic não estiver parado em cima do paddle
		tempo = (clock()-tempo)/ (CLOCKS_PER_SEC/10);							//Permute a imagem do sonic em pe, pela imagem do sonic
			if(tempo%2 == 0){													//girando, em que esta imgagem oscila em duas outras,
				player = load_bitmap("sonic11.bmp",NULL);						//dependendo do tempo: Se o tempo em decimos de segundos for 
				draw_sprite(bmp, player,(int)x-15,(int)y-20);					//par carrega a imagem sonic11, caso seja impar, carrega sonic33
				destroy_bitmap(player);											//desaloca a imagem da memoria
			}													
			else{																//
				player = load_bitmap("sonic33.bmp",NULL);						//
				draw_sprite(bmp, player,(int)x-15,(int)y-20);					//
				destroy_bitmap(player);											//
				
			}	

	}else draw_sprite(bmp, player,(int) x-15,(int) y-20);						
	
	BITMAP *coracao = load_bitmap("coracao.bmp", NULL); 						//Carrega coração que represeta a vida
	draw_sprite(bmp, coracao, 580, 400);										 //Exibir em tela o coração, as configurações se encontrar no nucleo.cpp 
	
	destroy_bitmap(player);														
	destroy_bitmap(coracao);													
}


void Sonic::lancar_x()
{
	dx = -rand_ex_f(dx * 0.9, dx * 1.1);

	if (rand() % 100 < 10)
		dx = rand_sign_switch(rand_ex_f(SONIC_VEL_MIN , SONIC_VEL_MAX ));
}


void Sonic::lancar_y()
{
	dy = -rand_ex_f(dy * 0.9, dy*1.1); 		//Menos pois o eixo y é invertido no Allegro

}
