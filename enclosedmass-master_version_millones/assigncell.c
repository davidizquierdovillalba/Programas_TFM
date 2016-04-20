#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>

#include "allvars.h"
#include "proto.h"

int get_nc(int ic, int cc)
{
   int _nc;
	
   if(ic + cc < 0)
      _nc = NCells + cc;
   else if ((ic + cc) >NCells)
	   _nc = cc - NCells;
   else
   _nc = ic + cc;

   return(_nc);
}

int get_off(int ic, int cc)
{
   int off;
   if(ic + cc < 0)
      off = -LBox;
   else if ((ic + cc) >NCells)
	   off = LBox;
   else
   off = 0.0;

   return(off);
}


void assigncell(particle *Data, unsigned long n)
{

	unsigned long i, j;
	unsigned int ix, iy, iz;

//	printf("assign.c\n");
//	dprinti(n);

// We check that there are no coordinates outside the box size. We do a reflexion.
	for(i=0;i<n;i++)
	{
		if(Data[i].z<0) {Data[i].z +=LBox;}
		else if(Data[i].z>LBox) {Data[i].z -=LBox;}
	}
	
	for(i=0;i<n;i++)
	{
		if(Data[i].x<0) {Data[i].x +=LBox;}
		else if(Data[i].x>LBox) {Data[i].x -=LBox;}
	}

	for(i=0;i<n;i++)
	{
		if(Data[i].y<0) {Data[i].y +=LBox;}
		else if(Data[i].y>LBox) {Data[i].y -=LBox;}
	}

	for(i = 0; i < n ; i++)
	{	
	/*	Now I compute the [ix,iy,iz] coordinates of the cell
		this particle belongs to */
		ix = (int) (Data[i].x / CellSize);
		iy = (int) (Data[i].y / CellSize);
		iz = (int) (Data[i].z / CellSize);


	/*  And now assign to each particle the id of the
		cell it belongs to */
		if (Data[i].x == LBox)
			ix = NCells-1;
		if (Data[i].y == LBox)
			iy = NCells-1;
		if (Data[i].z == LBox)
			iz = NCells-1;

		Data[i].id  = i;
		Data[i].ioc = (long) (ix + NCells*(iy) + (NCells*NCells)*(iz));


		if (ix > NCells || iy > NCells || iz > NCells)
		{
			printf("Assign_cell.c: Error when assigning particles to a given cell\n");
			printf("ix: %d iy: %d iz %d \n", ix,iy,iz);
			printf("NCells: %d NCells: %d NCells: %d \n", NCells, NCells, NCells);
			exit(0);
		}
		
	}
}
