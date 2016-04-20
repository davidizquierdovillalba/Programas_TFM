from astropy.io import ascii
import matplotlib.pyplot as plt

tabla1=[]
tabla2=[]
tabla3=[]
tabla4=[]
tabla5=[]
tabla6=[]
tabla7=[]
tabla8=[]
tabla9=[]
tabla10=[]
tabla11=[]
tabla12=[]
tabla13=[]
tabla14=[]
tabla15=[]
tabla16=[]
tabla17=[]
tabla18=[]
tabla19=[]
tabla20=[]
tabla21=[]
tabla22=[]
tabla23=[]
tabla24=[]
tabla25=[]
tabla26=[]
tabla27=[]
tabla28=[]

tabla1=ascii.read('Valores_Mediana_Radio_Halo')
distancia1=tabla1['Distancia']
densidad1=tabla1['Densidad']

tabla2=ascii.read('Valores_Percentil10_Radio_Halo')
distancia2=tabla2['Distancia']
densidad2=tabla2['Densidad']

tabla3=ascii.read('Valores_Percentil90_Radio_Halo')
distancia3=tabla3['Distancia']
densidad3=tabla3['Densidad']

tabla4=ascii.read('Valores_Percentil16_Radio_Halo')
distancia4=tabla4['Distancia']
densidad4=tabla4['Densidad']

tabla5=ascii.read('Valores_Percentil84_Radio_Halo')
distancia5=tabla5['Distancia']
densidad5=tabla5['Densidad']


tabla6=ascii.read('Valores_Mediana_Control_Halo')
distancia6=tabla6['Distancia']
densidad6=tabla6['Densidad']

tabla7=ascii.read('Valores_Percentil10_Control_Halo')
distancia7=tabla7['Distancia']
densidad7=tabla7['Densidad']

tabla8=ascii.read('Valores_Percentil90_Control_Halo')
distancia8=tabla8['Distancia']
densidad8=tabla8['Densidad']

tabla9=ascii.read('Valores_Percentil16_Control_Halo')
distancia9=tabla9['Distancia']
densidad9=tabla9['Densidad']

tabla10=ascii.read('Valores_Percentil84_Control_Halo')
distancia10=tabla10['Distancia']
densidad10=tabla10['Densidad']


tabla11=ascii.read('Valores_Mediana_Radio_Estelar')
distancia11=tabla11['Distancia']
densidad11=tabla11['Densidad']

tabla12=ascii.read('Valores_Percentil10_Radio_Estelar')
distancia12=tabla12['Distancia']
densidad12=tabla12['Densidad']

tabla13=ascii.read('Valores_Percentil90_Radio_Estelar')
distancia13=tabla13['Distancia']
densidad13=tabla13['Densidad']

tabla14=ascii.read('Valores_Percentil16_Radio_Estelar')
distancia14=tabla14['Distancia']
densidad14=tabla14['Densidad']

tabla15=ascii.read('Valores_Percentil84_Radio_Estelar')
distancia15=tabla15['Distancia']
densidad15=tabla15['Densidad']


tabla16=ascii.read('Valores_Mediana_Control_Estelar')
distancia16=tabla16['Distancia']
densidad16=tabla16['Densidad']

tabla17=ascii.read('Valores_Percentil10_Control_Estelar')
distancia17=tabla17['Distancia']
densidad17=tabla17['Densidad']

tabla18=ascii.read('Valores_Percentil90_Control_Estelar')
distancia18=tabla18['Distancia']
densidad18=tabla18['Densidad']

tabla19=ascii.read('Valores_Percentil16_Control_Estelar')
distancia19=tabla19['Distancia']
densidad19=tabla19['Densidad']

tabla20=ascii.read('Valores_Percentil84_Control_Estelar')
distancia20=tabla20['Distancia']
densidad20=tabla20['Densidad']

tabla21=ascii.read('Valores_Percentil25_Control_Estelar')
distancia21=tabla21['Distancia']
densidad21=tabla21['Densidad']

tabla22=ascii.read('Valores_Percentil75_Control_Estelar')
distancia22=tabla22['Distancia']
densidad22=tabla22['Densidad']

tabla23=ascii.read('Valores_Percentil25_Radio_Estelar')
distancia23=tabla23['Distancia']
densidad23=tabla23['Densidad']

tabla24=ascii.read('Valores_Percentil75_Radio_Estelar')
distancia24=tabla24['Distancia']
densidad24=tabla24['Densidad']


tabla25=ascii.read('Valores_Percentil25_Radio_Halo')
distancia25=tabla25['Distancia']
densidad25=tabla25['Densidad']

tabla26=ascii.read('Valores_Percentil75_Radio_Halo')
distancia26=tabla26['Distancia']
densidad26=tabla26['Densidad']

