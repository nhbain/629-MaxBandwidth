#include "Graph.h"

using namespace std;

// ------------------------------------------------ Heap 
int N[NODES+1];
vector<int> H;
static int flag = 0;

void heapify(vector<int> &D, int i, vector<int> &H){
	int l = 2*i;
	int r = 2*i + 1;
	int largest;

	if((l <= D.size() - 1) && (D[l] > D[i])){ largest = l;}
	else{ largest = i;}

	if((r <= D.size() - 1) && D[r] > D[largest]){ largest = r;}

	if(largest != i){
		int temp = N[H[largest]];
		N[H[largest]] = N[H[i]];
		N[H[i]] = temp;

		temp = H[largest];
		H[largest] = H[i];
		H[i] = temp;

		temp = D[i];
		D[i] = D[largest];
		D[largest] = temp;
		heapify(D, largest, H);
	}
}

vector<int> heapBuild(int a[NODES + 1]){
	vector<int> H;
	vector<int> D;
	vector<int>::iterator it;
	a[0] = 0;
	N[0] = 0;
	D.push_back(0);
	H.push_back(0);

	for(int i = 1; i <=NODES; i++){
		D.push_back(a[i]);
		H.push_back(i);
		N[i]= i;
	}

	for(int j = (D.size() - 1)/2; j >= 1; j--){
		heapify(D, j, H);
	}

	for(int k = 1; k < H.size(); k++){
		if(a[H[k]] == 0){
			it = H.begin() + k;
			H.erase(it);
			N[*it] = 0;
			k--;
		}
	}
	return H;
}

void heapInsert(int D[NODES + 1], int n, vector<int> &H){
	H.push_back(n);
	N[n] = H.size() - 1;
	int h = H.size() - 1;

	while((h > 1) && (D[H[h]] > D[H[h/2]])){
		int temp = N[H[h]];
		N[H[h]] = N[H[h/2]];
		N[H[h/2]] = temp;

		temp = H[h];
		H[h] = H[h/2];
		H[h/2] = temp;

		h = h/2;
	}
}

void heapDelete(int D[NODES + 1], int h, vector<int> &H){
	vector<int>::iterator it = H.begin() + (H.size() - 1);
	N[H[h]] = N[H[H.size() - 1]];
	H[h] = H[H.size() - 1];
	H.erase(H.begin() + (H.size() - 1));
	N[*it] = 0;

	if(H.size() == 2){return;}

	if((h > 1) && (D[H[h]] > D[H[h/2]])){
		while((h > 1) && (D[H[h]] > D[H[h/2]])){
			int temp = N[H[h]];
			N[H[h]] = N[H[h/2]];
			N[H[h/2]] = temp;

			temp = H[h];
			H[h] = H[h/2];
			H[h/2] = temp;

			h = h/2;
		}
	}

	else{
		int l = 2*h;
		int r = 2*h + 1;
		int largest;

		if((l <= H.size() - 1) && (D[H[l]] > D[H[h]])){ largest = l;}
		else{ largest = h;}
		if((r <= H.size() - 1) && (D[H[r]] > D[H[largest]])){ largest = r;}

		while(largest != h){
			int temp = N[H[largest]];
			N[H[largest]] = N[H[h]];
			N[H[h]] = temp;

			temp = H[largest];
			H[largest] = H[h];
			H[h] = temp;

			h = largest;
			l = 2*largest;
			r = 2*largest + 1;

			if((l > H.size()) && (r > H.size() - 1)){ break;}

			if((l <= H.size() - 1) && (D[H[l]] > D[H[h]])){ largest = l;}
			else{ largest = h;}
			if((r <= H.size() - 1) && (D[H[r]] > D[H[largest]])){ largest = r;}
		}
	}
}

int heapMax(int D[NODES + 1], vector<int> H){
	if(H.size() <=1){ return 0;}
	else{ return H[1];}
}
// ------------------------------------------------ Heap 

