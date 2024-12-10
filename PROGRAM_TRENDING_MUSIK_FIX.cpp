#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>
using namespace std;

// Struct untuk menyimpan data musik
struct Music {
    string title, genre, type;
};

// Fungsi untuk menghitung entropi (untuk C4.5)
double calculateEntropy(map<string, int>& data, int total) {
    double entropy = 0.0;
    for (auto& entry : data) {
        double prob = (double)entry.second / total;
        if (prob > 0)  // Menghindari log(0)
            entropy -= prob * log2(prob);
    }
    return entropy;
}

// Fungsi untuk menghitung gain (information gain) berdasarkan genre
double calculateInformationGain(const vector<Music>& data) {
    map<string, int> genreCount;
    int total = data.size();

    // Hitung distribusi berdasarkan genre
    for (const auto& music : data) {
        genreCount[music.genre]++;
    }

    // Hitung entropi awal dari seluruh data (sebelum pemisahan berdasarkan genre)
    double initialEntropy = calculateEntropy(genreCount, total);
    
    // Pembagian berdasarkan genre dan hitung rata-rata entropi setelah pemisahan
    double weightedEntropy = 0.0;
    for (auto& entry : genreCount) {
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
double calculateTFIDF(int termFrequency, int totalDocs, int docsWithTerm) {
    if (docsWithTerm == 0) return 0.0;  // Pastikan tidak membagi dengan 0
    return termFrequency * log((double)totalDocs / docsWithTerm);
}

// Fungsi untuk mencari musik trending
void findTrendingMusic(const vector<Music>& data) {
    int totalDocs = data.size();
    map<string, int> termFrequency, genreFrequency;
    map<string, double> musicTFIDF;

    // Hitung frekuensi judul musik dan genre
    for (const auto& music : data) {
        termFrequency[music.title]++;
        genreFrequency[music.genre]++;
    }

    // Hitung TF-IDF dan Gain untuk setiap musik
    cout << "\n=== Nilai TF-IDF dan Gain ===\n";
    for (const auto& music : data) {
        double tfidf = calculateTFIDF(termFrequency[music.title], totalDocs, genreFrequency[music.genre]);
        musicTFIDF[music.title] = tfidf;

        // Menampilkan nilai Gain (information gain) untuk genre
        double genreGain = calculateInformationGain(data);
        cout << "Musik: " << music.title << " | TF-IDF: " << tfidf << " | Genre Gain: " << genreGain << endl;
    }

    // Musik paling trending (TF-IDF tertinggi)
    auto maxTFIDF = max_element(musicTFIDF.begin(), musicTFIDF.end(), 
                                 [](const pair<string, double>& a, const pair<string, double>& b) {
                                     return a.second < b.second;
                                 });
    cout << "\n====== Musik Paling Trending ======\n";
    cout << "Musik: " << maxTFIDF->first << " dengan TF-IDF: " << maxTFIDF->second << endl;

    // Musik yang tidak terlalu trending (TF-IDF terendah)
    auto minTFIDF = min_element(musicTFIDF.begin(), musicTFIDF.end(), 
                                 [](const pair<string, double>& a, const pair<string, double>& b) {
                                     return a.second < b.second;
                                 });
    cout << "\n====== Musik Tidak Terlalu Trending ======\n";
    cout << "Musik: " << minTFIDF->first << " dengan TF-IDF: " << minTFIDF->second << endl;

    // Genre yang paling trending (genre dengan frekuensi terbanyak)
    auto maxGenre = max_element(genreFrequency.begin(), genreFrequency.end(),
                                 [](const pair<string, int>& a, const pair<string, int>& b) {
                                     return a.second < b.second;
                                 });
    cout << "\n=== Genre Paling Trending ===\n";
    cout << "Genre: " << maxGenre->first << " dengan frekuensi: " << maxGenre->second << endl;
}

// Data musik yang sudah tersedia dalam kode
vector<Music> musicData = {
    {"DJ Wait A Minute - DJ Exe", "House", "Montage/Vlog"},
    {"Guud Girls - Breaking Beattz", "House", "Montage/Vlog"},
    {"Running Up Thaht Hill - Kate Bush", "Pop", "Cosplay/Montage"},
    {"Gogo Dance - El Alfa", "Latin Ubrano", "Vlog"},
    {"Zedsly - Timbaland", "Dance/Electronic", "Montage"},
    {"Still Don’t Know My Name (Remix) - Kimotion", "Dance/Electronic", "Montage"},
    {"Manifest - Tiffany Laibhen Spencer", "Dance/Electronic", "Montage/Vlog"},
    {"Fur-Endor", "Dance/Electronic", "Montage"},
    {"Break My Soul - Beyonce", "R&B/Soul", "Montage"},
    {"BILLIE EILISH", "Lifestyle", "Transition, Montage"},
    {"Outlands - Spencer Welling", "Lifestyle", "Montage, Vlog"},
    {"The Night We Met - Lord Huron", "Lifestyle", "Montage, Vlog"},
    {"mha4bii - Sofia Reyes feat. Jason Derulo, De La Ghetto", "Lifestyle", "Lip Sync"},
    {"Angel Eyes - ABBA", "Lifestyle", "Montage"},
    {"MASSIVE - Drake", "Lifestyle", "Montage"},
    {"Vegas - Doja Cat", "Lifestyle", "Montage, Vlog"},
    {"Lucid Dreams Instrumental - Amarildo Notolli", "Lifestyle", "Montage"},
    {"A Beautiful View - The Verse", "Travel", "Montage"},
    {"The Shade - Rex Orange Country", "Lifestyle", "Montage, Vlog"},
    {"Before, After", "Lifestyle", "Transition"},
    {"Ianasher - Stereo Love", "Lifestyle", "Montage, Vlog"},
    {"Wind - Prm", "Lifestyle", "Montage"},
    {"One Step at a Time - Jordin Sparks", "Lifestyle", "Act Out + Text on Screen + Montage"},
    {"Move Your Feet - Autsin Millz", "Lifestyle", "Montage"},
    {"How Deep is Your Love Mashup - DJ Replica", "Lifestyle", "Montage"},
    {"Yet To Come - BTS", "Entertainment", "Hashtag + Challenge"},
    {"2 Baddies - NCT127", "Entertainment", "Hashtag + Challenge"},
    {"Sparkling - Chung Ha", "Entertainment", "Dance + Challenge"},
    {"Pink Venom - Blackpink", "Entertainment", "Dance + Challenge"},
    {"Nayeon - Nayeon", "Entertainment", "Dance + Challenge"}
}; 

// Program utama
int main() {
    cout << "Trending di instagram menggunakan algoritma C 4.5 dan TF-IDF:\n";
    findTrendingMusic(musicData);
    return 0;
}
