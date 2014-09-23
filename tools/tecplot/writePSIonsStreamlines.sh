#! bashrc

clear
module load tecplot

echo "SCRIPT TO WRITE A PS from the plots"
echo
echo "NOTE: send the job from the directory where you have the ./T*"
echo
echo "Creating ./RESULTSplots where the plots are stored"
resultDirectory=./RESULTSplots
resultIonStream=$resultDirectory/IonStreamlines
mkdir $resultDirectory
mkdir $resultIonStream 

for Directory in ./T*
do
echo
echo "The name of the binary should be of the kind of MRStudy4-time_0.plt"
echo
  # Reading the time from the files and
  # storing it into variable $time
  inputDirectory= $Directory
  time=$(echo ${Directory}| cut -c4-6)
  inputFileName=$Directory/"MRStudy4-time_"$time".plt"
  

  echo "Entering in $Directory"
  echo
  echo "Writing the tecplot macro ./exportPS.mcr"
  echo
  echo "Generating plots for $inputFileName"

  ## Writing first part of the Macro
  header="#!MC 1200 "
  
  directoryVar="\$!VarSet |MFBD| = '"$inputDirectory"'"
  

  mirror="\$!CREATEMIRRORZONES 
  SOURCEZONES =  [1-256] 
  MIRRORVAR = 'Y' 
\$!ALTERDATA  [257-512] 
  EQUATION = '{V0} = (-1)*{V0}' 
\$!ALTERDATA  [257-512] 
  EQUATION = '{V1} = (-1)*{V1}' 
\$!ALTERDATA  [257-512] 
  EQUATION = '{Bx} = (-1)*{Bx}' 
\$!GLOBALCONTOUR 1  VAR = 3 
\$!CONTOURLEVELS RESETTONICE 
  CONTOURGROUP = 1 
  APPROXNUMVALUES = 15 
\$!FIELDLAYERS SHOWSHADE = NO 
\$!FIELDLAYERS SHOWEDGE = NO 
\$!CREATEMIRRORZONES  
  SOURCEZONES =  [1-256] 
  MIRRORVAR = 'X' 
\$!CREATEMIRRORZONES  
  SOURCEZONES =  [257-512] 
  MIRRORVAR = 'X'
\$!ALTERDATA  [513-1024] 
  EQUATION = '{U0} = (-1)*{U0}' 
\$!ALTERDATA  [513-1024] 
  EQUATION = '{U1} = (-1)*{U1}' 
\$!ALTERDATA  [513-1024] 
  EQUATION = '{By} = (-1)*{By}' " 
  

  changeAxisAndCenter="\$!TWODAXIS DEPXTOYRATIO = 0.0250000000000000014 
\$!VIEW CENTER
\$!VIEW SETMAGNIFICATION 
  MAGNIFICATION = 6.17979502402 
\$!VIEW PUSH 
\$!TWODAXIS XDETAIL{TITLE{TITLEMODE = USETEXT}} 
\$!TWODAXIS XDETAIL{TITLE{TEXT = 'x [m]'}} 
\$!TWODAXIS YDETAIL{TITLE{TITLEMODE = USETEXT}} 
\$!TWODAXIS YDETAIL{TITLE{TEXT = 'y [m]'}} 
\$!RENAMEDATASETVAR  
  VAR = 20 
  NAME = 'Jz [A/m<sup>2</sup>]' 
\$!GLOBALCONTOUR 1  VAR = 20 
\$!CONTOURLEVELS RESETTONICE 
  CONTOURGROUP = 1 
  APPROXNUMVALUES = 15 "

  redraw="\$!REDRAW "
  

  setLegend="\$!GLOBALCONTOUR 1  LEGEND{SHOW = YES} 
\$!GLOBALCONTOUR 1  LEGEND{ISVERTICAL = NO}
\$!GLOBALCONTOUR 1  LEGEND{LABELLOCATION = COLORMAPDIVISIONS} 
\$!GLOBALCONTOUR 1  LEGEND{AUTORESIZE = YES} 
\$!GLOBALCONTOUR 1  LEGEND{XYPOS{Y = 98}} "

  alterData="\$!ALTERDATA 
  EQUATION = '{V<sub>ions</sub> [m/s]} = sqrt({U0}*{U0} + {V0}*{V0})'
\$!ALTERDATA 
  EQUATION = '{V<sub>neutrals</sub> [m/s]} = sqrt({U1}*{U1} + {V1}*{V1})'"
  
  changeNameVars="\$!RENAMEDATASETVAR  
  VAR = 13 
  NAME = 'U<sub>ion</sub> [m/s]'
\$!RENAMEDATASETVAR  
  VAR = 14 
  NAME = 'V<sub>ion</sub> [m/s]' 
\$!RENAMEDATASETVAR  
  VAR = 15 
  NAME = 'U<sub>neutral</sub> [m/s]' 
\$!RENAMEDATASETVAR  
  VAR = 16 
  NAME = 'V<sub>neutral</sub> [m/s]' "


  setTime="\$!ATTACHTEXT  
  ANCHORPOS 
    { 
    X = 86.91489361702128 
    Y = 6.382978723404253 
    } 
  TEXT = 't = $time' 
\$!PICK SETMOUSEMODE 
  MOUSEMODE = SELECT 
\$!PICK ADDATPOSITION 
  X = 8.92718746066 
  Y = 7.67389525368 
  CONSIDERSTYLE = YES 
\$!PICK SHIFT 
  X = 0.0524235175626 
  Y = 0.209492635025 
\$!PICK ADDATPOSITION 
  X = 10.3688341936 
  Y = 7.73936170213 
  CONSIDERSTYLE = YES 
