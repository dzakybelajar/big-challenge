#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"

Abjad abjad[26];
Abjad abjd_baca[26];

void inisialisasi(){
for(int i=0;i<26;i++) {
    abjad[i].abjad = 'a' + i;
    abjad[i].jumlah_kata = 0;
    }
}

void olah_teks(char file[]){
    char buffer[500000];
    char gabung[500000]= "";
    gabung[0] = '\0';
    inisialisasi();

    FILE *ft = fopen(file, "r");
        if (ft == NULL) {
            printf("File tidak ditemukan!\n");
            return;
        }
    
    int url = 0;
    int title = 0;
    int body = 0;
    while(fgets(buffer, sizeof(buffer), ft) != 0){
        char *sisa = buffer;

        while(*sisa){
            //hapus semua sampai </url>
            if (!url && strncmp(sisa, "<url>", 5) == 0){
                url = 1;
                sisa += 5;
                continue;
            }
            if(url && strncmp(sisa, "</url>", 6) == 0){
                url = 0;
                sisa += 6;
                continue;
            }
            if (url){
                sisa++;
                continue;
            }
            //ambil substring antara <title>...</title>
            if (!title && strncmp(sisa, "<title>", 7) == 0){
                title = 1;
                sisa += 7;
                continue;
            }
            if(title && strncmp(sisa, "</title>", 8) == 0){
                title = 0;
                sisa += 8;
                strcat(gabung, " ");
                continue;
            }
            //ambil substring antara <body>...</body>
            if (!body && strncmp(sisa, "<body>", 6) == 0){
                body = 1;
                sisa += 6;
                continue;
            }
            if(body && strncmp(sisa, "</body>", 7) == 0){
                body = 0;
                sisa += 7;
                continue;
            }
            //gabungkan title dan body
            if (title || body){
                strncat(gabung, sisa, 1);
            }

            sisa++;
            
        }
    proses(gabung);
    buffer[0]='\0';
    gabung[0]='\0';
    }     
    fclose(ft); 
    pengurutan();
}

void proses(char teks[]){
    char bersih[500000];
    int m = 0;
    //ubah ke huruf kecil dan ganti yang bukan huruf menjadi spasi
    m = 0;
    bersih[m] = '\0';
    for(int i = 0; teks[i] != '\0'; i++){
        char ch = teks[i];

        if (ch >= 'A' && ch <= 'Z'){
            ch += 32;
        }

        if(ch >= 'a' && ch <= 'z'){
            bersih[m++] = ch;
        }  
        else {
            bersih[m++] = ' ';
        }
    }
    bersih[m] = '\0';
    //tokenisasi dan masukin ke stuct
    char *kata = strtok(bersih , " ");
        while(kata != NULL){
            if (kata[0] < 'a' || kata[0] > 'z'){
                kata = strtok(NULL, " ");
                continue;
            }
            int awal = kata[0] - 'a';
            int ketemu = 0;
            int n = abjad[awal].jumlah_kata;

            if(n == 0){
                strcpy(abjad[awal].daftar_kata[0].kata, kata);
                abjad[awal].daftar_kata[0].panjang_kata = strlen(kata);
                abjad[awal].daftar_kata[0].frekuensi = 1;
                abjad[awal].jumlah_kata = 1;

                kata = strtok(NULL, " ");
                continue;
            }

            else{
                for (int i = 0; i < n; i++){
                    if(strcmp(abjad[awal].daftar_kata[i].kata, kata)== 0){
                        abjad[awal].daftar_kata[i].frekuensi += 1;
                        ketemu = 1;
                        break;
                    }
                }

                if(!ketemu){
                    strcpy(abjad[awal].daftar_kata[n].kata, kata);
                    abjad[awal].daftar_kata[n].panjang_kata = strlen(kata);
                    abjad[awal].daftar_kata[n].frekuensi = 1;
                    abjad[awal].jumlah_kata++;
                }
            }
                    kata = strtok(NULL, " ");
        }
        bersih[0]='\0';
}

