#include "matrix.hpp"
#include "string"
#include "sstream"
#include "iostream"
#include "vector"
#include "list"
#include "set"
#include "algorithm"


// R: Current clique
// P: Candidate set
// X: Exclusion set
std::list<std::set<int>> BK (std::vector<std::vector<int>> matrix, std::set<int> R, std::set<int> P, std::set <int> X) {
    if (P.empty() and X.empty()) {
        std::list<std::set<int>> maxCliques;
        maxCliques.push_back(R);
        return maxCliques;
    }
    else {
        std::list<std::set<int>> maxCliques;
        while (!P.empty()) {
            int node = *P.begin(); //The current node

            std::set<int> R_prime = R;
            std::set<int> P_prime;
            std::set<int> X_prime;

            std::set<int> node_neighbors; // neighbors of the current node are saved in node_neighbors
            //neighbors finding:
            for (int i = 0; i < matrix.size(); ++i) {
                if (matrix[node][i] == 1) {
                    node_neighbors.insert(i);
                }
            }

            R_prime.insert(node);

            std::set_intersection(P.begin(), P.end(), node_neighbors.begin(), node_neighbors.end(),
                                  std::inserter(P_prime, P_prime.begin()));
            std::set_intersection(X.begin(), X.end(), node_neighbors.begin(), node_neighbors.end(),
                                  std::inserter(X_prime, X_prime.begin()));

            std::list<std::set<int>> tmpMaxCliques = BK(matrix, R_prime, P_prime, X_prime);
            maxCliques.insert(maxCliques.end(), tmpMaxCliques.begin(), tmpMaxCliques.end());

            P.erase(node);
            X.insert(node);
        }
        return maxCliques;
    }
}

int main(int argc, const char* argv[]) {
    std::string line;
    std::vector<std::vector<int>> m; //entered adjacency matric from stdin is saved in m
    while (getline(std::cin, line)){
        if (line.empty()){
            std::cout <<"Error: Empty line. " <<std::endl;
            return -1;
        }
        std::stringstream ss(line);
        int number;
        std::vector<int> v;
        while (ss >> number){
            if(number != 0 and number != 1){
                std::cout << "Error: Value other than 0 and 1 found." << std::endl;
                return -1;
            }
            v.push_back(number);
        }
        m.push_back(v);
    }

    std::set<int> r;
    std::set<int> p;
    for (int i = 0; i < m.size(); ++i){
        p.insert(i);
    }
    std::set<int> x;
    std::list<std::set<int>> maximumCliques = BK(m, r, p, x);

    // Printing out the maximum cliques
    for (auto a1 : maximumCliques){
        std::cout << "{";
        for (auto a2 : a1){
            if (a2 != *a1.rbegin()){
                std::cout << a2 << ", ";
            }
            else{
                std::cout << a2;
            }
        }
        std::cout << "}";
        std::cout << std::endl;
    }

    return 0;
}

