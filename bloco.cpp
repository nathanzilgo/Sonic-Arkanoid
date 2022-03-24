#include "bloco.h"

Bloco::Bloco()
{

	w = h = 32;
	vida = 0;
}

Bloco::~Bloco()
{}


void Bloco::atualizar()
{}

void Bloco::renderizar(BITMAP *bmp)
{
	BITMAP* ring;
	if (vida < 1)
		return; // não desenha-se blocos quebrados
	
    
	if (w > 12 && h > 12)
	{
		ring = load_bitmap("ring3.bmp", NULL);
		draw_sprite(bmp, ring, x, y);
    if (vida ==1){
    	
    }
    if (vida ==2)
    {
        ring = load_bitmap("ring2.bmp", NULL);
		draw_sprite(bmp, ring, x, y);
    }
    if (vida ==3)
    {
        ring = load_bitmap("ring.bmp", NULL);
		draw_sprite(bmp, ring, x, y);
    }
    	destroy_bitmap(ring);
	}
	
}
