#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//AUXILIARES---------------------------------------------------
int NumeroGalaxias ();
void generaFicheroMasasHistogramaMuestra(char nombre[50]);
void sacaMasaHalo();
//-------------------------------------------------------------
//PASO 2
void EscribeGalaxias();//Escribe en un fichero solo las gaalxias que le indiques dentro del programa.

//PASO 3
void MuestraControl();//El programa supone que ya tenemos el fichero generado con todas las galaxias centrales
                     //sin emision de radio. --> Por tanto hay que correr el porgrama GalaxiasCentralesSinRadio()
                     //para generar el fichero.

void DistribucionTotalSiguiendoUnaDada();

void CorteEnMasaHalo();


int main()
{
char FicheroGalaxiasRadio[50]="Galaxias_Centrales_without_Lrg";
int n;
//generaFicheroMasasHistogramaMuestra(FicheroGalaxiasRadio);
//n=NumeroGalaxias();
//printf("El valor de numero de galaxias es: %d\n",n);
//GalaxiasCentralesSinRadio();
//EscribeGalaxias();
MuestraControl();
//DistribucionTotalSiguiendoUnaDada();
//CorteEnMasaHalo();
//sacaMasaHalo();


}

//------------------------------------------------------------------------------------------------------
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
printf("El numero de galaxias es: %d\n",j);
return j;
}
//---------------------------------------------------------------------------------------------------------

void generaFicheroMasasHistogramaMuestra(char nombre[50])
{
FILE *file1;
FILE *fileout;
char caracter;
float datoleido;
int i,j;
i=j=0;

file1=fopen(nombre,"r");
fileout=fopen("Masa_Halo_Distribucion_Estrellas_Histograma","w");

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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            if(i==2) fprintf(fileout,"%E\n",datoleido);
                        }

                }


         }

   }

fclose(file1);
fclose(fileout);
}

//---------------------------------------------------------------------------------------------------------
void EscribeGalaxias()
{
FILE *file1;
FILE *file2;
char caracter;
char nombreFichero[200];
float datoLeido,Lrg,vauxiliar[44];
int icentral,i,contador,NumeroGalaxiasExtraer,numeroGalaxiasMuestraAreproducir;

contador=0;

//--------------------Este dato harbrá que cambiarlo dependiendo lo que queramos---------------
numeroGalaxiasMuestraAreproducir=415;
NumeroGalaxiasExtraer=numeroGalaxiasMuestraAreproducir*10000;
//---------------------------------------------------------------------------------------------


printf("Fichero del que quieres que saque las %d galaxias para realizar la muestra de control:\n",NumeroGalaxiasExtraer);
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
file2=fopen("GalaxiasSinRadioHistograma","w");

if(file1==NULL) printf("El fichero 1 no existe\n");
else if(file2==NULL) printf("El fichero 2 no existe\n");

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

                        }

                    if(contador<NumeroGalaxiasExtraer)

                       {

                        for(i=0;i<43;i++)
                            {
                                if(i==0) fprintf(file2," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                                // después leerlo.
                                else fprintf(file2,"%E\t",vauxiliar[i]);

                            }
                              fprintf(file2,"\n");//Salto de linea.

                         contador++;
                        }
                }
            }

        }
printf("El numero de galaxias que se han extraido es: %d",contador);
fclose(file1);
fclose(file2);
}

//-----------------------------------------------------------------------------------------------------------

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
float datoleido,Lrg,vauxiliar[50],contador[100],delta;
int i,j,k,numeroIntervalos;
float Intervalos[100],maximo,minimo;
float frecuencia[100],correccionFrecuencia,aux;
int NDatosTotal;
//veces=0;
i=0;
NDatosTotal=0;
correccionFrecuencia=1;

//Inicializo las variables que quiero:---------------------------------------------------------
printf("Comenzamos leyendo los datos de intervalos y frecuencias de \nla muestra a reproducir\n");
printf("\nNombre fichero con el que se ha dibujado el histograma con intervalos y \nfrecuencias de la muestra a reproducir:\n");
scanf("%s",nombre);

