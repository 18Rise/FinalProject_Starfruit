#include "choice.h"
<<<<<<< Updated upstream

void evaluasiKonsumsi(Rumah *r)
{
=======
#include <stdio.h>
#include <string.h>

const char *sanitasiToStr(StatusSanitasi s)
{
    switch (s)
    {
    case BAIK:
        return "BAIK";
    case SEDANG:
        return "SEDANG";
    case BURUK:
        return "BURUK";
    default:
        return "-";
    }
}

void evaluasiAir(Rumah *r)
{
    int masalah = 0;

    if (r->bau == 1)
    {
        masalah++;
    }

    if (r->ph < 6.5 || r->ph > 8.5)
    {
        masalah++;
    }

    if (r->kekeruhan > 5)
    {
        masalah++;
    }

    if (masalah == 0)
    {
        r->sanitasi = BAIK;
    }
    else if (masalah == 1)
    {
        r->sanitasi = SEDANG;
    }
    else
    {
        r->sanitasi = BURUK;
    }

    switch (r->sanitasi)
    {
    case BURUK:
        snprintf(r->catatan.rekomendasi, sizeof(r->catatan.rekomendasi),
                 "Perlu filter untuk pH, bau, atau kekeruhan.");
        break;
    case SEDANG:
        r->catatan.hariSejakFilter = 3;
        break;
    case BAIK:
        r->catatan.hariSejakFilter = 1;
        break;
    default:
        break;
    }
}

void beriRekomendasi(Rumah *r)
{
    printf("\n[Rekomendasi untuk Rumah %s]\n", r->nama);
    switch (r->sanitasi)
    {
    case BAIK:
        printf("Sanitasi sudah BAIK. Tidak perlu tindakan tambahan. Pertahankan kondisi air saat ini.\n");
        break;
    case SEDANG:
        printf("Sanitasi SEDANG. Disarankan melakukan 1 tindakan filter untuk mencapai sanitasi BAIK.\n");
        if (r->ph < 6.5 || r->ph > 8.5)
            printf("  - Pertimbangkan menyesuaikan pH air.\n");
        if (r->kekeruhan > 5)
            printf("  - Pertimbangkan mengurangi kekeruhan air.\n");
        if (r->bau)
            printf("  - Pertimbangkan menghilangkan bau dari air.\n");
        break;
    case BURUK:
        printf("Sanitasi BURUK. Segera lakukan filter pada beberapa aspek berikut:\n");
        if (r->ph < 6.5 || r->ph > 8.5)
            printf("  - pH air tidak ideal.\n");
        if (r->kekeruhan > 5)
            printf("  - Kekeruhan tinggi.\n");
        if (r->bau)
            printf("  - Air terdeteksi berbau.\n");
        break;
    default:
        printf("Status sanitasi tidak dikenali.\n");
        break;
    }
>>>>>>> Stashed changes
}