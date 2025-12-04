typedef struct {
    int panjang_kata;
    char kata[50];
    int frekuensi;
}Kata;

typedef struct {
    char abjad;
    int jumlah_kata;
    Kata daftar_kata[50000];
}Abjad;

void inisialisasi();
void olah_teks(char file[]);
void pengurutan();
void simpan_ke_biner();
void ambil_dari_biner(int);