tabla27=ascii.read('Valores_Percentil25_Control_Halo')
distancia27=tabla27['Distancia']
densidad27=tabla27['Densidad']

tabla28=ascii.read('Valores_Percentil75_Control_Halo')
distancia28=tabla28['Distancia']
densidad28=tabla28['Densidad']



#----------------------------------------------MASA HALO -------------------------------------------------------------------------------------

#1) Radio galaxias:

#plt.plot(distancia1,densidad1,color='red',label='Radio Galaxias: Mediana')

#plt.fill_between(distancia1, densidad2, densidad3,color='orange',label='Percentiles de Radio Galaxias: [Cota superior $\mathrm{P_{90}}$ : Cota inferior $\mathrm{P_{10}}$]',alpha=0.5)

#plt.fill_between(distancia1, densidad4, densidad5,color='orange',label='Percentiles de Radio Galaxias: [Cota superior $\mathrm{P_{84}}$ : Cota inferior $\mathrm{P_{16}}$]',alpha=0.5)

#plt.fill_between(distancia1, densidad25, densidad26,color='orange',label='Percentiles de Radio Galaxias: [Cota superior $\mathrm{P_{75}}$ : Cota inferior $\mathrm{P_{25}}$]',alpha=0.5)

#2) Sin Radio:

#plt.plot(distancia6,densidad6,color='blue',label='Galaxias Control $\mathrm{M_{Halo}}$: Mediana')

#plt.fill_between(distancia6, densidad7, densidad8,color='blue',label='Percentiles de Muestra Control: [Cota superior $\mathrm{P_{90}}$ : Cota inferior $\mathrm{P_{10}}$]',alpha=0.35)

#plt.fill_between(distancia6, densidad9, densidad10,color='blue',label='Percentiles de Muestra Control: [Cota superior $\mathrm{P_{84}}$ : Cota inferior $\mathrm{P_{16}}$]',alpha=0.35)

#plt.fill_between(distancia6, densidad27, densidad28,color='blue',label='Percentiles de Muestra Control: [Cota superior $\mathrm{P_{75}}$ : Cota inferior $\mathrm{P_{25}}$]',alpha=0.35)

#-----------------------------------------------MASA ESTELAR----------------------------------------------------------------------------------

#1) Radio galaxias:

plt.plot(distancia11,densidad11,color='red',label='Radio Galaxias: Mediana')

#plt.fill_between(distancia11, densidad12, densidad13,color='orange',label='Percentiles de Radio Galaxias: [Cota superior $\mathrm{P_{90}}$ : Cota inferior $\mathrm{P_{10}}$]',alpha=0.5)

#plt.fill_between(distancia11, densidad14, densidad15,color='orange',label='Percentiles de Radio Galaxias: [Cota superior $\mathrm{P_{84}}$ : Cota inferior $\mathrm{P_{16}}$]',alpha=0.5)

plt.fill_between(distancia11, densidad23, densidad24,color='orange',label='Percentiles de Radio Galaxias: [Cota superior $\mathrm{P_{75}}$ : Cota inferior $\mathrm{P_{25}}$]',alpha=0.5)

#2) Sin Radio:

plt.plot(distancia16,densidad16,color='blue',label='Galaxias Control $\mathrm{M_{Estelar}}$: Mediana')

#plt.fill_between(distancia16, densidad17, densidad18,color='blue',label='Percentiles de Muestra Control: [Cota superior $\mathrm{P_{90}}$ : Cota inferior $\mathrm{P_{10}}$]',alpha=0.35)

#plt.fill_between(distancia16, densidad19, densidad20,color='blue',label='Percentiles de Muestra Control: [Cota superior $\mathrm{P_{84}}$ : Cota inferior $\mathrm{P_{16}}$]',alpha=0.35)

plt.fill_between(distancia16, densidad21, densidad22,color='blue',label='Percentiles de Muestra Control: [Cota superior $\mathrm{P_{75}}$ : Cota inferior $\mathrm{P_{25}}$]',alpha=0.35)

#---------------------------------------------------LEYENDA--------------------------------------------------------------------------------

plt.legend(loc="upper right",prop={'size':12})

plt.suptitle('Densidad alrededor de galaxias centrales\n z=0 \n', fontsize=18)
plt.title('Radio Galaxias vs No Radio Galaxias', fontsize=12)
#plt.title('Densidad', fontsize=12)
plt.ylabel('$\mathrm{log_{10}(\delta){[(Mpc/h)^{-3}]}}$',fontsize=17)
plt.xlabel('$\mathrm{r{[(Mpc/h)]}}$',fontsize=17)

plt.show()	
