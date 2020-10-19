#ifndef GRAPH_H
#define GRAPH_H
#include<map>
#include<set>
#include<vector>
#include<utility>
#include<iostream>

using namespace std;
template <class T, class U> 
class CGraph
{
public:
	CGraph() {}
	void addNode(int key, T* data){ v[key] = data;}
	void addEdge(int key1, int key2, U* edge){ e.insert(make_pair(make_pair(key1, key2), edge));}
	U * getEdge(int key1, int key2)
	{
		auto iter = e.find(make_pair(key1,key2));
		if (iter != e.end())
		{
			return iter->second;
		}
		return nullptr;
	}
	vector<U*> getEdges(int key)
	{
		vector<U*> res = {};
		for (auto it : e)
		{
			auto k = it.first;
			if (k.first == key || k.second == key)
				res.push_back(it.second);
		}
		return res;
	}
	void delNode(int key)
	{
		auto it = e.begin();
		while (it != e.end())
		{
			auto k = it->first;
			if (k.second == key || k.first == key)
			{
				it = e.erase(it);
			}
			else
			{
				it++;
			}
		}
		v.erase(key);
	}
	void delEdge(int key1, int key2)
	{
		e.erase(make_pair(key1, key2));
	}
	void printEdges()
	{
		cout << endl << "print_edges:";
		for (auto it : e)
		{
			auto k = it.first;
			cout << "(" << k.first << ";" << k.second << ")" << " ";
		}
	}
private:
	map<pair<int, int>,U*> e; //матрица смежности
	map<int, T*> v; //мап вершин
};
#endif // GRAPH_H