#include<stdio.h>
#include<math.h>
#include <stdlib.h>
#include<time.h>

#define NUMFILAS 16
#define  NUMCOLS 70

//función que inicializa lo que se muestra en la pantalla
void iniciapantalla( char pantalla[NUMFILAS][NUMCOLS])
{
 int i, j;
  for (i = 0; i < NUMFILAS; i++)
   {
    for (j = 0; j < NUMCOLS; j++)
     {
       pantalla[i][j] = ' ';

     }
   }

  //dibujo de la diana

  i=(int)(NUMFILAS/2-1);
  pantalla[i-1][NUMCOLS-5] = 'X';
  pantalla[i][NUMCOLS-5] = 'X';
  pantalla[i+1][NUMCOLS-5] = 'X';

  //dibujo de cañón
  pantalla[NUMFILAS-1][0] = '/';
}

//función que va moviendo toda las  dianas
void movertodadiana (char pantalla[NUMFILAS][NUMCOLS]){
  int i, j,p,q,k;        //contadores
  srand(time(NULL));
  int m=(int)(NUMFILAS/2-1)-1;    //posicion de la
  int n=NUMCOLS-5;                //primera diana
  q=-7+rand()%13;                 //numero aleatorio entre -7 y 5
  for (i=0;i<3;i++){              // loop para posicion de cada diana

    // la posicion propuesta debe de satisfacer que no haya ya una diana ahí
    // y que no se salga de la pantalla
    if(q!=0 && pantalla[m+i+q][n+q]==' ' && m+i+q<NUMFILAS && n+q<NUMCOLS){
      pantalla[m+i+q][n+q]='X';
      pantalla[m+i][n]=' ';
    }
  }
}

//función que va moviendo cada  diana
void movercadadiana (char pantalla[NUMFILAS][NUMCOLS]){
  int i, j,p,q;   //contadores
  int m=(int)(NUMFILAS/2-1)-1;    //posicion de la
  int n=NUMCOLS-5;                //primera diana
  srand(time(NULL));
  p=rand() % 2;                   //numero aleatorio entre 0 y 1
  for (i=0;i<3;i++){              // loop para posicion de cada diana
    q=-7+rand()%13;               //numero aleatorio entre -7 y 5

    //Si p=0 se mueve la diana a la izquierda o derecha si p=1 se mueve hacia
    //arriba o hacia abajo
    // la posicion propuesta debe de satisfacer que no haya ya una diana ahí
    // y que no se salga de la pantalla
    if(p==1 && q!=0 && pantalla[m+i+q][n]==' ' && m+i+q<NUMFILAS){
      pantalla[m+i+q][n]='X';
      pantalla[m+i][n]=' ';
    }
    if(p==0 && q!=0 && pantalla[m+i][n+q]==' ' && n+q<NUMCOLS){
      pantalla[m+i][n+q]='X';
      pantalla[m+i][n]=' ';
    }
  }
}

//función que imprime la matríz en pantalla
void dibujapantalla( char pantalla[NUMFILAS][NUMCOLS])
{
int i, j;
   printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");

  for( i = 0; i < NUMFILAS; i++)
  {
    for( j = 0; j < NUMCOLS; j++)
      {printf("%c" , pantalla[i][j] );
      }
      printf("\n");
  }
   printf("+++++++++++++++++++++++++++++++++++++++++++++++++\n");

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
  int k=1;
  char pantalla[NUMFILAS][NUMCOLS]; //matriz que dibuja la trayectoria del *

  do
  {
    x = 0, y = 0; //inicializa el asterisco en el origen
    iniciapantalla(pantalla);

    //if para que al primer tiro la diana este en su posicion
    //inicial y ya despues se mueva aleatoriamente
    if(k>1){
    movercadadiana(pantalla);
    }
    dibujapantalla(pantalla);

    printf("Angry asterísco\n");
    //El jugador introduce los datos

    printf("Introduce la velocidad inicial\n");
    scanf("%f", &v0);
    printf("Introduce ahora el ángulo de disparo en grados \n");
    scanf("%f", &alfa);

    //loop que calcula la trayectoria
    for( t=0; x<xd && x>=0; t=t+0.01)
    {
      posicion(v0, alfa, t, &x, &y);
      i=(int)(yd-y)/yd*NUMFILAS/2 + NUMFILAS/2 - 1;
      j = (int)x/xd*(NUMCOLS-1);

      //impresión de * si está dentro de la pantalla
      if ( i >= 0 && i<NUMFILAS && j >= 0 && j<NUMCOLS)
      {
       //Si se alcanza la diana se termina el loop
        if(pantalla[i][j]=='X')
        {acierto = 1; }
        pantalla[i][j]='*';
      }

    }

    dibujapantalla(pantalla);
    k=k+1;
  } while (acierto ==0);
  printf("Lo lograste, pasas al siguiente nivel\n");
}
