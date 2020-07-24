#!/bin/bash

export Linux_Flavour_="Ubuntu 18.04.3 LTS"
export System_="x86_64"
. /home/yong/src/KoalaSoft/build_jens/check_system.sh
if [ $same_system -eq 1 ]; then
	export SIMPATH="/home/yong/fairsoft/jun19"
	export ROOTSYS="/home/yong/fairsoft/jun19"
	export FAIRROOTPATH="/home/yong/fairroot/v18_jun19"
	if (true); then
		export Geant4_INCLUDE_DIRS="/home/yong/fairsoft/jun19/include/Geant4"
		export Geant4VMC_INCLUDE_DIRS="/home/yong/fairsoft/jun19/include/geant4vmc:/home/yong/fairsoft/jun19/include/g4root"
		export Geant4VMC_LIBRARY_DIR="lib"
		export Geant4VMC_MACRO_DIR=""
		export PLUTO_LIBRARY_DIR=""
		export PLUTO_INCLUDE_DIR=""
		export PYTHIA6_LIBRARY_DIR="/home/yong/fairsoft/jun19/lib"
		export Geant3_INCLUDE_DIRS="/home/yong/fairsoft/jun19/include/TGeant3"
		export G3SYS="/home/yong/fairsoft/jun19/share/geant3"
		export Geant3_LIBRARY_DIR="/home/yong/fairsoft/jun19/lib/Geant3-2.7.0/lib"
		export USE_VGM="1"
		export PYTHIA8DATA="/home/yong/fairsoft/jun19/share/pythia8/xmldoc"
		export CLASSPATH=""

		####################### Create the data set variables for Geant4 #############
export G4NEUTRONHPDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4NDL4.5
export G4LEDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4EMLOW7.7
export G4LEVELGAMMADATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/PhotonEvaporation5.3
export G4RADIOACTIVEDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/RadioactiveDecay5.3
export G4PARTICLEXSDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4PARTICLEXS1.1
export G4PIIDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4PII1.3
export G4REALSURFACEDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/RealSurface2.1.1
export G4SAIDXSDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4SAIDDATA2.0
export G4ABLADATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4ABLA3.1
export G4INCLDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4INCL1.0
export G4ENSDFSTATEDATA=/home/yong/fairsoft/jun19/share/Geant4-10.5.1/data/G4ENSDFSTATE2.2
##############################################################################

	fi
	export Geant3_INCLUDE_DIRS="/home/yong/fairsoft/jun19/include/TGeant3"
	export ROOT_LIBRARY_DIR="/home/yong/fairsoft/jun19/lib/root"
	export ROOT_LIBRARIES="-L/home/yong/fairsoft/jun19/lib/root -lGui -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -pthread -Wl,-rpath,/home/yong/fairsoft/jun19/lib/root -lm -ldl -rdynamic"
	export ROOT_INCLUDE_DIR="/home/yong/fairsoft/jun19/include/root6"
	export ROOT_INCLUDE_PATH="/home/yong/fairsoft/jun19/include/TGeant3:/home/yong/fairroot/v18_jun19/include"
	export VMCWORKDIR="/home/yong/src/KoalaSoft"
	export FAIRLIBDIR="/home/yong/src/KoalaSoft/build_jens/lib"
	export PYTHONPATH="/home/yong/src/KoalaSoft/python:/home/yong/fairsoft/jun19/lib:/home/yong/fairsoft/jun19/lib/root:/home/yong/fairsoft/jun19/lib/Geant4:/home/yong/fairsoft/jun19/lib/g4py"
	case $1 in
		-a | --append )
			export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:""
			export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:"/home/yong/src/KoalaSoft/build_jens/lib:/home/yong/fairroot/v18_jun19/lib:/home/yong/fairsoft/jun19/lib/root:/home/yong/fairsoft/jun19/lib/Geant3-2.7.0/lib:/home/yong/fairsoft/jun19/lib"
			export PATH=$PATH:"/home/yong/fairsoft/jun19/bin:/home/yong/.vscode-server/bin/d69a79b73808559a91206d73d7717ff5f798f23c/bin:/home/yong/.vscode-server/bin/a9f8623ec050e5f0b44cc8ce8204a1455884749f/bin:/home/yong/workspace/myenv/bin:/usr/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/sbin:/bin:/usr/games:/usr/local/games"
			;;
		-p | --prepend )
			export DYLD_LIBRARY_PATH="":$DYLD_LIBRARY_PATH
			export LD_LIBRARY_PATH="/home/yong/src/KoalaSoft/build_jens/lib:/home/yong/fairroot/v18_jun19/lib:/home/yong/fairsoft/jun19/lib/root:/home/yong/fairsoft/jun19/lib/Geant3-2.7.0/lib:/home/yong/fairsoft/jun19/lib":$LD_LIBRARY_PATH
			export PATH="/home/yong/fairsoft/jun19/bin:/home/yong/.vscode-server/bin/d69a79b73808559a91206d73d7717ff5f798f23c/bin:/home/yong/.vscode-server/bin/a9f8623ec050e5f0b44cc8ce8204a1455884749f/bin:/home/yong/workspace/myenv/bin:/usr/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/sbin:/bin:/usr/games:/usr/local/games":$PATH
			;;
		* )
			export DYLD_LIBRARY_PATH=""
			export LD_LIBRARY_PATH="/home/yong/src/KoalaSoft/build_jens/lib:/home/yong/fairroot/v18_jun19/lib:/home/yong/fairsoft/jun19/lib/root:/home/yong/fairsoft/jun19/lib/Geant3-2.7.0/lib:/home/yong/fairsoft/jun19/lib"
			export PATH="/home/yong/fairsoft/jun19/bin:/home/yong/.vscode-server/bin/d69a79b73808559a91206d73d7717ff5f798f23c/bin:/home/yong/.vscode-server/bin/a9f8623ec050e5f0b44cc8ce8204a1455884749f/bin:/home/yong/workspace/myenv/bin:/usr/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/sbin:/bin:/usr/games:/usr/local/games"
			;;
	esac
fi
