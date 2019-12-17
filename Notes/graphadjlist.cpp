//unweighted and directed graph
#include <iostream>
#include <list>
#include <queue>
#include <stack>

using namespace std;

class graph{
private:
	list<int> *adj;
	int n;
public:
	graph(int);
	~graph();
	void addedge(int,int);
	void removeedge(int,int);
	bool hasedge(int,int);
	bool ispath(int,int); //unweighted graph
	void bfs(int);
	void dfs(int);
};

void display(list<int>);

int main(){
	//this is bsed on the graph from the slides (flights from Manila to other cities in the Philippines)
	graph g(9);

	g.addedge(0,2);
	g.addedge(0,4);

	g.addedge(2,0);
	g.addedge(2,3);
	g.addedge(2,4);
	g.addedge(2,7);

	g.addedge(3,2);
	g.addedge(3,4);
	g.addedge(3,7);
	
	g.addedge(4,0);
	g.addedge(4,2);
	g.addedge(4,3);
	g.addedge(4,5);
	g.addedge(4,6);
	g.addedge(4,7);

	g.addedge(5,4);

	g.addedge(6,4);

	g.addedge(7,2);
	g.addedge(7,3);
	g.addedge(7,4);
	g.addedge(7,8);

	g.addedge(8,7);

	cout<<g.ispath(0,1)<<endl;
	cout<<g.ispath(0,8)<<endl;
	cout<<g.ispath(8,0)<<endl;
	
	g.bfs(4);
	g.dfs(4);
}

graph::graph(int s){
	n = s;
	adj = new list<int>[n];	
}
graph::~graph(){
	delete[] adj;
}
void graph::addedge(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1) //to make sure that i and j are within the range of vertices
		throw "vertex i or j does not exist.";
	else
		adj[i].push_back(j);
}

void graph::removeedge(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1) //to make sure that i and j are within the range of vertices
		throw "vertex i or j does not exist.";
	else{
		adj[i].remove(j);
	}
}

bool graph::hasedge(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1) //to make sure that i and j are within the range of vertices
		return false;
	for(list<int>::iterator it=adj[i].begin(); it!=adj[i].end(); it++){
		if(*it==j)
			return true;		
	}
	return false;
}

bool graph::ispath(int i, int j){
	queue<int> q;

	q.push(i);
	bool *visit = new bool[n];
	for(int i=0; i<n; i++)
		visit[i] = false;
	while(!q.empty()){
		int v = q.front();
		q.pop();
		if(v==j)
			return true;
		else{
			for(list<int>::iterator it=adj[v].begin(); it!=adj[v].end(); it++){
				if(!visit[*it]){
					q.push(*it);
					visit[*it]=true;
				}
			}				
		}
	}
	delete[] visit;
	return false;
}

void graph::bfs(int s){
	queue<int> q;

	bool *visit = new bool[n];
	for(int i=0; i<n; i++)
		visit[i] = false;
	q.push(s);
	visit[s] = true;
	while(!q.empty()){
		int v = q.front();
		cout<<v<<" ";
		q.pop();
		for(list<int>::iterator it=adj[v].begin(); it!=adj[v].end(); it++){
			if(!visit[*it]){
				q.push(*it);
				visit[*it]=true;
			}
		}
	}
	delete[] visit;
	cout<<endl;
}

void graph::dfs(int start){
	stack<int> s;

	bool *visit = new bool[n];
	for(int i=0; i<n; i++)
		visit[i] = false;
	
	s.push(start);
	
	while(!s.empty()){
		int v = s.top();
		if(!visit[v])
			cout<<v<<" ";
		visit[v] = true;
		s.pop();
				
		//since the display is to in ascending order, this is done
		//push the adjacent vertices of v in reverse order
		//if this is not required, then this may be removed entirely
		//start
		list<int> adjv;
		for(list<int>::iterator it=adj[v].begin(); it!=adj[v].end(); it++){
			adjv.push_front(*it);
		}
		
		for(list<int>::iterator it=adjv.begin(); it!=adjv.end(); it++){
			if(!visit[*it]){
				s.push(*it);				
			}
		}//end

		/*this entire block may replace the entire block from start to end above if the ascending order is not required

		for(list<int>::iterator it=adj[v].begin(); it!=adj[v].end(); it++){
			if(!visit[*it]){
				s.push(*it);				
			}
		}*/						
	}	
	delete[] visit;
	cout<<endl;
}

void display(list<int> l){
	for(list<int>::iterator it=l.begin(); it!=l.end(); it++)
		cout<<*it<<" ";
	cout<<endl;
}