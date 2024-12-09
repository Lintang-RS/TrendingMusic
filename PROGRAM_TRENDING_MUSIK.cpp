#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

// Struct untuk menyimpan data musik
struct Music
{
    string title, genre, type;
};

// Fungsi untuk menghitung entropi (untuk C4.5)
double calculateEntropy(map<string, int> &data, int total)
{
    double entropy = 0.0;
    for (auto &entry : data)
    {
        double prob = (double)entry.second / total;
        entropy -= prob * log2(prob);
    }
    return entropy;
}

// Fungsi untuk menghitung gain (information gain) berdasarkan genre
double calculateInformationGain(const vector<Music> &data)
{
    map<string, int> genreCount;
    int total = data.size();

    // Hitung distribusi berdasarkan genre
    for (const auto &music : data)
    {
        genreCount[music.genre]++;
    }

    // Hitung entropi awal dari seluruh data (sebelum pemisahan berdasarkan genre)
    double initialEntropy = calculateEntropy(genreCount, total);

    // Pembagian berdasarkan genre dan hitung rata-rata entropi setelah pemisahan
    double weightedEntropy = 0.0;
    for (auto &entry : genreCount)
    {
        int genreCountInGroup = entry.second;
        double prob = (double)genreCountInGroup / total;

        // Hitung entropi untuk genre tertentu
        map<string, int> genreData;
        genreData[entry.first] = genreCountInGroup;

        weightedEntropy += prob * calculateEntropy(genreData, genreCountInGroup);
    }

    // Gain adalah perbedaan antara entropi awal dan entropi rata-rata setelah pemisahan berdasarkan genre
    return initialEntropy - weightedEntropy;
}

// Fungsi untuk menghitung TF-IDF
double calculateTFIDF(int termFrequency, int totalDocs, int docsWithTerm)
{
    return docsWithTerm == 0 ? 0.0 : termFrequency * log((double)totalDocs / docsWithTerm);
}

// Fungsi untuk mencari musik trending
void findTrendingMusic(const vector<Music> &data)
{
    int totalDocs = data.size();
    map<string, int> termFrequency, genreFrequency;
    map<string, double> musicTFIDF;

    // Hitung frekuensi judul musik dan genre
    for (const auto &music : data)
    {
        termFrequency[music.title]++;
        genreFrequency[music.genre]++;
    }

    // Hitung TF-IDF dan Gain untuk setiap musik
    cout << "\n=== Nilai TF-IDF dan Gain ===\n";
    for (const auto &music : data)
    {
        double tfidf = calculateTFIDF(termFrequency[music.title], totalDocs, genreFrequency[music.genre]);
        musicTFIDF[music.title] = tfidf;

        // Menampilkan nilai Gain (information gain) untuk genre
        double genreGain = calculateInformationGain(data);
        cout << "Musik: " << music.title << " | TF-IDF: " << tfidf << " | Genre Gain: " << genreGain << endl;
    }

    // Musik paling trending (TF-IDF tertinggi)
    auto maxTFIDF = max_element(musicTFIDF.begin(), musicTFIDF.end(),
                                [](const pair<string, double> &a, const pair<string, double> &b)
                                {
                                    return a.second < b.second;
                                });
    cout << "\n====== Musik Paling Trending ======\n";
    cout << "Musik: " << maxTFIDF->first << " dengan TF-IDF: " << maxTFIDF->second << endl;

    // Musik yang tidak terlalu trending (TF-IDF terendah)
    auto minTFIDF = min_element(musicTFIDF.begin(), musicTFIDF.end(),
                                [](const pair<string, double> &a, const pair<string, double> &b)
                                {
                                    return a.second < b.second;
                                });
    cout << "\n====== Musik Tidak Terlalu Trending ======\n";
    cout << "Musik: " << minTFIDF->first << " dengan TF-IDF: " << minTFIDF->second << endl;

    // Genre yang paling trending (genre dengan frekuensi terbanyak)
    auto maxGenre = max_element(genreFrequency.begin(), genreFrequency.end(),
                                [](const pair<string, int> &a, const pair<string, int> &b)
                                {
                                    return a.second < b.second;
                                });
    cout << "\n=== Genre Paling Trending ===\n";
    cout << "Genre: " << maxGenre->first << " dengan frekuensi: " << maxGenre->second << endl;
}

// Data musik yang sudah tersedia dalam kode
vector<Music> musicData = {
    {"DJ Wait A Minute", "House", "Montage/Vlog"},
    {"Break My Soul", "R&B/Soul", "Montage"},
    {"Pink Venom", "Entertainment", "Dance + Challenge"},
    {"Running Up That Hill", "Pop", "Cosplay/Montage"},
    {"The Shade", "Lifestyle", "Montage/Vlog"},
    {"Levitating", "Pop", "Montage"},
    {"Massive", "Lifestyle", "Montage"},
    {"Nayeon", "Entertainment", "Dance + Challenge"},
    {"2 Baddies", "Entertainment", "Dance + Challenge"},
    {"Before, After", "Lifestyle", "Transition"},
};

// Program utama
int main()
{
    cout << "Trending di instagram menggunakan algoritma C 4.5 dan TF-IDF:\n";
    findTrendingMusic(musicData);
    return 0;
}
