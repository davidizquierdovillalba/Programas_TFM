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

printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias de campo (AllGal).\n");
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
float datoleido,vauxiliar[50],aux,auxMediana,percentil10,percentil90,D,valorDistancia,posicion[40],Mediana[40],mediana;
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
file2=fopen("Valores_Mediana","a");
file3=fopen("Valores_Percentil10","a");
file4=fopen("Valores_Percentil90","a");
if(k==0)
{
fprintf(file2,"Distancia\tDensidad\n");
fprintf(file3,"Distancia\tDensidad\n");
fprintf(file4,"Distancia\tDensidad\n");
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

aux=nGalaxias*0.1;
E=aux;
D=aux-E;

if(D==0) percentil10=(vMediana[E-1]+vMediana[E])/2;
else percentil10=vMediana[E];

aux=nGalaxias*0.9;
E=aux;
D=aux-E;

if(D==0) percentil90=(vMediana[E-1]+vMediana[E])/2;
else percentil90=vMediana[E];

vol=(4.0/3.0)*3.1415*pow(500,3);

printf("El valor de distancia es: %E\n",valorDistancia);
auxPromedio=promedio;
auxPromedio=auxPromedio/vol;
mediana=mediana/((4.0/3.0)*3.1415*pow(valorDistancia,3));
percentil10=percentil10/((4.0/3.0)*3.1415*pow(valorDistancia,3));
percentil90=percentil90/((4.0/3.0)*3.1415*pow(valorDistancia,3));

mediana=(mediana-auxPromedio)/auxPromedio;
percentil10=(percentil10-auxPromedio)/auxPromedio;
percentil90=(percentil90-auxPromedio)/auxPromedio;

fprintf(file2,"%f\t%f\n",valorDistancia,log10(mediana));
fprintf(file3,"%f\t%f\n",valorDistancia,log10(percentil10));
fprintf(file4,"%f\t%f\n",valorDistancia,log10(percentil90));

fclose(file2);
fclose(file3);
fclose(file4);
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
//--------------------------------------------------------------------------------------------------------------

void Normaliza()
{
FILE *fileMediana;
FILE *filePercentil10;
FILE *filePercentil90;
FILE *fileMedianaOut;
FILE *filePercentil10Out;
FILE *filePercentil90Out;
float NormalizarHistograma,datoleido,aux[50],dist[50],volumen[50];
char Distancia[10], Densidad[10];
int i,nbines;
nbines=21;
//Genero los ficheros de interes finales
fileMedianaOut=fopen("Valores_Mediana","w");
filePercentil10Out=fopen("Valores_Percentil10","w");
filePercentil90Out=fopen("Valores_Percentil90","w");


//Abro los ficheros auxiliares
fileMediana=fopen("Valores_Mediana_Auxiliar_Borrar","r");
filePercentil10=fopen("Valores_Percentil10_Auxiliar_Borrar","r");
filePercentil90=fopen("Valores_Percentil90_Auxiliar_Borrar","r");


if(fileMediana==NULL) printf("Error al abrir Valores_Mediana_Auxiliar_Borrar\n");
else if(filePercentil10==NULL) printf("Error al abrir Valores_Percentil10_Auxiliar_Borrar\n");
else if(filePercentil90==NULL) printf("Error al abrir Valores_Percentil90_Auxiliar_Borrar\n");

else
{
//Mediana
        NormalizarHistograma=0;
        i=0;
       fscanf(fileMediana, "%s",Distancia);
       fscanf(fileMediana, "%s",Densidad);


while(!feof(fileMediana))
         {
            fscanf(fileMediana, "%E",&datoleido);//leo distancia
            dist[i]=datoleido;
            fscanf(fileMediana, "%E",&datoleido);//leo distancia
            //NormalizarHistograma=NormalizarHistograma+datoleido;
            aux[i]=datoleido;
            i++;
         }
for(i=0;i<nbines;i++) printf("El valor de la distancia es: %f\n",dist[i]);
for(i=0;i<nbines;i++) NormalizarHistograma=aux[i]+NormalizarHistograma;
for(i=0;i<nbines;i++) aux[i]=aux[i]/NormalizarHistograma;
for(i=0;i<nbines;i++) volumen[i]=(4.0/3.0)*(3.141516)*pow(dist[i],3);
for(i=0;i<nbines;i++) aux[i]=aux[i]/volumen[i];
fprintf(fileMedianaOut,"Distancia\tDensidad\n");
for(i=0;i<nbines;i++) fprintf(fileMedianaOut,"%f\t%E\n",log10(dist[i]),log10(aux[i]));
fclose(fileMedianaOut);
fclose(fileMediana);

//Percentil 10
       for(i=0;i<nbines;i++) aux[i]=0;
        NormalizarHistograma=0;
        i=0;
       fscanf(filePercentil10, "%s",Distancia);
       fscanf(filePercentil10, "%s",Densidad);


while(!feof(filePercentil10))
         {
            fscanf(filePercentil10, "%E",&datoleido);//leo distancia
            fscanf(filePercentil10, "%E",&datoleido);//leo densidad
            aux[i]=datoleido;
            //NormalizarHistograma=NormalizarHistograma+datoleido;
            i++;
         }

for(i=0;i<nbines;i++) NormalizarHistograma=aux[i]+NormalizarHistograma;
for(i=0;i<nbines;i++) aux[i]=aux[i]/NormalizarHistograma;
for(i=0;i<nbines;i++) volumen[i]=(4.0/3.0)*(3.141516)*pow(dist[i],3);
for(i=0;i<nbines;i++) aux[i]=aux[i]/volumen[i];
fprintf(filePercentil10Out,"Distancia\tDensidad\n");
for(i=0;i<nbines;i++) fprintf(filePercentil10Out,"%f\t%E\n",log10(dist[i]),log10(aux[i]));
fclose(filePercentil10Out);
fclose(filePercentil10);



//Percentil 90
       for(i=0;i<nbines;i++) aux[i]=0;
        NormalizarHistograma=0;
        i=0;
       fscanf(filePercentil90, "%s",Distancia);
       fscanf(filePercentil90, "%s",Densidad);

while(!feof(filePercentil90))
         {
            fscanf(filePercentil90, "%E",&datoleido);//leo distancia
            fscanf(filePercentil90, "%E",&datoleido);//leo densidad
            aux[i]=datoleido;
            //NormalizarHistograma=NormalizarHistograma+datoleido;
            i++;
         }
for(i=0;i<nbines;i++) NormalizarHistograma=aux[i]+NormalizarHistograma;
for(i=0;i<nbines;i++) aux[i]=aux[i]/NormalizarHistograma;
for(i=0;i<nbines;i++) volumen[i]=(4.0/3.0)*(3.141516)*pow(dist[i],3);
for(i=0;i<nbines;i++) aux[i]=aux[i]/volumen[i];
fprintf(filePercentil90Out,"Distancia\tDensidad\n");
for(i=0;i<nbines;i++) fprintf(filePercentil90Out,"%f\t%E\n",log10(dist[i]),log10(aux[i]));
fclose(filePercentil90Out);
fclose(filePercentil90);
}

remove("Valores_Mediana_Auxiliar_Borrar");
remove("Valores_Percentil10_Auxiliar_Borrar");
remove("Valores_Percentil90_Auxiliar_Borrar");

}
