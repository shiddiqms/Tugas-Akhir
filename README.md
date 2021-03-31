# Tugas-Akhir
Melakukan efisiensi AC (air conditioner) dengan menggunakan PMV (predicted mean vote)berbasis teknologi IoT (internet of things)

File Terdiri dari file node-red, grafana dan file python

dalam menghitung PMV digunakan library pythermalcomfort bisa didapatkan dari https://pypi.org/project/pythermalcomfort/

data diambil dari sensor DHT 22 dan PZEM-004T dengan mikrokontroler wemos d1 mini, untuk mengirimkan perintah ke AC digunakan LED infrared

Kontrol AC dimulai dengan melakukan training data terus menggunakan ANN dan hasil training ini akan digunakan untuk mendapatkan DC (duty cycle) untuk AC

UI kontrol dalam melakukan efisiensi energi AC dengan node-red dashboard UI dan untuk monitoring data digunakan node-red dashboard UI dan Grafana
berikut ialah flowchart node-red dan UI node red

![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/Flowchart.png)
![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/UI.png)

UI grafana

![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/Grafana.PNG)

Data Hasil Kontrol Kontrol AC

![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/Temperature%26Humidity.png)
![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/PMV.png)
![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/Power.png)

