#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro.h>
#define P_AL 720
#define P_AN 1200
#define MAXFILAS 24
#define MAXCOL 30

//Dimension 30x30

////////////////////-JUGADOR
typedef struct{
	
	int posx;//posicion X
	int posy;// posicion Y
	int vel; // velocidad de movimiento
	int pts; // puntos
	int vidas; // vidas
	int dir; // 0 Derecha , 1 Izquierda , 2 Arriba, 3 Abajo
	
}Jugador;
////////////////////

////////////////////-Enemigos
typedef struct{
	
	int posx;// posicion X
	int posy; //posicion Y
	int vel; // Velocidad de movimiento
	int direccion; // Para seguir el movimiento del Jugador desde los enemigos inteligentes
	int tipo; // Tipo de movimiento (izq,der,arriba,abajo)
	
}Enemigo;

typedef struct{
	
	int posx;
	int posy;
	bool toca;
	
}Trampa;

////////////////////

////////////////////-Objetos
typedef struct{
	
	int posx;
	int posy;
	bool toca;
}Item;
////////////////////

///////////////////////////////////////////PROTOTIPOS/FUNCIONES//////////////////////////////////////////////////////////////////
void pantalla(Jugador p); //Imprime la pantalla y el jugador (su posicion)
void mapa(char mapa_matriz[MAXFILAS][MAXCOL],int ronda);// Lee el mapa
void dibuja(char mapa_matriz[MAXFILAS][MAXCOL]);// Dibuja el mapa y obstaculos
void dibuja_vida(Jugador player);//Dibuja la vida del personaje
void movimiento(char mapa_matriz[MAXFILAS][MAXCOL],Jugador *player);//Movimiento del personaje
int leer_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL]);// Lee los enemigos en el archivo .txt
void movimiento_enemigos(Enemigo npc[20],int cont_enemigos);//Movimiento de los enemigos
void colision_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos);//Colision de los enemigos con los obstaculos
void colision_enemigos_jugador(Jugador *player,Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos);//Colision de los enemigos con los jugadores
int leer_item_z(Item zanah[15],char mapa_matriz[MAXFILAS][MAXCOL]); //Lee items de archivo txt
void dibuja_item_z(Item zanah[15],int cont_items); // Dibuja los objetos de manera al azar en el mapa
int col_jugador_item(Jugador *player,Item zanah[15],int cont_items,char mapa_matriz[MAXFILAS][MAXCOL]); //colision de los objetos con el jugador
int leer_trampa(Trampa trampa[15],char mapa_matriz[MAXFILAS][MAXCOL]);
void dibuja_trampa(Trampa t[15],int conttrampa);
void col_jugador_trampa(Jugador *player,Trampa trampa[15],char mapa_matriz[MAXFILAS][MAXCOL],int conttrampa);
void puntos(Jugador player);
void menu(int op);
void destroys();//destruye los bitmaps necesarios
void init();//inicia los procesos de allegro
void deinit(); // finaliza las funciones de allegro
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////-BITMAPS
BITMAP *inicio;
BITMAP *fondo;
BITMAP *pj;
BITMAP *malo;
BITMAP *bush;
BITMAP *borde;
BITMAP *item1;
BITMAP *vida;
BITMAP *vida_menos;
BITMAP *pausa;
BITMAP *trampaimg;
////////////////////

SAMPLE *soundSample;

////////////////////Variables momentaneas globalos para prueba
int conteotoca=0;
int n = 0;
////////////////////