void pengurutan(){
    //urutin frekuensi
    for (int i = 0; i < 26; i++)
    {   
        for ( int n=0; n < abjad[i].jumlah_kata-1; n++)
        {
            for (int j=n+1; j > 0; j--)
            {  
                if (abjad[i].daftar_kata[j].frekuensi > abjad[i].daftar_kata[j-1].frekuensi )
                {
                    Kata temp = abjad[i].daftar_kata[j];
                    abjad[i].daftar_kata[j] = abjad[i].daftar_kata[j-1];  
                    abjad[i].daftar_kata[j-1] = temp;
                }
            }
        }
    } 

    //urutin berdasarkan panjang kata atau besar kecilnya kata jika frekuensinya sama
    for (int i = 0; i < 26; i++)
    {   
        for ( int n=0; n < abjad[i].jumlah_kata-1; n++)
        {
            for (int j=n+1; j > 0; j--)
            {  
                if (abjad[i].daftar_kata[j].frekuensi == abjad[i].daftar_kata[j-1].frekuensi )
                {
                    if (abjad[i].daftar_kata[j].panjang_kata > abjad[i].daftar_kata[j-1].panjang_kata)
                    {
                        Kata temp = abjad[i].daftar_kata[j];
                        abjad[i].daftar_kata[j] = abjad[i].daftar_kata[j-1];  
                        abjad[i].daftar_kata[j-1] = temp;
                    }
                    else if (abjad[i].daftar_kata[j].panjang_kata == abjad[i].daftar_kata[j-1].panjang_kata)
                    {
                        int p=strcmp(abjad[i].daftar_kata[j].kata,abjad[i].daftar_kata[j-1].kata);
                        if (p>0)
                        {
                            Kata temp = abjad[i].daftar_kata[j];
                            abjad[i].daftar_kata[j] = abjad[i].daftar_kata[j-1];  
                            abjad[i].daftar_kata[j-1] = temp;
                        }
                    }
                }
            }
        }
    } 
}

void simpan_ke_biner(){
   FILE *fp=fopen("binary.bin","wb");
   int n=0;
    while (n!=26)
    {   
        fwrite(&abjad[n].abjad,sizeof(char),1,fp);
        fwrite(&abjad[n].jumlah_kata,sizeof(int),1,fp);
        int i=0;
        while (i!=abjad[n].jumlah_kata)
        {
            fwrite(&abjad[n].daftar_kata[i].panjang_kata,sizeof(int),1,fp);
            fwrite(abjad[n].daftar_kata[i].kata,sizeof(char),abjad[n].daftar_kata[i].panjang_kata+1,fp);
            fwrite(&abjad[n].daftar_kata[i].frekuensi,sizeof(int),1,fp);
            i++;
        }
        n++;
    }
    fclose(fp);
}

void ambil_dari_biner(int n){
    FILE *fp=fopen("binary.bin","rb");

    if (fp==NULL)
    {
        printf("file binary tidak ditemukan!\n");
        return;
    }
    int c=fgetc(fp);
    if (c==EOF)
    {
        printf("file binary tidak ada isi!\n");
        fclose(fp); return;
    }
    rewind(fp);

    //baca file binary dan tampilin ke terminal
    int i=0;
    int j;

    printf("abjad   {kata(frekuensi)}\n");
    while (i!=26)
    {
        fread(&abjd_baca[i].abjad,sizeof(char),1,fp);
        printf("%c\t{",abjd_baca[i].abjad);
        fread(&abjd_baca[i].jumlah_kata,sizeof(int),1,fp);
        j=0;
        int batas,sampah1,sampah3;
        char sampah2[100];
        if (abjd_baca[i].jumlah_kata<=n)
        { batas=abjd_baca[i].jumlah_kata; }
        else if (abjd_baca[i].jumlah_kata>n)
        { batas=n; }
        
        while (j!=abjd_baca[i].jumlah_kata)
        {
            if (j<batas)
            {
                fread(&abjd_baca[i].daftar_kata[j].panjang_kata,sizeof(int),1,fp);
                fread(abjd_baca[i].daftar_kata[j].kata,sizeof(char),abjd_baca[i].daftar_kata[j].panjang_kata+1,fp);
                printf("%s",abjd_baca[i].daftar_kata[j].kata);
                fread(&abjd_baca[i].daftar_kata[j].frekuensi,sizeof(int),1,fp); 
                printf("(%d)",abjd_baca[i].daftar_kata[j].frekuensi);
                if (j<batas-1)
                { printf(","); }
            }
            
            else if (j>=batas)
            { 
                fread(&sampah1,sizeof(int),1,fp);
                fread(&sampah2,sizeof(char),sampah1+1,fp);
                fread(&sampah3,sizeof(int),1,fp); 
            }  
            j++;
        }
        printf("}\n");
        i++;
    }
    fclose(fp);    
}