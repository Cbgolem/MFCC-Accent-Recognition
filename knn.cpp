#include "knn.h"

void minMaxNormalization(vector<vector<double>>& dataVect)
{
	for(int j = 0; j < dataVect[0].size()-2; j++)//preserves the last 2 columns. index/distance
	{
		double max = 0;
		double min = 0;
		//finds the min and maximum values in each column
		for(int i = 0; i < dataVect.size(); i++)
		{
			if(i == 0)
			{
				max = dataVect[i][j];
				min = dataVect[i][j];
				continue;
			}
			if(max < dataVect[i][j])
			{
				max = dataVect[i][j];
			}
			if(min > dataVect[i][j])
			{
				min = dataVect[i][j];
			}
		}
	
		//applies the min max normalization to the column
		for(int i = 0; i < dataVect.size(); i++)
		{
			dataVect[i][j] = (dataVect[i][j] - min)/(max-min);
		}
	
	}	
}

void euclideanDistance(vector<vector<double>>& trainingData, vector<vector<double>> testVect, int k)
{
	for(int i = 0; i < trainingData.size(); i++)
	{
		double sum = 0;
		for(int j = 0; j < trainingData[0].size() - 2; j++)//doesnt calculate distance between index column distance column
		{
			double difference = testVect[k][j] - trainingData[i][j];
			sum += difference * difference;
		}
		trainingData[i][13] = sqrt(sum);//inserts distance into distance column(13)

	}
}

string knn(vector<vector<double>> dataVect,string outputLabel[],int k)
{
	string output = "";
	if(dataVect.size() < k || k == 0)//k larger than the amount of neighbors you have
	{
		string error = "error";
		return error;
	}
	
	//bubble sort, ascending order on the distance column
	bool swapped = false;
	for(int k = 0; k < dataVect.size(); k++)
	{
		swapped = false;
		for(int i = 1; i < dataVect.size(); i++)
		{
			if(dataVect[i][13] < dataVect[i-1][13])
			{
				swap(dataVect[i],dataVect[i-1]);
				swapped = true;
			}
		}
		if(swapped == false)
		{
			break;
		}
	}

	//adds to the string arr the k nearest neighbors
	vector<string> stringArr;
	for(int i = 0; i < k; i++)
	{
		int index = dataVect[i][12];
		string temp = outputLabel[index];
		stringArr.push_back(temp);
	}

	//counts the k nearest neighbors and returns the maximum occurance value
	unordered_map<string,int> hash;//string for language, occurrences
	int maxFreq = 0;
	for(int i = 0; i < k; i++)
	{
		hash[stringArr[i]] += 1;
		if(hash[stringArr[i]] > maxFreq)
		{
			maxFreq = hash[stringArr[i]];
			output = stringArr[i];
		}
	}
	return output;
}