int main() {
	
	
	init();
	
	int opmenu = 0;
	menu(opmenu);
	
	Jugador player;// renombra la estructura Jugador a "player"
	Enemigo enemigo[20]; // renombra la estructura Enemigo a un arreglo de 20 elementos llamado "enemigo"
	Item zanah[15]; // renombra la estructura de Item a un arreglo de 15 elementos llamado "zanah"
	Trampa trampa[15];
		
	player.posx = 60;//posicion de origen del player X
	player.posy = 660;//posicion de origen del player Y
	player.vel = 3; // velocidad base
	player.pts = 0; //puntos iniciales
	player.vidas = 5;// vidas de player
	player.dir = 0;
	
	srand(time(0));//funcion para el uso de numeros random dentro de las funciones al azar (enemigos y objetos)
	
	int tiempo=0,tiempo_real=0,cont_enemigos=0,cont_items=0,conttrampa=0;
	// tiempo y tiempo real se usan en el conteo de tiempo en milisegundos
	// cont_enemigos y cont_items se usan para el conteo tanto de enemigos como items dentro de los archivos txt para iniciar
	int m = 0;
	int lee = 1;
	int op = 0;
	int mov = 0;

	char mapa_matriz[MAXFILAS][MAXCOL];// mapa donde se desarrolla el juego en dimension de 30x30 pixeles cada bloque del mapa
	
	////////////////////-Inicializacion de los bitmaps
	pj = create_bitmap(30,30);
	fondo = create_bitmap(P_AL,P_AN);
	bush = create_bitmap(30,30);
	borde = create_bitmap(30,30);
	malo = create_bitmap(30,30);
	trampaimg = create_bitmap(30,30);
	item1 = create_bitmap(20,20);
	vida = create_bitmap(60,60);
	vida_menos = create_bitmap(60,60);
	pausa = create_bitmap(500,400);
	////////////////////
	mapa(mapa_matriz,m);//lee el mapa
	cont_enemigos = leer_enemigos(enemigo,mapa_matriz); //lee los enemigos y guarda la cantidad
	cont_items = leer_item_z(zanah,mapa_matriz); //lee los items y guarda la cantidad	
	conttrampa = leer_trampa(trampa,mapa_matriz);
	
		
		do{
			////////////////////////////////////////////////////////////-Carga de imagenes	
			pj = load_bitmap("media/bunnyder.bmp",NULL);
			fondo = load_bitmap("media/fondo.bmp",NULL);
			bush = load_bitmap("media/bush.bmp",NULL);
			borde = load_bitmap("media/borde.bmp",NULL);
			item1 = load_bitmap("media/item1.bmp",NULL);
			vida = load_bitmap("media/vida.bmp",NULL);
			vida_menos = load_bitmap("media/vidamenos.bmp",NULL);
			pausa = load_bitmap("media/PAUSA.bmp",NULL);
			trampaimg = load_bitmap("media/trampa.bmp",NULL);
			
				///////////////////////////////////////////////////////////
				
					
					
				////////////////////-Pausa
				while(key[KEY_ENTER]){
					
					draw_sprite(screen,pausa,210,100);
					readkey();
				}
				////////////////////
					
				////////////////////////////////////////////////////////////-Funciones principales del juego
				if(m == 3  && lee == 1){
					op++;
					mapa(mapa_matriz,op);//lee el mapa
					cont_enemigos = leer_enemigos(enemigo,mapa_matriz); //lee los enemigos y guarda la cantidad
					cont_items = leer_item_z(zanah,mapa_matriz); //lee los items y guarda la cantidad
					conttrampa = leer_trampa(trampa,mapa_matriz);
					
					player.posx = 690;
					player.posy = 570;
					lee = 0;
				}
					
				if(m == 6 && lee == 0){
					op++;
					mapa(mapa_matriz,op);//lee el mapa
					cont_enemigos = leer_enemigos(enemigo,mapa_matriz); //lee los enemigos y guarda la cantidad
					cont_items = leer_item_z(zanah,mapa_matriz); //lee los items y guarda la cantidad
					conttrampa = leer_trampa(trampa,mapa_matriz);
					
					player.posx = 540;
					player.posy = 180;
					lee = 1;
				}
				
				dibuja(mapa_matriz);//dibuja el mapa
				dibuja_item_z(zanah,cont_items);//dibuja los objetos en el mapa
				dibuja_trampa(trampa,conttrampa);
				dibuja_vida(player);//dibuja la vida del jugador
				movimiento(mapa_matriz,&player);//movimiento del jugador
				m = col_jugador_item(&player,zanah,cont_items,mapa_matriz);//colision jugador con el item
				movimiento_enemigos(enemigo,cont_enemigos);//movimiento del enemigo
				colision_enemigos(enemigo,mapa_matriz,cont_enemigos);//colision de los enemigos con obstaculos
				colision_enemigos_jugador(&player,enemigo,mapa_matriz,cont_enemigos);//colision de jugador con enemigos
				col_jugador_trampa(&player,trampa,mapa_matriz,conttrampa);
				puntos(player);

					////////////////////////////////////////////////////////////////////////////////////////////
					
				pantalla(player);//imprime el jugador y el fondo en la pantalla
			
			
						
				////////////////////////////////////////////////////////////-Cronometro
				tiempo++;
				if(tiempo == 70){
					tiempo_real++;
					tiempo = 0;
				}
				textprintf_ex(screen, font,100,35, makecol(0, 0, 0),-1, "Tiempo Partida : %d segundos",tiempo_real);//5 min de partida aprox
				textprintf_ex(screen, font,100,45, makecol(0, 0, 0),-1, "Ronda : %d ",m);
			
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
				destroys();
			}while(!key[KEY_ESC]);


	

	

	deinit();
	return 0;
}
END_OF_MAIN()

