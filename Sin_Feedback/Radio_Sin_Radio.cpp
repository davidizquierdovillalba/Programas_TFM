#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;
char nombreFichero[20];//<-----VARIABLE GLOBAL

typedef struct {
float central;
float masaHalo;
float masaEstelar;
float x;
float y;
float z;
} particle;

particle GalaxiasSinRadio[5000000];
particle GalaxiasSinRadioAuxiliar[5000000];
//-------------------------------------FUNCIONES ---------------------------------------------------

void extraeGalaxiasCentralesRadio();
void extraeGalaxiasCentralesSinRadio();
void FicheroMasaPosiciones();
void FicheroMasaPosicionesCentralesFicheroFeedback();
void FicheroMasaPosicionesCentralesFicheroSinFeedback();


//-----------------------------------------------------------------------------------------------------

int main()
{
//extraeGalaxiasCentralesRadio();
//extraeGalaxiasCentralesSinRadio();
//FicheroMasaPosicionesCentralesFicheroFeedback();
//FicheroMasaPosicionesCentralesFicheroSinFeedback();
FicheroMasaPosiciones();
}

//FUNCIONES--------------------------------------------------------------------------------------------------------
void extraeGalaxiasCentralesRadio()
{
FILE *file1;
FILE *file2;
FILE *file3;
particle GalaxiasRadio[1000];
char caracter;
char nombreFichero[200],nombreFicheroSinFeedback[500];
float datoLeido,vauxiliar[50];
int i,j,galaxiaRadio,galaxiasRadioSinFeedback;
i=j=0;
galaxiaRadio=0;
galaxiasRadioSinFeedback=0;


printf("Dime el nombre del fichero CON feedback de AGN del que saque las galaxias radio\n");
scanf("%s",nombreFichero);

printf("Dime el nombre del fichero SIN feedback de AGN de donde he de buscar las mismas galaxias radio\n");
scanf("%s",nombreFicheroSinFeedback);

file1=fopen(nombreFichero,"r");
file3=fopen(nombreFicheroSinFeedback,"r");
file2=fopen("Galaxias_Centrales_Lrg","w");

if(file1==NULL) printf("El fichero con Feedback no existe\n");
else if(file3==NULL) printf("El fichero sin Feedback no existe\n");
else if(file2==NULL) printf("El fichero de salida no se puede genrar\n");

else
   {
//Cabecera del fichero de salida.

        fprintf(file2,"#       redz      weight        Lqso      mhhalo\t");
        fprintf(file2,"x           y           z          vx          vy          vz   L_Lyalpha\t");
        fprintf(file2,"C_Lyalpha_ext    mstardot mstardot_bst       mcold   mcold_bst\t");
        fprintf(file2,"zcold   zcold_bst       rdisk      rbulge       rcomb\t");
        fprintf(file2,"vhhalo L_disk_Lyalpha L_bulge_Lyalpha       vdisk      vbulge      tburst\t");
        fprintf(file2,"tsf_bst mstardot_ave   C_Lyalpha       t_uni        tacc         Lrg    L_Halpha L_Halpha_ext\t");
        fprintf(file2,"magUAr  magUAr_ext       mhalo          jm       jtree  is_central\t");
        fprintf(file2,"mstars      mbulge      mbulge\n#\n");


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

                    for(i=0;i<45;i++)
                        {
                            fscanf(file1, "%E",&datoLeido);
                            vauxiliar[i]=datoLeido;

                         }

                    if(vauxiliar[40]==1 && vauxiliar[32]>=22.5)
                        {
                            GalaxiasRadio[galaxiaRadio].central=vauxiliar[40];
                            GalaxiasRadio[galaxiaRadio].masaHalo=vauxiliar[3];// Masa estelar
                            GalaxiasRadio[galaxiaRadio].x=vauxiliar[4];// Posicion x
                            GalaxiasRadio[galaxiaRadio].y=vauxiliar[5];// Posicion y
                            GalaxiasRadio[galaxiaRadio].z=vauxiliar[6];// Posicion z
                            galaxiaRadio++;
                        }
                }

            }

for(j=0;j<galaxiaRadio;j++) printf("Galaxia %d central %f masa halo: %E posicionX: %f posicionY: %f posicionZ: %f\n",j,GalaxiasRadio[j].central,GalaxiasRadio[j].masaHalo,GalaxiasRadio[j].x,GalaxiasRadio[j].y,GalaxiasRadio[j].z);
//Ahora comparo con el otro catálogo (SIN FEEDBACK)