file2=fopen(nombre,"r");
if(file2==NULL) printf("El fichero para hacer el histograma no existe\n");
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
        fscanf(file2, "%E",&datoleido);
    while(!feof(file2))
      {

          Intervalos[i]=datoleido;
        //printf("1-El dato leido es: %f\n",datoleido);
        fscanf(file2, "%E",&datoleido);
          frecuencia[i]=datoleido*correccionFrecuencia;
        fscanf(file2, "%E",&datoleido);
          i++;
        //printf("2-El dato leido es: %f\n",datoleido);
      }

 }

delta=Intervalos[1]-Intervalos[0];
numeroIntervalos=i;
for(i=0;i<numeroIntervalos;i++) printf("El valor %d de los intervalos es: %E con frecuencia %f\n",i,Intervalos[i],frecuencia[i]);

for(i=0;i<numeroIntervalos;i++) contador[i]=0;
fclose(file2);
//----------------------------------------------------------------------------------------------

printf("\nNombre de fichero de galaxias (sin radio y centrales) para generar la MUESTRA DE CONTROL.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
fileout=fopen("MuestraDeControl","w");

//CABECERA DEL FICHERO DE SALIDA ------------------------------------------
fprintf(fileout,"# MUESTRA CONTROL\n");
fprintf(fileout,"#       redz        Lqso      mhhalo\t");
fprintf(fileout,"x           y           z          vx          vy          vz   L_Lyalpha\t");
fprintf(fileout,"C_Lyalpha_ext    mstardot mstardot_bst       mcold   mcold_bst\t");
fprintf(fileout,"zcold   zcold_bst       rdisk      rbulge       rcomb\t");
fprintf(fileout,"vhhalo L_disk_Lyalpha L_bulge_Lyalpha       vdisk      vbulge      tburst\t");
fprintf(fileout,"tsf_bst   C_Lyalpha        tacc         Lrg    L_Halpha L_Halpha_ext\t");
fprintf(fileout,"magUAr  magUAr_ext       mhalo        ivol          jm  is_central\t");
fprintf(fileout,"ident  ident_next ident_final  mstars_tot mstars_bulge\n#\n");
//-------------------------------------------------------------------------

if(file1==NULL)
    printf("El fichero que vamos a sacar los datos de la muestra de control no existe\n");

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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            vauxiliar[i]=datoleido;
                        }
                        //printf("He entrado %d veces\n",veces);
                        //veces++;
//AHORA HAY QUE ESCOGER LOS DATOS:------------------------------------------------------------------------------------------
                    for(j=0;j<numeroIntervalos;j++)
                        {
                            minimo=Intervalos[j];
                            maximo=Intervalos[j]+(delta);
//printf("El valor de auxiliar[2] es: %E\n",vauxiliar[2]);
                            if(vauxiliar[2]<maximo && vauxiliar[2]>=minimo && contador[j]<frecuencia[j])
                                 {
                                    for(i=0;i<43;i++)
                                        {
                                            if(i==0) fprintf(fileout," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                            // después leerlo.
                                            else fprintf(fileout,"%E\t",vauxiliar[i]);
                                        }
                                    contador[j]=contador[j]+1;
                                    fprintf(fileout,"\n");
                                 }


                            else {k++;}

                        }


//--------------------------------------------------------------------------------------------------------------------------
                }

         }

fileout2=fopen("H_MuestraDeControl","w");
fprintf(fileout2,"#Intervalo\t Frecuencia\n");
for(i=0;i<numeroIntervalos;i++) NDatosTotal=NDatosTotal+contador[i];
//for(i=0;i<numeroIntervalos;i++) contador[i]=contador[i]/NDatosTotal; //NORMALIZO
for(i=0;i<numeroIntervalos;i++) fprintf(fileout2,"%E\t%f\n",Intervalos[i],contador[i]);
fclose(fileout2);
printf("\n----------------------------------------------------------------------------------------\n");
aux=correccionFrecuencia*415.0;
printf("El numero total de galaxias es de: %d y el teorico deberia ser: %f\n",NDatosTotal,aux);
printf("--------------------------------------------------------------------------------------------\n");
   }
printf("El valor del contador es:\n");
for(i=0;i<numeroIntervalos;i++) printf("%d\t%f\n",i,contador[i]);

printf("El valor de la frecuencia es:\n");
for(i=0;i<numeroIntervalos;i++) printf("%d\t%f\n",i,frecuencia[i]);

//Genero fichero solo con las masas-----------------------------
/*char name[50]="MuestraDeControl";
generaFicheroMasasHistogramaMuestra(name);*/