////////////////////-Inicializacion de allegro
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
}
////////////////////

////////////////////-Limpia
void deinit() {
	clear_keybuf();
}
////////////////////

////////////////////-LEE EL MAPA
void mapa(char mapa_matriz[MAXFILAS][MAXCOL],int ronda){
	
	int i,j;//Contadores
	FILE* MAPA;//Abrir el archivo de texto donde esta el mapa

	if(ronda == 0){
		MAPA = fopen("MAPA1.txt","r");
	}
	if(ronda == 1){
		MAPA = fopen("MAPA2.txt","r"); 
	}		
	if(ronda == 2){
		MAPA = fopen("MAPA3.txt","r"); 
	}
	
	if(MAPA == NULL){
		printf("ERROR AL LEER MAPA, NO SE PUDO ABRIR ARCHIVO");//devolucion de "error" si es que no se lee el mapa correctamente
	}
	
	//lee
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			fscanf(MAPA,"%c",&mapa_matriz[i][j]);//for anidado en otro for para guardar los datos del archivo de texto en una matriz para el mapa
		}
	}
	

	fclose(MAPA);//Cerrar el archivo txt
	
}
////////////////////

////////////////////-DIBUJA EL MAPA
void dibuja(char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;//contadores
	
	//Ciclo for anidado en otro for para dibujar los obstaculos
	for(i=0;i<MAXFILAS;i++){
		for(j=0;j<MAXCOL;j++){
			
			//Si encuentra una 'x' en la matriz se dibuja un bloque de tierra superior
			if(mapa_matriz[i][j] == 'x'){
			
				draw_sprite(fondo,bush,j*30,i*30);//se multiplica la ubicacion en 30x30 pixeles
			}
			//Si encuentra una 'b' se dibuja un bloque de tierra base que normalmente se dibujara debajo de un bloque de tierra superior
			if(mapa_matriz[i][j] == 'b'){
				
				draw_sprite(fondo,borde,j*30,i*30);//se multiplica la ubicacion en 30x30 pixeles
			}
		
		}
	}	
}
////////////////////

