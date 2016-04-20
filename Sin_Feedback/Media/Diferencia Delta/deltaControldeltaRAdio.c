#include <stdio.h>
#include <math.h>
#include <stdlib.h>



void DifereniaDelta();


int main()
{
DifereniaDelta();
}

void DifereniaDelta()
{
FILE *fileRadio;
FILE *fileControl;
FILE *fileout;
char radio[50],control[50],Distancia[50],Densidad[50];
float datoleido,deltaRadio[50],deltaControl[50],diferencia[50],posicion[50];
int i,j,nbines;

nbines=21;

printf("Dame el nombre del archivo de delta de las radio galaxias\n");
scanf("%s",radio);
printf("Dame el nombre del archivo de delta de las galaxias de control\n");
scanf("%s",control);

fileRadio=fopen(radio,"r");
fileControl=fopen(control,"r");
fileout=fopen("DiferenciaRadio_z_3","w");

if(fileRadio==NULL) printf("ERROR al abrir el fichero radio\n");
else if (fileControl==NULL) printf("ERROR al abrir el fichero control\n");
else if (fileout==NULL) printf("ERROR al generar el fichero de salida\n");
else
{
        fscanf(fileRadio, "%s",Distancia);
       fscanf(fileRadio, "%s",Densidad);

        for(j=0;j<nbines;j++)
        {
            fscanf(fileRadio,"%f",&datoleido);
            posicion[j]=datoleido;
            //printf("pocicion: %E\t densidad: %E\n",posicion,densidad);
            fscanf(fileRadio,"%f",&datoleido);
            deltaRadio[j]=datoleido;

        }

fclose(fileRadio);

       fscanf(fileControl, "%s",Distancia);
       fscanf(fileControl, "%s",Densidad);

        for(j=0;j<nbines;j++)
        {
            fscanf(fileControl,"%f",&datoleido);
            fscanf(fileControl,"%f",&datoleido);
            deltaControl[j]=datoleido;
        }

fclose(fileControl);

printf("El valor para las radio galaxias es:\n");

for(i=0;i<nbines;i++) printf("deltaRadio[%d]=%E\n",i,deltaRadio[i]);

printf("El valor para las galaxias de control es:\n");

for(i=0;i<nbines;i++) printf("deltaControl[%d]=%E\n",i,deltaControl[i]);

for(i=0;i<nbines;i++) diferencia[i]=(deltaRadio[i]-deltaControl[i])/deltaControl[i];

fprintf(fileout,"Distancia\tDensidad\n");
for(i=0;i<nbines;i++){fprintf(fileout,"%f\t%f\n",posicion[i],diferencia[i]);}

fclose(fileout);
}

}
