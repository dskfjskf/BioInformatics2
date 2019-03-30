#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

const string ACD = "ACDEFGHIKLMNPQRSTVWY";
const int ind = -5;

void Parse(vector<string>& str, vector<vector<int>>& mat) {
	
	for (int i = 1; i < 21; i++) {
		str[i].erase(0, 1);
		for (int j = 0; j < 20; j++) {
			mat[i - 1][j] = stoi(str[i].substr(0, 3));
			str[i].erase(0, 3);
		}
	}

}

void GlobalAlignmentProblem(string s1, string s2, vector<vector<int>>& mat) {
	int n = s1.length(), m = s2.length();
	vector<vector<int>> res(n + 1, vector<int>(1));

	res[0][0] = 0;

	for (int i = 1; i < n + 1; i++)
	{
		res[i] = res[i - 1];
		res[i][0] += ind;
		res[i].push_back(1);
	}

	for (int i = 1; i < m + 1; i++) {
		for (int j = n; j > 0; j--)
			if (res[j][0] + ind > res[j - 1][0] + mat[ACD.find(s2[i - 1])][ACD.find(s1[j - 1])])
			{
				res[j][0] += ind;
				res[j].push_back(2);
			}
			else
			{
				res[j] = res[j - 1];
				res[j][0] += mat[ACD.find(s2[i - 1])][ACD.find(s1[j - 1])];
				res[j].push_back(3);
			}

		res[0][0] += ind;
		res[0].push_back(2);

		for (int j = 1; j < n + 1; j++)
			if (res[j - 1][0] + ind > res[j][0])
			{
				res[j] = res[j - 1];
				res[j][0] += ind;
				res[j].push_back(1);
			}
	}

	cout << res[n][0] << endl;

	string res1 = "", res2 = "";
	int f = 0, s = 0;
	for (int i = 1; i < res[n].size(); i++)		
		switch (res[n][i]) {
		case 1:res2+='-'; res1 += s1[f]; f++; break;
		case 2:res1 += '-'; res2 += s2[s]; s++; break;
		case 3:res1 += s1[f]; f++; res2 += s2[s]; s++; break;
		}

	cout << res1 << endl;
	cout << res2 << endl;
}

void LocalAlignmentProblem(string s1, string s2, vector<vector<int>>& mat) {
	int n = s1.length(), m = s2.length();
	vector<vector<int>> res(n + 1, vector<int>(3));
	vector<int> temp = { 0,0,0 };
	vector<int> max(1);
	
	for (int i = 0; i < n + 1; i++)
		res[i][0] = 0;

	for (int i = 1; i < m + 1; i++) {
		for (int j = n; j > 0; j--)
			if (res[j][0] + ind > res[j - 1][0] + mat[ACD.find(s2[i - 1])][ACD.find(s1[j - 1])])
			{
				res[j][0] += ind;
				res[j].push_back(2);
			}
			else
			{
				res[j] = res[j - 1];
				res[j][0] += mat[ACD.find(s2[i - 1])][ACD.find(s1[j - 1])];
				res[j].push_back(3);
			}

		res[0][0] += ind;
		res[0].push_back(2);

		for (int j = 1; j < n + 1; j++) {
			if (res[j - 1][0] + ind > res[j][0])
			{
				res[j] = res[j - 1];
				res[j][0] += ind;
				res[j].push_back(1);
			}
			if (res[j][0] < 0)
				res[j] = temp;
			else
			{
				if (res[j][1] * res[j][2] == 0)
				{
					res[j][1] = i;
					res[j][2] = j;
				}
				if (res[j][0] > max[0])
					max = res[j];
			}
		}
	}

	cout << max[0] << endl;

	string res1 = "", res2 = "";
	int f = max[2]-1, s = max[1]-1;
	for (int i = 3; i < max.size(); i++)
		switch (max[i]) {
		case 1:res2 += '-'; res1 += s1[f]; f++; break;
		case 2:res1 += '-'; res2 += s2[s]; s++; break;
		case 3:res1 += s1[f]; f++; res2 += s2[s]; s++; break;
		}

	cout << res1 << endl;
	cout << res2 << endl;
}
int EditDistanceProblem(string s1, string s2) {
	int n = s1.length(), m = s2.length();
	vector<int> res(n + 1);	
	int k=1;

	for (int i = 0; i < n + 1; i++)	
		res[i] = i;	

	for (int i = 1; i < m + 1; i++) {
		for (int j = n; j > 0; j--) {
			k = 1;
			if (s2[i - 1] == s1[j - 1])
				k = 0;
			if (res[j] + 1 < res[j - 1] + k)
				res[j]++;
			else
				res[j] = res[j - 1] + k;
		}

		res[0] = i;
	
		for (int j = 1; j < n + 1; j++)
			if (res[j - 1] + 1 < res[j])
				res[j] = res[j - 1] + 1;
	}

	return res[n];
}

int main()
{
	//ifstream in;													//7.1

	//vector<string> str(21);
	//vector<vector<int>> mat(20,vector<int> (20));
	//string s1, s2;

	//in.open("D:\\Study\\bio\\7\\BLOSUM62.txt");

	//for (int i = 0; i < 21; i++) 
	//	getline(in, str[i]);

	//in.close();

	//in.open("D:\\Study\\bio\\7\\dataset_216071_1.txt");
	//
	//getline(in, s1);
	//getline(in, s2);

	//in.close();

	//Parse(str, mat);

	//GlobalAlignmentProblem(s1, s2, mat);

	//ifstream in;													//7.2

	//vector<string> str(21);
	//vector<vector<int>> mat(20,vector<int> (20));
	//string s1, s2;

	//in.open("D:\\Study\\bio\\7\\PAM250_1.txt");

	//for (int i = 0; i < 21; i++) 
	//	getline(in, str[i]);

	//in.close();

	//in.open("D:\\Study\\bio\\7\\dataset_216105_1.txt");
	//
	//getline(in, s1);
	//getline(in, s2);

	//in.close();

	//Parse(str, mat);
	//LocalAlignmentProblem(s1, s2, mat);

	string s1, s2;													//7.3

	cin >> s1 >> s2;

	cout<<EditDistanceProblem(s1, s2)<<endl;
	
	system("pause");
	return 0;
}