////////////////////-DIBUJA VIDA DEL JUGADOR
void dibuja_vida(Jugador player){
	
	
	switch (player.vidas){
		
		case 0 :// Dibuja 5 corazones grises (0 vidas)

			draw_sprite(fondo,vida_menos,880,100);
			draw_sprite(fondo,vida_menos,940,100);
			draw_sprite(fondo,vida_menos,1000,100);
			draw_sprite(fondo,vida_menos,1060,100);
			draw_sprite(fondo,vida_menos,1120,100);
		break;

		case 1 :// Dibuja 4 corazones grises y 1 rojos (1 vidas)
		
			draw_sprite(fondo,vida,880,100);
			draw_sprite(fondo,vida_menos,940,100);
			draw_sprite(fondo,vida_menos,1000,100);
			draw_sprite(fondo,vida_menos,1060,100);
			draw_sprite(fondo,vida_menos,1120,100);
		break;
		
		case 2 : // Dibuja 3 corazones grises y 2 rojos (2 vidas)

			draw_sprite(fondo,vida,880,100);
			draw_sprite(fondo,vida,940,100);
			draw_sprite(fondo,vida_menos,1000,100);
			draw_sprite(fondo,vida_menos,1060,100);
			draw_sprite(fondo,vida_menos,1120,100);
			break;
		
		case 3 : //Dibuja 2 corazones grises y 3 rojos (3 vidas)

			draw_sprite(fondo,vida,880,100);
			draw_sprite(fondo,vida,940,100);
			draw_sprite(fondo,vida,1000,100);
			draw_sprite(fondo,vida_menos,1060,100);
			draw_sprite(fondo,vida_menos,1120,100);
		break;
		
		case 4 : //Dibuja 1 corazon gris y 4 rojos (4 vidas)

			draw_sprite(fondo,vida,880,100);
			draw_sprite(fondo,vida,940,100);
			draw_sprite(fondo,vida,1000,100);
			draw_sprite(fondo,vida,1060,100);
			draw_sprite(fondo,vida_menos,1120,100);
		break;
		
		case 5 ://Dibuja 5 corazones rojos (5 vidas)

			draw_sprite(fondo,vida,880,100);
			draw_sprite(fondo,vida,940,100);
			draw_sprite(fondo,vida,1000,100);
			draw_sprite(fondo,vida,1060,100);
			draw_sprite(fondo,vida,1120,100);
		break;
		
		default : ;break;
	}
	
	
}
////////////////////

