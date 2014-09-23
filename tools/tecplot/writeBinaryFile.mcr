#!MC 1200
$!CREATEMIRRORZONES 
  SOURCEZONES =  [1-256] 
  MIRRORVAR = 'Y' 
$!ALTERDATA  [257-512] 
  EQUATION = '{V0} = (-1)*{V0}' 
$!ALTERDATA  [257-512] 
  EQUATION = '{V1} = (-1)*{V1}' 
$!ALTERDATA  [257-512] 
  EQUATION = '{Bx} = (-1)*{Bx}' 
$!GLOBALCONTOUR 1  VAR = 3 
$!CONTOURLEVELS RESETTONICE 
  CONTOURGROUP = 1 
  APPROXNUMVALUES = 15 
$!FIELDLAYERS SHOWCONTOUR = YES 
$!FIELDLAYERS SHOWSHADE = NO 
$!FIELDLAYERS SHOWEDGE = NO 
$!CREATEMIRRORZONES  
  SOURCEZONES =  [1-256] 
  MIRRORVAR = 'X' 
$!CREATEMIRRORZONES  
  SOURCEZONES =  [257-512] 
  MIRRORVAR = 'X'
$!ALTERDATA  [513-1024] 
  EQUATION = '{U0} = (-1)*{U0}' 
$!ALTERDATA  [513-1024] 
  EQUATION = '{U1} = (-1)*{U1}' 
$!ALTERDATA  [513-1024] 
  EQUATION = '{By} = (-1)*{By}' 
$!VarSet |MFBD| = './T422'
$!ALTERDATA
EQUATION = '{Jz} = ({Ez} + {U0}*{By} - {V0}*{Bx})/0.075'
$!ALTERDATA
EQUATION = '{J<sub>nonDim</sub>} = {Jz}/7.96e-3'
$!ALTERDATA
EQUATION = '{n<sub>i</sub>} = {rho0}/1.67262177774e-27'
$!ALTERDATA
EQUATION = '{n<sub>n</sub>} = {rho1}/1.6735327160314e-27'
$!ALTERDATA
EQUATION = '{n<sub>Tot</sub>} = {n<sub>i</sub>} + {n<sub>n</sub>} '
$!ALTERDATA
EQUATION = '{rho<sub>Tot</sub>} = {rho0} + {rho1}'
$!ALTERDATA
EQUATION = '{Psi<sub>i</sub>} = {n<sub>i</sub>} /({n<sub>Tot</sub>})'
$!ALTERDATA
EQUATION = '{B} = sqrt({Bx}*{Bx} + {By}*{By} )'
$!ALTERDATA
EQUATION = '{v<sub>A</sub>} = {B}/(sqrt(4*3.14159265359*1e-7*{rho<sub>Tot</sub>}))'
$!ALTERDATA
EQUATION = '{U0Ad} = {U0}/1.20071303e5'
$!ALTERDATA
EQUATION = '{V0Ad} = {V0}/1.20071303e5'
$!ALTERDATA
EQUATION = '{U1Ad} = {U1}/1.20071303e5'
$!ALTERDATA
EQUATION = '{U1Ad} = {U1}/1.20071303e5'
$!ALTERDATA
EQUATION = '{V1Ad} = {V1}/1.20071303e5'
$!WRITEDATASET "|MFBD|/MirroredMRStudy4-time_422.plt"
INCLUDETEXT = NO
INCLUDEGEOM = NO
INCLUDECUSTOMLABELS = NO
INCLUDEAUTOGENFACENEIGHBORS = YES
ASSOCIATELAYOUTWITHDATAFILE = NO
BINARY = YES
USEPOINTFORMAT = NO
PRECISION = 9
TECPLOTVERSIONTOWRITE = TECPLOTCURRENT
$!RemoveVar |MFBD|
