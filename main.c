#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "choice.h"

#define MAX 100

void inputRumah(Rumah *r)
{
    printf("Nama\t\t\t: ");
    scanf(" %[^\n]", r->nama);
    printf("Pemakaian air (L)\t: ");
    scanf("%d", &r->konsumsi_air);
    printf("Apakah air berbau? (1 = Ya, 0 = Tidak): ");
    scanf("%d", &r->bau);
    printf("pH air\t\t\t: ");
    scanf("%f", &r->ph);
    printf("Kekeruhan air (NTU)\t: ");
    scanf("%d", &r->kekeruhan);
}

int main()
{
    printf("Sistem Evaluasi Konsumsi & Kualitas Air Rumah Tangga\n");

    Rumah rumah[MAX];
    int jumlah_rumah = 0;
    char c;

    while (1)
    {
        printf("\nInput rumah baru? (Y/N): ");
        scanf(" %c", &c);
        getchar();

        if (c == 'Y' || c == 'y')
        {
            int n;
            printf("Berapa rumah yang ingin diinput? ");
            scanf("%d", &n);

            for (int i = 0; i < n; i++)
            {
                printf("\n[Rumah %d]\n", jumlah_rumah + 1);
                inputRumah(&rumah[jumlah_rumah]);
                jumlah_rumah++;
            }
        }
        else if (jumlah_rumah == 0)
        {
            printf("Belum ada data rumah. Silakan input terlebih dahulu.\n");
            continue;
        }

        int choice;
        printf("\nApa yang ingin dilakukan?\n1. Evaluasi Konsumsi\n2. Evaluasi Sanitasi\n3. Tampilkan Semua Data\n0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &choice);

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1:
            for (int i = 0; i < jumlah_rumah; i++)
            {
                evaluasiKonsumsi(&rumah[i]);
                printf("\n[Rumah: %s] Konsumsi: %dL, Kategori: %d, Poin: %d\n",
                       rumah[i].nama, rumah[i].konsumsi_air, rumah[i].kategori, rumah[i].poin_insentif);
            }
            break;

        case 2:
            for (int i = 0; i < jumlah_rumah; i++)
            {
                evaluasiSanitasi(&rumah[i]);
                printf("\n[Rumah: %s] PH: %.1f, Bau: %d, Kekeruhan: %d, Status: %d\n",
                       rumah[i].nama, rumah[i].ph, rumah[i].bau, rumah[i].kekeruhan, rumah[i].sanitasi);
            }
            break;

        case 3:
            for (int i = 0; i < jumlah_rumah; i++)
            {
                printf("\n--- Rumah %d ---\n", i + 1);
                printf("Nama: %s\n", rumah[i].nama);
                printf("Konsumsi: %d L\n", rumah[i].konsumsi_air);
                printf("PH: %.1f | Bau: %d | Kekeruhan: %d\n",
                       rumah[i].ph, rumah[i].bau, rumah[i].kekeruhan);
                printf("Kategori: %d | Status Sanitasi: %d | Poin: %d\n",
                       rumah[i].kategori, rumah[i].sanitasi, rumah[i].poin_insentif);
            }
            break;

        default:
            printf("Pilihan tidak valid.\n");
        }
    }

    printf("Program selesai.\n");
    return 0;
}
