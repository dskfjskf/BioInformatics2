#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>
#include <vector>

using namespace std;

const string ACGT = "ACGT";

string f(string text, int k, vector<vector<double>>& matr) {
	string str = "", temp;
	double p, pmax = -1;

	for (int i = 0; i < text.size() - k + 1; i++)
	{
		temp = text.substr(i, k);
		p = 1;
		for (int j = 0; j < k; j++)
			p *= matr[ACGT.find(temp[j])][j];
		if (p > pmax)
		{
			pmax = p;
			str = temp;
		}
	}

	return str;
}

void GreedyMotifSearch(vector<string>& Dna, int k, int t) {
	vector<string> bestmotifs, motifs(t);
	vector<vector<double>> prob(4, vector<double>(k));
	vector<int> temp(4);
	int score = k*t, curscore;

	for (int i = 0; i < Dna[0].size() - k + 1; i++)
	{
		for (int p = 0; p < 4; p++)
			for (int j = 0; j < k; j++)
				prob[p][j] = 0;

		motifs[0] = Dna[0].substr(i, k);
		for (int s = 0; s < k; s++)
			prob[ACGT.find(motifs[0][s])][s]++;
		for (int j = 1; j < t; j++)
		{
			motifs[j] = f(Dna[j], k, prob);
			for (int s = 0; s < k; s++)
				prob[ACGT.find(motifs[j][s])][s]++;
		}


		curscore = 0;
		for (int j = 0; j < k; j++)
		{
			for (int p = 0; p < 4; p++)
				temp[p] = 0;
			for (int p = 0; p < t; p++)
				temp[ACGT.find(motifs[p][j])]++;
			sort(temp.rbegin(), temp.rend());
			for (int p = 1; p < 4; p++)
				curscore += temp[p];
		}
		if (curscore < score)
		{
			score = curscore;
			bestmotifs = motifs;
		}

	}

	for (int i = 0; i < t; i++)
		cout << bestmotifs[i] << endl;
}

void GreedyMotifSearch2(vector<string>& Dna, int k, int t) {
	vector<string> bestmotifs, motifs(t);
	vector<vector<double>> prob(4, vector<double>(k));
	vector<int> temp(4);
	int score = k*t, curscore;

	for (int i = 0; i < Dna[0].size() - k + 1; i++)
	{
		for (int p = 0; p < 4; p++)
			for (int j = 0; j < k; j++)
				prob[p][j] = 1;

		motifs[0] = Dna[0].substr(i, k);
		for (int s = 0; s < k; s++)
			prob[ACGT.find(motifs[0][s])][s]++;

		for (int j = 1; j < t; j++)
		{
			motifs[j] = f(Dna[j], k, prob);
			for (int s = 0; s < k; s++)
				prob[ACGT.find(motifs[j][s])][s]++;
		}

		curscore = 0;
		for (int j = 0; j < k; j++)
		{
			for (int p = 0; p < 4; p++)
				temp[p] = 0;
			for (int p = 0; p < t; p++)
				temp[ACGT.find(motifs[p][j])]++;
			sort(temp.rbegin(), temp.rend());
			for (int p = 1; p < 4; p++)
				curscore += temp[p];
		}
		if (curscore < score)
		{
			score = curscore;
			bestmotifs = motifs;
		}

	}

	for (int i = 0; i < t; i++)
		cout << bestmotifs[i] << endl;
}

int main() {
	vector<string> Dna;
	int k, t;

	cin >> k >> t;
	Dna.resize(t);
	for (int i = 0; i < t; i++)
		cin >> Dna[i];

	GreedyMotifSearch2(Dna, k, t);

	system("pause");

	return 0;
}