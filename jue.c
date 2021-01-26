/////////////////////////////////////////////
//Angry asterísco :
//	Juego en el que se lanza un asterísco que debe alcanzar la X
//Integrantes: Rosa Vianney Avila 
//	       Oscar Daniel Ortega
//	       Diego Peña
//	       Claudia Elizabeth Peña
//////////////////////////////////////////////	       


#include<stdio.h>
#include<math.h>

#define NUMFILAS 16
#define NUMCOLS 70

int lifesi = 3, lifesf; //vidas iniciales y finales
 
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

//función que suma dos vidas 
int ganavidas (int lifesf)
{
	lifesf = lifesi + 2;
	lifesi = lifesf; 
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

///////////////////////
void bonus( char pantalla[NUMFILAS][NUMCOLS])
{
 int i, j;
	printf("Si le das al <3, obtienes 2 vidas extra\n"); 
  for (i = 0; i < NUMFILAS; i++)
    for (j = 0; j < NUMCOLS; j++)
     pantalla[i][j] = ' ' ;
        //dibujo de la diana
        	i=(int)NUMFILAS/2-1;
        	//pantalla[i-1][NUMCOLS-1] = 'X';
        	pantalla[i-3][NUMCOLS-1] = '3';
        	pantalla[i-3][NUMCOLS-2] = '<';
        	//dibujo del cañón
        	pantalla[NUMFILAS - 1][0] = '/';
        }

/////////////////////////////////////////////////////////

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

//función que calcula la posición del objeto
//en un medio viscoso de parámetro "b"
void posicionvisc( float v, float alfa, float t, float *px, float *py) 
{
  float g=9.8; 
  float b=0.1;
  float vx0 = v*cos(alfa*M_PI/180); 
  float vy0 = v*sin(alfa*M_PI/180); 
  
  *px = (vx0/b)*(1-exp(-b*t)); 
  *py = (1/b)*(g/b+vy0)*(1-exp(-b*t))-(g/b)*t;
}

//función que calcula la posición del objeto
//en un medio viscoso de parámetro distintos. Usando la constante del objeto y una forma arbitraria.
void posvis( float v, float alfa, float t, float *px, float *py, float beta_, float G_)
{
  float g=9.8;
  float vx0 = v*cos(alfa*M_PI/180);
  float vy0 = v*sin(alfa*M_PI/180);

  *px = (vx0/beta_)*(1-exp(-beta_*t));
  *py = (G_/pow(beta_,2))*(1+(beta_*vx0/G_))*(1-exp(-beta_*t))-(g/beta_)*t;
}





//función que le da la oportunidad al usuario de ganar dos vidas extra

void extravidas(void)
{

float x, y; //posición del objeto
 //////////////////
float xd=100, yd=50; //posición de la diana
 ////////////////////////
 float alfa, v0, t; // ángulo, velocidad, tiempo
 int i, j, acierto =0; //contadores
 char pantalla[NUMFILAS][NUMCOLS]; //matriz que dibuja la trayectoria del *
 		x = 0;
 		y = 0; //inicializa el asterisco en el origen

	bonus(pantalla);
      	dibujapantalla(pantalla);
        printf("Introduce la velocidad inicial\n");
        scanf("%f", &v0);
        printf("Introduce ahora el ángulo de disparo en grados \n");
        scanf("%f", &alfa);

                for( t = 0; x < xd && x >= 0; t=t+0.01)
        {
        posicion(v0, alfa, t, &x, &y);
        i=(int)(yd-y)/yd*NUMFILAS/2 + NUMFILAS/2 - 1;
        j = (int)x/xd*(NUMCOLS-1);

                if ( i >= 0 && i < NUMFILAS && j >= 0 && j<NUMCOLS)
                {
                if(pantalla[i][j]=='<')
                {acierto = 1; }
                pantalla[i][j]='*';
                }
        }
	if(acierto == 1) //si acierta,
        {
         ganavidas(lifesi); //gana las dos vidas 
             }	

	dibujapantalla(pantalla); 
}


void nivel1(void)
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
	    	////////////////////////////////////////////
		if(lifesi == 1)
		{

		extravidas();

		 //dibujapantalla(pantalla);
		}
		//////////////////////////////////////////// 
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
}

void nivel2(void)
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
      	posicionvisc(v0, alfa, t, &x, &y); 
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
	    	////////////////////////////////////////////
		if(lifesi == 1)
		{

		extravidas();

		 //dibujapantalla(pantalla);
		}
		//////////////////////////////////////////// 
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
}

void nivel3(void)
{
        float x, y; //posición del objeto
 //////////////////
        float xd=100, yd=50; //posición de la diana 
 /////////////////////// 
        float alfa, v0, t; // ángulo, velocidad, tiempo 
        int i, j, acierto =0; //contadores
	float G, beta;  //Valores de consantes para un medio viscoso
	float rho_e, rho_f, nu, R_1;//  Definición de las variables,densida del medio, densidad del objeto, indice de viscocidad y radio de objeto
	float g_1;//Definición de la gravedad fuera de la función para calcular G y beta, y meterlo a la función.
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

        printf("Introduce la velocidad inicial:\n");
        scanf("%f", &v0);
        printf("Introduce ahora el ángulo de disparo en grados :\n");
        scanf("%f", &alfa);
	printf("Introduce el índice de viscocidad:\n");
	scanf("%f", &nu);
	printf("Intriduce la densidad del medio\n");
	scanf("%f", &rho_e);


	R_1 = 1;
        rho_f = 1;
        G = (1-(rho_f/rho_e))*9.81;
        beta = (9*nu)/(2*pow(R_1, 2)*rho_e);



         //loop que calcula la trayectoria
         for( t = 0; x < xd && x >= 0; t=t+0.01)
	{
        posvis(v0, alfa, t, &x, &y, beta, G);
        i = (int)(yd-y)/yd*NUMFILAS/2 + NUMFILAS/2 - 1;
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
                ////////////////////////////////////////////
                if(lifesi == 1)
                {

                extravidas();

                 //dibujapantalla(pantalla);
                }
                //////////////////////////////////////////// 
                if(lifesi == 0)//si se acaban las vidas
                {
                acierto = 1;  // Se termina el juego  
                salir() ; } //despedida 
                }
          else //Se logró el objetivo
        {
        dibujapantalla(pantalla);
        printf("Lo lograste!! Pasas al siguiente nivel \n"); }
	}while (acierto ==0);
}






int main()
{
	    nivel1(); 
      nivel2();	 
nivel3();
return 0; 
}
