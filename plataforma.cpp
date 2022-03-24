#include "plataforma.h"

void Plataforma::init()
{
	// lame default values... DEBUG - this should be better done
	w = (int)(SCREEN_W * 0.20);
	h = (int)(SCREEN_H * 0.05);

	x = SCREEN_W / 2;  //Posição x inicial
	y = SCREEN_H - h - 10; //Posição y inicial

}

// atualiza os controles do paddle(plataforma)
void Plataforma::atualizar()
{
	// Controle do paddle
	if(key[KEY_RIGHT])
                     x = x+10;
    if(key[KEY_LEFT])
                     x = x-10;

    //Opção de uso de mouse
                    
    //x = mouse_x - (w / 2);
	
    //y = mouse_y - (h / 2); // I disabled the Y movement for now -- DEBUG

	if (y < SCREEN_H - (SCREEN_H / 3))
		y = SCREEN_H - (SCREEN_H / 3);

	if (y > SCREEN_H - h)
		y = SCREEN_H - h;

	if (x < 0)
		x = 0;

	if (x > SCREEN_W - w)
		x = SCREEN_W - w;

}

void Plataforma::renderizar( BITMAP * bmp )
{
    BITMAP *img; 
    img = load_bitmap("paddleS.bmp", NULL);
          
    draw_sprite(bmp, img,(int)x,(int)y);
          
}

Plataforma::Plataforma()
{
	init();
}

Plataforma::~Plataforma()
{}