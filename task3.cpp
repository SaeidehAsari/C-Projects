#include "fstream"
#include "iostream"
#include "vector"
#include<bits/stdc++.h>
#include "string"

// Hash function
struct Hash{
public:
    std::size_t operator()(const std::string& kmer) const {
        int sum = 0;
        for (size_t i = 0; i <= kmer.size() - 1; i++) {
            //if (k_mer[i] == 'A') sum = sum + (0 * pow(4, k - i - 1));  this is equal to zero
            if (kmer[i] == 'C') sum = sum + (1 * pow(4, kmer.size() - i - 1));
            else if (kmer[i] == 'G') sum = sum + (2 * pow(4, kmer.size() - i - 1));
            else if (kmer[i] == 'T') sum = sum + (3 * pow(4, kmer.size() - i - 1));
        }
        return sum;
    }
};

//nSkipGen is a function that creates n skipped k mers and returns an unordered_map
//which stores each kmer and its counts
std::unordered_map<std::string, int, Hash> nSkipkGen(const std::string& sequence, const int& n, const int& k);

int main(int argc, char* argv[]) {
    std::ifstream infile(argv[1]);
    int k = std::stoi(argv[2]);
    int n = std::stoi(argv[3]);

    std::string line;
    std::string seq = "";       // to track the current sequence while eliminating break lines
    std::string seq_id = "";    // to save sequence ids after removing '>' sign
    int seq_counter = 0;

    //// input retrieval and break lines curation
    std::vector<std::pair<std::string, std::string>> sequences;
    while (getline(infile, line)) {
        if (argc != 4 or line.empty()){
            std::cout << "wrong number of arguments" << std::endl;
            return -1;
        }
        else if (line[0] == '>') {
            line.erase(std::remove(line.begin(), line.end(), '>'), line.end());
            if (seq != "" && seq.find_first_not_of("ATCGatcg") == std::string::npos) {
                sequences.push_back({seq_id , seq});
            }
            else{
                std::cout << seq_id  << std::endl;
                std::cout << std::endl;
            }
            seq = "";
            seq_id = line;
            seq_counter++;
        } else{
            seq += line;
        }
    }
    if (sequences.size() < seq_counter ){
        if (seq != "" && seq.find_first_not_of("ATCGatcg") == std::string::npos) {
            sequences.push_back({seq_id, seq});
        } else{
            std::cout << seq_id  << std::endl;
            std::cout << std::endl;
        }
    }
    //// input retrieval and break lines curation

    ///// printing out the data
    for (int i = 0; i < sequences.size(); i++) {
        std::cout << sequences[i].first << std::endl;
        std::unordered_map<std::string, int, Hash> n_skip_kmers = nSkipkGen(sequences[i].second, n, k);
        std::vector<std::string> seq_kmers;

        seq_kmers.reserve(n_skip_kmers.size());
        for (const auto &el : n_skip_kmers) {
            seq_kmers.push_back(el.first);
        }
        std::sort (seq_kmers.begin(), seq_kmers.end());
        for (std::string kmer : seq_kmers) {
            std::cout << kmer << " " << n_skip_kmers[kmer] << std::endl;
        }
        std::cout << std::endl;
    }
    //// printing out the data
    return 0;
}

//nSkipGen is a function that return n skip kmers
///I got help from one of my friends (David Rasp) for this part
std::unordered_map<std::string, int, Hash> nSkipkGen(const std::string &sequence, const int &n, const int &k) {
    std::unordered_map<std::string, int, Hash> nSkippedKmers;
    for (int i = 0; i + (k - 1) * (n + 1) < sequence.size(); i++) {
        char kmer[k];
        kmer[k] = '\0';
        for (int j = 0; j < k; j++) {
            kmer[j] = toupper(sequence[i + j * (n + 1)]);
        }
        std::string nSippedKmer = kmer;
        nSkippedKmers[nSippedKmer]++;
    }
    return nSkippedKmers;
}