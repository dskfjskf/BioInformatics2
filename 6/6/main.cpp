#include <iostream>
#include <string>
#include <vector>

using namespace std;

int Change(int money, string strcoins) {
	vector<int> coins;
	vector<int> MNC(money + 1);

	while (strcoins.find(',') != strcoins.npos)
	{
		coins.push_back(stoi(strcoins.substr(0, strcoins.find(','))));
		strcoins.erase(0, strcoins.find(',')+1);
	}
	coins.push_back(stoi(strcoins.substr(0, strcoins.size())));

	for (int i = 0; i < money + 1; i++)
		MNC[i] = i*coins[coins.size()-1];

	for (int i = 1; i < money + 1; i++)
	{
		for (int j = 0; j < coins.size(); j++)
			if (i >= coins[j] && MNC[i] > MNC[i - coins[j]] + 1)
				MNC[i] = MNC[i - coins[j]] + 1;
	}

	return MNC[money];
}

int ManhattanTouristProblem(int n, int m, vector<vector<int>>& Down, vector<vector<int>>& Right) {
	vector<int> res(m + 1);

	res[0] = 0;
	for (int i = 1; i < m + 1; i++)
		res[i] = res[i - 1] + Right[0][i - 1];

	for (int i = 1; i < n+1; i++) {
		res[0] += Down[i - 1][0];
		for (int j = 1; j < m+1; j++)
			if (res[j - 1] + Right[i][j - 1] > res[j] + Down[i - 1][j])
				res[j] = res[j - 1] + Right[i][j - 1];
			else res[j] = res[j] + Down[i - 1][j];
	}

	return res[m];
}

string LongestCommonSubsequenceProblem(string str1, string str2) {
	int m = str1.length(), n= str2.length(),k;
	vector<int> res(m+1);
	vector<vector<int>> way(m+1);

	res[0] = 0;

	
	for (int i = 1; i < m+1; i++) {
		res[i] = 0;
		way[i]=way[i-1];
		way[i].push_back(1);
	}

	for (int i = 1; i < n+1; i++) {						
		for (int j = m; j > 0; j--) {
			if (str2[i-1] == str1[j-1])
				k = 1;
			else k = 0;
			if (res[j] < res[j - 1] + k)
			{
				res[j] = res[j - 1] + k;
				way[j] = way[j - 1];
				way[j].push_back(3);
			}
			else way[j].push_back(2);
		}

		res[0] = 0;
		way[0].push_back(2);				

		for (int j = 1; j < m+1; j++)
		{
			if (res[j] < res[j - 1])
			{
				res[j] = res[j - 1];
				way[j] = way[j - 1];
				way[j].push_back(1);
			}
		}
	}

	string rs="";
	int p = 0;
	for (int i = 0; i < way[m].size()-1; i++)
		switch (way[m][i]) {
		case 1:p++; break;		
		case 2:break;
		case 3:rs += str1[p]; p++; break;
		}
	return rs;
}

int main() {
	//int n, m;
	//string s;

	//cin >> n >> m;

	//vector<vector<int>> Down(n,vector<int> (m+1)), Right(n+1, vector<int>(m));

	//for (int i = 0; i < n; i++)
	//	for (int j = 0; j < m + 1; j++)
	//		cin >> Down[i][j];

	//cin>>s;

	//	for (int i = 0; i < n+1; i++)
	//		for (int j = 0; j < m; j++)
	//			cin >> Right[i][j];

	//	cout << ManhattanTouristProblem(n, m, Down, Right);

	string str1="ATCGTCC",str2="ATGTTATA";

//	cin >> str1 >> str2;
	cout<<LongestCommonSubsequenceProblem(str1, str2)<<endl;

	system("pause");
	return 0;
}