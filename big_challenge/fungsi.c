#include<stdio.h>

typedef struct {
    int panjang_kata;
    char *kata;
    int frekuensi;
}Kata;

typedef struct {
    char abjad;
    int jumlah_kata;
    Kata *daftar_kata;
}Abjad;

void olah_teks(char file[]){}

void pengurutan(Abjad abjad[]){

    for (int i = 0; i < 26; i++)
    {   if (abjad[i].jumlah_kata==1)
            { continue; }
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
}

void simpan_ke_biner(Abjad abjd[]){
   FILE *fp=fopen("binary.bin","wb");
   int n=0;
    while (n!=26)
    {   
        fwrite(&abjd[n].abjad,sizeof(char),1,fp);
        fwrite(&abjd[n].jumlah_kata,sizeof(int),1,fp);
        int i=0;
        while (i!=abjd[n].jumlah_kata)
        {
            fwrite(&abjd[n].daftar_kata[i].panjang_kata,sizeof(int),1,fp);
            fwrite(abjd[n].daftar_kata[i].kata,sizeof(char),abjd[n].daftar_kata[i].panjang_kata+1,fp);
            fwrite(&abjd[n].daftar_kata[i].frekuensi,sizeof(int),1,fp);
            i++;
        }
        n++;
    }
    fclose(fp);
}

void ambil_dari_biner(Abjad abjd_baca[],int n){
    Abjad sampah[26];
    FILE *fp=fopen("binary.bin","rb");

    if (fp==NULL)
    {
        printf("file binary tidak ditemukan!\n");
        fclose(fp); return;
    }
    int c=fgetc(fp);
    if (c==EOF)
    {
        printf("file binary tidak ada isi!\n");
        fclose(fp); return;
    }
    rewind(fp);

    //baca file binary
    int i=0;
    while (i!=26)
    {
        fread(&abjd_baca[i].abjad,sizeof(char),1,fp);
        fread(&abjd_baca[i].jumlah_kata,sizeof(int),1,fp);
        int j=0;
        while (j!=abjd_baca[i].jumlah_kata)
        {
            fread(&abjd_baca[i].daftar_kata[j].panjang_kata,sizeof(int),1,fp);
            fread(abjd_baca[i].daftar_kata[j].kata,sizeof(char),abjd_baca[i].daftar_kata[j].panjang_kata,fp);
            fread(&abjd_baca[i].daftar_kata[j].frekuensi,sizeof(int),1,fp);
            if (j==n-1)
            {  while (j!=abjd_baca[i].jumlah_kata)
                {
                    fread(&sampah[i].daftar_kata[j].panjang_kata,sizeof(int),1,fp);
                    fread(sampah[i].daftar_kata[j].kata,sizeof(char),abjd_baca[i].daftar_kata[j].panjang_kata,fp);
                    fread(&sampah[i].daftar_kata[j].frekuensi,sizeof(int),1,fp);
                    j++; 
                } 
                j--;
            }  
            j++; 
        }
        printf("}\n");
        i++;
    }
    
    //tampilin ke terminal
    i=0;
    while (i!=26)
    {
        printf("%c\t{",abjd_baca[i].abjad);
        int j=0;
        while (j!=abjd_baca[i].jumlah_kata)
        {
            if (j==abjd_baca[i].jumlah_kata-1)
            {
            printf("%s",abjd_baca[i].daftar_kata[j].kata);
            printf("(%d)",abjd_baca[i].daftar_kata[j].frekuensi); j++; continue;
            }
            printf("%s",abjd_baca[i].daftar_kata[j].kata);
            printf("(%d),",abjd_baca[i].daftar_kata[j].frekuensi);
            j++;
        }
        printf("}\n");
        i++;
    }
    fclose(fp);    
}