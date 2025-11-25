#include<stdio.h>

int main (){

    int pilihan;
    int n;
    int p;

    do
    {   
        printf("------pilihan------\n");
        printf("1.simpan hasil olahan ke file binary\n");
        printf("2.menampilkan isi file binary sebanyak n kata(0<n<=25)\n");
        printf("3.keluar\n");
        printf("masukkan pilihan:");
        p=scanf("%d",&pilihan);

        if (p!=1)
        {
            printf("plihan tidak valid!\n");
            while (getchar() != '\n'); 
            continue;  
        }
        switch (pilihan)
        {
        case 1:
            simpan_ke_biner();
            break;
        case 2:
            input_lagi:
            printf("banyak kata yang ingin ditampilkan(n):");
            p=scanf("%d",&n);
            if (n<=0 || n>25 || p!=1)
            { printf("nilai n tidak valid!\n"); 
                while (getchar() != '\n');
                goto input_lagi; }
            else
            { ambil_dari_biner(n); }
                break;
        case 3:
            printf("anda keluar dari program\n"); break;
        default:
            printf("plihan tidak valid!\n"); 
        }
    } while (pilihan!=3);
    
    return 0;
}