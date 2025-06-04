#include <stdio.h>
#include "choice.h"

void tampilkanStatistik(Rumah daftar[], int jumlah)
{
    if (jumlah == 0)
    {
        printf("Belum ada data rumah untuk ditampilkan.\n");
        return;
    }

    float total_ph = 0.0f;
    int total_kekeruhan = 0;
    int count_baik = 0, count_sedang = 0, count_buruk = 0;

    for (int i = 0; i < jumlah; i++)
    {
        evaluasiAir(&daftar[i]);
        total_ph += daftar[i].ph;
        total_kekeruhan += daftar[i].kekeruhan;
        switch (daftar[i].sanitasi)
        {
        case BAIK:
            count_baik++;
            break;
        case SEDANG:
            count_sedang++;
            break;
        case BURUK:
            count_buruk++;
            break;
        }
    }

    float rata_ph = total_ph / jumlah;
    float rata_kekeruhan = (float)total_kekeruhan / jumlah;

    printf("\n=== Statistik Kualitas Air Rumah Tangga ===\n");
    printf("Jumlah rumah terdata     : %d\n", jumlah);
    printf("Rata-rata pH             : %.2f\n", rata_ph);
    printf("Rata-rata kekeruhan (NTU): %.2f\n", rata_kekeruhan);
    printf("Status Sanitasi:\n");
    printf("  - BAIK   : %d rumah\n", count_baik);
    printf("  - SEDANG : %d rumah\n", count_sedang);
    printf("  - BURUK  : %d rumah\n", count_buruk);
}