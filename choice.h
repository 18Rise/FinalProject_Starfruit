#ifndef CHOICE_H
#define CHOICE_H

typedef enum
{
    BURUK,
    SEDANG,
    BAIK
} StatusSanitasi;

typedef union
{
    char rekomendasi[100];
    int hariSejakFilter;
} CatatanRumah;

typedef struct
{
    char nama[30];
    int bau;
    float ph;
    int kekeruhan;
    StatusSanitasi sanitasi;
    int poin_insentif;
    int aksiFilterTelahDigunakan;
    CatatanRumah catatan;
} Rumah;

const char *sanitasiToStr(StatusSanitasi s);
void evaluasiAir(Rumah *r);
void prosesFilter(Rumah *r);
void beriRekomendasi(Rumah *r);
void tampilkanStatistik(Rumah daftar[], int jumlah);

#endif