#Inisiasi modul-modul yang digunakan
import pandas as pd
import numpy as np

#baca csv
df = pd.read_csv(r'C:\Users\user\Documents\test\LearningFIX.csv', sep=',')

#milih nilai input dan output
TL = df['TL'].values
PMV = df['PMV'].values
RC = df['RC'].values
y = df[['DC']].values

#scale dua jenis input yang berbeda
from sklearn.preprocessing import MinMaxScaler
scaler = MinMaxScaler(feature_range=(0, 1))

TL2 = np.reshape(TL, (-1, 1))
TL_scaled = scaler.fit_transform(TL2)
PMV2 = np.reshape(PMV, (-1, 1))
PMV_scaled = scaler.fit_transform(PMV2)
RC2 = np.reshape(RC, (-1, 1))
RC_scaled = scaler.fit_transform(RC2)
DC_scaled = scaler.fit_transform(y)

inputTRC = np.hstack([TL_scaled, RC_scaled, PMV_scaled])

from sklearn.model_selection import train_test_split
# Assign the output to four variables
X_training, X_testing, Y_training, Y_testing = train_test_split(inputTRC, 
                                                                DC_scaled, 
                                                                test_size=0.30,
                                                                random_state=3)
X_training = inputTRC
Y_training = DC_scaled
#X_testing = inputTRC
#Y_testing = DC_scaled

#setting keras
import keras
from keras.models import Sequential
from keras.layers import *
from keras import optimizers
from keras.layers import Dense
from keras.models import load_model


#Define the model
model = load_model(r'C:\Users\user\Documents\test\modelANNFIX.h5')
model.compile(loss='binary_crossentropy', optimizer='adam')

#train the model
history = model.fit(
    X_training,
    Y_training,
    epochs=2200,
    shuffle=True,
    verbose=0
)

#print(" ")
#Evaluate the model
test_error_rate = model.evaluate(X_testing, Y_testing, verbose=0)
#print("The mean squared error (MSE) for the test data set is: {}".format(test_error_rate))

# Make a prediction with the neural network
Y_predicted1 = model.predict(X_testing)

# Unscale the data back to it's original units (dollars)
Y_predicted = scaler.inverse_transform(Y_predicted1)
Y_predicted0 = np.around(Y_predicted, decimals=0)

Y_real = scaler.inverse_transform(Y_testing)
Y_real0 = np.around(Y_real, decimals=0)

from sklearn.metrics import explained_variance_score
#from sklearn.metrics import max_error
from sklearn.metrics import r2_score

EVS = explained_variance_score(Y_real, Y_predicted0)
#max_error(Y_real, Y_predicted0)
R2 = r2_score(Y_real, Y_predicted0)

#print(" ")
#print(EVS)

#print(R2)
#print(" ")

# Grab just the first element of the first prediction
for i in range(5): 
    prediction = Y_predicted0[i][0] 
    real_DC = Y_real[i]

    #print("Prediksi DC - {}%".format(prediction) + "DC seharusnya - {}%".format(real_DC))

rangedata = len(Y_real)
bed0 = 0
bed1 = 0
bedmore2 = 0
for i in range(rangedata): 
    prediction = Y_predicted0[i][0] 
    real_DC = Y_real0[i][0]
    selisihDC = abs(prediction-real_DC)
    if selisihDC == 0:
        bed0 = bed0 + 1
    elif selisihDC > 0 and selisihDC <= 3:
        bed1 = bed1 + 1
    elif selisihDC > 3:
        bedmore2 = bedmore2 + 1

#print(" ")
akurasi = (bed0/rangedata)*100
bed1prs = (bed1/rangedata)*100
bed2prs = 100 - (akurasi + bed1prs)
#print("Selisih DC = 0%) = " + str(akurasi) +" % dari " + str(rangedata)+ " data")
#print("Selisih DC 2% = " + str(bed1prs) +" % dari " + str(rangedata)+ " data")
#print("Selisih DC lebih dari 2% = " + str(bed2prs) +" % dari " + str(rangedata)+ " data") 
#print("Akurasi = " + str(akurasi+bed1prs)+" %")

#print(" ")
#print(str(bed0) + " " + str(bed1) + " " + str(bedmore2))

ACC = akurasi+bed1prs

if ACC > 50 :
	model.save(r'C:\Users\user\Documents\test\modelANNFIX.h5')

buff = '{"ACC":'+ str(ACC) +'}'
print(buff)
#buat ngeload modelnya
# from keras.models import load_model
# (nama model) = load_model('nama file.h5')