// ------------------------------------------------ Dijkstra
void dijkstra(Graph *g, int s, int t){
	int cap[NODES];
	int parent[NODES];
	color visited[NODES];
	int v, tempV, tempW;
	int inTree = 0;
	
	//initialize
	for(int i = 0; i < NODES; i++){
		cap[i] = 0;
		visited[i] = white;
		parent[i] = i;
	}

	//set values for source
	visited[s] = black;
	inTree++;

	//check s's edges and add vertices to fringe
	for(int j = 0; j < g->AdjList[s].size(); j++){
		tempV = g->AdjList[s][j].destination;
		visited[tempV] = grey;
		parent[tempV] = s;
		cap[tempV] = g->AdjList[s][j].weight;
	}

	while(inTree < NODES){
		//select node with max eight
		int maxW = 0;
		for(int k = 0; k < NODES; k++){
			if((visited[k] == grey) && (cap[k] > maxW)){
				maxW = cap[k];
				v = k;
			}
		}

		visited[v] = black;
		inTree++;

		for(int ii = 0; ii < g->AdjList[v].size(); ii++){
			tempV = g->AdjList[v][ii].destination;
			tempW = g->AdjList[v][ii].weight;

			if(visited[tempV] == white){
				visited[tempV] = grey;
				parent[tempV] = v;
				cap[tempV] = min(cap[v], tempW);
			}

			else if((visited[tempV] == grey) && (cap[tempV] < min(cap[v], tempW))){
				parent[tempV] = v;
				cap[tempV] = min(cap[v], tempW);
			}
		}
	}

	cout<<"Max bandwidth path from "<<s<<" to "<<t<<" is:"<<endl;
	tempV = t;

	if(parent[tempV] != tempV){
		while(parent[tempV] != s){
			cout<<tempV<<" --> ";
			tempV = parent[tempV];
		}
		cout<<tempV<<" --> "<< parent[tempV]<<endl;
	}
} 
// ------------------------------------------------ Dijkstra

// ------------------------------------------------ Dijkstra with Heap
void dijkstraHeap(Graph *g, int s, int t){
	int cap[NODES + 1]; // +1 to deal with heap being from 1...n instead of 0...n
	int parent[NODES + 1];
	color visited[NODES + 1];
	vector<int> heap;

	int v, tempV, tempW;
	int fringe = 0;

	//initialize
	for(int i = 1; i <= NODES; i++){
		cap[i] = 0;
		visited[i] = white;
		parent[i] = i;
	}

	//set values for source
	visited[s] = black;

	for(int j = 0; j < g->AdjList[s].size(); j++){
		fringe = 1;
		tempV = g->AdjList[s][j].destination;
		visited[tempV] = grey;
		parent[tempV] = s;
		cap[tempV] = g->AdjList[s][j].weight;	
	}

	heap = heapBuild(cap);

	while(fringe){
		//find biggest edge in fringe
		int m = heapMax(cap, heap);
		if(m == 0){ break;}

		heapDelete(cap, 1, heap);

		v = m;
		visited[v] = black;

		for(int k = 0; k < g->AdjList[v].size(); k++){
			tempV = g->AdjList[v][k].destination;
			tempW = g->AdjList[v][k].weight;

			if(visited[tempV] == white){
				visited[tempV] = grey;
				parent[tempV] = v;
				cap[tempV] = min(cap[v], tempW);
				heapInsert(cap, tempV, heap);
			}

			else if((visited[tempV] == grey) && (cap[tempV] < min(cap[v], tempW))){
				parent[tempV] = v;
				cap[tempV] = min(cap[v], tempW);
				int p = N[tempV];

				if(p !=0){
					heapDelete(cap, p, heap);
					heapInsert(cap, tempV, heap);
				}
			}
		}
	}

	cout<<"Max bandwidth path from "<<s<<" to "<<t<<" in reverse is:"<<endl;
	tempV = t;

	if(parent[tempV] != tempV){
		while(parent[tempV] != s){
			cout<<tempV<<" --> ";
			tempV = parent[tempV];
		}
		cout<<tempV<<" --> "<< parent[tempV]<<endl;
	}
}
// ------------------------------------------------ Dijkstra with Heap

