#!MC 900
$!VarSet |MFBD| = '/home/lani/EULER_25_4/mprojs/MESHDATA'
$!ALTERDATA 
  EQUATION = '{u} = {rhoU}/{rho}' 
$!ALTERDATA 
  EQUATION = '{v} = {rhoV}/{rho}' 
$!ALTERDATA 
  EQUATION = '{w} = {rhoW}/{rho}' 
$!ALTERDATA 
  EQUATION = '{p} = 0.4*({rhoE}-0.5*{rho}*({u}**2.+{v}**2.+{w}**2.))' 
$!ALTERDATA 
  EQUATION = '{M} = sqrt(({u}**2.+{v}**2.+{w}**2.)/(1.4*{p}/{rho}))' 
$!ALTERDATA 
  EQUATION = '{T} = {p}/({rho}*287.046)'
$!ALTERDATA 
  EQUATION = '{Tt} = {T}*(1. + 0.2*{M}**2.)'
$!ALTERDATA 
  EQUATION = '{pt} = {p}*(1. + 0.2*{M}**2.)**3.5'
$!ALTERDATA 
  EQUATION = '{s} = log({p})-1.4*log({rho})'
$!RemoveVar |MFBD|
