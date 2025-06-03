#include <stdio.h>
#include <string.h>
#include "choice.h"

#define MAX 100

void beriPoinInsentifAwal(Rumah *r)
{
    evaluasiAir(r);
    if (r->sanitasi == BAIK)
    {
        r->poin_insentif += 50;
    }
    else if (r->sanitasi == SEDANG)
    {
        r->poin_insentif += 20;
    }
    printf("Poin insentif awal untuk rumah %s: %d\n", r->nama, r->poin_insentif);
}

void updatePoinSetelahFilter(Rumah *r, StatusSanitasi status_sebelum, int filter_digunakan_sebelum_sesi)
{
    evaluasiAir(r);
    StatusSanitasi status_sesudah = r->sanitasi;
    int poin_tambahan_sesi_ini = 0;
    int filter_dilakukan_di_sesi_ini = r->aksiFilterTelahDigunakan - filter_digunakan_sebelum_sesi;

    if (filter_dilakukan_di_sesi_ini > 0)
    {
        if (status_sebelum == BURUK && status_sesudah == BAIK)
        {
            poin_tambahan_sesi_ini += 75;
        }
        else if (status_sebelum == BURUK && status_sesudah == SEDANG)
        {
            poin_tambahan_sesi_ini += 30;
        }
        else if (status_sebelum == SEDANG && status_sesudah == BAIK)
        {
            poin_tambahan_sesi_ini += 40;
        }

        if (status_sesudah == BAIK && r->aksiFilterTelahDigunakan <= 2)
        {
            poin_tambahan_sesi_ini += 15;
        }
    }

    if (poin_tambahan_sesi_ini > 0)
    {
        r->poin_insentif += poin_tambahan_sesi_ini;
        printf("Selamat! Rumah %s mendapatkan %d poin tambahan dari filter. Total poin: %d\n", r->nama, poin_tambahan_sesi_ini, r->poin_insentif);
    }
    else if (filter_dilakukan_di_sesi_ini > 0)
    {
        printf("Filter dilakukan namun tidak ada peningkatan status sanitasi yang memberikan poin tambahan kali ini untuk rumah %s.\n", r->nama);
    }
}

void inputRumah(Rumah *r_ptr)
{
    printf("Nama\t\t\t: ");
    if (fgets(r_ptr->nama, sizeof(r_ptr->nama), stdin) != NULL)
    {
        size_t len = strlen(r_ptr->nama);
        if (len > 0 && r_ptr->nama[len - 1] == '\n')
        {
            r_ptr->nama[len - 1] = '\0';
        }
    }
    else
    {
        strcpy(r_ptr->nama, "Rumah Misterius");
    }

    printf("Apakah air berbau? (1 = Ya, 0 = Tidak): ");
    scanf("%d", &r_ptr->bau);
    int ch_bau;
    while ((ch_bau = getchar()) != '\n' && ch_bau != EOF)
        ;

    printf("pH air\t\t\t: ");
    scanf("%f", &r_ptr->ph);
    int ch_ph;
    while ((ch_ph = getchar()) != '\n' && ch_ph != EOF)
        ;

    printf("Kekeruhan air (NTU)\t: ");
    scanf("%d", &r_ptr->kekeruhan);
    int ch_kekeruhan;
    while ((ch_kekeruhan = getchar()) != '\n' && ch_kekeruhan != EOF)
        ;

    r_ptr->poin_insentif = 0;
    r_ptr->aksiFilterTelahDigunakan = 0;
}

