#include "munkres_algorithm.hpp"
#include "algorithm"
#include <iostream>
#include "vector"
#include "set"
Matrix<int> run_munkres_algorithm(Matrix<int> c){
//void run_munkres_algorithm(Matrix<int> c) {

    // #1 Calculating the min value of each row and subtracting each value of the row from that minimum

    // Calculating minimum value for each row
    std::vector<int> rowMinValues;
    for (size_t row = 0; row < c.nrows(); row++) {
        int min = c(row, 0);
        for (size_t col = 1; col < c.ncols(); col++) {
            if (c(row, col) < min) {
                min = c(row, col);
            }
        }
        rowMinValues.push_back(min);
    }
    // Sbtracting minimum value of each row from every element of that row
    for (size_t i = 0; i < c.nrows(); i++) {
        for (size_t j = 0; j < c.ncols(); j++) {
            c(i, j) = c(i, j) - rowMinValues[i];
        }
    }

    //#2 Calculating the min value of each column and subtracting each value of that column from that minimum

    //Calculating minimum value for each column
    std::vector<int> colMinValues;
    for (size_t col = 0; col < c.ncols(); col++) {
        int min = c(0, col);
        for (size_t row = 1; row < c.nrows(); row++) {
            if (c(row, col) < min) {
                min = c(row, col);
            }
        }
        colMinValues.push_back(min);
    }

    // Sbtracting minimum value of each column from every element that column
    for (size_t i = 0; i < c.nrows(); i++) {
        for (size_t j = 0; j < c.ncols(); j++) {
            c(i, j) = c(i, j) - colMinValues[j];
        }
    }

    // For all zeros z i in C, mark z i with a star if there is no starred zero in its row or column
    Matrix<int> assignedMatrix(c.nrows(), c.ncols());
    std::vector<std::pair<int, int>> starredZeros;
    std::vector<int> starredRow;
    std::vector<int> starredCol;
    for (size_t i = 0; i < c.nrows(); i++) {
        for (size_t j = 0; j < c.ncols(); j++) {
            if (c(i, j) == 0 and
                std::count(starredRow.begin(), starredRow.end(), i) == 0 and
                std::count(starredCol.begin(), starredCol.end(), j) == 0) {
                assignedMatrix(i, j) = 1;
                starredZeros.push_back({i, j});
                starredRow.push_back(i);
                starredCol.push_back(j);
            }
        }
    }
    for (size_t i = 0; i < c.nrows(); i++) {
        for (size_t j = 0; j < c.ncols(); j++) {
            std::cout << assignedMatrix(i, j) << std::endl;
        }
    }


    // Step 1

    Step1:

    // covering the column which contains starrted zero
    std::set<int> coveredCol;
    std::set<int> coveredRow;


    for (auto col : starredCol) {
        coveredCol.insert(col);
    }

    if (coveredCol.size() == c.nrows()) {
        goto Done;
    } else {
        goto Step2;
    }


    // Step 2
    Step2:

    // Priming an uncovered zero:
    //std::set<std::pair<int, int>> primedZeros;
    int primedRow;
    int primedCol;
    int min_e;
    std::pair z0 = {primedRow, primedCol};

    //std::pair <int,int> z0;
    //std::set<int> primedRow;
    //std::set<int> primedCol;
    if (coveredCol.size() < c.ncols()) {
        for (size_t col = 0; col < c.ncols(); ++col) {
            if (std::count(coveredCol.begin(), coveredCol.end(), col) == 0) {
                for (size_t row = 0; row < c.nrows(); ++row) {
                    if (c(row, col) == 0) {
                        //z0 = {row, col};
                        //primedZeros.insert({row, col});
                        primedCol = col;
                        primedRow = row;
                        //primedCol.insert(col);
                        //primedRow.insert(row);
                    }
                }
            }
        }
        //coveredCols.find(col) != coveredCols.end()
        if (std::count (starredRow.begin(), starredRow.end(), primedRow) == 0){;
            goto Step3;
        }
        else {
            //std::set<int> coveredRow;
            coveredRow.insert(primedRow);
            for (auto el : starredZeros) {
                if (el.first == primedRow) {
                    coveredCol.erase(el.second);
                }
            }
            goto Step2;
        }

    } /*else {
        //int min_e;
        for (size_t col = 0; col < c.ncols(); ++col) {
            if (std::count(coveredCol.begin(), coveredCol.end(), col) == 0) {
                min_e = c(0, col);
                for (size_t row = 1; row < c.nrows(); ++row) {
                    if (c(row, col) < min_e) {
                        min_e = c(row, col);
                    }
                }
            }
        }

    }
    goto Step4;

    Step3:
    std::vector<std::pair<int, int>> s;
    s.push_back(z0);
    /*for (int i = 0; i < c.ncols(); i++){
        if(starredCol[i] == primedCol){
            std::pair z1 = {starredRow[i], i};
            s.push_back(z1);
            primedRow =
        }
    }*///////////

    //goto Step1;

    // Step 4
    // For step 4 I got help from my friend David Rasp
    Step4:

    for(std::size_t col = 0; col < c.ncols(); col++) {
        for (std::size_t row = 0; row < c.nrows(); row++) {
            if(coveredRow.find(row) != coveredRow.end()){
                c(row, col) = c(row, col) + min_e;
            }
            if(coveredCol.find(col) == coveredCol.end()){
                c(row, col) = c(row, col) - min_e;
            }
        }
    }
    goto Step2;

    Done:
    return assignedMatrix;


}