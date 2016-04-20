
#define Pi 3.141592654                                                           
#define MIN(a,b) ((a)<(b)?(a):(b))                                                    
#define MAX(a,b) ((a)>(b)?(a):(b))                                                   
#define dprinti(expr) printf(#expr " = %d\n", expr)                                  
#define dprintf(expr) printf(#expr " = %f\n", expr)                                  
#define dprints(expr) printf(#expr " = %s\n", expr)                                       
#define SQR(a) ((a)*(a))                                                                  
#define NCELLMAX 207000              
#define NMAX 5600000                                                               
#define NMAXDM 5600000 
#define NBINMAX 100                                                                       
#define NCHARMAX 255
#define  NBinsMAX 100 //Controlo la dimension de la matriz MassEnclosed[NMAX[NBinsMAX] ubicada en el main.c                                                          
                                       
typedef struct {                                                                          
    unsigned long ioc;
	unsigned long id;
float masa; 
    float x;
   	float y;
	float z;
} particle;
                                                                              
extern float CellSize; 
extern int NCells;
extern unsigned int NCellTotal; 
extern int NRunXX, nXX, Seed;
extern float LBox;
extern int LogBins;
