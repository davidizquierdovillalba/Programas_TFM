#include <stdio.h>
#include <stdlib.h>
#include <math.h>


char nombreFich[100];
char nombreFichero[100];
float promedio;
using namespace std;
//-------------------------------------FUNCIONES ---------------------------------------------------
int NumeroGalaxias();
int NumeroGalaxiasDistintoFormato();
void CalculaMediana(int k);
void intercambiaMediana (int pos1, int pos2, float v[50000]);
void ordenaMinimoMediana (int dimV, float v[50000]);
void Normaliza();

//-----------------------------------------------------------------------------------------------------

int main()
{
int i;
int numero,nbines;
nbines=21;


printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias\n");
scanf("%s",nombreFichero);

printf("Dime el nombre del fichero del que quieres que calcule la mediana\n");
scanf("%s",nombreFich);

numero=NumeroGalaxias();
printf("El valor de numero de Galaxias es: %d\n",numero);

promedio=NumeroGalaxiasDistintoFormato();

for(i=0;i<nbines;i++) CalculaMediana(i);
//Normaliza();
//CalculaMediana(2);


}

//FUNCIONES--------------------------------------------------------------------------------------------------------

int NumeroGalaxias()
{
FILE *file1;
char caracter;
float datoleido;
int i,j;
i=j=0;
int nbines;

nbines=21;

file1=fopen(nombreFichero,"r");

if(file1==NULL)
    printf("El fichero no existe\n");

else
   {

    fscanf(file1, "%f",&datoleido);

         while(!feof(file1))
         {

            for(i=0;i<nbines;i++)
            {
                fscanf(file1, "%E",&datoleido);
                fscanf(file1, "%E",&datoleido);

            }
            j++;
            fscanf(file1, "%E",&datoleido);

         }

   }

fclose(file1);
return j;
}
//--------------------------------------------------------------------------------------------------------------
int NumeroGalaxiasDistintoFormato()
{
FILE *file1;
char caracter;
char name[100];
float datoleido;
int i,j;
i=j=0;

printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias de campo.\n");
scanf("%s",name);

file1=fopen(name,"r");

if(file1==NULL)
    printf("El fichero no existe\n");

else
   {

         while(!feof(file1))
         {
                for(i=0;i<4;i++)
                    {
                        fscanf(file1, "%E",&datoleido);
                    }

             j++;

                }


         }


j--;

fclose(file1);
return j;

}

//----------------------------------------------------------------------------------------------------------------------
void CalculaMediana(int k)
{
FILE *file1;
FILE *file2;
FILE *file3;
FILE *file4;
char caracter;
char nombreFichero[20];
float datoleido,vauxiliar[50],aux,auxMediana,percentil16,percentil84,D,valorDistancia,posicion[40],Mediana[40],mediana;
float volumen,num,vMediana[50000],vol,auxPromedio;
int i,j,nGalaxias,E,contadorantes,contadordespues,pos1,pos2,contadorceros,contador;
contadorantes=0;
contadordespues=0;
contadorceros=0;
contador=0;
num=0;
int nbines;

nbines=21;


printf("----------------El valor de k es: %d-------------------\n",k);


file1=fopen(nombreFich,"r");
file2=fopen("Valores_Percentil16","a");
file3=fopen("Valores_Percentil84","a");

if(k==0)
{
fprintf(file2,"Distancia\tDensidad\n");
fprintf(file3,"Distancia\tDensidad\n");
}

if(file1==NULL) printf("El fichero 1 no existe\n");
else if(file2==NULL) printf("El fichero 2 no existe\n");

else
   {    j=0;
        fscanf(file1, "%E",&datoleido);// leo la masa

         while(!feof(file1))
         {
            for(i=0;i<nbines;i++)
            {
                fscanf(file1, "%E",&datoleido);//leo la posicion
                posicion[i]=datoleido;
                fscanf(file1, "%E",&datoleido);// leo la densidad numerica
                Mediana[i]=datoleido;

            }
        vMediana[j]=Mediana[k];
        j++;
        fscanf(file1, "%E",&datoleido);//leo la masa
         }
valorDistancia=posicion[k];

    }
fclose(file1);
nGalaxias=NumeroGalaxias();
printf("El valor de nGalaxias es: %d",nGalaxias);

ordenaMinimoMediana(nGalaxias,vMediana);
//for(i=0;i<nGalaxias;i++) printf("El valor de la mediana %d es: %f\n",i,vMediana[i]);

if((nGalaxias%2)!=0)
{

pos1=(nGalaxias)/2; //Quito el +1 por que los vectores empiezan en 0
mediana=vMediana[pos1];
printf("IMPAR: El valor de la mediana es: %f\n",mediana);
}
else
{

pos1=(nGalaxias/2)-1;//Hago el cambio por que los vectores empiezan en 0
pos2=(nGalaxias)/2;//Hago el cambio por que los vectores empiezan en 0

mediana=(vMediana[pos1]+vMediana[pos2])/2;
printf("PAR: El valor de la mediana es: %f\n",mediana);
}

aux=nGalaxias*0.16;
E=aux;
D=aux-E;

if(D==0) percentil16=(vMediana[E-1]+vMediana[E])/2;
else percentil16=vMediana[E];

aux=nGalaxias*0.84;
E=aux;
D=aux-E;

if(D==0) percentil84=(vMediana[E-1]+vMediana[E])/2;
else percentil84=vMediana[E];

vol=(4.0/3.0)*3.1415*pow(500,3);

printf("El valor de distancia es: %E\n",valorDistancia);
auxPromedio=promedio;
auxPromedio=auxPromedio/vol;

percentil16=percentil16/((4.0/3.0)*3.1415*pow(valorDistancia,3));
percentil84=percentil84/((4.0/3.0)*3.1415*pow(valorDistancia,3));

percentil16=(percentil16-auxPromedio)/auxPromedio;
percentil84=(percentil84-auxPromedio)/auxPromedio;

fprintf(file2,"%f\t%f\n",valorDistancia,log10(percentil16));
fprintf(file3,"%f\t%f\n",valorDistancia,log10(percentil84));

fclose(file2);
fclose(file3);
}
//------------------------------------------------------------------------------------------------------

void intercambiaMediana (int pos1, int pos2,float v[50000])
{
float aux0,aux1,aux2,aux3;

aux0=v[pos1];
v[pos1]=v[pos2]; //Intercambio
v[pos2]=aux0;
}

//--------------------------------------------------------------------------------------------------------------

void ordenaMinimoMediana(int dimV,float v[50000])
{

int i, j, ipos;
int aux;
for(i=0; i<(dimV-1);i++)
{
ipos=i;

    for(j=i+1; j<dimV; j++)
        {
            if(v[j]<v[ipos])
                {ipos=j;}
        }
intercambiaMediana(i,ipos,v);
}

}
