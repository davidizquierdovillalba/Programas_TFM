#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
char nombreFichero[20];//<-----VARIABLE GLOBAL

//-------------------------------------FUNCIONES ---------------------------------------------------
int NumeroGalaxias ();
void extraeGalaxiasCentralesRadio();
void extraeGalaxiasCentralesSinRadio();
void calculaMediaMasa ();
void FicheroMasaPosiciones();
void FicheroMasaPosicionesCentrales();//Se hace lo mismo que FicheroMasaPosiciones pero poniendo condiciones a las gal centrales
void calculaMaximo();
void muestraVector(float v[900000], int dimV);

//-----------------------------------------------------------------------------------------------------

int main()
{
int numeroG;


//extraeGalaxiasCentralesRadio();
//extraeGalaxiasCentralesSinRadio();
//numeroG=NumeroGalaxias();
//printf("El numero de galaxias es: %d\n",numeroG);
FicheroMasaPosiciones();
//FicheroMasaPosicionesCentrales();
//calculaMaximo();
}

//FUNCIONES--------------------------------------------------------------------------------------------------------

int NumeroGalaxias ()
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

            fscanf(file1, "%c",&caracter);

            if(caracter=='#')
                {   //printf("He leido uno\n");
                    while(caracter!='\n')
                        {
                            fscanf(file1, "%c",&caracter);

                        }
                }

            if(caracter==' ')
                {

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            //if(i==29) printf("El valor de is_central es: %f\n",datoleido);
                        }
                        j++;

                }


         }

   }

fclose(file1);
return j;
}
//--------------------------------------------------------------------------------------------------------------
void extraeGalaxiasCentralesRadio()
{
FILE *file1;
FILE *file2;
char caracter;
char nombreFichero[20];
float datoLeido,Lrg,vauxiliar[44],mediaMasaEstrellas;
int icentral,i,j,k,l;
i=j=k=l=0;
mediaMasaEstrellas=0;

printf("Dime el nombre del fichero del que quieres que saque los objetos centrales con Lrg>22.5 (CON EMISION EN RADIO).\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
file2=fopen("Galaxias_Centrales_Lrg","w");

if(file1==NULL)
    printf("El fichero 1 no existe\n");
else if(file2==NULL)
    printf("El fichero 2 no existe\n");

else
   {
//Cabecera del fichero de salida.

        fprintf(file2,"#       redz        Lqso      mhhalo\t");
        fprintf(file2,"x           y           z          vx          vy          vz   L_Lyalpha\t");
        fprintf(file2,"C_Lyalpha_ext    mstardot mstardot_bst       mcold   mcold_bst\t");
        fprintf(file2,"zcold   zcold_bst       rdisk      rbulge       rcomb\t");
        fprintf(file2,"vhhalo L_disk_Lyalpha L_bulge_Lyalpha       vdisk      vbulge      tburst\t");
        fprintf(file2,"tsf_bst   C_Lyalpha        tacc         Lrg    L_Halpha L_Halpha_ext\t");
        fprintf(file2,"magUAr  magUAr_ext       mhalo        ivol          jm  is_central\t");
        fprintf(file2,"ident  ident_next ident_final  mstars_tot mstars_bulge\n#\n");
j=0;

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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoLeido);

                            vauxiliar[i]=datoLeido;

                            if(i==29) Lrg=datoLeido;
                            else if (i==37) icentral=datoLeido;

                        }

                    if(Lrg>=22.5 && icentral==1)
                        {
                            k++;

                            mediaMasaEstrellas=vauxiliar[41]+mediaMasaEstrellas;

                            for(i=0;i<43;i++)
                                {
                                    if(i==0) fprintf(file2," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                                    // después leerlo.
                                    else fprintf(file2,"%E\t",vauxiliar[i]);
                                }
                            fprintf(file2,"\n");//Salto de linea.

                        }
                }

            }


         }
mediaMasaEstrellas=mediaMasaEstrellas/k;
printf("El valor de Masa estella Media es: %E\n",mediaMasaEstrellas);
printf("El numero de galaxias radio total es: %d\n",k);
fclose(file1);
fclose(file2);
}