////////////////////-MOVIMIENTO DEL JUGADOR
void movimiento(char mapa_matriz[MAXFILAS][MAXCOL],Jugador *player){
	
	
	if(player->dir == 0){
		pj = load_bitmap("media/bunnyder.bmp",NULL);
	}
	if(player->dir == 1){
		pj = load_bitmap("media/bunnyizq.bmp",NULL);
	}
	if(player->dir == 2){
		pj = load_bitmap("media/bunnyder.bmp",NULL);
	}
	if(player->dir == 3){
		pj = load_bitmap("media/bunnyizq.bmp",NULL);
	}
	
	
	
	if(key[KEY_A]){ //MOVIMIENTO A LA IZQUIERDA
		
		player->dir = 1;
		
		if((player->posx)%30!=0){
			player->posx -= player->vel;
		}
		else{
			player->posx -= player->vel;
		if(mapa_matriz[(player->posy/30)][((player->posx/30))]=='x' || mapa_matriz[(player->posy+29)/30][(player->posx/30)]=='x' || mapa_matriz[(player->posy/30)][((player->posx/30))]=='b' || mapa_matriz[(player->posy+29)/30][(player->posx/30)]=='b' )
                player->posx += player->vel;
		}
		pj = load_bitmap("media/bunnyizq2.bmp",NULL);
		
	}
	
	if(key[KEY_D]){ //MOVIMIENTO A LA DERECHA
	
		player->dir = 0;
		
		if((player->posx)%30!=0){
			player->posx += player->vel;
		}
		else{
			player->posx += player->vel;
		if(mapa_matriz[(player->posy/30)][((player->posx)/30)+1]=='x' || mapa_matriz[(player->posy+29)/30][(player->posx/30)+1]=='x' || mapa_matriz[(player->posy/30)][((player->posx)/30)+1]=='b' || mapa_matriz[(player->posy+29)/30][(player->posx/30)+1]=='b')
                player->posx -= player->vel;
		}
		pj = load_bitmap("media/bunnyder2.bmp",NULL);
		
	}
	
	if(key[KEY_W]){ //MOVIMIENTO ARRIBA
	
		player->dir = 2;
	
		
		if((player->posy)%30!=0){
			player->posy -= player->vel;
		}
		else{
			player->posy -= player->vel;
		if(mapa_matriz[(player->posy/30)][(player->posx/30)]=='x' || mapa_matriz[(player->posy)/30][(player->posx+29)/30]=='x' || mapa_matriz[(player->posy/30)][(player->posx/30)]=='b' || mapa_matriz[(player->posy)/30][(player->posx+29)/30]=='b') 
                player->posy += player->vel;
    	
		}
	}
	
	if(key[KEY_S]){ //MOVIMIENTO ABAJO
		
		player->dir = 3;
		
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
////////////////////

////////////////////-lEE ENEMIGOS DEL ARCHIVO TXT Y LOS INICIALIZA
int leer_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;//contadores
	int cont=0;//contador de cantidad de enemigo que sera regresada en el retur a la variable en el main 'cont_enemigos'
	
	for(i=0;i<MAXFILAS;i++){//Ciclo for anidado en un ciclo for para la inicializacion de los enemigos dependiendo de la matriz
		for(j=0;j<MAXCOL;j++){
			
			if(mapa_matriz[i][j] == 'e'){ //Si detecta una 'e' en el mapa comienza la inicializacion de los enemigos
				
				npc[cont].posx = j*30; //posicion inicial enemigo X
				npc[cont].posy = i*30; //posicion inicial enemigo y
				npc[cont].vel = 4.5; //velocidad del enemigo
				npc[cont].direccion = 1; // direccion donde iniciara moviendose el enemigo segun la colision
				npc[cont].tipo = (rand() % 2)+1; // tipo de movimiento (Arriba,Abajo,Izq,Der) de manera al azar
				cont++; //incremento
				
			}
		}
	}
	
	return cont;//devolucion del valor cont para el uso de otra funcion
}
////////////////////

////////////////////-MOVIMIENTO DEL ENEMIGO
void movimiento_enemigos(Enemigo npc[20],int cont_enemigos){
	
	int i,j;//contadores
	
	for(i=0;i<cont_enemigos;i++){
		
		if(npc[i].tipo == 1 ){ // Incrementa el movimiento positivo segun direccion en X
			npc[i].posx += npc[i].direccion*npc[i].vel;
			malo = load_bitmap("media/enemigoloop.bmp",NULL);

		}
		
		if(npc[i].tipo == 2){ // Incrementa el movimiento positivo segun direccion en Y
			npc[i].posy -= npc[i].direccion*npc[i].vel; 
			malo = load_bitmap("media/enemigo.bmp",NULL);

		}
		draw_sprite(fondo,malo,npc[i].posx,npc[i].posy);
	}
	
}
////////////////////

////////////////////-COLISION DEL ENEMIGO Y CAMBIO DE DIRECCION
void colision_enemigos(Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos){
	
	int i; //contador
	
	for(i=0;i<cont_enemigos;i++){ //Ciclo for encargado de iniciar el funcionamiento de las colisiones
		
		if(npc[i].tipo == 1){ //Los de TIPO 1 cambian a TIPO 2 al encontrar un obstaculo y estos cambian de direccion de movimiento

			if(mapa_matriz[(npc[i].posy/30)][((npc[i].posx)/30)+1]=='x' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)+1]=='x' || mapa_matriz[(npc[i].posy/30)][((npc[i].posx)/30)+1]=='b' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)+1]=='b'){
				
			
	                npc[i].direccion = npc[i].direccion*-1;
	                
			}
		
			if(mapa_matriz[(npc[i].posy/30)][((npc[i].posx/30))]=='x' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)]=='x' || mapa_matriz[(npc[i].posy/30)][((npc[i].posx/30))]=='b' || mapa_matriz[(npc[i].posy+29)/30][(npc[i].posx/30)]=='b' ){
			
				    npc[i].direccion = npc[i].direccion*-1;
			}
			
		}
		
		if(npc[i].tipo == 2){ //Los de TIPO 2 cambian a TIPO 1 al encontrar un obstaculo y estos cambian de direccion de movimiento

			if(mapa_matriz[(npc[i].posy/30)][(npc[i].posx/30)]=='x' || mapa_matriz[(npc[i].posy)/30][(npc[i].posx+29)/30]=='x' || mapa_matriz[(npc[i].posy/30)][(npc[i].posx/30)]=='b' || mapa_matriz[(npc[i].posy)/30][(npc[i].posx+29)/30]=='b'){
			
				npc[i].direccion = npc[i].direccion*-1;
			} 
			if(mapa_matriz[(npc[i].posy/30)+1][(npc[i].posx/30)]=='x' || mapa_matriz[(npc[i].posy/30)+1][(npc[i].posx+29)/30]=='x' || mapa_matriz[(npc[i].posy/30)+1][(npc[i].posx/30)]=='b' || mapa_matriz[(npc[i].posy/30)+1][(npc[i].posx+29)/30]=='b'){

				npc[i].direccion = npc[i].direccion*-1;
			
			}
		}
		
	}
}
////////////////////