while(!feof(file3))
         {
            fscanf(file3, "%c",&caracter);


            if(caracter=='#')
                {
                    while(caracter!='\n')
                        {
                            fscanf(file3, "%c",&caracter);


                        }
                }

            if(caracter==' ')
                {

                    for(i=0;i<44;i++)
                        {
                            fscanf(file3, "%E",&datoLeido);
                            vauxiliar[i]=datoLeido;
                            //printf("El valor de vauxiliar[40]=%f\n",vauxiliar[40]);
                        }

                    for(j=0;j<galaxiaRadio;j++)
                    {
                            if(GalaxiasRadio[j].central==vauxiliar[40] && GalaxiasRadio[j].masaHalo==vauxiliar[3] && GalaxiasRadio[j].x==vauxiliar[4] && GalaxiasRadio[j].y==vauxiliar[5] && GalaxiasRadio[j].z==vauxiliar[6])
                            {
                                galaxiasRadioSinFeedback++;

                                for(i=0;i<44;i++)
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



    }
printf("El valor de galaxias Radio en catalogo Feedback es: %d\n",galaxiaRadio);
printf("El valor de galaxias Radio en catalogo sin Feedback es: %d\n",galaxiasRadioSinFeedback);
fclose(file1);
fclose(file2);
fclose(file3);
}


//--------------------------------------------------------------------------------------------------------------
void extraeGalaxiasCentralesSinRadio()
{
FILE *file1;
FILE *file2;
FILE *file3;

char caracter;
char nombreFichero[200],nombreFicheroSinFeedback[500];
float datoLeido,vauxiliar[50];
int i,j,k,galaxiaSinRadio,galaxiasSinRadioSinFeedback;
i=j=k=0;
galaxiaSinRadio=0;
galaxiasSinRadioSinFeedback=0;


printf("Dime el nombre del fichero CON feedback de AGN del que saque las NO galaxias radio\n");
scanf("%s",nombreFichero);

printf("Dime el nombre del fichero SIN feedback de AGN de donde he de buscar las mismas NO galaxias radio\n");
scanf("%s",nombreFicheroSinFeedback);

file1=fopen(nombreFichero,"r");
file3=fopen(nombreFicheroSinFeedback,"r");
file2=fopen("Galaxias_Centrales_Without_Lrg","w");

if(file1==NULL) printf("El fichero con Feedback no existe\n");
else if(file3==NULL) printf("El fichero sin Feedback no existe\n");
else if(file2==NULL) printf("El fichero de salida no se puede genrar\n");

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

                    for(i=0;i<45;i++)
                        {
                            fscanf(file1, "%E",&datoLeido);
                            vauxiliar[i]=datoLeido;

                         }

                    if(vauxiliar[40]==1 && vauxiliar[32]<22.5 && vauxiliar[41]>5e9)
                        {
                            GalaxiasSinRadio[galaxiaSinRadio].central=vauxiliar[40];
                            GalaxiasSinRadio[galaxiaSinRadio].masaHalo=vauxiliar[3];// Masa estelar
                            GalaxiasSinRadio[galaxiaSinRadio].masaEstelar=vauxiliar[41];
                            GalaxiasSinRadio[galaxiaSinRadio].x=vauxiliar[4];// Posicion x
                            GalaxiasSinRadio[galaxiaSinRadio].y=vauxiliar[5];// Posicion y
                            GalaxiasSinRadio[galaxiaSinRadio].z=vauxiliar[6];// Posicion z
                            galaxiaSinRadio++;
                        }
                }

            }
printf("el numero de galaxias sin radio encontradas en el catlogo con feedback es: %d\n",galaxiaSinRadio);
printf("Galaxia %d central %f masa halo: %E masa estelar: %E posicionX: %f posicionY: %f posicionZ: %f\n",2,GalaxiasSinRadio[2].central,GalaxiasSinRadio[2].masaHalo,GalaxiasSinRadio[2].masaEstelar,GalaxiasSinRadio[2].x,GalaxiasSinRadio[2].y,GalaxiasSinRadio[2].z);
//Ahora comparo con el otro catálogo (SIN FEEDBACK)

while(!feof(file3))
         {
            fscanf(file3, "%c",&caracter);


            if(caracter=='#')
                {
                    while(caracter!='\n')
                        {
                            fscanf(file3, "%c",&caracter);


                        }
                }

            if(caracter==' ')
                {

                    for(i=0;i<44;i++)
                        {
                            fscanf(file3, "%E",&datoLeido);
                            vauxiliar[i]=datoLeido;


                        }
                if(vauxiliar[40]==1 && vauxiliar[41]>5e9)
                {
                    GalaxiasSinRadioAuxiliar[galaxiasSinRadioSinFeedback].central=vauxiliar[40];
                    GalaxiasSinRadioAuxiliar[galaxiasSinRadioSinFeedback].masaHalo=vauxiliar[3];
                    GalaxiasSinRadioAuxiliar[galaxiasSinRadioSinFeedback].masaEstelar=vauxiliar[41];
                    GalaxiasSinRadioAuxiliar[galaxiasSinRadioSinFeedback].x=vauxiliar[4];
                    GalaxiasSinRadioAuxiliar[galaxiasSinRadioSinFeedback].y=vauxiliar[5];
                    GalaxiasSinRadioAuxiliar[galaxiasSinRadioSinFeedback].z=vauxiliar[6];
                    galaxiasSinRadioSinFeedback++;

                }

                }


           }
printf("el numero de galaxias sin radio encontradas en el catlogo SIN feedback es: %d\n",galaxiasSinRadioSinFeedback);
printf("Galaxia %d central %f masa halo: %E masa estelar: %E posicionX: %f posicionY: %f posicionZ: %f\n",2,GalaxiasSinRadioAuxiliar[2].central,GalaxiasSinRadioAuxiliar[2].masaHalo,GalaxiasSinRadioAuxiliar[2].masaEstelar,GalaxiasSinRadioAuxiliar[2].x,GalaxiasSinRadio[2].y,GalaxiasSinRadioAuxiliar[2].z);

printf("Voy a comenzar a comparar\n");
fprintf(file2,"#Masa_Halo\tMasa_Estelar\tx\ty\tz\n");
k=0;

for(j=0;j<galaxiasSinRadioSinFeedback;j++)
{//printf("----\n");
    for(i=0;i<galaxiaSinRadio;i++)
    {
        if(GalaxiasSinRadioAuxiliar[j].masaHalo==GalaxiasSinRadio[i].masaHalo && GalaxiasSinRadioAuxiliar[j].masaEstelar==GalaxiasSinRadio[i].masaEstelar && GalaxiasSinRadioAuxiliar[j].x==GalaxiasSinRadio[i].x && GalaxiasSinRadioAuxiliar[j].y==GalaxiasSinRadio[i].y && GalaxiasSinRadioAuxiliar[j].z==GalaxiasSinRadio[i].z)
        {
            k++;
            printf("El valor de k es: %d\n",k);
            fprintf(file2,"%E\t%E\t%E\t%E\t%E\n",GalaxiasSinRadioAuxiliar[i].masaHalo,GalaxiasSinRadioAuxiliar[i].masaEstelar,GalaxiasSinRadioAuxiliar[i].x,GalaxiasSinRadioAuxiliar[i].y,GalaxiasSinRadioAuxiliar[i].z);

        }


        if(k==100000)
        {
        j=galaxiasSinRadioSinFeedback;
        i=galaxiaSinRadio;
        }

    }


}



    }
