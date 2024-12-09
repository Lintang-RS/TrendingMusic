# TrendingMusic
# Algoritma Musik Trending dengan C4.5 dan TF-IDF

Proyek ini menunjukkan penerapan algoritma C4.5 dan TF-IDF (Term Frequency-Inverse Document Frequency) untuk mendeteksi musik dan genre yang sedang tren. Program ini menggunakan data mengenai judul musik dan genre terkait untuk menghitung information gain (menggunakan algoritma C4.5) dan nilai TF-IDF untuk menentukan musik yang sedang populer berdasarkan beberapa parameter.

## Fitur

- **Perhitungan Information Gain dengan C4.5**: Menghitung informasi gain pada genre musik untuk menganalisis bagaimana genre-genre tertentu membantu mengklasifikasikan data musik.
- **Perhitungan TF-IDF**: Menghitung nilai TF-IDF untuk setiap judul musik berdasarkan frekuensinya dan frekuensi genre terkait dalam dataset.
- **Mendeteksi Musik Trending**: Menemukan musik yang paling dan paling sedikit trending berdasarkan nilai TF-IDF yang dihitung.
- **Mendeteksi Genre Trending**: Mengidentifikasi genre dengan frekuensi tertinggi dalam dataset.

## Cara Kerja

1. **Algoritma C4.5**:
   - Menghitung entropi dari distribusi genre musik dalam dataset.
   - Menggunakan information gain untuk menilai seberapa signifikan genre dalam mengklasifikasikan musik.

2. **Algoritma TF-IDF**:
   - Mengukur kepentingan sebuah judul musik terkait dengan genre-nya.
   - Nilai TF-IDF yang lebih tinggi menunjukkan musik yang lebih signifikan atau "trending".

3. **Deteksi Musik & Genre Trending**:
   - Menemukan musik paling trending berdasarkan skor TF-IDF tertinggi.
   - Menemukan musik yang kurang trending berdasarkan skor TF-IDF terendah.
   - Menemukan genre dengan frekuensi terbanyak.

## Instalasi

### Persyaratan

Pastikan Anda memiliki kompiler C++ yang terpasang di sistem Anda (misalnya, GCC, Clang).

### Kompilasi

1. Clone repositori ini ke mesin lokal Anda:

   ```bash
   git clone https://github.com/your-username/trending-music-c45-tfidf.git
   cd trending-music-c45-tfidf

2. Compile the C++ program:

   g++ -o trending_music main.cpp
   
3. Run the program:

   ./trending_music
