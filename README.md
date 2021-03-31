# Tugas-Akhir
Melakukan efisiensi AC (air conditioner) dengan menggunakan PMV (predicted mean vote)berbasis teknologi IoT (internet of things)

File Terdiri dari file node-red, grafana dan file python

dalam menghitung PMV digunakan library pythermalcomfort bisa didapatkan dari https://pypi.org/project/pythermalcomfort/

data diambil dari sensor DHT 22 dan PZEM-004T dengan mikrokontroler wemos d1 mini, untuk mengirimkan perintah ke AC digunakan LED infrared

Kontrol AC dimulai dengan melakukan training data terus menggunakan ANN dan hasil training ini akan digunakan untuk mendapatkan DC (duty cycle) untuk AC
