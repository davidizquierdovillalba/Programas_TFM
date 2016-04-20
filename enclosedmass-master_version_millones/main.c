#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <string.h>
#include "allvars.h"
#include "proto.h"

#define MAXLEN 500
/* Code to output the total dark matter mass as a function of radii for a 
 * list of central positions. 
 * The input corresponds to the Dark matter simulation and the 
 * positions for the central objects from which the enclosed mass
 * is computed. */



float id_Central[NMAX];
float MassEnclosed[NMAX][NBinsMAX];

int main(int argc, char *argv[])
{
   FILE *fcen,*fout;
   unsigned int npart;
   unsigned int NCentral;
   int junk;
   int NBins;
   char gadgetfile[MAXLEN],gadget_[MAXLEN],centralfile[MAXLEN],outfile[MAXLEN];
   long i,j,k;
   long hocDM[NCELLMAX],hocCentral[NCELLMAX];
//   unsigned long iaddDM[NMAXDM],iaddCentral[NMAX]; 
   long *iaddDM, *iaddCentral;
   particle *Central, *DarkMatter;
   int icx,icy,icz,idCen,_xc,_yc,_zc,_xnc,_ync,_znc,idDM,idPart,dBin;
   float xoff,yoff,zoff,fxx,fyy,fzz,dist;
//   float RMax = 20.0; // Maximum radius.
//   float RMin = 1.0;
   int NSubVol,iv,iv0,iv1;
//   NBins = (RMax - RMin)/BinSize + 1.0;
   float RMax, RMin, BinSize,R_10;
   int /*id_Central[NMAX],*/LogBins;
	
   float _ind;
   Central = (particle *) malloc(NMAX * sizeof(particle));


/*  if (argc != 10) {
     printf("Usage: ./enclosedmass <gadget_file> <central_file> <output_file> LBox CellSize NSubVol LogBins RMin RMax \n");
     exit(0);
  }
*/   
   strncpy(gadget_, argv[1], MAXLEN);
   strncpy(centralfile, argv[2], MAXLEN);
   strncpy(outfile, argv[3], MAXLEN);
   LBox= atof(argv[4]);
printf("LBox: %E\n",LBox);
   CellSize= atof(argv[5]); 


   LogBins= atoi(argv[6]);

   RMin= atof(argv[7]);
   RMax= atof(argv[8]);


   if (LogBins == 0) 
   {
      RMax = 10.0;  
    RMin = 0.0;
    BinSize = 0.5;
    NBins = (RMax - RMin)/BinSize + 1.0;
   }

   if (LogBins ==1)
   {
      BinSize = 0.1;
    NBins = ceil((RMax - RMin)/BinSize + 1.0);
   }

  
printf("El valor de NBins es: %d\n",NBins);


   for (i = 0; i<NMAX; i++)
   {
    for (j = 0; j < NBins; j++)
       MassEnclosed[i][j] = 0.0;
   }

   NCells = ( LBox / CellSize);
   NCellTotal = NCells * NCells * NCells;


   printf("NCells = %d NCellTotal = %d\n",NCells,NCellTotal);   

   printf("Reading %s\n",centralfile); 
   if (!(fcen = fopen(centralfile,"r")))
   {
      printf("File %s cannot be opened.\n",centralfile);
    exit(1);
   }

   j = 0;   
   while(!feof(fcen))
   {

        fscanf(fcen,"%E %E %E %E",&id_Central[j],&Central[j].x,\
    &Central[j].y,&Central[j].z);
    j++;

//    Apply Redshift-Space distortion Here (TODO)
//
   }
printf("He llegado hasta aqui\n");
// hocXXX[j]: id of first particle in cell j
// iaddXXX[k]: particle id k points to the id of the next particle in linked list
   NCentral = j-1;
          
   iaddCentral = (long *) malloc(NCentral * sizeof(long));
   printf("Central catalogue read\n");
   assigncell(Central,NCentral);


//printf("\n\nEl valor de NCentral es:%d\n\n",NCentral);


   linkedlist(Central,iaddCentral,hocCentral,NCentral);  
   printf("Cells assigned and linked lists constructed\n");
 
// Loop to read each DM file here:

//   for (iv = 0; iv < NSubVol; iv++)
   //for (iv = iv0; iv <= iv1; iv++)
   //{
   sprintf(gadgetfile,"%s",gadget_);
   printf("%s\n",gadgetfile);  

   npart = get_nparticles(gadgetfile);
   DarkMatter = (particle *) malloc(npart * sizeof(particle)); 
   iaddDM = (long *) malloc(npart * sizeof(long));
   read_gadget(DarkMatter,gadgetfile);

   printf("%d dark matter particles from %s read successfully \n",npart,gadgetfile);
// Apply redshift-space distortion here (TODO)
//


   assigncell(DarkMatter, npart);
   linkedlist(DarkMatter,iaddDM,hocDM,npart);
   printf("Cells assigned and linked lists constructed\n");

  R_10 = pow(10,RMax);

// Loop over all cells:
//
   for (icz = 0; icz < NCells; icz++)
   {
      for (icy = 0; icy < NCells; icy++)
    { 
       for (icx = 0; icx < NCells; icx++)
     {



        // id of selected cell
            i = icx + icy*NCells + icz*NCells*NCells; 
        idCen = hocCentral[i];

            if (idCen == -1)
               continue; // if there are no Central objects here, continue.


// Loop over the neighbouring cells
// (taking into account periodicity)
//
          for (_xc = -1 ; _xc <= 1; _xc++)
          { 
         _xnc = get_nc(icx,_xc);
         xoff = get_off(icx,_xc);
         for (_yc = -1; _yc<=1; _yc++)
         {
          _ync = get_nc(icy,_yc);
          yoff =get_off(icy,_yc);
          
          for (_zc = -1;_zc<=1;_zc++)
          {
          
             _znc = get_nc(icz,_zc);
          
           zoff = get_off(icz,_zc);
        
            idCen = hocCentral[i];
        
// id of cell where to look for DM neighbours
                
           idDM = _xnc + NCells*_ync + NCells*NCells*_znc;
           
           idPart = hocDM[idDM];
            

           if (idPart == -1)
              continue; // if there are no particles here (unlikely), continue.
            
// Loop over each Central galaxy and over all DM particles in selected cells. 
           while (idCen != -1)
           {  
            idPart = hocDM[idDM];
            
            


//              printf("idCen %d\n",idCen);
            
              while(idPart != -1)
            {
// Particle coordinates (corrected for periodicity)
               
               fxx = DarkMatter[idPart].x + xoff;   
               fyy = DarkMatter[idPart].y + yoff;   
               fzz = DarkMatter[idPart].z + zoff;
               
// Distance between Central and DM Particles. 
                           
                 dist = sqrt(SQR(fxx - Central[idCen].x) +\
               SQR(fyy- Central[idCen].y) +\
               SQR(fzz - Central[idCen].z));
               dBin = floor(dist/BinSize);
              
              _ind = 0.1*floor(10*log10(dist));

// If Distance is within Bins, then count it.   
//
//

               if (dist < RMax && dist >=RMin)
               {
//                printf("dist %f dBin %d idPart %d\n",dist,dBin,idPart);
                dBin = (dist - RMin)/BinSize;

                  for (k = dBin; k<NBins; k++)
                MassEnclosed[idCen][k]++;
//              printf("idCen %d\n",idCen);
               }
// Next particle in the linked list              
               idPart = iaddDM[idPart];
            }
// Next Central particle in the linked list.
            idCen = iaddCentral[idCen];

           }
          }
               }
            } 
 
         }
      }
   }

    free(DarkMatter); 
  free(iaddDM);

  //}

 

   if (!(fout = fopen(outfile,"w")))
   {
      printf("File %s cannot be opened.\n",outfile);
      exit(1);
   }

   for (i = 0; i<NCentral; i++)
   {
/*---------------------->cambio de %d a %E!!!!*/ fprintf(fout,"%E\n",id_Central[i]);
      for (j = 0;j<NBins;j++)
         fprintf(fout,"%f\t%f\n",RMin + BinSize*j,MassEnclosed[i][j]);
   }
    fclose(fout);
    fclose(fcen);

    free(Central);

} 
