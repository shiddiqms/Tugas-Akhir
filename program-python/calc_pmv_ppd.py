import sys
import json
from pythermalcomfort.models import pmv_ppd
from pythermalcomfort.psychrometrics import v_relative
from pythermalcomfort.utilities import met_typical_tasks
from pythermalcomfort.utilities import clo_individual_garments
myString1 = sys.argv[1]
#print(myString1)
data = json.loads(myString1)
t1 = data["T_Dalam"]
#t2 = data["T_Luar"]
h1 = data["H_Dalam"]
s = data["sta"]

#input variables
tdb = t1  # dry-bulb air temperature, [$^{\circ}$C]
tr = t1  # mean radiant temperature, [$^{\circ}$C]
if (s == 1):
	v = 0.31
elif (s == 2):
	v = 0.212
else:
	v = 0.1
#v = 0.212 + s*0.098  # average air velocity, [m/s]
rh = h1  # relative humidity, [%]
activity = "Typing"  # participant's activity description
garments = ["Sweatpants", "T-shirt"]

met = met_typical_tasks[activity]  # activity met, [met]
icl = 0.5#sum([clo_individual_garments[item] for item in garments])  # calculate total clothing insulation

# calculate the relative air velocity
vr = v_relative(v=v, met=met)

# calculate PMV in accordance with the ASHRAE 55 2017
results = pmv_ppd(tdb=tdb, tr=tr, vr=vr, rh=rh, met=met, clo=icl, standard="ASHRAE")

# print the results
#print(results)

buff = '{"PMV":'+str(results['pmv'])+',"PPD":'+str(results['ppd'])+'}'
print(buff)
# print PMV value
#print(f"pmv={results['pmv']}, ppd={results['ppd']}%")
