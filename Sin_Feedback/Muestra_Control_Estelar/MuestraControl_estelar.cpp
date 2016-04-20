#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//AUXILIARES---------------------------------------------------
void CambiaFormatoViejoaNuevo();
float NumeroGalaxias (char nombreFichero[100]);
void MuestraControl();//El programa supone que ya tenemos el fichero generado con todas las galaxias centrales
                     //sin emision de radio. --> Por tanto hay que correr el porgrama GalaxiasCentralesSinRadio()
                     //para generar el fichero.

int main()
{
int num;
char nombre[100];
/*printf("Nombre fichero de la muestra a reproducir:\n");
scanf("%s",nombre);
num=NumeroGalaxias(nombre);
printf("El numero de galaxias es: %d\n",num);*/
//CambiaFormatoViejoaNuevo();
MuestraControl();



}

//------------------------------------------------------------------------------------------------------
void CambiaFormatoViejoaNuevo()
{
FILE *file1;
FILE *fileout;
char caracter,nombre[50];
float datoleido,vaux[50];
int i;
printf("Dame el nombre del fichero del que quieres que cambie el formato\n");
scanf("%s",nombre);

file1=fopen(nombre,"r");
fileout=fopen("Nuevo_Formato","w");

if(file1==NULL) printf("El fichero no existe\n");
else if(fileout==NULL) printf("El fichero no se puede generar\n");

else
   {
        fprintf(fileout,"#Masa_halo \t Masa_Estelar \t x \t y \t z\n");

         while(!feof(file1))
         {

            fscanf(file1, "%c",&caracter);

            if(caracter=='#')
                {   //printf("He leido uno\n");
                    while(caracter!='\n')
                        {
                            fscanf(file1, "%c",&caracter);

                        }
                }

            else
                {
                   for(i=0;i<44;i++)
                   {
                      fscanf(file1, "%E",&datoleido);
                      vaux[i]=datoleido;
                   }

                   fprintf(fileout,"%E\t%E\t%E\t%E\t%E\n",vaux[3],vaux[41],vaux[4],vaux[5],vaux[6]);

                }


         }

   }

fclose(file1);
fclose(fileout);

}

//------------------------------------------------------------------------------------------------------

float NumeroGalaxias (char nombreFichero[100])
{
FILE *file1;
char caracter;
float datoleido,galaxias;


file1=fopen(nombreFichero,"r");

if(file1==NULL) printf("El fichero no existe\n");

else
   {

         while(!feof(file1))
         {

            fscanf(file1, "%c",&caracter);

            if(caracter=='#')
                {   //printf("He leido uno\n");
                    while(caracter!='\n')
                        {
                            fscanf(file1, "%c",&caracter);

                        }
                }

            else
                {
                   fscanf(file1, "%E",&datoleido);
                   //printf("datoledido: %f\n",datoleido);
                   fscanf(file1, "%E",&datoleido);
                   //printf("datoledido: %f\n",datoleido);
                   galaxias=galaxias+datoleido;
                   //printf("galaxias: %f\n",galaxias);

                }


         }

   }

fclose(file1);
return galaxias;
}

