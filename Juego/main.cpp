#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#define P_AL 720
#define P_AN 800
#define MAXFILAS 20
#define MAXCOL 18
#define VEL 5

//github

typedef struct{
	
	int vida;
	int posx;
	int posy;
	int vel;
	
}Jugador;

typedef struct{
	
	int vida;
	
}Enemigo;

void mapa();
void dibujaVida(Jugador* player);
void movimiento(Jugador* player);
void pantalla(Jugador p);
void destroys();
void init();
void deinit();

BITMAP *inicio;
BITMAP *fondo;
BITMAP *pj;
BITMAP *enemigo;
BITMAP *bush;


int main() {
	
	
	init();
	
	Jugador player;
	Enemigo npc;
	
	player.posx = 100;
	player.posy = 100;
	player.vida = 3;
	player.vel = VEL;
	
	
	pj = create_bitmap(40,40);
	fondo = create_bitmap(P_AL,P_AN);
	bush = create_bitmap(40,40);
	enemigo = create_bitmap(40,40);
					
	
	

	while (!key[KEY_ESC]) {

		pj = load_bitmap("media/bunny.bmp",NULL);
		fondo = load_bitmap("media/fondo.bmp",NULL);
		bush = load_bitmap("media/bush.bmp",NULL);
		enemigo = load_bitmap("media/enemigo.bmp",NULL);
		textprintf_ex(screen,font,player.posx,player.posy,makecol(255,255,255),-1,"X =%d Y=%d", player.posx, player.posy);
		textprintf_ex(screen,font,400,500,makecol(255,255,255),-1,"X =%d Y=%d", player.posx/40, player.posy/40);


		

		mapa();
		movimiento(&player);
		pantalla(player);
		dibujaVida(&player);
		
		if(player.vida==0){

			allegro_exit();
		}

		destroys();
	}



	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, P_AN, P_AL, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

void movimiento(Jugador* player){
	
	
	
	if(key[KEY_LEFT]){
		player->posx -= player->vel;
	}
	if(key[KEY_RIGHT]){
		player->posx += player->vel;
	}
	if(key[KEY_UP]){
		player->posy -= player->vel;
	}
	if(key[KEY_DOWN]){
		player->posy += player->vel;
	}
	
}

void mapa(){
	
	int i,j;
	char MAPA[MAXCOL][MAXFILAS]=
	{
		"XXXXXXXXXXXXXXXXXX",
		"X                X",
		"X   E            X",
		"X     X          X",
		"X                X",
		"X  E  X XXX      X",
		"X   XX X         X",
		"X     X          X",
		"X         E      X",
		"X    X X         X",
		"X                X",
		"X       X        X",
		"X                X",
		"X                X",
		"X                X",
		"X                X",
		"X                X",		
		"XXXXXXXXXXXXXXXXXX",
	};
	
	for(i=0;i<MAXCOL;i++){
		for(j=0;j<MAXFILAS;j++){
				
			if(MAPA[j][i] == 'X'){
			
				draw_sprite(fondo,bush,i*40,j*40);
				
			}
			if(MAPA[j][i] == 'E'){
				
				draw_sprite(fondo,enemigo,i*40,j*40);
			}
		}
	}	
}

void destroys(){
	
	destroy_bitmap(fondo);
	destroy_bitmap(pj);
	destroy_bitmap(bush);	
	
}

void pantalla(Jugador p){
	
	draw_sprite(fondo,pj,p.posx,p.posy);
	blit(fondo,screen,0,0,0,0,P_AN,P_AL);
	
}
void dibujaVida(Jugador* p){

	textprintf_ex(screen,font,50,50,makecol(255,255,255),-1,"VIDAS = %d",p->vida);
	if(key[KEY_SPACE]){
		p->vida--;
		rest(100);
		
	}

}


