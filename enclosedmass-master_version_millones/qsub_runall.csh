#!/bin/tcsh
#$ -S
#$ -cwd

# Script to run enclosedmass
#
#

set Nruns = 16
set NSubVol = 512

set Central = 'qso'

set Bin = `echo $NSubVol $Nruns | gawk '{print $1/$2}'` 

@ i = 0

while ($i < $Nruns)
	
	@ iv0 = $i * $Bin 
	@ iv1 = ($i + 1) * $Bin - 1

#foreach snap ('17' '20' '25' '29')
	foreach snap ('29')
#	foreach snap ('17' '20' '25' '29')
	
		set logfile = $Central'_out_iz'$snap'.'$i
		set name    = $Central'_env_iz'$snap'.'$i
		echo $name $iv0 $iv1 $Central
		bsub  -P durham -L /bin/tcsh  -q cordelia  -u aaorsi@gmail.com  -J $name  -oo $logfile run.csh $snap $iv0 $iv1 $i $Central
	end

	@ i++

end
