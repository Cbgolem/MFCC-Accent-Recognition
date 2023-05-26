#ifndef KNN_H
#define KNN_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include<unordered_map>
using namespace std;

void minMaxNormalization(vector<vector<double>>& dataVect);
void euclideanDistance(vector<vector<double>>& trainingData, vector<vector<double>> testVect,int k);
string knn(vector<vector<double>> dataVect,string output_label[],int k);
//void euclidian_distance(double training_data[][],double testing_data[][], int k)

#endif