fclose(file1);
fclose(fileout);
}
//---------------------------------------------------------------------------------------------------------

void DistribucionTotalSiguiendoUnaDada()
{
FILE *file1;
FILE *file2;
FILE *fileout;
FILE *fileout2;
char caracter;
char nombreFichero[100],nombre[50];
float datoleido,vauxiliar[43],contador[25],delta;
int i,j,k,numeroIntervalos;
float Intervalos[25],maximo,minimo;
float frecuencia[25],correccionFrecuencia,aux;
int NDatosTotal;
//veces=0;
correccionFrecuencia=10;
i=0;
NDatosTotal=0;

//Inicializo las variables que quiero:---------------------------------------------------------
printf("Comenzamos leyendo los datos de intervalos y frecuencias de \nla muestra a reproducir:\n");
printf("\nNombre fichero con el que se ha dibujado el histograma con intervalos a reproducir:\n");
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
        //printf("1-El dato leido es: %f\n",datoleido);
        fscanf(file2, "%E",&datoleido);
          frecuencia[i]=datoleido*correccionFrecuencia;
          i++;
        //printf("2-El dato leido es: %f\n",datoleido);
      }

 }

delta=Intervalos[1]-Intervalos[0];
numeroIntervalos=i-1;
for(i=0;i<numeroIntervalos;i++) printf("El valor %d de los intervalos es: %E con frecuencia %f\n",i,Intervalos[i],frecuencia[i]);

for(i=0;i<numeroIntervalos;i++) contador[i]=0;
fclose(file2);
//----------------------------------------------------------------------------------------------

printf("\nNombre de fichero de galaxias sin radio y centrales para generar la MUESTRA DE CONTROL.\n");
scanf("%s",nombreFichero);

file1=fopen(nombreFichero,"r");
fileout=fopen("DistribucionTotal_2","w");

//CABECERA DEL FICHERO DE SALIDA ------------------------------------------
fprintf(fileout,"# MUESTRA CONTROL\n");
fprintf(fileout,"#       redz        Lqso      mhhalo\t");
fprintf(fileout,"x           y           z          vx          vy          vz   L_Lyalpha\t");
fprintf(fileout,"C_Lyalpha_ext    mstardot mstardot_bst       mcold   mcold_bst\t");
fprintf(fileout,"zcold   zcold_bst       rdisk      rbulge       rcomb\t");
fprintf(fileout,"vhhalo L_disk_Lyalpha L_bulge_Lyalpha       vdisk      vbulge      tburst\t");
fprintf(fileout,"tsf_bst   C_Lyalpha        tacc         Lrg    L_Halpha L_Halpha_ext\t");
fprintf(fileout,"magUAr  magUAr_ext       mhalo        ivol          jm  is_central\t");
fprintf(fileout,"ident  ident_next ident_final  mstars_tot mstars_bulge\n#\n");
//-------------------------------------------------------------------------

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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            vauxiliar[i]=datoleido;
                        }
                        //printf("He entrado %d veces\n",veces);
                        //veces++;
//AHORA HAY QUE ESCOGER LOS DATOS:------------------------------------------------------------------------------------------
                    for(j=0;j<numeroIntervalos;j++)
                        {
                            minimo=Intervalos[j];
                            maximo=Intervalos[j]+(delta);
//printf("El valor de auxiliar[2] es: %E\n",vauxiliar[2]);
                            if(vauxiliar[2]<maximo && vauxiliar[2]>minimo && contador[j]<frecuencia[j] && frecuencia[j]!=0 )
                                 {
                                    for(i=0;i<43;i++)
                                        {
                                            if(i==0) fprintf(fileout," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                            // después leerlo.
                                            else fprintf(fileout,"%E\t",vauxiliar[i]);
                                        }
                                    contador[j]=contador[j]+1;
                                    fprintf(fileout,"\n");
                                 }
                            else if (vauxiliar[2]==minimo && contador[j]<frecuencia[j] && frecuencia[j]!=0)
                                  {
                                    for(i=0;i<43;i++)
                                        {
                                            if(i==0) fprintf(fileout," %E\t",vauxiliar[0]);//Le doy el formato que quiero para
                                                                            // después leerlo.
                                            else fprintf(fileout,"%E\t",vauxiliar[i]);
                                        }
                                    contador[j-1]=contador[j-1]+1;
                                    fprintf(fileout,"\n");
                                 }


                            else {k++;}

                        }
//--------------------------------------------------------------------------------------------------------------------------

                }

         }
