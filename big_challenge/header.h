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

void olah_teks(char file[]);
void pengurutan(Abjad abjad[]);
void simpan_ke_biner();
void ambil_dari_biner(int);
