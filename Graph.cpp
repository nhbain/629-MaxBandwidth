#include "Graph.h"

using namespace std;

Graph::Graph(){
	AdjList.resize(NODES);
}

bool Graph::Check(int u, int v){
	bool unique = true;
	for(int i = 0; i < AdjList[v].size(); i++){
		if(AdjList[v][i].destination == u){
			unique = false;
			break;
		}
	}
	return unique;
}

void Graph::Generate(int degree){
	int v;
	unsigned int w;
	kedge knode;
	edge node;

	srand(time(NULL)); //randomize seed

	//Generate basic graph
	for(int i = 0; i < NODES - 1; i++){

		w = rand()%MAX_WEIGHT + 1; //generate random weight

		//connect each node to the next
		knode.u = i;
		knode.v = i + 1;
		knode.weight = w;
		EdgeList.push_back(knode); //store in edgelist

		//store edge for i + 1
		node.destination = i;
		node.weight = w;
		AdjList[i+1].push_back(node);

		//store edge for i
		node.destination = i + 1;
		AdjList[i].push_back(node);
	}

	//Form necessary amount of edges between nodes
	for(int j = 0; j < degree - 1; j++){
		for(int k = 0; k < NODES; k++){
			if(AdjList[k].size() < degree){
				while(AdjList[k].size() < degree){
					//select random node
					v = rand()%NODES;

					while((v == k) && (Check(v,k) == false)){
						v = rand()%NODES; //random node
					}

					if(AdjList[v].size() == degree){continue;}

					w = rand()%MAX_WEIGHT + 1; //random weight

					knode.u = k;
					knode.v = v;
					knode.weight = w;
					EdgeList.push_back(knode); //store edge in edgelist

					node.destination = v;
					node.weight = w;
					AdjList[k].push_back(node);//store edge for node k

					node.destination = k;
					AdjList[v].push_back(node);//store edge for node v
				}
			}
		}
	}

	if((AdjList[0].size() < degree) && (AdjList[AdjList.size() - 1].size() < degree)){
		w = rand()%MAX_WEIGHT + 1;
		int n = AdjList.size() - 1;

		knode.u = 0;
		knode.v = n;
		knode.weight = w;
		EdgeList.push_back(knode);

		node.destination = n;
		node.weight = w;
		AdjList[0].push_back(node);

		node.destination = 0;
		AdjList[n].push_back(node);
	}
}

void Graph::GenerateTest(char* filename){
	ifstream file;
	file.open(filename);
	kedge knode;
	edge node;
	int E;

	if(file){
		file>>E;
		for(int i = 0; i < E; i++){
			file>>knode.u;
			file>>knode.v;
			file>>knode.weight;
			EdgeList.push_back(knode);

			node.weight = knode.weight;
			node.destination = knode.v;
			AdjList[knode.u].push_back(node);
			node.destination = knode.u;
			AdjList[knode.v].push_back(node);
		}
	}

	else{
		cout<<"Invalid filename."<<endl;
		exit(1);
	}
	file.close();
	return;
}

void Graph::Print(char* filename){
	ofstream output(filename);
	output<<EdgeList.size()<<endl;
	for(int i = 0; i < EdgeList.size(); i++){
		output<<EdgeList[i].u<<" "<<EdgeList[i].v<<" "<<EdgeList[i].weight<<endl;
	}
	output.close();
}

void Graph::EdgeCheck(int degree){
	int bad = 0;
	int good = 0;

	for(int i=0; i < NODES; i++){
		if(AdjList[i].size() != degree){
			bad++;
			cout<<AdjList[i].size()<<endl;
		}
		else{good++;}
	}
	cout<<"There are "<<bad<<" nodes and "<<good<< " nodes"<<endl;
		
}