////////////////////-COLISION DEL JUGADOR CON EL ENEMIGO
void colision_enemigos_jugador(Jugador *player, Enemigo npc[20],char mapa_matriz[MAXFILAS][MAXCOL],int cont_enemigos){
	
	int i,j; //Contadores
		
	for(i=0;i<cont_enemigos;i++){ //Ciclo for encargado de comprobar las colisiones del enemigo y el jugador
		
		if(player->posx/30  == npc[i].posx/30 && player->posy/30 == npc[i].posy/30){ //Si el jugador colisiona con algun enemigo
			
			//Vuelve a la posicion de X e Y iniciales
			player->posx = 60;
			player->posy = 660;
		
			player->vidas--;// Se descuentan vidas
			
			if(player->vidas<=0){ //limite de reduccion de vida que es igual a 0
				player->vidas = 0;
			}
		
			player->pts = player->pts - 50;// Colisionar con enemigos reduce puntos
			
			if(player->pts<=0){ //limite de reduccion de puntos que sean 0
				player->pts = 0;
			}
			
		}
	}

	
}
////////////////////	

////////////////////-LEE LOS OBJETOS DEL ARCHIVO TXT Y LOS INICIALIZA CON POSICION AL AZAR
int leer_item_z(Item zanah[15],char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;// contador
	int cont_item=0; // contador de item para devolucion fuera de la funcion para el uso de otra funcion
	
	for(i=0;i<MAXFILAS;i++){ //Ciclo for anidado en otro for para inicializar las posiciones de los objetos
		for(j=0;j<MAXCOL;j++){
			
			if(mapa_matriz[i][j] == 'z'){ // si encuentra una 'z' que es un objeto representado como zanahoria
				
				zanah[cont_item].posx = (rand() % 22)+1;//Al azar da un valor a la posicion x
				zanah[cont_item].posy = (rand() % 22)+1;//Al azar da un valor a la posicion y
				
				//Limitante por si se encuentra un obstaculo recalcular numeros al azar para las posisiones
				while(mapa_matriz[zanah[cont_item].posy][zanah[cont_item].posx] == 'x' || mapa_matriz[zanah[cont_item].posy][zanah[cont_item].posx]  == 'b' || mapa_matriz[zanah[cont_item].posy][zanah[cont_item].posx]  == 'e'){
					zanah[cont_item].posx = (rand() % 22)+1;
					zanah[cont_item].posy = (rand() % 22)+1;
				}	
				
				//Se multiplican las posiciones para que esten de acuerdo con los bloques que serian en 30x30
				zanah[cont_item].posx *= 30;
				zanah[cont_item].posy *= 30;
				
				zanah[cont_item].toca = false; // Inicializa en false para usarse en las colisiones con el jugador en otra funcion
				cont_item++;//contador para devolver el valor de cuantos objetos hay
			}
			
		}
	}
	
	return cont_item; // retorno del valor del contador de objetos en mapa
	
}
////////////////////

