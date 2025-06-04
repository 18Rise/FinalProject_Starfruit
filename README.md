# Sistem Evaluasi Kualitas Air Rumah Tangga - Proyek Akhir Kelompok Starfruit

## Tim Pengembang

<<<<<<< Updated upstream
Anggota kelompok:
=======
| Nama                       | NPM        |
| -------------------------- | ---------- |
| Caesar Nur Falah Widiyanto | 2406487052 |
| Naziehan labieb            | 2406487102 |
| Satrio Atalla Rahardjo     | 2406413666 |
| Yusru Sukur                | 2406345305 |
| Zahir                      | 2406487084 |
>>>>>>> Stashed changes

## Deskripsi Proyek

Program ini adalah aplikasi berbasis konsol yang dirancang untuk mengelola dan mengevaluasi kualitas air rumah tangga. Pengguna dapat memasukkan data untuk beberapa rumah, menilai status sanitasi air berdasarkan parameter pH, kekeruhan, dan bau, serta mensimulasikan proses penyaringan air. Aspek kunci dari aplikasi ini adalah sistem poin insentif yang memberikan penghargaan atas peningkatan kualitas air dan penggunaan filter yang efisien.

<<<<<<< Updated upstream
- Memasukkan data rumah: nama, pemakaian air per bulan, dan data kualitas air.
- Melakukan evaluasi air pada setiap rumah berdasarkan pH, kekeruhan, dan bau.
- Melakukan filter air pada rumah yang dipilih oleh user.
=======
## Fitur Utama
>>>>>>> Stashed changes

Program ini memungkinkan pengguna untuk:

- **Input Data Rumah:** Memasukkan detail untuk setiap rumah, termasuk nama pemilik/rumah dan parameter kualitas air awal (pH, kekeruhan, bau).
- **Evaluasi Kualitas Air:** Secara otomatis menentukan status sanitasi air (BAIK, SEDANG, BURUK) untuk setiap rumah berdasarkan parameter yang dimasukkan.
- **Proses Filter Air Interaktif:**
  - Memungkinkan pengguna untuk memilih rumah tertentu dan menerapkan tindakan filter untuk memperbaiki parameter pH, mengurangi kekeruhan, atau menghilangkan bau.
  - Setiap rumah memiliki batasan jumlah penggunaan filter (maksimal 3 kali).
- **Sistem Poin Insentif:**
  - Memberikan poin insentif awal berdasarkan status sanitasi air saat data rumah pertama kali dimasukkan.
  - Memberikan poin tambahan ketika tindakan filter berhasil meningkatkan status sanitasi air (misalnya, dari BURUK menjadi SEDANG, atau SEDANG menjadi BAIK).
  - Memberikan poin bonus jika status sanitasi BAIK (Bagus) dicapai dengan jumlah penggunaan filter yang efisien (misalnya, dalam 1 atau 2 kali filter).
- **Tampilan Data Komprehensif:** Menampilkan daftar semua data rumah, termasuk kualitas air terkini, status sanitasi, jumlah filter yang telah digunakan, dan total poin insentif yang dimiliki.
- **Statistik Kualitas Air:** Menyajikan ringkasan statistik mengenai kualitas air dari seluruh rumah yang terdaftar, seperti rata-rata pH dan kekeruhan, serta jumlah rumah dalam setiap kategori status sanitasi.

## Struktur Proyek

Proyek ini terdiri dari beberapa file C dan satu file header:

- `main.c`: Berisi loop program utama, antarmuka pengguna (menu), dan logika utama untuk menambah rumah, mengelola alur program, serta mengkoordinasikan pemanggilan fungsi dari modul lain.
- `filter.c`: Mengimplementasikan fungsionalitas proses filter air secara interaktif, di mana pengguna dapat memilih jenis filter yang akan diterapkan pada rumah yang dipilih.
- `evaluation.c`: Berisi fungsi-fungsi untuk mengevaluasi kualitas air berdasarkan parameter yang ada, menentukan status sanitasi, dan memberikan rekomendasi terkait.
- `statistic.c`: Menyediakan fungsi untuk menghitung dan menampilkan data statistik terkait kualitas air dari semua rumah yang terdaftar.
- `choice.h`: File header yang mendefinisikan struktur data umum (seperti `Rumah`, `StatusSanitasi`, `CatatanRumah`) dan deklarasi fungsi (prototipe) yang digunakan di berbagai modul dalam proyek.

## Kompilasi Program

```bash
gcc main.c filter.c evaluation.c statistic.c -o main.exe
```

```bash
main.exe
```
