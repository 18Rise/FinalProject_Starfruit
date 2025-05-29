// main.c
#include <stdio.h>
#include <string.h>
#include "choice.h"

#define MAX 100

void inputRumah(Rumah *r_ptr) { // Anda menggunakan -> di sini, saya akan biarkan.
                               // Jika ingin konsisten (*r_ptr).nama, silakan disesuaikan.
    printf("Nama\t\t\t: ");
    // fgets untuk input nama
    if (fgets(r_ptr->nama, sizeof(r_ptr->nama), stdin) != NULL) {
        size_t len = strlen(r_ptr->nama);
        if (len > 0 && r_ptr->nama[len - 1] == '\n') {
            r_ptr->nama[len - 1] = '\0';
        }
    } else {
        strcpy(r_ptr->nama, "Rumah Misterius"); // Default jika fgets gagal
    }
    // Tidak perlu clear buffer di sini jika fgets adalah yang pertama dipanggil dalam fungsi ini setelah clear buffer di main

    printf("Apakah air berbau? (1 = Ya, 0 = Tidak): ");
    scanf("%d", &r_ptr->bau);
    int ch_bau;
    while ((ch_bau = getchar()) != '\n' && ch_bau != EOF);

    printf("pH air\t\t\t: ");
    scanf("%f", &r_ptr->ph);
    int ch_ph;
    while ((ch_ph = getchar()) != '\n' && ch_ph != EOF);

    printf("Kekeruhan air (NTU)\t: ");
    scanf("%d", &r_ptr->kekeruhan);
    int ch_kekeruhan;
    while ((ch_kekeruhan = getchar()) != '\n' && ch_kekeruhan != EOF);

    r_ptr->poin_insentif = 0;
    r_ptr->aksiFilterTelahDigunakan = 0; // <<< INISIALISASI PENGHITUNG FILTER
}

