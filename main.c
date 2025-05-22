#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "choice.h"

#define MAX 100

void inputRumah(Rumah *r)
{
    printf("Nama\t\t\t: ");
    scanf(" %[^\n]", r->nama);
    printf("Apakah air berbau? (1 = Ya, 0 = Tidak): ");
    scanf(" %d", &r->bau);
    printf("pH air\t\t\t: ");
    scanf(" %f", &r->ph);
    printf("Kekeruhan air (NTU)\t: ");
    scanf(" %d", &r->kekeruhan);
}

void menambahkanRumah(Rumah *rumah, int *jumlah_rumah)
{
    printf("\n\nJumlah data rumah saat ini: %d", *jumlah_rumah);

    int n;
    printf("\nBerapa rumah yang ingin diinput? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("\n[Rumah %d]\n", *jumlah_rumah + 1);
        inputRumah(&rumah[*jumlah_rumah]);
        (*jumlah_rumah)++;
    }
}

int main()
{
    printf("\n======= Sistem Evaluasi Konsumsi & Kualitas Air Rumah Tangga =======\n");

    bool cek = true;
    Rumah rumah[MAX];
    int jumlah_rumah = 0;

    while (cek)
    {
        int choice;
        printf("\nApa yang ingin dilakukan?\n1. Tambah Rumah\n2. Evaluasi Air\n3. Proses Filter Air\n4. Tampilkan Semua Data\n0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            cek = false;
            continue;
        }

        switch (choice)
        {
        case 1:
            menambahkanRumah(rumah, &jumlah_rumah);
            break;
        case 2:
            if (jumlah_rumah == 0)
            {
                printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
            }
            else
            {
                for (int i = 0; i < jumlah_rumah; i++)
                {
                    evaluasiAir(&rumah[i]);
                    printf("\n[Rumah: %s]\n", rumah[i].nama);
                    printf("PH: %.1f | Bau: %s | Kekeruhan: %d NTU\n", rumah[i].ph, rumah[i].bau ? "Ya" : "Tidak", rumah[i].kekeruhan);
                    printf("Status Sanitasi: %s\n", sanitasiToStr(rumah[i].sanitasi));
                }
            }
            break;

        case 3:
            if (jumlah_rumah == 0)
            {
                printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
            }
            else
            {
                for (int i = 0; i < jumlah_rumah; i++)
                {
                    printf("a");
                }
            }
            break;

        case 4:
            if (jumlah_rumah == 0)
            {
                printf("\nBelum ada data rumah. Silakan input terlebih dahulu.\n");
            }
            else
            {
                for (int i = 0; i < jumlah_rumah; i++)
                {
                    printf("\n--- Rumah %d ---\n", i + 1);
                    printf("Nama: %s\n", rumah[i].nama);
                    printf("PH: %.1f | Bau: %d | Kekeruhan: %d\n", rumah[i].ph, rumah[i].bau, rumah[i].kekeruhan);
                }
            }
            break;

        default:
            printf("\nPilihan tidak valid.\n");
        }
    }

    printf("\nTerima kasih!.\n");
    return 0;
}
