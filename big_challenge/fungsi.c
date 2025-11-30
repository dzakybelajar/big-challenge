#include<stdio.h>
#include<string.h>

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

    //urutin frekuensi
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

    //urutin berdasarkan panjang kata atau besar kecilnya kata jika frekuensinya sama
     for (int i = 0; i < 26; i++)
    {   if (abjad[i].jumlah_kata==1)
            { continue; }
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
        return;
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
    int j;
    while (i!=26)
    {
        fread(&abjd_baca[i].abjad,sizeof(char),1,fp);
        fread(&abjd_baca[i].jumlah_kata,sizeof(int),1,fp);
        j=0;
        int k=0;
        while (j!=abjd_baca[i].jumlah_kata)
        {
            if (j<n)
            {
                fread(&abjd_baca[i].daftar_kata[j].panjang_kata,sizeof(int),1,fp);
                fread(abjd_baca[i].daftar_kata[j].kata,sizeof(char),abjd_baca[i].daftar_kata[j].panjang_kata+1,fp);
                fread(&abjd_baca[i].daftar_kata[j].frekuensi,sizeof(int),1,fp); 
            }
            
            else if (j>=n)
            { 
                fread(&sampah[i].daftar_kata[k].panjang_kata,sizeof(int),1,fp);
                fread(sampah[i].daftar_kata[k].kata,sizeof(char),sampah[i].daftar_kata[k].panjang_kata+1,fp);
                fread(&sampah[i].daftar_kata[k].frekuensi,sizeof(int),1,fp); k++;
            }  
            j++;
        }
        i++;
    }
    
    //tampilin ke terminal
    i=0;
    while (i!=26)
    {
        printf("%c\t{",abjd_baca[i].abjad);
        int batas;
        if (abjd_baca[i].jumlah_kata <= n)
        { batas=abjd_baca[i].jumlah_kata; }
        else
        { batas=n; }
        
        j=0;
        while (j!=batas)
        {
            printf("%s",abjd_baca[i].daftar_kata[j].kata);
            printf("(%d)",abjd_baca[i].daftar_kata[j].frekuensi);
            if (j<batas-1)
            { printf(","); }
            j++;
        }
        printf("}\n");
        i++;
    }
    fclose(fp);    
}