// ------------------------------------------------ Kruskal & helper functions
int kfind(int parent[NODES + 1], int v){
	int w = v;
	vector<int> s;
	while(parent[w] != 0){
		s.push_back(w);
		w = parent[w];
	}
	for(int i = 0; i < s.size(); i++){
		parent[s[i]] = w;
	}
	return w;
}

void kunion(int parent[NODES + 1], int rank[NODES + 1], int r1, int r2){
	if(rank[r1] > rank[r2]){
		parent[r2] = r1;
	}
	else if(rank[r1] < rank[r2]){
		parent[r1] = r2;
	}
	else if(rank[r1] == rank[r2]){
		parent[r2] = r1;
		rank[r1]++;
	}
}

void dfsMain(int s, int t, color visited[NODES + 1], map<int, vector<int> > &adj){
	visited[s] = grey;
	if(s == t){
		flag = 1;
		cout<<s<<" --> ";
		visited[s] = black;
		return;
	}

	vector<int> verts = adj[s];

	for(int i = 0; i < adj[s].size(); i++){
		if(visited[verts[i]] == white){
			dfsMain(verts[i], t, visited, adj);
		}
		if(flag == 1){
			cout<<s<<" --> ";
			visited[s] = black;
			return;
		}
	}
	visited[s] = black;
}

void dfs(int s, int t, map<int, vector<int> > adj){
	color visited[adj.size()];

	for(map<int, vector<int> >::iterator it = adj.begin(); it != adj.end(); it++){
		visited[it->first] = white;
	}
	flag = 0;
	dfsMain(s, t, visited, adj);
	cout<<endl;
}

void kruskal(Graph *g, int s, int t){
	int parent[NODES+1];
	int rank[NODES+1];

	make_heap(g->EdgeList.begin(), g->EdgeList.end(), CompareEdges());
	sort_heap(g->EdgeList.begin(), g->EdgeList.end(), CompareEdges());
	vector<kedge> sorted;
	for(vector<kedge>::reverse_iterator it = g->EdgeList.rbegin(); it!= g->EdgeList.rend(); it++){ sorted.push_back(*it);}

	for(int i = 1; i <= NODES; i++){
		parent[i] = 0;
		rank[i] = 0;
	}

	vector<kedge> solution;

	for(int j = 0; j < g->E; j++){
		int u = sorted[j].u;
		int v = sorted[j].v;
		int r1 = kfind(parent, u);
		int r2 = kfind(parent, v);
		if(r1 != r2){
			solution.push_back(sorted[j]);
			kunion(parent, rank, r1, r2);
		}
	}

	//Use DFS to output path
	cout<<"Finished kruskal's... runing DFS."<<endl;
	map<int, vector<int> > adj;

	int count = 0;
	for(vector<kedge>::iterator it = solution.begin(); it != solution.end(); it++){
		adj[(*it).u].push_back((*it).v);
    	adj[(*it).v].push_back((*it).u);
	}
	dfs(s, t, adj);
}
// ------------------------------------------------ Kruskal & helper functions


