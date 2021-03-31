# Tugas-Akhir
Melakukan efisiensi AC (air conditioner) dengan menggunakan PMV (predicted mean vote)berbasis teknologi IoT (internet of things)

Proyek tugas akhir ini sudah dapat :
> Melakukan efisiensi kontrol AC dengan berfokus pada kenyamanan termal (PMV)
> Melakukan kontrol AC dengan berfokus pada jumlah energy yang ingin disaving dengan mengatur DC (duty cycle) dari AC

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

Data Hasil Kontrol Kontrol AC dengan kontrol PMV dalam 3 kali pengulangan, (20 menit fase pengukuran keadaan termal ruangan, 1 jam waktu kontrol, dan 20 menit waktu istirahat AC dan pembelajaran model ANN)

![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/Temperature%26Humidity.png)
![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/PMV.png)
![](https://github.com/shiddiqms/Tugas-Akhir/blob/main/gambar/Power.png)

Didapatkan nilai PMV rata-rata selama fase kontrol cukup mendekati 0 yaitu sebesar -0.062 ini menunjukkan pada saat kontrol ruangan berada dalam kenyamanan termal yang sangat baik