//----------------------------------------------------------------------------------------------------------------
void MuestraControl() //El programa supone que ya tenemos el fichero generado con todas las galaxias centrales
{                     // sin emision de radio.
printf("\n-----------------------------------------------------------------------------\n");
printf("Recordar que esta funcion void ''MuestraControl()'' ");
printf("necesita datos previos del\nhistograma del que queremos que se parezca:\n");
printf("1)Separacion entre intervalos (delta)\n2)Centro de cada intervalo\n");
/*printf("Habrá que modificar este programa para cada histograma de una muestra ");
printf(" (---> cada vez que tengamos distintos # de intervalos)\n");*/
printf("-----------------------------------------------------------------------------\n");

FILE *file1;
FILE *file2;
FILE *fileout;
FILE *fileout2;
char caracter;
char nombreFichero[100],nombre[50];
float datoleido,Lrg,vauxiliar[50],contador[100],delta,Intervalos[100],maximo,minimo,frecuencia[100],aux;
int i,j,k,numeroIntervalos,NDatosTotal;
i=0;
NDatosTotal=0;

//Inicializo las variables que quiero:---------------------------------------------------------
printf("Comenzamos leyendo los datos de intervalos y frecuencias de \nla muestra a reproducir\n");
printf("\nNombre fichero con el que se ha dibujado el histograma con intervalos y \nfrecuencias de la muestra a reproducir:\n");
scanf("%s",nombre);

file2=fopen(nombre,"r");
if(file2==NULL) printf("El fichero no existe\n");
else
 {

    fscanf(file2, "%c",&caracter);

    if(caracter=='#')
        {
            while(caracter!='\n')
                {
                    fscanf(file2, "%c",&caracter);

                }
        }

    while(!feof(file2))
      {
        fscanf(file2, "%E",&datoleido);
          Intervalos[i]=datoleido;

        fscanf(file2, "%E",&datoleido);
          frecuencia[i]=datoleido;
          i++;
      }

 }

delta=Intervalos[1]-Intervalos[0];
numeroIntervalos=i-1;
for(i=0;i<numeroIntervalos;i++) printf("El valor %d de los intervalos es: %E con frecuencia %f\n",i,Intervalos[i],frecuencia[i]);

for(i=0;i<numeroIntervalos;i++) contador[i]=0;
fclose(file2);
//----------------------------------------------------------------------------------------------

printf("\nNombre de fichero de galaxias (sin radio y centrales) para generar la MUESTRA DE CONTROL.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
fileout=fopen("MuestraDeControl_Estelar","w");

//CABECERA DEL FICHERO DE SALIDA ------------------------------------------
fprintf(fileout,"#Masa_halo \t Masa_Estelar \t x \t y \t z\n");
//-------------------------------------------------------------------------
int aux2=0;
if(file1==NULL) printf("El fichero no existe\n");

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
                        vauxiliar[i]=datoleido;
                        fscanf(file1, "%E",&datoleido);
                   }
        if(aux2==5) for(j=0;j<5;j++) printf("vaux[%d]=%E\n",j,vauxiliar[j]);
        aux2++;
//AHORA HAY QUE ESCOGER LOS DATOS:---------------------
                    for(j=0;j<numeroIntervalos;j++)
                        {
                            minimo=Intervalos[j];
                            maximo=Intervalos[j]+(delta);

                            if(vauxiliar[1]<maximo && vauxiliar[1]>=minimo && contador[j]<frecuencia[j])
                                 {
                                    for(i=0;i<5;i++)
                                        {
                                            if(i==0) fprintf(fileout," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                            // después leerlo.
                                            else fprintf(fileout,"%E\t",vauxiliar[i]);
                                        }
                                    contador[j]=contador[j]+1;
                                    fprintf(fileout,"\n");

                                 }

                        }


//-------------------------------------------------------
                }



fileout2=fopen("H_MuestraDeControl","w");
fprintf(fileout2,"#Intervalo\t Frecuencia\n");
for(i=0;i<numeroIntervalos;i++) NDatosTotal=NDatosTotal+contador[i];
//for(i=0;i<numeroIntervalos;i++) contador[i]=contador[i]/NDatosTotal; //NORMALIZO
for(i=0;i<numeroIntervalos;i++) fprintf(fileout2,"%E\t%f\n",Intervalos[i],contador[i]);
fclose(fileout2);
fclose(file1);
fclose(fileout);
   }

printf("\n----------------------------------------------------------------------------------------\n");
aux=NumeroGalaxias(nombre);
printf("El numero total de galaxias es de: %d y el teorico deberia ser: %f\n",NDatosTotal,aux);
printf("--------------------------------------------------------------------------------------------\n");


for(i=0;i<numeroIntervalos;i++) printf("%d \t Reproducir: %f \t Encontrados: %f\n",i,contador[i],frecuencia[i]);
}
//---------------------------------------------------------------------------------------------------------