////////////////////-DIBUJA EL OBJETO EN PANTALLA
void dibuja_item_z(Item zanah[15],int cont_items){
	
	int i=0;// contador
	
	for(i=0;i<cont_items;i++){ // ciclo for que usa el cont_items para dibujar los objetos hasta la cantidad de objetos que existen en el mapa
		
		if(zanah[i].toca  == false){ // Si no es colisionado por el jugador
		
		draw_sprite(fondo,item1,zanah[i].posx,zanah[i].posy); // se dibuja en la posicion correspondiente
		
		}
	}
	
}
////////////////////

////////////////////-COLISION DEL JUGADOR CON EL ITEM
int col_jugador_item(Jugador *player,Item zanah[15],int cont_items,char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i=0,j=0;//contador
	int cont_enemigos;

	
	for(i=0;i<cont_items;i++){
		
		//Entra al if si la posicion del jugador es la misma que la del objeto y si este objeto no fue tocado con anterioridad
		if(player->posx/30 == zanah[i].posx/30 && player->posy/30 == zanah[i].posy/30 && zanah[i].toca == false){ //abajo
		
			player->pts += 50;//suma puntos
			zanah[i].toca = true; //cambia a tocado el objeto
			conteotoca++;//conteo de cuantas toca en mapa para el reinicio de los objetos y reiniciar la cantidad
		}
		
		
		if(conteotoca == 9){ // una vez se hayan tocado todos los objetos del mapa
	
			dibuja_item_z(zanah,cont_items); //los vuelve a dibujar en posiciones diferentes
			cont_items = leer_item_z(zanah,mapa_matriz); //vuelve a leer la cantidad original de los objetos
			conteotoca = 0; // se reinicia el conteo de item para repetir el proceso
			n++;
		}
		
		
	}
	return n;
}
////////////////////

////////////////////-DIBUJA AL JUGADOR Y EL FONDO
void pantalla(Jugador p){
	
	draw_sprite(fondo,pj,p.posx,p.posy); //dibuja el personaje
	blit(fondo,screen,0,0,0,0,P_AN,P_AL); //Imprime el fondo
	
}
////////////////////

////////////////////-DIBUJA PUNTOS DEL JUGADOR
void puntos(Jugador player){
		
	textprintf_ex(fondo, font,400,35, makecol(0, 0, 0),-1, "%d  pts",player.pts); //imprime los puntos en x 400 y 35
}
////////////////////

void menu(int op){
	
	int inicia = 0;
	
	do{
		
		if(key[KEY_S] && op != 2){
			op++;
			rest(80);
		}
		if(key[KEY_W] && op != 0){
			op--;
			rest(80);
			
		}
		
		if(op == 0){
			fondo = load_bitmap("media/menu1.bmp",NULL);
			blit(fondo,screen,0,0,0,0,P_AN,P_AL);
			
			if(key[KEY_SPACE]){
				inicia = 1;
			}
		}
		if(op == 1){
			fondo = load_bitmap("media/menu2.bmp",NULL);
			blit(fondo,screen,0,0,0,0,P_AN,P_AL);
		}
		if(op == 2){
			fondo = load_bitmap("media/menu3.bmp",NULL);
			blit(fondo,screen,0,0,0,0,P_AN,P_AL);
			
			if(key[KEY_SPACE]){
				allegro_exit();
			}
			
		}
		
		
		
	}while(inicia != 1);
	
}

