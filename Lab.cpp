/*
  Archivo: Laberinto.cpp
  Autor: Luis Felipe Valencia (1824494), Jose Fernando Botina (1830628)
  Email: luis.valencia.valencia@correounivalle.edu.co
  Fecha creación: 2018-09-17
  Fecha última modificación: 2018-10-05
  Versión: 0.1
  Licencia: GPL
*/

#include "Laberinto.h"

Laberinto::Laberinto(int numeroFilas, int numeroColumnas, int numeroTesoros, int numeroGnomos, int numeroDragones, double porcentajeCasillasVacias)
{
  this->numeroFilas = numeroFilas;
  this->numeroColumnas = numeroColumnas;
  this->numeroTesoros = numeroTesoros;
  this->numeroGnomos = numeroGnomos;
  this->numeroDragones = numeroDragones;
  this->porcentajeCasillasVacias = porcentajeCasillasVacias;
  tablero = new int*[numeroFilas];
  for(int fila=0; fila<numeroFilas; fila++)
  {
    tablero[fila] = new int[numeroColumnas];
    for(int columna=0; columna<numeroColumnas; columna++)
      tablero[fila][columna] = 1;  // Llena todo el laberinto con paredes
  }
  casillasVacias = 0;

  filaEntrada = rand() % numeroFilas;
  tablero[filaEntrada][0] = 5;  // Pone la entrada
  filaSalida = rand() % numeroFilas;
  tablero[filaSalida][numeroColumnas-1] = 6;  // Pone la salida
}


Laberinto::~Laberinto()
{
  for(int fila=0; fila<numeroFilas; fila++)
    delete tablero[fila];
  delete [] tablero;
  //tablero = 0;
}


void Laberinto::fabricarCamino()
{
  
  this->ponerEnCasillaLlenaAlAzar(0);
  
  for(int i = 0; i<500; i++)
  {
    this->ponerEnCasillaVaciaAlAzar(1);
    
  }
  
  casillasVacias += trazaLineaRecta(filaEntrada, 0, filaSalida, numeroColumnas-1); // Hacer el camino de salida:
  
  /*
  int numeroDeCaminosAInsertar = 0;    // Hacer caminos al azar:
  while(numeroDeCaminosAInsertar < 6)
  {
    trazaLineaRecta(1,1,19,79); 
    numeroDeCaminosAInsertar++;
  }
  
  trazaLineaRecta(5,1,19,79);
  
  */
  
 
  // Poner los Tesoros(2) al azar 
  int numeroDeTesorosAInsertar = 0;
  while(numeroDeTesorosAInsertar < numeroTesoros)
  {
    ponerEnCasillaVaciaAlAzar(2);
    numeroDeTesorosAInsertar++;
  } 
  // Poner los Gnomos(3) al azar 
  int numeroDeGnomosAInsertar = 0;
  while(numeroDeGnomosAInsertar < numeroGnomos)
  {
    ponerEnCasillaVaciaAlAzar(3);
    numeroDeGnomosAInsertar++;
  } 

  // Poner los Dragones(4) al azar, cerca de la salida
  int numeroDeDragonesAInsertar = 0;
  while (numeroDeDragonesAInsertar < numeroDragones)
  {
    ponerEnCasillaVaciaAlAzar(4);
    numeroDeDragonesAInsertar++;
  }
  
  tablero[filaEntrada][0] = 5;
  tablero[filaSalida][numeroColumnas - 1] = 6;

  
}


int Laberinto::trazaLineaRecta(int filaInicial, int columnaInicial, int filaFinal, int columnaFinal)
{
  int contarVacias = 0;

  float y = (filaFinal - filaInicial);
  float x = (columnaFinal - columnaInicial);
  float pendiente = y / x;
  
  for (int posx = 0; posx < columnaFinal; posx++)
  {
    int ecuacionRecta = (pendiente * posx) + (pendiente * columnaFinal * -1) + filaFinal;
    tablero[ecuacionRecta][posx] = 0;
    tablero[ecuacionRecta][posx + 1] = 0;
    tablero[ecuacionRecta][posx - 1] = 0;
    contarVacias++;
  }

 return contarVacias;
}



void Laberinto::imprimir()
{
  for(int columna=0; columna<numeroColumnas+2; columna++)
    cout << "X";
  cout << endl;
  for(int fila=0; fila<numeroFilas; fila++)
  {
    cout << "X";
    for(int columna=0; columna<numeroColumnas; columna++)
      if(tablero[fila][columna] == 0)
        cout << " ";
      else
        cout << tablero[fila][columna];
    cout << "X" << endl;
  }
  for(int columna=0; columna<numeroColumnas+2; columna++)
    cout << "X";
  cout << endl;
  
}
    

void Laberinto::buscarCasillaAlAzar(int &fila, int &columna, int contenido)
{
  do
  {
    fila = rand() % numeroFilas;
    columna = rand() % numeroColumnas;
  }
  while(tablero[fila][columna] != contenido);
}



void Laberinto::ponerEnCasillaVaciaAlAzar(int contenido)
{
  if(contenido == 0)
  {
    int i;
    for(i=0;i<numeroDragones;i++)
    {
      if(tablero[filaSalida-1][numeroColumnas-2]==0)
      {
        tablero[filaSalida-1][numeroColumnas-2] = contenido;
      }
      else
      {
        if(tablero[filaSalida-1][numeroColumnas-1]==0)
        {
          tablero[filaSalida-1][numeroColumnas-1] = contenido;
        }
        else
        {
          if(tablero[filaSalida][numeroColumnas-2] == 0)
          {
            tablero[filaSalida][numeroColumnas-2] = contenido;
          }
          else
          {
            if(tablero[filaSalida+1][numeroColumnas-2] == 0)
            {
              tablero[filaSalida+1][numeroColumnas-2] = contenido;
            }
            else
            {
              if(tablero[filaSalida+1][numeroColumnas-1] == 0)
              {
                tablero[filaSalida+1][numeroColumnas-1] = contenido;}
            }
          }
        }
      }
    }
  }
  else
  {
    int fila, columna;
    buscarCasillaAlAzar(fila, columna, 0);
    tablero[fila][columna] = contenido;
  }
  

}

void Laberinto::ponerEnCasillaLlenaAlAzar(int contenido)
{
  for (int fila = 0; fila < numeroFilas; fila++)
    {
      for (int columna = 0; columna < numeroColumnas; columna++)
        {
          if(tablero[fila][columna] == 1)
            tablero[fila][columna] = contenido;
        }
    }
}