void menambahkanRumah(Rumah daftar_rumah[], int *jumlah_rumah_ptr) {
    int n;
    printf("\nJumlah data rumah saat ini: %d", *jumlah_rumah_ptr);
    printf("\nBerapa rumah yang ingin diinput? ");
    if (scanf("%d", &n) != 1) { // Periksa return value scanf
        printf("Input jumlah tidak valid.\n");
        int c; while((c=getchar())!='\n' && c!=EOF); // clear buffer
        return;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer setelah scanf %d

    if (n <= 0) { // Pindahkan validasi ini setelah scanf dan clear buffer
        printf("Jumlah rumah yang diinput harus positif.\n");
        return;
    }
    if (*jumlah_rumah_ptr + n > MAX) {
        printf("Kapasitas penyimpanan data rumah tidak mencukupi untuk %d rumah baru.\n", n);
        printf("Sisa kapasitas: %d\n", MAX - *jumlah_rumah_ptr);
        return;
    }

    for (int i = 0; i < n; i++) {
        // Pengecekan if (*jumlah_rumah_ptr < MAX) di sini redundant karena sudah dicek di atas
        printf("\n[Rumah %d]\n", *jumlah_rumah_ptr + 1);
        inputRumah(&daftar_rumah[*jumlah_rumah_ptr]);
        (*jumlah_rumah_ptr)++;
    }
}

int main() {
    printf("\n======= Sistem Evaluasi Konsumsi & Kualitas Air Rumah Tangga =======\n");
    int program_berjalan = 1;
    Rumah data_semua_rumah[MAX];
    int jumlah_rumah_saat_ini = 0;
    int ch; // Deklarasi ch di scope yang lebih luas jika dipakai di beberapa tempat

    while (program_berjalan) {
        int pilihan_menu;
        printf("\nApa yang ingin dilakukan?\n");
        printf("1. Tambah Rumah\n");
        printf("2. Evaluasi Kualitas Air Semua Rumah\n");
        printf("3. Proses Filter Air (Pilih Rumah)\n");
        printf("4. Tampilkan Semua Data Rumah\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilihan_menu) != 1) {
            printf("Input tidak valid. Harap masukkan angka.\n");
            while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer
            continue; // Kembali ke awal loop menu utama
        }
        while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer setelah scanf yang berhasil

        switch (pilihan_menu) {
            case 0:
                program_berjalan = 0;
                break;

            case 1:
                menambahkanRumah(data_semua_rumah, &jumlah_rumah_saat_ini);
                break;

            case 2:
                if (jumlah_rumah_saat_ini == 0) {
                    printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
                } else {
                    printf("\n--- Hasil Evaluasi Kualitas Air ---\n");
                    for (int i = 0; i < jumlah_rumah_saat_ini; i++) {
                        evaluasiAir(&data_semua_rumah[i]); // Menggunakan -> atau (*). akan dihandle di evaluasiAir
                        printf("\n[Rumah: %s]\n", data_semua_rumah[i].nama);
                        printf("  PH: %.1f | Bau: %s | Kekeruhan: %d NTU\n",
                               data_semua_rumah[i].ph,
                               data_semua_rumah[i].bau == 1 ? "Ya" : "Tidak",
                               data_semua_rumah[i].kekeruhan);
                        printf("  Status Sanitasi: %s\n", sanitasiToStr(data_semua_rumah[i].sanitasi));
                    }
                }
                break;

            case 3:
                if (jumlah_rumah_saat_ini == 0) {
                    printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
                } else {
                    int nomor_rumah_untuk_filter;
                    int indeks_dipilih = -1;

                    if (jumlah_rumah_saat_ini == 1) {
                        // Jika hanya satu rumah, cek dulu kesempatannya
                        if (data_semua_rumah[0].aksiFilterTelahDigunakan >= 3) {
                            printf("\nRumah %s sudah mencapai batas maksimal (3 kali) tindakan filter.\n", data_semua_rumah[0].nama);
                        } else {
                            printf("\nMemproses filter untuk satu-satunya rumah: %s (Sisa kesempatan: %d).\n", 
                                   data_semua_rumah[0].nama, 
                                   3 - data_semua_rumah[0].aksiFilterTelahDigunakan);
                            indeks_dipilih = 0;
                        }
                    } else {
                        printf("\n--- Pilih Rumah untuk Difilter ---\n");
                        for (int i = 0; i < jumlah_rumah_saat_ini; i++) {
                            printf("%d. %s (Telah digunakan: %d dari 3 kesempatan filter)\n", 
                                   i + 1, 
                                   data_semua_rumah[i].nama, 
                                   data_semua_rumah[i].aksiFilterTelahDigunakan);
                        }
                        printf("Masukkan nomor rumah (1-%d): ", jumlah_rumah_saat_ini);
                        
                        while (1) {
                            if (scanf("%d", &nomor_rumah_untuk_filter) == 1 &&
                                nomor_rumah_untuk_filter >= 1 && nomor_rumah_untuk_filter <= jumlah_rumah_saat_ini) {
                                indeks_dipilih = nomor_rumah_untuk_filter - 1;
                                // Cek apakah rumah yang dipilih sudah habis kesempatannya
                                if (data_semua_rumah[indeks_dipilih].aksiFilterTelahDigunakan >= 3) {
                                    printf("\nRumah %s sudah mencapai batas maksimal (3 kali) tindakan filter. Pilih rumah lain atau kembali.\n", data_semua_rumah[indeks_dipilih].nama);
                                    indeks_dipilih = -1; // Reset agar tidak diproses, dan loop minta input lagi
                                    // Atau bisa langsung break dan tidak memproses, tergantung alur yang diinginkan
                                    // Untuk sekarang, kita biarkan user memilih lagi. Atau tampilkan menu lagi.
                                    // Untuk simplicity, kita set indeks_dipilih = -1 dan user harus input lagi.
                                    // Sebaiknya, setelah pesan ini, loop input di-break dan kembali ke menu utama atau tawarkan input ulang.
                                    // Mari kita buat agar loop input berlanjut.
                                } else {
                                    break; // Pilihan valid dan masih ada kesempatan
                                }
                            } else {
                                printf("Input tidak valid. Ulangi.\n");
                            }
                            while ((ch = getchar()) != '\n' && ch != EOF); // Selalu clear buffer setelah scanf di loop
                            printf("Masukkan nomor rumah (1-%d): ", jumlah_rumah_saat_ini); // Minta input lagi
                        }
                        while ((ch = getchar()) != '\n' && ch != EOF); // Clear buffer setelah scanf nomor rumah yang berhasil
                    }

                    if (indeks_dipilih != -1) { // Hanya proses jika rumah valid dipilih DAN masih ada kesempatan
                        printf("\nAnda memilih untuk memfilter Rumah: %s\n", data_semua_rumah[indeks_dipilih].nama);
                        prosesFilter(&data_semua_rumah[indeks_dipilih]);
                        evaluasiAir(&data_semua_rumah[indeks_dipilih]);

                        printf("\nStatus Air Rumah %s Setelah Filter:\n", data_semua_rumah[indeks_dipilih].nama);
                        printf("  PH: %.1f | Bau: %s | Kekeruhan: %d NTU\n",
                               data_semua_rumah[indeks_dipilih].ph,
                               data_semua_rumah[indeks_dipilih].bau == 1 ? "Ya" : "Tidak",
                               data_semua_rumah[indeks_dipilih].kekeruhan);
                        printf("  Status Sanitasi Baru: %s\n", sanitasiToStr(data_semua_rumah[indeks_dipilih].sanitasi));
                        printf("  Total aksi filter digunakan untuk rumah ini: %d\n", data_semua_rumah[indeks_dipilih].aksiFilterTelahDigunakan);
                    }
                }
                break;

            case 4:
                if (jumlah_rumah_saat_ini == 0) {
                    printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
                } else {
                    printf("\n--- Semua Data Rumah Saat Ini ---\n");
                    for (int i = 0; i < jumlah_rumah_saat_ini; i++) {
                        evaluasiAir(&data_semua_rumah[i]);
                        printf("\n--- Rumah %d ---\n", i + 1);
                        printf("Nama: %s\n", data_semua_rumah[i].nama);
                        printf("PH: %.1f\n", data_semua_rumah[i].ph);
                        printf("Bau: %s (%d)\n", data_semua_rumah[i].bau == 1 ? "Ya" : "Tidak", data_semua_rumah[i].bau);
                        printf("Kekeruhan: %d NTU\n", data_semua_rumah[i].kekeruhan);
                        printf("Status Sanitasi: %s\n", sanitasiToStr(data_semua_rumah[i].sanitasi));
                        printf("Aksi filter telah digunakan: %d dari 3\n", data_semua_rumah[i].aksiFilterTelahDigunakan);
                    }
                }
                break;

            default:
                printf("\nPilihan tidak valid.\n");
                break;
        }
    }

    printf("\nTerima kasih telah menggunakan sistem ini!\n");
    return 0;
    }