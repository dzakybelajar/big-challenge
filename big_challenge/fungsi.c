#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

Abjad abjad[26];
Abjad abjd_baca[26];

void olah_teks(char file[]){
    char buffer[500000];
    char *pt = buffer;
    Kata k;
    FILE *file = fopen(file, "r");
        if (file == NULL) {
            printf("File tidak ditemukan!\n");
            return 1;
        }
    
    while(fgets(buffer, sizeof(buffer), file) != 0){
        if (strcmp(buffer, "<url>") != 0 && strcmp(buffer, "</url>") != 0) {
            continue;
        }
        if(buffer [0] == '<' && buffer [0] == '>' ){
            continue;
        }
        int i = 0;
        char ch = buffer[i];
        if((ch >= 32 && ch <= 64) && (ch >= 91 && ch <= 96) && (ch >= 123 && ch <= 126)){
            i++;
            continue;
        }
    }

    while(*pt != '\0'){
        if (*pt = buffer[0] || *(pt-1) == ' '){
            if(*pt >= 'A' && *pt <= 'A')
                *pt += 32;
            }
            else{
                continue;
            }
        pt++;
    }
    fclose(file);
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
    Abjad sampah[26];
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
    while (i!=26)
    {
        fread(&abjd_baca[i].abjad,sizeof(char),1,fp);
        printf("%c\t{",abjd_baca[i].abjad);
        fread(&abjd_baca[i].jumlah_kata,sizeof(int),1,fp);
        abjd_baca[i].daftar_kata=malloc(abjd_baca[i].jumlah_kata*sizeof(Kata));
        j=0;
        int k=0;
        int batas;
        if (abjd_baca[i].jumlah_kata<=n)
        { batas=abjd_baca[i].jumlah_kata; }
        else if (abjd_baca[i].jumlah_kata>n)
        { batas=n; }
        
        while (j!=abjd_baca[i].jumlah_kata)
        {
            if (j<batas)
            {
                fread(&abjd_baca[i].daftar_kata[j].panjang_kata,sizeof(int),1,fp);
                abjd_baca[i].daftar_kata[j].kata=malloc(abjd_baca[i].daftar_kata[j].panjang_kata+1);
                fread(abjd_baca[i].daftar_kata[j].kata,sizeof(char),abjd_baca[i].daftar_kata[j].panjang_kata+1,fp);
                printf("%s",abjd_baca[i].daftar_kata[j].kata);
                fread(&abjd_baca[i].daftar_kata[j].frekuensi,sizeof(int),1,fp); 
                printf("(%d)",abjd_baca[i].daftar_kata[j].frekuensi);
                if (j<batas-1)
                { printf(","); }
            }
            
            else if (j>=batas)
            { 
                fread(&sampah[i].daftar_kata[k].panjang_kata,sizeof(int),1,fp);
                fread(sampah[i].daftar_kata[k].kata,sizeof(char),sampah[i].daftar_kata[k].panjang_kata+1,fp);
                fread(&sampah[i].daftar_kata[k].frekuensi,sizeof(int),1,fp); k++;
            }  
            j++;
        }
        printf("}\n");
        i++;
    }
    fclose(fp);    
}