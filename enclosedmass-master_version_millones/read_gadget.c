#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAXLEN 500

#include "allvars.h"
#include "proto.h"

void read_gadget(particle *part, char *fname)
{
FILE *file1;
int i,j;
float mass,posicionX,posicionY,posicionZ;



file1=fopen(fname,"r");


if(file1==NULL)
    printf("El fichero no existe\n");

else
   {    i=0;

        while(!feof(file1))
            {
                fscanf(file1, "%E",&mass);
                fscanf(file1, "%E",&posicionX);
                fscanf(file1, "%E",&posicionY);
                fscanf(file1, "%E",&posicionZ);
                part[i].masa= mass;
                part[i].x = posicionX;
                part[i].y = posicionY;
                part[i].z = posicionZ;

                i++;

            }
    }

fclose(file1);

}
