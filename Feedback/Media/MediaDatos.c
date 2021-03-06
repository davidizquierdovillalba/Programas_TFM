#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int extraeNumeroGalaxias ();
int extraeNumeroGalaxiasDistintoFormato ();
void CalculaMediaFichero ();


int main()
{
/*int nGalaxias;
nGalaxias=extraeNumeroGalaxias();
printf("El numero de galaxias es: %d\n",nGalaxias);*/
CalculaMediaFichero();
}


//----------------------------------------------------------------------------------------------------

int extraeNumeroGalaxias ()
{
FILE *file1;
char caracter;
char nombreFichero[100];
float datoleido;
int i,j,nBines;
i=j=0;
nBines=21;

printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");

if(file1==NULL)
    printf("El fichero no existe\n");

else
   {

         while(!feof(file1))
         {
            fscanf(file1, "%E",&datoleido);
            //printf("He leido: %E\n",datoleido);
                for(i=0;i<nBines;i++)
                    {
                        fscanf(file1, "%E",&datoleido);
                        fscanf(file1, "%E",&datoleido);
                        //if(i==29) printf("El valor de is_central es: %f\n",datoleido);
                    }

             j++;

                }


         }


j--;

fclose(file1);
return j;
}

//----------------------------------------------------------------------------------------------------

int extraeNumeroGalaxiasDistintoFormato()
{
FILE *file1;
char caracter;
char nombreFichero[100];
float datoleido;
int i,j;
i=j=0;

printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");

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

//-------------------------------------------------------------------------------------------

void CalculaMediaFichero ()
{
FILE *filein;
FILE *file3;
float indice, posicion,densidadNumerica,vol,volumen[100],posi[100],media[100],delta[100],n,nPromedio;
int i,j,NormalizarHistograma,numeroGalaxias,numGal,nbines;
char s[100];
nbines=21;

printf("Dame el nombre del archivo para que genere meida .vs. distancia y delta .vs. distancia\n");
scanf("%s",s);

numGal=0;
NormalizarHistograma=0;

for(i=0;i<nbines;i++) media[i]=0;

filein=fopen(s,"r");

if(filein==NULL) printf("ERROR\n");

else
{   fscanf(filein,"%E",&indice);

    while(!feof(filein))
    {
        for(j=0;j<nbines;j++)
        {
            fscanf(filein,"%f %f",&posicion,&densidadNumerica);
            media[j]=media[j]+densidadNumerica;
            if(numGal==0) posi[j]=posicion;
        }
    numGal++;
    fscanf(filein,"%E",&indice);

    }

printf("El valor de numGal es: %d\n",numGal);

vol=(4.0/3.0)*3.1415*pow(500,3);

nPromedio=extraeNumeroGalaxiasDistintoFormato();

printf("El valor de galaxias campo es: %f\n",nPromedio);

printf("El numero de galaxias es: %f\n",nPromedio);
nPromedio=nPromedio/vol;

for(i=0;i<nbines;i++) volumen[i]=(4./3)*3.1415*pow(posi[i],3);

//printf("El valor normalizado del histograma es: %d\n",NormalizarHistograma);
for(i=0;i<nbines;i++) media[i]=media[i]/numGal;//Hago la media
for(i=0;i<nbines;i++) media[i]=media[i]/volumen[i];
for(i=0;i<nbines;i++) media[i]=(media[i]-nPromedio)/nPromedio;
for(i=0;i<nbines;i++) printf("El valor de media[%d] es: %f\n",i,media[i]);

printf("---------------------------------------------\n");

file3=fopen("Densidad","w");

if(file3==NULL) printf("ERROR EN LA APERTURA DEL FICHERO QUE GENERARE LA DENSIDAD .VS. DISTANCIA\n");

else
    {
            fprintf(file3,"Distancia\tDensidad\n");
            for(i=0;i<nbines;i++){fprintf(file3,"%f\t%f\n",posi[i],log10(media[i]));}
    }
}
fclose(filein);
fclose(file3);
}
