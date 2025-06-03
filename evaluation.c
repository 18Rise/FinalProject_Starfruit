#include "choice.h"
#include <stdio.h>

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
}