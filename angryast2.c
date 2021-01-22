/////////////////////////////////////////////
//Angry asterísco :
//	Juego en el que se lanza un asterísco que debe alcanzar la X
//Integrantes: Rosa Vianney
//	       Oscar Daniel Ortega
//	       Diego Peña
//	       Claudia Elizabeth Peña
//////////////////////////////////////////////	       


#include<stdio.h>
#include<math.h>

#define NUMFILAS 16
#define NUMCOLS 70

int lifesi = 5, lifesf; //vidas iniciales y finales
 
//función que actualiza el número de vidas del jugador 
int vidas(int lifesf)
{
	lifesf = lifesi; //actualizamos las vidas
	
	if (lifesi == 0)
	{ 
	  printf("Has perdido, lo sentimos :( \n"); 
	}
	else 
	{
	printf("Tienes %d vidas, suerte :D \n", lifesi);  
	}
	return lifesf; 
}

//función que resta una vida cada intento fallido
int retiro ( int lifesf)
{
	lifesf = lifesi-1;
	lifesi=lifesf; 
	vidas(lifesi);
	return lifesf;  

} 


//función que inicializa lo que se muestra en la pantalla
void iniciapantalla( char pantalla[NUMFILAS][NUMCOLS])
{
 int i, j; 
  for (i = 0; i < NUMFILAS; i++)
    for (j = 0; j < NUMCOLS; j++)
     pantalla[i][j] = ' ' ; 
  
	//dibujo de la diana
	i=(int)NUMFILAS/2-1;
  pantalla[i-1][NUMCOLS-1] = 'X'; 
  pantalla[i][NUMCOLS-1] = 'X'; 
  pantalla[i+1][NUMCOLS-1] = 'X';


	//dibujo del cañón
	pantalla[NUMFILAS - 1][0] = '/'; 
}
//función que imprime la matríz en pantalla

void dibujapantalla( char pantalla[NUMFILAS][NUMCOLS])
{
int i, j; 
  //printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");
  printf("\n");

  for( i = 0; i < NUMFILAS; i++)
  {
    for( j = 0; j < NUMCOLS; j++)
    { printf("%c" , pantalla[i][j] ); }
	printf("\n");
  }
  //printf("++++++++++++++++++++++++++++++++++++++++++++++++\n"); 
}

void salir(void)
{
	printf("Vuelve pronto ;) \n");
}

//función que calcula la posición del objeto
void posicion( float v, float alfa, float t, float *px, float *py) 
{
  float g=9.8; 
  float vx0 = v*cos(alfa*M_PI/180); 
  float vy0 = v*sin(alfa*M_PI/180); 
  
  *px = vx0*t; 
  *py = -(g*pow(t,2)/2) + vy0*t;
}
int main()
{

  	float x, y; //posición del objeto
 //////////////////
 	float xd=100, yd=50; //posición de la diana 
 /////////////////////// 
 	float alfa, v0, t; // ángulo, velocidad, tiempo 
 	int i, j, acierto =0; //contadores
 	
	////////
	char pantalla[NUMFILAS][NUMCOLS]; //matriz que dibuja la trayectoria del * 
	


	do 
 	{ 
	x = 0;
	y = 0; //inicializa el asterisco en el origen
	iniciapantalla(pantalla);
    	dibujapantalla(pantalla);
    
   	printf("Angry asterísco\n"); 
    	//El jugador introduce los datos
	
	printf("Introduce la velocidad inicial\n"); 
    	scanf("%f", &v0); 
    	printf("Introduce ahora el ángulo de disparo en grados \n"); 
    	scanf("%f", &alfa); 
    
   	 //loop que calcula la trayectoria
   	 for( t = 0; x < xd && x >= 0; t=t+0.01)
    	{
      	posicion(v0, alfa, t, &x, &y); 
      	i=(int)(yd-y)/yd*NUMFILAS/2 + NUMFILAS/2 - 1; 
      	j = (int)x/xd*(NUMCOLS-1); 
      
      	//impresión de * si está dentro de la pantalla
      	if ( i >= 0 && i < NUMFILAS && j >= 0 && j<NUMCOLS)
      {
       //Si se alcanza la diana se termina el loop
	if(pantalla[i][j]=='X')
        {acierto = 1; }	
        pantalla[i][j]='*';
      }
    	}
	  if(acierto == 0) //si no acierta
	{  retiro(lifesi); //restamos una vida
	dibujapantalla(pantalla);//comienza de nuevo el juego 
	  	if(lifesi == 0)//si se acaban las vidas
		{
		acierto = 1;  // Se termina el juego  
		salir() ; } //despedida 
		}
	  else //Se logró el objetivo
	{
	dibujapantalla(pantalla); 
	printf("Lo lograste!! Pasas al siguiente nivel \n"); }
  	} while (acierto ==0);
	 

return 0; 
}
