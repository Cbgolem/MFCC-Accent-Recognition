#include "knn.h"

int main()
{
	/*
	grabs the data for the KNN classifier
	there  are 329 rows and 14 columns
	1-12 are columns for data,13th column contains index for label
	14th column is for the distance from each instance
	*/
	ifstream language ("languages.txt");
	ifstream number_file ("numbers.txt");
	vector<vector<double>> dataVect;
	vector<vector<double>> trainingData;
	vector<vector<double>> testingData;
	string outputLabel[329];
	string result = "";
	string actualResult = "";
	
	for(int i = 0; i < 329; i++)
	{
		vector<double> temp;
		for( int j = 0; j < 12; j++)
		{
			double tempDouble = 0;
			number_file >> tempDouble;
			temp.push_back(tempDouble);
		}
		language >> outputLabel[i];
		temp.push_back(i); //adds the index for the output label to data
		temp.push_back(0); //adds the distance to the data
		dataVect.push_back(temp);
	}

	//applies min max normalization to the data columns
	minMaxNormalization(dataVect);
	
	//splits the data into 80% training and 20% testing
	for(int i = 0; i < dataVect.size(); i++)
	{
		if(i%5 == 0)//20% split for testing
		{
			vector<double> temp;
			for(int j = 0; j < dataVect[0].size(); j++)
			{
				temp.push_back(dataVect[i][j]);	
			}
			testingData.push_back(temp);
		}
		else//80% split for training
		{
			vector<double> temp;
			for(int j = 0; j < dataVect[0].size(); j++)
			{
				temp.push_back(dataVect[i][j]);	
			}
			trainingData.push_back(temp);
		}
	}
	
	//clears memory 
	dataVect.clear();

	//calculates the testing error
	float testingError = 0;
	for(int i = 0; i < testingData.size(); i++)
	{
		euclideanDistance(trainingData, testingData, i);
		int temp = testingData[i][12];
		actualResult = outputLabel[temp];
		result = knn(trainingData,outputLabel,7);
		if(actualResult != result)
			testingError++;
	}
	cout << "Testing Error is: " << testingError/testingData.size() * 100 << "%" <<endl;

	//calculates the training error
	float trainingError = 0;
	for(int i = 0; i < trainingData.size(); i++)
	{
		euclideanDistance(trainingData, trainingData, i);
		int temp = trainingData[i][12];
		actualResult = outputLabel[temp];
		result = knn(trainingData,outputLabel,7);
		if(actualResult != result)
			trainingError++;
	}
	cout << "Training Error is: " << trainingError/trainingData.size() * 100 << "%" <<endl;
	
}