//--------------------------------------------------------------------------------------------------------------
void extraeGalaxiasCentralesSinRadio()
{
FILE *file1;
FILE *file2;
char caracter;
char nombreFichero[200];
float datoLeido,Lrg,vauxiliar[44],Mmean,masaEstrellas,mediaMasaEstrellas;
int icentral,i,j,k;
i=j=k=0;

mediaMasaEstrellas=0;

printf("El valor de Mmean es: %E\n",Mmean);

printf("Dime el nombre del fichero del que quieres que saque los objetos centrales con Lrg<22.5 (SIN EMISION DE RADIO).\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
file2=fopen("Galaxias_Centrales_without_Sin_Cortes_En_Masa","w");

if(file1==NULL)
    printf("El fichero 1 no existe\n");
else if(file1==NULL)
    printf("El fichero 2 no existe\n");

else
   {
//Cabecera del fichero de salida.

        fprintf(file2,"#       redz        Lqso      mhhalo\t");
        fprintf(file2,"x           y           z          vx          vy          vz   L_Lyalpha\t");
        fprintf(file2,"C_Lyalpha_ext    mstardot mstardot_bst       mcold   mcold_bst\t");
        fprintf(file2,"zcold   zcold_bst       rdisk      rbulge       rcomb\t");
        fprintf(file2,"vhhalo L_disk_Lyalpha L_bulge_Lyalpha       vdisk      vbulge      tburst\t");
        fprintf(file2,"tsf_bst   C_Lyalpha        tacc         Lrg    L_Halpha L_Halpha_ext\t");
        fprintf(file2,"magUAr  magUAr_ext       mhalo        ivol          jm  is_central\t");
        fprintf(file2,"ident  ident_next ident_final  mstars_tot mstars_bulge\n#\n");


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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoLeido);

                            vauxiliar[i]=datoLeido;

                            if(i==41) masaEstrellas=log10(datoLeido);
                            else if(i==29) Lrg=datoLeido;
                            else if (i==37) icentral=datoLeido;

                        }

                    if(icentral==1 && Lrg<22.5)
                        {
                            k++;
                            mediaMasaEstrellas=vauxiliar[41]+mediaMasaEstrellas;

                         for(i=0;i<43;i++)
                            {
                                if(i==0) fprintf(file2," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                            // después leerlo.
                                else fprintf(file2,"%E\t",vauxiliar[i]);

                            }
                          fprintf(file2,"\n");//Salto de linea.
                        }
                }

            }


         }

mediaMasaEstrellas=mediaMasaEstrellas/k;
printf("El numero de galaxias sin radio que han pasado el corte son: %d\n",k);
printf("El valor de Masa estella Media es: %E\n",mediaMasaEstrellas);
fclose(file1);
fclose(file2);
}


//--------------------------------------------------------------------------------------------------------------

void calculaMediaMasa ()
{

FILE *file1;
FILE *file2;
char caracter,Fichero[50];
float datoleido,masa,media;
int i,j;
j=0;
masa=0;

printf("Dame el nombre del fichero que quieres que haga la media de las masas\n");
scanf("%s",Fichero);

file1=fopen(Fichero,"r");
file2=fopen("Media_Galaxias_Radio","w");

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

            if(caracter==' ')
                {

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            if(i==2)
                                {
                                    //printf("El valor de is_central es: %E\n",datoleido);
                                    masa+=datoleido;
                                }
                        }

                        j++;

                }


         }

   }
//printf("El valor de j es: %d\n",j);
media=masa/j;
//printf("\n----------\nEl valor de la media es: %E\n\n----------\n",media);
fprintf(file2,"#El valor de masa media de las radio galaxias centrales con Lrg>23 es:\n%E",media);
fclose(file1);
fclose(file2);
}

//-----------------------------------------------------------------------------------------------------
void FicheroMasaPosiciones()
{

FILE *file1;
FILE *file2;
char caracter,nombre1[50],nombre2[50];
float datoleido,vaux[50];
int i,j;
i=j=0;


printf("Dame el nombre del fichero del que quieres que genere el formato Masa   Poscion X   Posicion Y   Posicion Z\n");
scanf("%s",nombre1);
printf("y, ¿Como quieres que se llame su fichero de salida?\n");
scanf("%s",nombre2);


file1=fopen(nombre1,"r");
file2=fopen(nombre2,"w");

if(file1==NULL)
    printf("El fichero no existe\n");

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

            if(caracter==' ')
                {

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            vaux[i]=datoleido;

                        }


                        fprintf(file2,"%E\t",vaux[41]);//Masa Estrellas
                        fprintf(file2,"%E\t",vaux[3]);//Posicion X
                        fprintf(file2,"%E\t",vaux[4]);//Posicion Y
                        fprintf(file2,"%E\n",vaux[5]);//Posicion Z

                }


         }

   }