void menambahkanRumah(Rumah daftar_rumah[], int *jumlah_rumah_ptr)
{
    int n;
    printf("\nJumlah data rumah saat ini: %d", *jumlah_rumah_ptr);
    printf("\nBerapa rumah yang ingin diinput? ");
    if (scanf("%d", &n) != 1)
    {
        printf("Input jumlah tidak valid.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        return;
    }
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
        ;

    if (n <= 0)
    {
        printf("Jumlah rumah yang diinput harus positif.\n");
        return;
    }
    if (*jumlah_rumah_ptr + n > MAX)
    {
        printf("Kapasitas penyimpanan data rumah tidak mencukupi untuk %d rumah baru.\n", n);
        printf("Sisa kapasitas: %d\n", MAX - *jumlah_rumah_ptr);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\n[Rumah %d]\n", *jumlah_rumah_ptr + 1);
        inputRumah(&daftar_rumah[*jumlah_rumah_ptr]);
        evaluasiAir(&daftar_rumah[*jumlah_rumah_ptr]);
        beriPoinInsentifAwal(&daftar_rumah[*jumlah_rumah_ptr]);
        (*jumlah_rumah_ptr)++;
    }
}

int main()
{
    printf("\n======= Sistem Evaluasi Konsumsi & Kualitas Air Rumah Tangga =======\n");
    int program_berjalan = 1;
    Rumah data_semua_rumah[MAX];
    int jumlah_rumah_saat_ini = 0;
    int ch;

    while (program_berjalan)
    {
        int pilihan_menu;
        printf("\nApa yang ingin dilakukan?\n");
        printf("1. Tambah Rumah\n");
        printf("2. Evaluasi Kualitas Air Semua Rumah\n");
        printf("3. Proses Filter Air (Pilih Rumah)\n");
        printf("4. Tampilkan Semua Data Rumah\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilihan_menu) != 1)
        {
            printf("Input tidak valid. Harap masukkan angka.\n");
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            continue;
        }
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        switch (pilihan_menu)
        {
        case 0:
            program_berjalan = 0;
            break;

        case 1:
            menambahkanRumah(data_semua_rumah, &jumlah_rumah_saat_ini);
            break;

        case 2:
            if (jumlah_rumah_saat_ini == 0)
            {
                printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
            }
            else
            {
                printf("\n--- Hasil Evaluasi Kualitas Air ---\n");
                for (int i = 0; i < jumlah_rumah_saat_ini; i++)
                {
                    evaluasiAir(&data_semua_rumah[i]);
                    printf("\n[Rumah: %s]\n", data_semua_rumah[i].nama);
                    printf("  PH: %.1f | Bau: %s | Kekeruhan: %d NTU\n",
                           data_semua_rumah[i].ph,
                           data_semua_rumah[i].bau == 1 ? "Ya" : "Tidak",
                           data_semua_rumah[i].kekeruhan);
                    printf("  Status Sanitasi: %s\n", sanitasiToStr(data_semua_rumah[i].sanitasi));
                    printf("  Poin Insentif: %d\n", data_semua_rumah[i].poin_insentif);
                }
            }
            break;

        case 3:
            if (jumlah_rumah_saat_ini == 0)
            {
                printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
            }
            else
            {
                int nomor_rumah_untuk_filter;
                int indeks_dipilih = -1;

                if (jumlah_rumah_saat_ini == 1)
                {
                    if (data_semua_rumah[0].aksiFilterTelahDigunakan >= 3)
                    {
                        printf("\nRumah %s sudah mencapai batas maksimal (3 kali) tindakan filter.\n", data_semua_rumah[0].nama);
                    }
                    else
                    {
                        printf("\nMemproses filter untuk satu-satunya rumah: %s (Sisa kesempatan: %d).\n",
                               data_semua_rumah[0].nama,
                               3 - data_semua_rumah[0].aksiFilterTelahDigunakan);
                        indeks_dipilih = 0;
                    }
                }
                else
                {
                    printf("\n--- Pilih Rumah untuk Difilter ---\n");
                    for (int i = 0; i < jumlah_rumah_saat_ini; i++)
                    {
                        printf("%d. %s (Telah digunakan: %d dari 3 kesempatan filter, Poin: %d)\n",
                               i + 1,
                               data_semua_rumah[i].nama,
                               data_semua_rumah[i].aksiFilterTelahDigunakan,
                               data_semua_rumah[i].poin_insentif);
                    }
                    printf("Masukkan nomor rumah (1-%d): ", jumlah_rumah_saat_ini);

                    while (1)
                    {
                        if (scanf("%d", &nomor_rumah_untuk_filter) == 1 &&
                            nomor_rumah_untuk_filter >= 1 && nomor_rumah_untuk_filter <= jumlah_rumah_saat_ini)
                        {
                            indeks_dipilih = nomor_rumah_untuk_filter - 1;
                            if (data_semua_rumah[indeks_dipilih].aksiFilterTelahDigunakan >= 3)
                            {
                                printf("\nRumah %s sudah mencapai batas maksimal (3 kali) tindakan filter. Pilih rumah lain.\n", data_semua_rumah[indeks_dipilih].nama);
                                indeks_dipilih = -1;
                                printf("Masukkan nomor rumah (1-%d): ", jumlah_rumah_saat_ini);
                            }
                            else
                            {
                                break;
                            }
                        }
                        else
                        {
                            printf("Input tidak valid. Ulangi.\n");
                            printf("Masukkan nomor rumah (1-%d): ", jumlah_rumah_saat_ini); // Minta input lagi
                        }
                        while ((ch = getchar()) != '\n' && ch != EOF)
                            ;
                    }
                    while ((ch = getchar()) != '\n' && ch != EOF)
                        ;
                }

                if (indeks_dipilih != -1)
                {
                    printf("\nAnda memilih untuk memfilter Rumah: %s\n", data_semua_rumah[indeks_dipilih].nama);

                    StatusSanitasi status_sebelum_filter = data_semua_rumah[indeks_dipilih].sanitasi;
                    int filter_digunakan_sebelum_sesi_ini = data_semua_rumah[indeks_dipilih].aksiFilterTelahDigunakan;

                    prosesFilter(&data_semua_rumah[indeks_dipilih]);

                    evaluasiAir(&data_semua_rumah[indeks_dipilih]);

                    updatePoinSetelahFilter(&data_semua_rumah[indeks_dipilih], status_sebelum_filter, filter_digunakan_sebelum_sesi_ini);

                    printf("\nStatus Air Rumah %s Setelah Sesi Filter:\n", data_semua_rumah[indeks_dipilih].nama);
                    printf("  PH: %.1f | Bau: %s | Kekeruhan: %d NTU\n",
                           data_semua_rumah[indeks_dipilih].ph,
                           data_semua_rumah[indeks_dipilih].bau == 1 ? "Ya" : "Tidak",
                           data_semua_rumah[indeks_dipilih].kekeruhan);
                    printf("  Status Sanitasi Baru: %s\n", sanitasiToStr(data_semua_rumah[indeks_dipilih].sanitasi));
                    printf("  Poin Insentif Saat Ini: %d\n", data_semua_rumah[indeks_dipilih].poin_insentif);
                    printf("  Total aksi filter digunakan untuk rumah ini: %d\n", data_semua_rumah[indeks_dipilih].aksiFilterTelahDigunakan);
                }
            }
            break;

        case 4:
            if (jumlah_rumah_saat_ini == 0)
            {
                printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
            }
            else
            {
                printf("\n--- Semua Data Rumah Saat Ini ---\n");
                for (int i = 0; i < jumlah_rumah_saat_ini; i++)
                {
                    evaluasiAir(&data_semua_rumah[i]);
                    printf("\n--- Rumah %d ---\n", i + 1);
                    printf("Nama: %s\n", data_semua_rumah[i].nama);
                    printf("PH: %.1f\n", data_semua_rumah[i].ph);
                    printf("Bau: %s (%d)\n", data_semua_rumah[i].bau == 1 ? "Ya" : "Tidak", data_semua_rumah[i].bau);
                    printf("Kekeruhan: %d NTU\n", data_semua_rumah[i].kekeruhan);
                    printf("Status Sanitasi: %s\n", sanitasiToStr(data_semua_rumah[i].sanitasi));
                    printf("Poin Insentif: %d\n", data_semua_rumah[i].poin_insentif);
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