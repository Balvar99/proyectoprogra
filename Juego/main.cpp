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
	int vel;
	int direccion; // 1 , 1-
	int tipo;//1 estatico, 2 dinamico, 3 inteligente
	
}Enemigo;


void mecanicas(Enemigo *npc,Jugador *player,char mapa_matriz[MAXFILAS][MAXCOL]);
void pantalla(Jugador p);
void mapa(char mapa_matriz[MAXFILAS][MAXCOL]);
void dibuja(char mapa_matriz[MAXFILAS][MAXCOL]);
void movimiento(char mapa_matriz[MAXFILAS][MAXCOL],Jugador *player);
int leer_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL]);
void movimiento_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos);
void colision_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos);
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
	
	
	
	int tiempo=0,tiempo_real=0,cont_enemigos=0;
	char mapa_matriz[MAXFILAS][MAXCOL];	
	
	pj = create_bitmap(30,30);
	fondo = create_bitmap(P_AL,P_AN);
	bush = create_bitmap(30,30);
	borde = create_bitmap(30,30);
	malo = create_bitmap(30,30);
	item1 = create_bitmap(20,20);
	
	mapa(mapa_matriz);
	cont_enemigos = leer_enemigos(enemigo,mapa_matriz);

		

	while (!key[KEY_ESC]) {

		pj = load_bitmap("media/bunny.bmp",NULL);
		fondo = load_bitmap("media/fondo.bmp",NULL);
		bush = load_bitmap("media/bush.bmp",NULL);
		borde = load_bitmap("media/borde.bmp",NULL);
		malo = load_bitmap("media/enemigo.bmp",NULL);
		item1 = load_bitmap("media/item1.bmp",NULL);
		
		mecanicas(&enemigo[20],&player,mapa_matriz);
		dibuja(mapa_matriz);
		movimiento(mapa_matriz,&player);
		movimiento_enemigos(enemigo,mapa_matriz,cont_enemigos);
		colision_enemigos(enemigo,mapa_matriz,cont_enemigos);
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

void mapa(char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;
	FILE* MAPA;
	
	MAPA = fopen("MAPA.txt","r");
	
	
	if(MAPA == NULL){
		printf("ERROR AL LEER MAPA, NO SE PUDO ABRIR ARCHIVO");
	}
	
	//lee
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			fscanf(MAPA,"%c",&mapa_matriz[i][j]);
		}
	}
	

	fclose(MAPA);
	
}

void dibuja(char mapa_matriz[MAXFILAS][MAXCOL]){
//dibuja
	int i,j;
	
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			
			if(mapa_matriz[i][j] == 'x'){
			
				draw_sprite(fondo,bush,j*30,i*30);
			}
			if(mapa_matriz[i][j] == 'b'){
				
				draw_sprite(fondo,borde,j*30,i*30);
			}
			if(mapa_matriz[i][j] == 'z'){
				draw_sprite(fondo,item1,j*30,i*30);
			}
		}
	}	
}

void movimiento(char mapa_matriz[MAXFILAS][MAXCOL],Jugador *player){
	
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
	
}
int leer_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;
	int cont=0;
	
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			if(mapa_matriz[i][j] == 'e'){
				
				npc[cont].posx = j*30;
				npc[cont].posy = i*30;
				npc[cont].vel = 5;
				npc[cont].direccion = 1;
				npc[cont].tipo = 1;
				cont++;
				
			}
		}
	}
	
	return cont;
}

void movimiento_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos){
	
	int i,j;
	
	for(i=0;i<cont_enemigos;i++){
		
		npc[i].posx += npc[i].direccion*npc[i].vel;
		
		draw_sprite(fondo,malo,npc[i].posx,npc[i].posy);
	}
	
}

void colision_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos){
	
	int i;
	
	for(i=0;i<cont_enemigos;i++){
		
		if(mapa_matriz[(npc[i].posy/30)][((npc[i].posx)/30)+1]=='x' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)+1]=='x' || mapa_matriz[(npc[i].posy/30)][((npc[i].posx)/30)+1]=='b' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)+1]=='b'){
		
                npc[i].direccion = npc[i].direccion*-1;
		}
		if(mapa_matriz[(npc[i].posy/30)][((npc[i].posx)/30)]=='x' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)]=='x' || mapa_matriz[(npc[i].posy/30)][((npc[i].posx)/30)]=='b' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)]=='b'){
		
                npc[i].direccion = npc[i].direccion*-1;
		}
		
}
}
	



void mecanicas(Enemigo *npc,Jugador *player,char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;
	clock_t beginALL = clock();
	
	
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


