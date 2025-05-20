#ifndef CHOICE_H
#define CHOICE_H

typedef enum
{
    HEMAT,
    NORMAL,
    BOROS
} KategoriAir;

typedef enum
{
    BURUK,
    SEDANG,
    BAIK
} StatusSanitasi;

typedef struct
{
    char nama[30];
    int konsumsi_air;
    int bau;
    float ph;
    int kekeruhan;
    KategoriAir kategori;
    StatusSanitasi sanitasi;
    int poin_insentif;
} Rumah;

void evaluasiKonsumsi(Rumah *r);
int hitungPoin(KategoriAir kategori);
void evaluasiSanitasi(Rumah *r);

#endif