printf("El valor de NO galaxias Radio en catalogo Feedback es: %d\n",galaxiaSinRadio);
printf("El valor de NO galaxias Radio en catalogo sin Feedback es: %d\n",k);
fclose(file1);
fclose(file2);
fclose(file3);
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
                        vaux[i]=datoleido;
                        fscanf(file1, "%E",&datoleido);
                   }

                fprintf(file2,"%E\t%E\t%E\t%E\n",vaux[1],vaux[2],vaux[3],vaux[4]);
        }

   }

fclose(file1);
fclose(file2);
}

//--------------------------------------------------------------------------------------------------------------
void FicheroMasaPosicionesCentralesFicheroFeedback()
{

FILE *file1;
FILE *file2;
char caracter,nombre1[50],nombre2[50];
float datoleido,vaux[50];
int i,j;
i=j=0;

printf("FORMATO CON FEEDBACK\n");
printf("Centrales: Dame el nombre del fichero del que quieres que genere el formato Masa   Poscion X   Posicion Y   Posicion Z\n");
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

                    for(i=0;i<45;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            vaux[i]=datoleido;
                        }

                        if(vaux[41]>=1e9)
                            {
                                fprintf(file2,"%E\t",vaux[41]);//Masa Estrellas
                                fprintf(file2,"%E\t",vaux[4]);//Posicion X
                                fprintf(file2,"%E\t",vaux[5]);//Posicion Y
                                fprintf(file2,"%E\n",vaux[6]);//Posicion Z
                            }


                }


         }

   }

fclose(file1);
fclose(file2);
}

//--------------------------------------------------------------------------------------------------------------
void FicheroMasaPosicionesCentralesFicheroSinFeedback()
{

FILE *file1;
FILE *file2;
char caracter,nombre1[50],nombre2[50];
float datoleido,vaux[50];
int i,j;
i=j=0;

printf("FORMATO SIN FEEDBACK\n");
printf("Centrales: Dame el nombre del fichero del que quieres que genere el formato Masa   Poscion X   Posicion Y   Posicion Z\n");
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

                    for(i=0;i<44;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            vaux[i]=datoleido;
                        }

                        if(vaux[41]>=1e9)
                            {
                                fprintf(file2,"%E\t",vaux[41]);//Masa Estrellas
                                fprintf(file2,"%E\t",vaux[4]);//Posicion X
                                fprintf(file2,"%E\t",vaux[5]);//Posicion Y
                                fprintf(file2,"%E\n",vaux[6]);//Posicion Z
                            }


                }


         }

   }

fclose(file1);
fclose(file2);
}

