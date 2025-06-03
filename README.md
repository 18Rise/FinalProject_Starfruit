# Final Project Kelompok Starfruit

| Nama                       | NPM        |
| -------------------------- | ---------- |
| Caesar Nur Falah Widiyanto | 2406487052 |
| Naziehan labieb            | 2406487102 |
| Satrio Atalla Rahardjo     | 2406413666 |
| YusrI Sukur                | 2406345305 |
| Zahir                      | 2406487084 |

## Tujuan Program

Program memungkinkan user untuk:

- Memasukkan data rumah: nama, dan data kualitas air (pH, kekeruhan, bau).
- Melakukan evaluasi air pada setiap rumah berdasarkan pH, kekeruhan, dan bau untuk menentukan status sanitasi (BAIK, SEDANG, BURUK).
- Melakukan filter air pada rumah yang dipilih oleh user untuk parameter pH, kekeruhan, dan bau, dengan batasan penggunaan filter per rumah.
- Menerapkan Sistem Poin Insentif:
  - Memberikan poin awal berdasarkan status sanitasi air saat rumah pertama kali didata.
  - Memberikan poin tambahan ketika tindakan filter berhasil meningkatkan status sanitasi air.
  - Memberikan poin bonus jika status sanitasi BAIK dicapai dengan jumlah penggunaan filter yang efisien.
  - Menampilkan total poin insentif yang dimiliki oleh setiap rumah.
- Menampilkan semua data rumah termasuk kualitas air terkini, status sanitasi, jumlah filter yang telah digunakan, dan total poin insentif.

## Cara menjalankan program

Compile

```bash
gcc main.c filter.c evaluation.c -o main.exe
```

Run

```bash
main.exe
```