fclose(fileout);
fclose(file1);

fileout2=fopen("H_Total_2","w");
fprintf(fileout2,"#Intervalo\t Frecuencia\n");
for(i=0;i<numeroIntervalos;i++) NDatosTotal=NDatosTotal+contador[i];
for(i=0;i<numeroIntervalos;i++) contador[i]=contador[i]/NDatosTotal; //NORMALIZO
for(i=0;i<numeroIntervalos;i++) fprintf(fileout2,"%E\t%f\n",Intervalos[i],contador[i]);
fclose(fileout2);
printf("\n----------------------------------------------------------------------------------------\n");
printf("El numero total de galaxias es: %d\n",NDatosTotal);
printf("--------------------------------------------------------------------------------------------\n");
   }
printf("El valor del contador es:\n");
for(i=0;i<numeroIntervalos;i++) printf("%d\t%f\n",i,contador[i]);
//Genero fichero solo con las masas-----------------------------
char name[50]="DistribucionTotal";
generaFicheroMasasHistogramaMuestra(name);
}
//---------------------------------------------------------------------------------------------------------


void CorteEnMasaHalo()
{
FILE *file1;
FILE *fileout;
char caracter;
char nombreFichero[100];
float datoleido;
float v[50];
float minimo;
int contador,i;
contador=0;
minimo=1.740000E+12;

printf("Dame el nombre del fichero del que quieres hacer un corte en masa halo\n");
scanf("%s",nombreFichero);
file1=fopen(nombreFichero,"r");
printf("Se hará un corte en masa del halo para valores mayores que %E\n",minimo);

fileout=fopen("out","w");
//CABECERA DEL FICHERO DE SALIDA ------------------------------------------
fprintf(fileout,"# MUESTRA CONTROL\n");
fprintf(fileout,"#       redz        Lqso      mhhalo\t");
fprintf(fileout,"x           y           z          vx          vy          vz   L_Lyalpha\t");
fprintf(fileout,"C_Lyalpha_ext    mstardot mstardot_bst       mcold   mcold_bst\t");
fprintf(fileout,"zcold   zcold_bst       rdisk      rbulge       rcomb\t");
fprintf(fileout,"vhhalo L_disk_Lyalpha L_bulge_Lyalpha       vdisk      vbulge      tburst\t");
fprintf(fileout,"tsf_bst   C_Lyalpha        tacc         Lrg    L_Halpha L_Halpha_ext\t");
fprintf(fileout,"magUAr  magUAr_ext       mhalo        ivol          jm  is_central\t");
fprintf(fileout,"ident  ident_next ident_final  mstars_tot mstars_bulge\n#\n");
//-------------------------------------------------------------------------

if(file1==NULL) printf("Error en la apertura del fichero %s\n",nombreFichero);
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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            v[i]=datoleido;
                        }

                    if(v[2]>=minimo)
                    {
                        contador++;

                        for(i=0;i<43;i++)
                            {
                                if(i==0) fprintf(fileout," %E\t",v[0]);//Le doy el formato que quiero para
                                                                                // después leerlo.
                                else fprintf(fileout,"%E\t",v[i]);

                            }
                              fprintf(fileout,"\n");//Salto de linea.

                    }
                }
         }

}

printf("El numero total de galaxias que han pasado el cortes es: %d\n",contador);
fclose(file1);
fclose(fileout);

}

//------------------------------------------------------------------------------------------------------------
void sacaMasaHalo()
{
FILE *file1;
FILE *fileout;
char caracter;
char nombreFichero[100];
float datoleido;
float v[50];
float minimo;
int contador,i;
contador=0;

printf("Dame el nombre del fichero del que quieres hacer un corte en masa halo\n");
scanf("%s",nombreFichero);
file1=fopen(nombreFichero,"r");


fileout=fopen("MasaHalo","w");

if(file1==NULL) printf("Error en la apertura del fichero %s\n",nombreFichero);
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

                    for(i=0;i<43;i++)
                        {
                            fscanf(file1, "%E",&datoleido);
                            v[i]=datoleido;
                        }

                    fprintf(fileout,"%E\n",v[2]);

                }
         }

}

fclose(file1);
fclose(fileout);
}