int leer_trampa(Trampa trampa[15],char mapa_matriz[MAXFILAS][MAXCOL]){
	
	int i,j;// contador
	int cont_trampa=0; // contador de item para devolucion fuera de la funcion para el uso de otra funcion
	
	for(i=0;i<MAXFILAS;i++){ //Ciclo for anidado en otro for para inicializar las posiciones de los objetos
		for(j=0;j<MAXCOL;j++){
			
			if(mapa_matriz[i][j] == 't'){ // si encuentra una 'z' que es un objeto representado como zanahoria
				
				trampa[cont_trampa].posx = (rand() % 22)+1;//Al azar da un valor a la posicion x
				trampa[cont_trampa].posy = (rand() % 22)+1;//Al azar da un valor a la posicion y
				
				//Limitante por si se encuentra un obstaculo recalcular numeros al azar para las posisiones
				while(mapa_matriz[trampa[cont_trampa].posy][trampa[cont_trampa].posx] == 'x' || mapa_matriz[trampa[cont_trampa].posy][trampa[cont_trampa].posx]  == 'b' || mapa_matriz[trampa[cont_trampa].posy][trampa[cont_trampa].posx]  == 'e' || mapa_matriz[trampa[cont_trampa].posy][trampa[cont_trampa].posx]  == 'z'){
					trampa[cont_trampa].posx = (rand() % 22)+1;
					trampa[cont_trampa].posy = (rand() % 22)+1;
				}	
				
				//Se multiplican las posiciones para que esten de acuerdo con los bloques que serian en 30x30
				trampa[cont_trampa].posx *= 30;
				trampa[cont_trampa].posy *= 30;
				
				trampa[cont_trampa].toca = false; // Inicializa en false para usarse en las colisiones con el jugador en otra funcion
				cont_trampa++;//contador para devolver el valor de cuantos objetos hay
			}
			
		}
	}
	
	return cont_trampa;
	
}
void dibuja_trampa(Trampa t[15],int conttrampa){
	
	int i=0;// contador
	
	for(i=0;i<conttrampa;i++){ // ciclo for que usa el cont_items para dibujar los objetos hasta la cantidad de objetos que existen en el mapa
		
		if(t[i].toca  == false){ // Si no es colisionado por el jugador
		
		draw_sprite(fondo,trampaimg,t[i].posx,t[i].posy); // se dibuja en la posicion correspondiente
		
		}
	}
}

void col_jugador_trampa(Jugador *player,Trampa trampa[15],char mapa_matriz[MAXFILAS][MAXCOL],int conttrampa){
	
	int i=0,j=0;//contador
	int cont_enemigos;

	
	for(i=0;i<conttrampa;i++){
		
		//Entra al if si la posicion del jugador es la misma que la del objeto y si este objeto no fue tocado con anterioridad
		if(player->posx/30 == trampa[i].posx/30 && player->posy/30 == trampa[i].posy/30 && trampa[i].toca == false){
		
			player->pts -= 100;//suma puntos
			
			if(player->pts<=0){ //limite de reduccion de puntos que sean 0
				player->pts = 0;
			}
			
			player->vidas --;
			trampa[i].toca = true; //cambia a tocado el objeto
		}
		
	}
}

////////////////////DESTROYS
void destroys(){
	
	destroy_bitmap(inicio);
	destroy_bitmap(fondo);
	destroy_bitmap(pj);
	destroy_bitmap(malo);
	destroy_bitmap(bush);
	destroy_bitmap(borde);	
	destroy_bitmap(item1);
	destroy_bitmap(vida);
	destroy_bitmap(vida_menos);
	destroy_bitmap(pausa);
	destroy_bitmap(trampaimg);

	
	
}
////////////////////
