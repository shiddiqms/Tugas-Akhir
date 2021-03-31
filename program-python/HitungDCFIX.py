import sys
import json
import pandas as pd
import numpy as np
import keras

myString1 = sys.argv[1]
#print(myString1)
data = json.loads(myString1)

TL = data["T_Luar"]
RC = data["RC"]
PMV = data["PMV"]
minTL = data["minTL"]
minRC = data["minRC"]
minPMV = data["minPMV"]
maxTL = data["maxTL"]
maxRC = data["maxRC"]
maxPMV = data["maxPMV"]

def scaleTL(TL):
    sc = (TL-minTL)/(maxTL-minTL)
    return sc
def scalePMV(PMV):
    sc = (PMV-minPMV)/(maxPMV-minPMV)
    return sc
def scaleRC(RC):
    sc = (RC-minRC)/(maxRC-minRC)
    return sc
def invscaleDC(DC):
    invsc = (DC)*100
    return invsc

from keras.models import load_model

model = load_model(r'C:\Users\user\Documents\test\modelANNFIX.h5')

xinput = np.array([[float(TL),float(RC),float(PMV)]])
xinput_scaled = np.array([[scaleTL(xinput[0][0]),scaleRC(xinput[0][1]), scalePMV(xinput[0][2])]])

youtput = model.predict(xinput_scaled)
youtput_scaled = invscaleDC(youtput)
DC = np.around(youtput_scaled, decimals=0)

if(DC>100):
    DC = 100;
elif(DC<20):
    DC = 20;

#print(youtput)
#print("Duty Cycle = " + str(float(DC)) + " %")
buff = '{"DC":'+ str(float(DC)) +'}'
print(buff)