fclose(file1);
fclose(file2);
}

//--------------------------------------------------------------------------------------------------------------
void FicheroMasaPosicionesCentrales()
{

FILE *file1;
FILE *file2;
char caracter,nombre1[50],nombre2[50];
float datoleido,vaux[50];
int i,j,contador;
i=j=0;
contador=0;

printf("Dame el nombre del fichero del que quieres que genere el formato Masa   Poscion X   Posicion Y   Posicion Z\n");
scanf("%s",nombre1);
printf("y, ¿Como quieres que se llame su fichero de salida?\n");
scanf("%s",nombre2);


file1=fopen(nombre1,"r");
file2=fopen(nombre2,"w");

if(file1==NULL)
    printf("El fichero no existe\n");

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

            if(caracter==' ')
                {

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            vaux[i]=datoleido;

                        }

                        if(vaux[41]>=1e9)
                            {contador++;
                                fprintf(file2,"%E\t",vaux[41]);//Masa Estrellas
                                fprintf(file2,"%E\t",vaux[3]);//Posicion X
                                fprintf(file2,"%E\t",vaux[4]);//Posicion Y
                                fprintf(file2,"%E\n",vaux[5]);//Posicion Z
                            }


                }


         }

   }
printf("El numero de galaxias que he cogido han sido: %d\n",contador);
fclose(file1);
fclose(file2);
}
//--------------------------------------------------------------------------------------------------------------
void calculaMaximo()
{
FILE *file1;
float datoleido,masa,maximoX,maximoY,maximoZ,x,y,z;
char nombre1[50];

printf("Dame el nombre del fichero del que quieres que saque la posicion máxima\n");
scanf("%s",nombre1);

file1=fopen(nombre1,"r");


if(file1==NULL)
    printf("El fichero no existe\n");

else
   {
            fscanf(file1, "%E",&masa);
            fscanf(file1, "%E",&maximoX);
            fscanf(file1, "%E",&maximoY);
            fscanf(file1, "%E",&maximoZ);


         while(!feof(file1))
         {

            fscanf(file1, "%E",&masa);
            fscanf(file1, "%E",&x);
            fscanf(file1, "%E",&y);
            fscanf(file1, "%E",&z);

            if(maximoX<x) maximoX=x;


        }

    }

fclose(file1);

printf("El valor máximo en x es: %f\n",maximoX);

file1=fopen(nombre1,"r");


if(file1==NULL)
    printf("El fichero no existe\n");

else
   {
            fscanf(file1, "%E",&masa);
            fscanf(file1, "%E",&maximoX);
            fscanf(file1, "%E",&maximoY);
            fscanf(file1, "%E",&maximoZ);


         while(!feof(file1))
         {

            fscanf(file1, "%E",&masa);
            fscanf(file1, "%E",&x);
            fscanf(file1, "%E",&y);
            fscanf(file1, "%E",&z);

            if(maximoY<y) maximoY=y;


        }

   }
printf("El valor máximo en y es: %f\n",maximoY);

fclose(file1);



file1=fopen(nombre1,"r");


if(file1==NULL)
    printf("El fichero no existe\n");

else
   {
            fscanf(file1, "%E",&masa);
            fscanf(file1, "%E",&maximoX);
            fscanf(file1, "%E",&maximoY);
            fscanf(file1, "%E",&maximoZ);


         while(!feof(file1))
         {

            fscanf(file1, "%E",&masa);
            fscanf(file1, "%E",&x);
            fscanf(file1, "%E",&y);
            fscanf(file1, "%E",&z);

            if(maximoZ<z) maximoZ=z;


        }

   }

printf("El valor máximo en z es: %f\n",maximoZ);
fclose(file1);
}

//--------------------------------------------------------------------------------------------------------------
void muestraVector(float v[900000], int dimV)
{

int i;

for(i=0;i<dimV;i++)
{
printf("El valor %d del vector es: %E \n",i,v[i]);
}

}

//--------------------------------------------------------------------------------------------------------------

