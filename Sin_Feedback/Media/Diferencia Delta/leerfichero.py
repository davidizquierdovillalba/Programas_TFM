from astropy.io import ascii
import matplotlib.pyplot as plt
tabla=[]
tabla2=[]
tabla3=[]
#Abrir el documento txt:
tabla=ascii.read('DiferenciaRadio_z_3')
#Sacar columnas:
distancia=tabla['Distancia']
densidad=tabla['Densidad']

plt.plot(distancia,densidad,color='red',label='z=3')

plt.legend(loc="upper right",prop={'size':12})

plt.suptitle("Densidad alrededor de galaxias centrales",fontsize=18)
plt.title('Radio Galaxias .vs. No Radio Galaxias de Control ($\mathrm{M_{Estelar}}$)', fontsize=12)
plt.ylabel('$\mathrm{(\delta_{Radio}-\delta_{Control})/\delta_{Control}}$',fontsize=17)
plt.xlabel('$\mathrm{r{[(Mpc/h)]}}$',fontsize=17)

plt.show()	
