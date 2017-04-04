#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <ctime>

using namespace std;

#define NODES 5000
#define SPARSE 6
#define DENSE (.2*NODES)
#define MAX_WEIGHT 5000

enum color{white,grey,black};

struct edge{
	int destination;
	int weight;
};

struct kedge{
public:
	int u;
	int v;
	int weight;

	kedge& operator=(const kedge& rhs){
		u = rhs.u;
		v = rhs.v;
		weight = rhs.weight;
		return *this;
	}

};

class CompareEdges{
public:
	bool operator()(kedge a, kedge b){
		return a.weight < b.weight;
	}
};

class Graph{
public:
	vector< vector<edge> >AdjList;
	vector<kedge> EdgeList;
	int E; //number of edges

	Graph();
	void Generate(int degree);
	void GenerateTest(char* filename);
	bool Check(int vert, int k);
	void EdgeCheck(int degree);
	void Print(char* filename);
};

#endif