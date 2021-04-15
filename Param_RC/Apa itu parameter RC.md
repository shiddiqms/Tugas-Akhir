Parameter RC atau pada projek ini disebut sebagai parameter keadaan termal ruangan

intinya suatu parameter fisis dimana dapat menunjukkan keadaan termal dari suatu ruagan 

baca lebih lanjut mengenai pemodelan parameter ini di :

https://github.com/shiddiqms/Tugas-Akhir/blob/main/Param_RC/parameter%20keadaan%20termal%20ruangan%20(RC).pdf

Gimana si cara menghitung RC??

pertama ambil data raw dari temperatur dalam terdapat dalam folder data/raw/

>plot temperatur dalam terhadap waktu - untuk mengetahui apakah data temperatur ini benar apa tidak, sesuaikan dengan gambar pada folder raw
>pilih bagian temperatur mana yang ingin dilakukan plotting untuk mendapatkan RC 
>plot daya terhadap waktu (dari sesnor pzem) - untuk mengetahui secara persis kapan waktu kerja AC, ambil waktu hidup/dan mati AC berdasarkan pilihan awal temperatur sebagai t0 dan t1
>ambil temperatur maksimal, catat waktu temperatur sebagai t2
>ambil seluruh data temperatur dari t2 sampai t1 dalam suatu array
>plot RC dengan menggunakan kode python https://github.com/shiddiqms/Tugas-Akhir/blob/main/Param_RC/plotRC_manual.py 
>Selamat mencoba

Untuk menghitung RC secara otomatis pada projek ini silahkan pelajari langsung flow node-red utama :https://github.com/shiddiqms/Tugas-Akhir/blob/main/Flow%20Node-Red%20Final%20TA.json
