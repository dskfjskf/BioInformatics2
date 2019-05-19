#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <stack>

using namespace std;

void StringCompositionProblem(int k, string str) {
	for (int i = 0; i < str.size() - k + 1; i++)
		cout << str.substr(i, k) << endl;
}

string StringSpelledByAGenomePathProblem(vector<string>& str) {
	string res=str[0];
	int s = str[0].size();

	for (int i = 1; i < str.size(); i++)
		res += str[i][s - 1];

	return res;
}

void OverlapGraphProblem(vector<string>& str){
	vector<string> f(str.size());
	int size = str[0].size();

	for (int i = 0; i < str.size(); i++)	
		for (int j = 0; j < str.size(); j++)
			if (i != j && str[i].substr(1, size - 1) == str[j].substr(0, size - 1))
				f[i] = str[j];
	

	for (int i = 0; i < str.size(); i++)
		if (f[i] != "")
			cout << str[i] << " -> " << f[i] << endl;

}

map<string, stack<string>>  DeBruijnGraphFromAStringProblem(int k, string str) {
	vector<string> edge(str.size()-k+1);
	vector<string> vertex(edge.size()+1);
	map<string, stack<string>> graph;

	for (int i = 0; i < edge.size(); i++)
		edge[i] = str.substr(i, k);

	vertex[0]= edge[0].substr(0, k - 1);
	
	for (int i = 1; i < edge.size()+1; i++)
	{
		vertex[i] = edge[i-1].substr(1, k - 1);
		graph[vertex[i-1]].push(vertex[i]);
	}

	//for (auto i = graph.begin(); i != graph.end(); ++i)
	//{
	//	cout << i->first << " -> ";
	//	for (int j = 0; j < i->second.size() - 1; j++)
	//		cout << i->second[j]<<", ";
	//	cout << i->second[i->second.size() - 1] << endl;
	//}

	return graph;
	
}


vector <string> EulerianCycle(map<string, stack<string>> &m) {
	string fv = m.begin()->first, cur=fv,temp,s="";
	bool f=true;
	vector <string> res,t;
	int ind=0;

	while (f)
	{
		res = t;
		t.resize(0);
		cur=fv;
		while (!m[cur].empty())
		{
			res.push_back(cur);
			temp = cur;
			cur = m[cur].top();
			m[temp].pop();
		}

		f = false;
		for (int i=0;i<res.size();i++) 
			if (!m[res[i]].empty())
			{
				f = true;
				fv =res[i];
				ind = i;
				break;
			}

		for (int i = ind; i < res.size(); i++)
			t.push_back(res[i]);

		for (int i = 0; i < ind; i++)
			t.push_back(res[i]);
	}

	res.push_back(fv);

//	for (int i = 0; i < res.size(); i++)
//		cout << res[i] << "->";
	return res;

}

map<string, stack<string>> pars(vector<string>& str) {
	string ind;
	map<string, stack<string>> m;

	for (int i = 0; i < str.size(); i++)
	{
		ind = str[i].substr(0, str[i].find(" "));
		str[i].erase(0, str[i].find(" ")+1);
		str[i].erase(0, str[i].find(" ") + 1);

		while (str[i].find(",") != str[i].npos)
		{
			m[ind].push(str[i].substr(0, str[i].find(",")));
			str[i].erase(0, str[i].find(",") + 1);

		}
		m[ind].push(str[i]);
	}

	return m;
}

vector <string> EulerianPath(map<string, stack<string>> &m1) {
	map<string, int> s;
	string f, l;
	map<string, stack<string>> m = m1;
	vector <string> res, temp;

	for (auto i = m.begin(); i != m.end(); ++i) {
		s[i->first]+=i->second.size();
		while (!i->second.empty())
		{
			s[i->second.top()]--;
			i->second.pop();
		}
	}

	for (auto i = s.begin(); i != s.end(); ++i)
	{
		if (i->second > 0)
			f = i->first;
		if (i->second < 0)
			l = i->first;
	}

	m1[l].push(f);

	res = EulerianCycle(m1);

	int ind = 0;	

	for (int i = 1; i <res.size(); i++)
	{
		if (res[i] == f && res[i-1]==l)
		{
			ind = i;
			break;
		}
	}

	for (int i = ind; i < res.size(); i++)
	{
		temp.push_back(res[i]);
//		cout << res[i]<<"->";
	}
	for (int i = 1; i <ind; i++)
	{
		temp.push_back(res[i]);
//		cout << res[i] << "->";
	}
	
  return temp;
}

void StringReconstruction(int k, vector<string>& str) {
	map<string, stack<string>> graph;
	for (int i = 0; i < str.size(); i++)
	{
		for (int j = 0; j < str.size(); j++)
			if (i != j && str[i].substr(1, k - 1) == str[j].substr(0, k - 1))
				graph[str[i]].push(str[j]);
	}

	vector<string> res = EulerianPath(graph);
	cout << StringSpelledByAGenomePathProblem(res)<<endl;
}

int main() {
	int k;
	vector<string> str;
	string temp;
	
	
	getline(cin, temp);
	k = stoi(temp);
	getline(cin, temp);
	while (temp!="")
	{		
		str.push_back(temp);
		getline(cin, temp);
	}

	StringReconstruction(k, str);

	system("pause");
	return 0;
}