#include <stdio.h>
#include "choice.h"

void prosesFilter(Rumah *r)
{
    int pilihan_filter_pengguna;
    int tindakan_dilakukan_sesi_ini = 0;

    printf("\n--- Memulai Proses Filter Interaktif untuk Rumah %s ---\n", (*r).nama);

    do
    {
        printf("\nKualitas Air Rumah %s Saat Ini:\n", (*r).nama);
        printf("  PH: %.1f\n", (*r).ph);
        printf("  Bau: %s\n", (*r).bau == 1 ? "Ya" : "Tidak");
        printf("  Kekeruhan: %d NTU\n", (*r).kekeruhan);

        printf("  (Rumah ini telah menggunakan %d dari 3 total kesempatan filter)\n", (*r).aksiFilterTelahDigunakan);

        if ((*r).aksiFilterTelahDigunakan >= 3)
        {
            printf("\nBatas filter (3 kali) untuk rumah %s telah habis.\n", (*r).nama);
            printf("Sesi filter untuk rumah ini akan diakhiri. Silakan pilih 0 untuk kembali.\n");
        }

        printf("\nPilihan Filter yang Tersedia:\n");
        if ((*r).aksiFilterTelahDigunakan < 3)
        {
            printf("  1. Proses Filter Bau\n");
            printf("  2. Proses Filter pH\n");
            printf("  3. Proses Filter Kekeruhan\n");
        }
        printf("  0. Selesai Filter untuk Rumah Ini (Kembali ke Menu Utama)\n");
        printf("Pilih tindakan: ");

        if (scanf("%d", &pilihan_filter_pengguna) != 1)
        {
            printf("Input tidak valid. Harap masukkan angka.\n");
            int c_clear;
            while ((c_clear = getchar()) != '\n' && c_clear != EOF)
                ;
            continue;
        }
        int ch_clear;
        while ((ch_clear = getchar()) != '\n' && ch_clear != EOF)
            ;

        if ((*r).aksiFilterTelahDigunakan >= 3 && pilihan_filter_pengguna != 0)
        {
            printf("Pilihan filter tidak tersedia karena batas 3 kali telah tercapai. Pilih 0 untuk kembali.\n");
            continue;
        }

        switch (pilihan_filter_pengguna)
        {
        case 1: // Proses Filter Bau
            if ((*r).aksiFilterTelahDigunakan < 3)
            {
                if ((*r).bau == 1)
                {
                    printf("  Memproses filter untuk menghilangkan bau...\n");
                    (*r).bau = 0;
                    printf("  Bau pada air berhasil dihilangkan.\n");
                    tindakan_dilakukan_sesi_ini = 1;
                    (*r).aksiFilterTelahDigunakan++;
                }
                else
                {
                    printf("  Air sudah tidak berbau. Tidak perlu tindakan.\n");
                }
            }
            else
            {
                printf("  Pilihan filter ini tidak tersedia karena batas 3 kali tindakan telah tercapai.\n");
            }
            break;
        case 2: // Proses Filter pH
            if ((*r).aksiFilterTelahDigunakan < 3)
            {
                int ph_berubah = 0;
                if ((*r).ph < 6.5f)
                {
                    printf("  Memproses filter pH untuk menaikkan pH (dari %.1f)...\n", (*r).ph);
                    (*r).ph += 1.0f;
                    if ((*r).ph > 14.0f)
                        (*r).ph = 14.0f;
                    printf("  pH air disesuaikan menjadi %.1f.\n", (*r).ph);
                    ph_berubah = 1;
                }
                else if ((*r).ph > 8.5f)
                {
                    printf("  Memproses filter pH untuk menurunkan pH (dari %.1f)...\n", (*r).ph);
                    (*r).ph -= 1.0f;
                    if ((*r).ph < 0.0f)
                        (*r).ph = 0.0f;
                    printf("  pH air disesuaikan menjadi %.1f.\n", (*r).ph);
                    ph_berubah = 1;
                }
                else
                {
                    printf("  pH air saat ini (%.1f) sudah ideal. Tidak perlu tindakan.\n", (*r).ph);
                }

                if (ph_berubah)
                {
                    tindakan_dilakukan_sesi_ini = 1;
                    (*r).aksiFilterTelahDigunakan++;
                }
            }
            else
            {
                printf("  Pilihan filter ini tidak tersedia karena batas 3 kali tindakan telah tercapai.\n");
            }
            break;
        case 3: // Proses Filter Kekeruhan
            if ((*r).aksiFilterTelahDigunakan < 3)
            {
                int kekeruhan_berubah = 0;
                if ((*r).kekeruhan > 5)
                {
                    printf("  Memproses filter untuk mengurangi kekeruhan (dari %d NTU)...\n", (*r).kekeruhan);
                    int kekeruhan_awal = (*r).kekeruhan;
                    if ((*r).kekeruhan >= 10)
                    {
                        (*r).kekeruhan -= 3;
                    }
                    else if ((*r).kekeruhan >= 7)
                    {
                        (*r).kekeruhan -= 2;
                    }
                    else
                    {
                        (*r).kekeruhan -= 1;
                    }
                    if ((*r).kekeruhan < 0)
                        (*r).kekeruhan = 0;
                    printf("  Kekeruhan air disesuaikan menjadi %d NTU.\n", (*r).kekeruhan);

                    if ((*r).kekeruhan < kekeruhan_awal)
                    {
                        kekeruhan_berubah = 1;
                    }
                }
                else
                {
                    printf("  Kekeruhan air saat ini (%d NTU) sudah rendah. Tidak perlu tindakan.\n", (*r).kekeruhan);
                }

                if (kekeruhan_berubah)
                {
                    tindakan_dilakukan_sesi_ini = 1;
                    (*r).aksiFilterTelahDigunakan++;
                }
            }
            else
            {
                printf("  Pilihan filter ini tidak tersedia karena batas 3 kali tindakan telah tercapai.\n");
            }
            break;
        case 0:
            printf("  Menyelesaikan sesi filter untuk rumah %s dan kembali ke menu utama.\n", (*r).nama);
            break;
        default:
            printf("  Pilihan %d tidak valid. Silakan pilih angka sesuai menu.\n", pilihan_filter_pengguna);
        }

    } while (pilihan_filter_pengguna != 0 && (*r).aksiFilterTelahDigunakan < 3);

    if ((*r).aksiFilterTelahDigunakan >= 3 && pilihan_filter_pengguna != 0)
    {
        printf("\nSesi filter untuk rumah %s ini berakhir otomatis karena 3 kesempatan filter telah digunakan.\n", (*r).nama);
    }

    printf("\n--- Sesi Filter Interaktif Selesai untuk Rumah %s ---\n", (*r).nama);
    printf("Kualitas Air Akhir Rumah %s:\n", (*r).nama);
    printf("  PH: %.1f\n", (*r).ph);
    printf("  Bau: %s\n", (*r).bau == 1 ? "Ya" : "Tidak");
    printf("  Kekeruhan: %d NTU\n", (*r).kekeruhan);
    printf("  Total aksi filter yang telah digunakan untuk rumah ini secara keseluruhan: %d dari 3\n", (*r).aksiFilterTelahDigunakan);

    if (tindakan_dilakukan_sesi_ini == 1)
    {
        printf("Ada perubahan kualitas air di sesi ini.\n");
    }
    else
    {
        printf("Tidak ada perubahan kualitas air di sesi ini.\n");
    }
    printf("------------------------------------------------------------------\n");
}