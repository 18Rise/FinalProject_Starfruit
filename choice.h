#ifndef CHOICE_H
#define CHOICE_H

typedef enum
{
    BURUK,
    SEDANG,
    BAIK
} StatusSanitasi;

typedef struct
{
    char nama[30];
    int bau;
    float ph;
    int kekeruhan;
    StatusSanitasi sanitasi;
    int poin_insentif;
    int aksiFilterTelahDigunakan;
} Rumah;

const char *sanitasiToStr(StatusSanitasi s);
void evaluasiAir(Rumah *r);
void prosesFilter(Rumah *r);

#endif