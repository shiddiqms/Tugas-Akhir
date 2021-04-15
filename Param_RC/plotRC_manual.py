import sys
import matplotlib.pyplot as plt
import numpy as np
import scipy.optimize as so
def baseFunction(x,a,b,c):
        return a * np.exp(-(x / b)) + c
myString1 = input();
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
        #RQIN = fit_param[1]*(valueYMAX-valueYMIN)
        OMR = '{"MAX":' + str(valueYMAX) + ', "MIN":' + str(valueYMIN) + ', "RCH":' + str(fit_param[1]) + '}'
        print(OMR)
        print(fit_param)
        fig=plt.figure(figsize=(15,8))
        plt.scatter(valueOfX, valueOfY, label='data', color='blue')
        plt.plot(valueOfX, baseFunction(valueOfX, *fit_param), 'r-',label='fit: a='+str(round(fit_param[0],3))+', b='+str(round(fit_param[1],3))+', c='+str(round(fit_param[2],3))+'')
        plt.legend(fontsize='xx-large')
        plt.show()
else:
        print(myString1)
        print("null")
