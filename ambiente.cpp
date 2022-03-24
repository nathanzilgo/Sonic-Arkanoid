#include <allegro.h>
#include "ambiente.h"
#include "krandom.h"

Ambiente::Ambiente()	//mod
{
	w = h = bc = bdc = 0;
}

Ambiente::~Ambiente()	//mod
{}

// cria um nível novo

void Ambiente::do_new_random_level(int w, int h, int max_life)	//mod
{
	if (w < 1 || w > AMBIENTE_MAX_W) 
		w = AMBIENTE_MAX_W; // safe check
	if (h < 1 || h > AMBIENTE_MAX_H) 
		h = AMBIENTE_MAX_H; // safe check
	
	this->w = w;
	this->h = h;
	bc = 0;

//nível 1
if (max_life == 1){

for (int y = 0 ; y < h; y++)
	{
		for (int x = 0 ; x < w; x++)
		{
			bricks[x][y].vida = 1;

			bricks[x][y].x = x * 71; //***************************************************
			bricks[x][y].y = y * 71;

			bricks[x][y].w = 71;
			bricks[x][y].h = 71;
			

			bc ++; // conta o número de blocos criados
		}
	}
}
//nível 2

if (max_life == 2){

for (int y = 0 ; y < h; y++)
	{
		for (int x = 0 ; x < w; x++)
		{
			bricks[x][y].vida = 1;
            
            if(y==0 || y==2 || (y==1 && x==0) || (y==1 && x==8))
				bricks[x][y].vida = 2;
            
            bricks[x][y].x = x * 71; //***************************************************
			bricks[x][y].y = y * 71;

			bricks[x][y].w = 71;
			bricks[x][y].h = 71;
			

			bc ++; // conta o número de blocos criados
		}
	}	
}
// nível 3
if (max_life == 3){

for (int y = 0 ; y < h; y++)
	{
		for (int x = 0 ; x < w; x++)
		{
			bricks[x][y].vida = 2;
            
            
			if((y+x)%2==0)
				bricks[x][y].vida = 3;
            
            bricks[x][y].x = x * 71; //***************************************************
			bricks[x][y].y = y * 71;

			bricks[x][y].w = 71;
			bricks[x][y].h = 71;
			

			bc ++; // conta o número de blocos criados
		}
	}	
}
}

// returns true if we finished the level (0 bricks left)
bool Ambiente::atualizar()	//mod
{
	return (bool)(bc < 1);
	
}

void Ambiente::renderizar(BITMAP *bmp)	//mod
{
	for (int y = 0 ; y < h; y++)
	{
		for (int x = 0 ; x < w; x++)
		{
			bricks[x][y].renderizar(bmp);
		}
	}
}

bool Ambiente::sonic_hit_brick(int x_px , int y_px)	//mod
{
	// é usada para a colisão entre a bola e os blocos, returna true se um bloco for atingido
	int w_b = 71;           //**************************************//
	int h_b = 71;

	if (y_px < 0 ||
	        x_px < 0 ||
	        y_px / h_b > h ||
	        x_px / w_b > w)
		return false; // bola fora dos limites da janela

	if (bricks[x_px / w_b][y_px / h_b].vida > 0)
	{
		bricks[x_px / w_b][y_px / h_b].vida--;
        
		if (bricks[x_px / w_b][y_px / h_b].vida <= 0)
			bc--;
		bdc++;
        SAMPLE *som;
		som = load_sample ("sonic_coin1.wav"); 	//Audio colisão /*nathan*/
		play_sample(som, 255, 128, 1000, FALSE);
		return true; // bloco atingido
		
	}

	return false;
}