\$!PICK SETMOUSEMODE 
  MOUSEMODE = SELECT "

  exportSetup="\$!EXPORTSETUP EXPORTFORMAT = PS 
\$!PRINTSETUP PALETTE = COLOR 
\$!EXPORTSETUP IMAGEWIDTH = 1275 "

  PSname="\$!EXPORTSETUP EXPORTFNAME = '$resultIonStream/IonStreamlines-time_$time.ps' "

  export="\$!EXPORT  
  EXPORTREGION = CURRENTFRAME"

  streamtraces="\$!GLOBALTWODVECTOR UVAR = 13
\$!GLOBALTWODVECTOR VVAR = 14
\$!RESETVECTORLENGTH 
\$!STREAMTRACELAYERS SHOW = YES
\$!STREAMTRACE ADD
  NUMPTS = 10
  STREAMTYPE = TWODLINE
  STARTPOS
    {
    X = 1000
    Y = 20000
    }
  ALTSTARTPOS
    {
    X = 200000
    Y = 20000
    }
\$!STREAMTRACE ADD
  NUMPTS = 10
  STREAMTYPE = TWODLINE
  STREAMDIRECTION = BOTH
  STARTPOS
    {
    X = 1000
    Y = -20000
    }
  ALTSTARTPOS
    {
    X = 200000
    Y = -20000
    }
\$!STREAMTRACE ADD
  NUMPTS = 10
  STREAMTYPE = TWODLINE
  STREAMDIRECTION = BOTH
  STARTPOS
    {
    X = -200000
    Y = 20000
    }
  ALTSTARTPOS
    {
    X = -1000
    Y = 20000
    }
\$!STREAMTRACE ADD
  NUMPTS = 10
  STREAMTYPE = TWODLINE
  STREAMDIRECTION = BOTH
  STARTPOS
    {
    X = -200000
    Y = -20000
    }
  ALTSTARTPOS
    {
    X = -1000
    Y = -20000
    }
\$!STREAMATTRIBUTES LINETHICKNESS = 0.599999999999999978
\$!STREAMATTRIBUTES COLOR = MULTI" 

  userDefinedContourMap="\$!GLOBALCOLORMAP 1  CONTOURCOLORMAP = USERDEF
\$!GLOBALCOLORMAP 1  USERDEFINED{NUMCONTROLPOINTS = 4}
\$!COLORMAPCONTROL 1 REDISTRIBUTECONTROLPOINTS
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{R = 23}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{R = 176}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{G = 4}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{G = 94}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{G = 169}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 1 {LEADRGB{G = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 30}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 30}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 236}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 236}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 71}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 71}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 233}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 233}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 56}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 56}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 225}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 225}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 23}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 23}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 19}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 19}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 251}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 251}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 56}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 56}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 26}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 26}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{G = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{G = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 244}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 244}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{B = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{B = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 15}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 15}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 218}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 218}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 221}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 221}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 229}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 229}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {TRAILRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 2 {LEADRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {TRAILRGB{G = 248}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {LEADRGB{G = 248}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {TRAILRGB{G = 30}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {LEADRGB{G = 30}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {TRAILRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {LEADRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {TRAILRGB{R = 11}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {LEADRGB{R = 11}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {TRAILRGB{R = 165}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {LEADRGB{R = 165}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {TRAILRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 3 {LEADRGB{R = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{B = 8}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{B = 8}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{B = 101}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{B = 101}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{B = 240}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{B = 240}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{B = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{B = 255}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{B = 184}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{B = 184}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{B = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{B = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{G = 244}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{G = 244}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{G = 150}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{G = 150}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{G = 8}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{G = 8}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{G = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{R = 236}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{R = 236}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{R = 19}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{R = 19}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {TRAILRGB{R = 0}}}
\$!GLOBALCOLORMAP 1  USERDEFINED{CONTROLPOINT 4 {LEADRGB{R = 0}}}"

  ending="\$!RemoveVar |MFBD| " 

  #We start with the U_ion VAR = 13

  setContour="\$!GLOBALCONTOUR 1  VAR = 33 
\$!CONTOURLEVELS RESETTONICE 
  CONTOURGROUP = 1 
  APPROXNUMVALUES = 15 
\$!GLOBALCONTOUR 1  COLORMAPFILTER{COLORMAPDISTRIBUTION = CONTINUOUS}
\$!GLOBALCONTOUR 1  COLORMAPFILTER{CONTINUOUSCOLOR{CMIN = -1500}}
\$!GLOBALCONTOUR 1  COLORMAPFILTER{CONTINUOUSCOLOR{CMAX = 1500}}"

  

  #Writing the macro
  echo "$header" > exportPS.mcr
  echo "$directoryVar" >> exportPS.mcr
  echo "$mirror" >> exportPS.mcr
  echo "$alterData" >> exportPS.mcr
  echo "$changeNameVars" >> exportPS.mcr
  echo "$changeAxisAndCenter" >> exportPS.mcr
  echo "$setTime" >> exportPS.mcr
  echo "$streamtraces" >> exportPS.mcr
  echo "$userDefinedContourMap" >> exportPS.mcr
  echo "$setContour" >> exportPS.mcr
  echo "$setLegend" >> exportPS.mcr
  echo "$redraw" >> exportPS.mcr
  echo "$exportSetup" >> exportPS.mcr
  echo "$PSname" >> exportPS.mcr
  echo "$export" >> exportPS.mcr

  #ending the script
  echo "$ending" >> exportPS.mcr

  

  echo "Finished writing the macro named ./exportPS.mcr"
  echo "Running tecplot"

  tec360 -b $inputFileName -p exportPS.mcr 
done
echo "End of the script"
