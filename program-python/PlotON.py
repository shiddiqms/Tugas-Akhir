import sys
import numpy as np
import scipy.optimize as so
def baseFunction(x,a,b,c):
        return a*np.exp(-(x / b))+c
myString1 = sys.argv[1]
myString2 = myString1.replace("[","")
myString1 = myString2.replace("]","")
myArray1 = myString1.split(",")
myArray2 = []
lengthOfArray = len(myArray1)
if lengthOfArray > 2:
        for y in myArray1:
                myFloat = float(y)
                myArray2.append(myFloat)
        valueOfY = myArray2
        myArray3 = []
        for x in range(0,lengthOfArray):
                myArray3.append(x)
        valueOfX = myArray3
        valueYMIN = min(valueOfY)
        valueYMAX = max(valueOfY)
        OM = '{"TMIN":' + str(valueYMIN) + ', "TMAX":' + str(valueYMAX) + '}'
        fit_param, pcov = so.curve_fit(baseFunction,valueOfX,valueOfY)
        OMR = '{"TMIN":' + str(valueYMIN) + ', "RCt":' + str(fit_param[1]) + '}'
        print(OMR)
else:
        print('null')
