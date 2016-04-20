from astropy.io import ascii
import matplotlib.pyplot as plt
tabla=[]
tabla1=[]
tabla2=[]
tabla3=[]
tabla4=[]
tabla5=[]


tabla=ascii.read('Densidad_Radio_Estelar')
distancia=tabla['Distancia']
densidad=tabla['Densidad']

tabla1=ascii.read('Densidad_Sin_Radio_Estelar')
distancia1=tabla1['Distancia']
densidad1=tabla1['Densidad']

tabla2=ascii.read('Densidad_Radio_Estelar_Con_Feedback')
distancia2=tabla2['Distancia']
densidad2=tabla2['Densidad']

tabla3=ascii.read('Densidad_Sin_Radio_Estelar_Con_Feedback')
distancia3=tabla3['Distancia']
densidad3=tabla3['Densidad']

tabla4=ascii.read('Densidad_Radio_Halo')
distancia4=tabla4['Distancia']
densidad4=tabla4['Densidad']


tabla5=ascii.read('Densidad_Sin_Radio_Halo')
distancia5=tabla5['Distancia']
densidad5=tabla5['Densidad']

tabla6=ascii.read('Densidad_Radio_Halo_Con_Feedback')
distancia6=tabla6['Distancia']
densidad6=tabla6['Densidad']


tabla7=ascii.read('Densidad_Sin_Radio_Halo_Con_Feedback')
distancia7=tabla7['Distancia']
densidad7=tabla7['Densidad']

#--------------------------------------------------------------------Graficos--------------------------------------------------------------

#plt.plot(distancia,densidad,color='red',label='NO FEEDBACK: RADIO GALAXIAS: Galaxias centrales con Lrg>22.5 (#galaxias=32)')
#plt.plot(distancia1,densidad1,color='blue',label='NO FEEDBACK: GALAXIAS CONTROL ($\mathrm{M_{Estelar}}$) : Centrales con Lrg<22.5 (#galaxias=32)')
#plt.plot(distancia2,densidad2,color='orange',label='FEEDBACK: RADIO GALAXIAS: Galaxias centrales con Lrg>22.5 (#galaxias=415)')
#plt.plot(distancia3,densidad3,color='cyan',label='FEEDBACK: GALAXIAS CONTROL ($\mathrm{M_{Estelar}}$) : Centrales con Lrg<22.5 (#galaxias=415)')

plt.plot(distancia4,densidad4,color='red',label='NO FEEDBACK: RADIO GALAXIAS: Galaxias centrales con Lrg>22.5 (#galaxias=9)')
plt.plot(distancia5,densidad5,color='blue',label='NO FEEDBACK: GALAXIAS CONTROL ($\mathrm{M_{Halo}}$) : Centrales con Lrg<22.5 (#galaxias=9)')
plt.plot(distancia6,densidad6,color='orange',label='FEEDBACK: RADIO GALAXIAS: Galaxias centrales con Lrg>22.5 (#galaxias=365)')
plt.plot(distancia7,densidad7,color='cyan',label='FEEDBACK: GALAXIAS CONTROL ($\mathrm{M_{Halo}}$) : Centrales con Lrg<22.5 (#galaxias=361)')

#--------------------------------------------------------------------Leyenda--------------------------------------------------------------
plt.legend(loc="upper right",prop={'size':12})

plt.suptitle("Sin Feedback de AGN: Densidad alrededor de galaxias centrales\n z=3\n",fontsize=18)
plt.title('Radio Galaxias .vs. No Radio Galaxias', fontsize=12)
plt.ylabel('$\mathrm{log_{10}(\delta){[(Mpc/h)^{-3}]}}$',fontsize=17)
plt.xlabel('$\mathrm{r{[(Mpc/h)]}}$',fontsize=17)

plt.show()	