int main(){
	char filename[] = "testgraph.txt";
	char sparsename[] = "SparseGraph.txt";
	char densename[] = "DenseGraph.txt";
	Graph g1; //sparse
	Graph g2; //dense
	Graph test;

	clock_t start;
	srand(time(NULL)); //randomize seed
	double DijkstraSparse, DijkstraHeapSparse, KruskalSparse, DijkstraDense, DijkstraHeapDense, KruskalDense;
	int s, t;

	s = rand()%NODES;
	t = rand()%NODES;
	while(s == t){
		t = rand()%NODES;
	}

	// cout<<"-----------------------Test Graph ----------------------------"<<'\n'<<endl;
	
	// test.GenerateTest(filename);
	// // test.Print();
	// cout<<"Test graph initialized."<<endl;

	// cout<<"Running Kruskal's algorithm on test graph..."<<endl;
	// kruskal(&test, 0, 4);

	// cout<<"Running Dijkstra without heap on test graph..."<<endl;
	// dijkstra(&test, 0, 4);

	// cout<<"Running Dijkstra without heap on test graph..."<<endl;
	// dijkstraHeap(&test, 0, 4);

	// cout<<'\n'<<"-----------------------Test Graph ----------------------------"<<endl;

	cout<<"-----------------------Sparse Graphs ----------------------------"<<'\n'<<endl;
	
	g1.Generate(SPARSE);// Use these two lines to generate fresh graph and save to output file
	g1.Print(sparsename);

	// g1.GenerateTest(sparsename);//Use this line to upload previously generated graph for further testing
	
	cout<<"Sparse graph initialized."<<endl;

	cout<<"Running Kruskal's algorithm on sparse graph with source: "<<s<<" and target: "<<t<<endl;
	start = clock();
	kruskal(&g1, s, t);
	KruskalSparse = clock()-start/(double)CLOCKS_PER_SEC;
	

	cout<<"Running Dijkstra without heap on sparse graph with source: "<<s<<" and target: "<<t<<endl;
	start = clock();
	dijkstra(&g1, s, t);
	DijkstraSparse = clock()-start/(double)CLOCKS_PER_SEC;
	

	cout<<"Running Dijkstra with heap on sparse graph with source: "<<s<<" and target: "<<t<<endl;
	start = clock();
	dijkstraHeap(&g1, s, t);
	DijkstraHeapSparse = clock()-start/(double)CLOCKS_PER_SEC;
	
	cout<<'\n'<<"-----------------------Sparse Graphs ----------------------------"<<endl;

	cout<<"-----------------------Dense Graphs ----------------------------"<<'\n'<<endl;
	g2.Generate(DENSE);// Use these two lines to generate fresh graph and save to output file
	g2.Print(densename);

	// g2.GenerateTest(densename);//Use this line to upload previously generated graph for further testing

	cout<<"Dense graph initialized."<<endl;

	cout<<"Running Kruskal's algorithm on dense graph with source: "<<s<<" and target: "<<t<<endl;
	start = clock();
	kruskal(&g2, s, t);
	KruskalDense = clock()-start/(double)CLOCKS_PER_SEC;

	cout<<"Running Dijkstra without heap on dense graph with source: "<<s<<" and target: "<<t<<endl;
	start = clock();
	dijkstra(&g2, s, t);
	DijkstraDense = clock()-start/(double)CLOCKS_PER_SEC;

	cout<<"Running Dijkstra with heap on dense graph with source: "<<s<<" and target: "<<t<<endl;
	start = clock();
	dijkstraHeap(&g2, s, t);
	DijkstraHeapDense = clock()-start/(double)CLOCKS_PER_SEC;
	
	cout<<'\n'<<"-----------------------Dense Graphs ----------------------------"<<endl;

	cout<<"-----------------------Timing Results----------------------------"<<endl;

	cout<<"Source: "<<s<<", Target: "<<t<<endl;
	cout<<"Sparse Dijkstra Timing: "<<DijkstraSparse<<endl;
	cout<<"Sparse Dijkstra With Heap Timing: "<<DijkstraHeapSparse<<endl;
	cout<<"Sparse Kruskal Timing: "<<KruskalSparse<<endl;

	cout<<"Dense Dijstra Timing: "<<DijkstraDense<<endl;
	cout<<"Dense Dijkstra With Heap Timing: "<<DijkstraHeapDense<<endl;
	cout<<"Dense Kruskal Timing: "<<KruskalDense<<endl;

	cout<<"-----------------------Timing Results----------------------------"<<endl;
	return 0;
}