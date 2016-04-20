#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#define MAXLEN 500

int get_nparticles(char * fname)
{
  
FILE *file1;
float datoleido;
int i;
i=0;

file1=fopen(fname,"r");

if(file1==NULL)
    printf("El fichero no existe\n");

else
   {
         while(!feof(file1))
         {
            fscanf(file1, "%E",&datoleido);
		i++;

         }
	i=i/4;
   }

fclose(file1);
return i;
 
}
