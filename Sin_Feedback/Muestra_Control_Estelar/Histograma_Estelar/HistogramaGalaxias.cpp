#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define Max 1000000

int nIteraciones;
void pintavector(float v[Max], int dim);
int leeFichero (float vout[Max]);
void Histograma (float v[Max],int NumDatos);
void generaFicheroMasasHistogramaFormatoViejo();
void generaFicheroMasasHistogramaFormatoNuevo();

int main()
{
//generaFicheroMasasHistogramaFormatoViejo();
generaFicheroMasasHistogramaFormatoNuevo();
float v[Max];
int i, NumDatos;

NumDatos=leeFichero(v);
printf("El numero de datos es: %d\n",NumDatos);
Histograma(v,NumDatos);


}

//------------------------------------------------------------------------------------------------------
void generaFicheroMasasHistogramaFormatoNuevo()
{
FILE *file1;
FILE *fileout;
char caracter;
char nombreFichero[100];
float datoleido;
int i,j;
i=j=0;


printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
fileout=fopen("MasaSinRadio","w");

if(file1==NULL)
    printf("El fichero no existe\n");

else
   {
        fscanf(file1, "%c",&caracter);

         while(caracter!='\n')
            {
                fscanf(file1, "%c",&caracter);

            }

fscanf(file1, "%E",&datoleido);
         while(!feof(file1))
         {
                for(i=0;i<5;i++)
                   {
                        if(i==1) fprintf(fileout,"%E\n",datoleido);
                        fscanf(file1, "%E",&datoleido);
                   }

         }


   }

fclose(file1);
fclose(fileout);
}

//------------------------------------------------------------------------------------------------------

void generaFicheroMasasHistogramaFormatoViejo()
{
FILE *file1;
FILE *fileout;
char caracter;
char nombreFichero[100];
float datoleido;
int i,j;
i=j=0;


printf("Dime el nombre del fichero del que quieres que saque el numero de galaxias.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
fileout=fopen("MasaSinRadio","w");

if(file1==NULL)
    printf("El fichero no existe\n");

else
   {

         while(!feof(file1))
         {

            fscanf(file1, "%c",&caracter);

            if(caracter=='#')
                {
                    while(caracter!='\n')
                        {
                            fscanf(file1, "%c",&caracter);

                        }
                }

            if(caracter==' ')
                {

                    for(i=0;i<44;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            if(i==41) fprintf(fileout,"%E\n",datoleido);
                            //printf("El valor de dato leido es: %E\n",datoleido);
                        }

                }


         }

   }

fclose(file1);
fclose(fileout);
}
//---------------------------------------------------------------------------------------------------------

void pintavector(float v[Max], int dim)
{
     int i;
    for(i=0; i<dim;i++)
    {
        printf("%f\n",v[i]);
    }
}

//--------------------------------------------------------------------------------------------------------------

int leeFichero (float vout[1000])
{
FILE *file;
int i;
float datoleido;
char nombre[100];

i=0;

printf("Dame el nombre del archivo del que quieres que haga el histograma\n");
scanf("%s",nombre);

file=fopen(nombre,"r");
if(file==NULL)
{
    printf("El archivo no existe\n");
}

else
    {   fscanf(file,"%E",&datoleido);
        while(!feof(file))
        {
            vout[i]=datoleido;
            i++;
            fscanf(file,"%E",&datoleido);

        }
    }

return i;
//for(i=0;i<n;i++)  printf("%f\n",vout[i]);


fclose(file);

}

//-------------------------------------------------------------------------------------------------------------

void Histograma (float v[Max],int NumDatos)
{

    FILE *ficherohistograma;
    int i, Indice,l;
    float normalizar;
    float H[5000];
    float maxi,mini,delta;


    maxi=v[0];
    mini=v[0];

    for(i=0; i<NumDatos; i++)
    {
        if(v[i]<(mini))
        {
            (mini)=v[i];

        }
        else
        {
           if(v[i]>(maxi))
           {
               maxi=v[i];
           }

        }
    }

printf("---------------------------\n");
printf("El valor minimo es: %E\n",mini);
printf("El valor maximo es: %E\n",maxi);
printf("---------------------------\n");

printf("Introduce el numero de iteraciones (intervalos)\n");
scanf("%d",&nIteraciones);

for(l=0;l<nIteraciones;l++) H[i]==0;

delta=(maxi-mini)/nIteraciones;
printf("El valor de delta es: %E\n",delta);

for(i=0; i<NumDatos;i++)
    {
        Indice=(v[i]-(mini))/(delta);
        H[Indice]++;
    }

//Normalizo
//for(i=0;i<nIteraciones;i++) H[i]=H[i]/NumDatos;
ficherohistograma=fopen("Histograma","w");
fprintf(ficherohistograma,"#Intervalo\tFrecuencia\n");

for(i=0; i<nIteraciones;i++)
 {
    fprintf(ficherohistograma,"%E\t%f\n",i*delta+(mini),H[i]);
 }


fclose (ficherohistograma);

}
