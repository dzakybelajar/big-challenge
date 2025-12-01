#include<stdio.h>
#include "header.h"

int main (){

    int pilihan,n,p,i=0;
    char file[20];

    ulang:
    printf("masukkan nama file(txt):");
    scanf("%s",file);
    FILE *fp=fopen(file,"r");
    if (fp==NULL)
    {
        printf("file tidak ada isi atau file tidak ditemukan!\n");
        goto ulang;
    }
    int c=fgetc(fp);
    if (c==EOF)
    {
        printf("file tidak ada isi atau file tidak ditemukan!\n");
        fclose(fp); goto ulang;
    }
    rewind(fp);
    olah_teks(file);
    fclose(fp);

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
            simpan_ke_biner(); i=1;
            break;
        case 2:
            input_lagi:
            if (i!=1)
            { printf("simpan ke biner terlebih dahulu (pilihan 1)!\n"); break; }
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