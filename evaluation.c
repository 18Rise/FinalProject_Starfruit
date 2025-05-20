#include "choice.h"

typedef enum
{
    hemat,
    normal,
    boros
} Kategori;

typedef struct
{
    char nama[50];
    int pemakaian;
    Kategori kategori;
    int poin;
} Rumah;

void evaluation()
{
}