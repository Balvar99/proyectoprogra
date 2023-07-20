#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#define P_AL 720
#define P_AN 1200
#define MAXFILAS 24
#define MAXCOL 30
#define VEL 5
//Dimension 30x30

typedef struct{
	
	int posx;
	int posy;
	int vel;
	int pts;
	bool dios;
	
}Jugador;

typedef struct{
	
	int posx;
	int posy;
	
}Enemigo;

int enemigo_cont=0;


void mecanicas(Jugador *player,Enemigo *enemigo);
void pantalla(Jugador p);
void destroys();
void init();
void deinit();

BITMAP *inicio;
BITMAP *fondo;
BITMAP *pj;
BITMAP *malo;
BITMAP *bush;
BITMAP *borde;
BITMAP *item1;


int main() {
	
	
	init();
	
	Jugador player;
	Enemigo enemigo[20];
		
	player.posx = 60;
	player.posy = 660;
	player.vel = VEL;
	player.pts = 0;
	
	int tiempo=0,tiempo_real=0;
	
	pj = create_bitmap(30,30);
	fondo = create_bitmap(P_AL,P_AN);
	bush = create_bitmap(30,30);
	borde = create_bitmap(30,30);
	malo = create_bitmap(30,30);
	item1 = create_bitmap(20,20);
	
		

	while (!key[KEY_ESC]) {

		pj = load_bitmap("media/bunny.bmp",NULL);
		fondo = load_bitmap("media/fondo.bmp",NULL);
		bush = load_bitmap("media/bush.bmp",NULL);
		borde = load_bitmap("media/borde.bmp",NULL);
		malo = load_bitmap("media/enemigo.bmp",NULL);
		item1 = load_bitmap("media/item1.bmp",NULL);
		
		
		mecanicas(&player,&enemigo[20]);
		pantalla(player);
		
		tiempo++;
		if(tiempo == 70){
			tiempo_real++;
			tiempo = 0;
		}
		
		
		textprintf_ex(screen, font,900,100, makecol(0, 0, 0),-1, "Tiempo Partida : %d segundos",tiempo_real);
		textprintf_ex(screen, font,900,300, makecol(0, 0, 0),-1, "%d  pts",player.pts);



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


void mecanicas(Jugador *player,Enemigo *enemigo){
	
	int i,j;
	char mapa_matriz[MAXFILAS][MAXCOL];
	clock_t beginALL = clock();
	FILE* MAPA;
	
	MAPA = fopen("MAPA.txt","r");
	
	if(MAPA == NULL){
		printf("ERROR AL LEER MAPA, NO SE PUDO ABRIR ARCHIVO");
	}
	
	
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			fscanf(MAPA,"%c",&mapa_matriz[i][j]);
		}
	}
	
	
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			if(mapa_matriz[i][j] == 'x'){
			
				draw_sprite(fondo,bush,j*30,i*30);
			}
			if(mapa_matriz[i][j] == 'b'){
				
				draw_sprite(fondo,borde,j*30,i*30);
				
			}
			if(mapa_matriz[i][j] == 'e'){
				draw_sprite(fondo,malo,j*30,i*30);
			}
			if(mapa_matriz[i][j] == 'z'){
				draw_sprite(fondo,item1,j*30,i*30);
			}
		}
	}

	fclose(MAPA);
	////////////////////////////////////////////////////////////////


	
	
	////////////////////////////////////////////////////////////////
	if(key[KEY_A]){
		
		if((player->posx)%30!=0){
			player->posx -= player->vel;
		}
		else{
			player->posx -= player->vel;
		if(mapa_matriz[(player->posy/30)][((player->posx/30))]=='x' || mapa_matriz[(player->posy+29)/30][(player->posx/30)]=='x' || mapa_matriz[(player->posy/30)][((player->posx/30))]=='b' || mapa_matriz[(player->posy+29)/30][(player->posx/30)]=='b' )
                player->posx += player->vel;
		}
	}
	
	if(key[KEY_D]){
		if((player->posx)%30!=0){
			player->posx += player->vel;
		}
		else{
			player->posx += player->vel;
		if(mapa_matriz[(player->posy/30)][((player->posx)/30)+1]=='x' || mapa_matriz[(player->posy+29)/30][(player->posx/30)+1]=='x' || mapa_matriz[(player->posy/30)][((player->posx)/30)+1]=='b' || mapa_matriz[(player->posy+29)/30][(player->posx/30)+1]=='b')
                player->posx -= player->vel;
		}
	}
	
	if(key[KEY_W]){
		if((player->posy)%30!=0){
			player->posy -= player->vel;
		}
		else{
			player->posy -= player->vel;
		if(mapa_matriz[(player->posy/30)][(player->posx/30)]=='x' || mapa_matriz[(player->posy)/30][(player->posx+29)/30]=='x' || mapa_matriz[(player->posy/30)][(player->posx/30)]=='b' || mapa_matriz[(player->posy)/30][(player->posx+29)/30]=='b') 
                player->posy += player->vel;
    	
		}
	}
	
	if(key[KEY_S]){
		
		if((player->posy)%30!=0){
			player->posy += player->vel;
		}
		else{
			player->posy += player->vel;
		if(mapa_matriz[(player->posy/30)+1][(player->posx/30)]=='x' || mapa_matriz[(player->posy/30)+1][(player->posx+29)/30]=='x' || mapa_matriz[(player->posy/30)+1][(player->posx/30)]=='b' || mapa_matriz[(player->posy/30)+1][(player->posx+29)/30]=='b')
                player->posy -= player->vel;
    	
		}
	}
	
	/////////////////////////////////////////////////
	
	if(mapa_matriz[(player->posy/30)][(player->posx/30)+1] == 'e'){
		
		player->posx = 60;
		player->posy = 660;
		player->pts = player->pts - 50;
		if(player->pts<=0){
			player->pts = 0;
		}		
	}
	if(mapa_matriz[(player->posy/30)][(player->posx/30)+1] == 'z'){
		player->pts += 100;
		
	}
	////////////////////////////////////////////////
}

void destroys(){
	
	destroy_bitmap(fondo);
	destroy_bitmap(pj);
	destroy_bitmap(malo);
	destroy_bitmap(bush);
	destroy_bitmap(borde);	
	destroy_bitmap(item1);
	
}

void pantalla(Jugador p){
	
	draw_sprite(fondo,pj,p.posx,p.posy);
	blit(fondo,screen,0,0,0,0,P_AN,P_AL);
	
}


