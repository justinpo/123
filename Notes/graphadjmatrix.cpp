//unweighted and directed graph
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

class graph{
private:
	int **adj;
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
	list<int> dfs_list(int);
	list<int> bfs_list(int);
	list<int> dfs_strictly_list(int);
	list<int> bfs_strictly_list(int);
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
	
	cout<<"breadth-first search traversal: ";
	g.bfs(4);
	cout<<"depth-first search traversal: ";
	g.dfs(4);
	cout<<"breadth-first search traversal returning a list of visits: ";
	list<int> bfstraversal = g.bfs_list(4);
	display(bfstraversal);
	cout<<"depth-first search traversal returning a list of visits: ";
	list<int> dfstraversal = g.dfs_list(4);
	display(dfstraversal);
	cout<<"depth-first search traversal returning a list of visits without using bool visit: ";
	list<int> dfstraversallist = g.dfs_strictly_list(4);
	display(dfstraversallist);
	cout<<"breadth-first search traversal returning a list of visits without using bool visit: ";
	list<int> bfstraversallist = g.bfs_strictly_list(4);
	display(bfstraversallist);

}

graph::graph(int s){
	n = s;
	adj = new int*[n];
	for(int i=0; i<n; i++){
		adj[i] = new int[n];
		for(int j=0; j<n; j++)
			adj[i][j] = 0;
	}		
}
graph::~graph(){
	for( int i = 0 ; i<n; i++ )
    	delete[] adj[i]; // delete array within matrix
	delete[] adj;
}
void graph::addedge(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1 || i==j) //to make sure that i and j are within the range of vertices
		throw "vertex i or j does not exist.";
	else
		adj[i][j] = 1;
}

void graph::removeedge(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1 || i==j) //to make sure that i and j are within the range of vertices
		throw "vertex i or j does not exist.";
	else{
		adj[i][j] = 0;
	}
}

bool graph::hasedge(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1 || i==j) //to make sure that i and j are within the range of vertices
		return false;
	else
		return adj[i][j];
}

bool graph::ispath(int i, int j){
	if(i<0 || i>n-1 || j<0 || j>n-1 || i==j)
		return false;
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
			for(int i=0; i<n; i++){
				if(adj[v][i] && !visit[i] ){
					q.push(i);
					visit[i]=true;					
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
		for(int i=0; i<n; i++){
			if(adj[v][i] && !visit[i] ){
				q.push(i);
				visit[i]=true;					
			}
		}
	}
	delete[] visit;
	cout<<endl;
}

list<int> graph::bfs_list(int s){
	queue<int> q;
	list<int> visited;
	bool *visit = new bool[n];
	for(int i=0; i<n; i++)
		visit[i] = false;
	q.push(s);
	visit[s] = true;
	while(!q.empty()){
		int v = q.front();
		visited.push_back(v);
		q.pop();
		for(int i=0; i<n; i++){
			if(adj[v][i] && !visit[i] ){
				q.push(i);
				visit[i]=true;					
			}
		}
	}
	delete[] visit;
	return visited;
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
		for(int i=n-1; i>=0; i--){
			if(adj[v][i] && !visit[i] ){
				s.push(i);
			}
		}//end

		//this entire block may replace the entire block from start to end above if the ascending order is not required
		//starts from index 0 instead of n-1
		/*for(int i=0; i<n; i++){
			if(adj[v][i] && !visit[i] ){
				s.push(i);
			}
		}*/						
	}	
	delete[] visit;
	cout<<endl;
}

list<int> graph::dfs_list(int start){
	stack<int> s;
	list<int> visited;
	bool *visit = new bool[n];
	for(int i=0; i<n; i++)
		visit[i] = false;
	
	s.push(start);
	
	while(!s.empty()){
		int v = s.top();		
		if(!visit[v]){
			visited.push_back(v);
			visit[v] = true;
		}
		s.pop();
		
		for(int i=n-1; i>=0; i--){
			if(adj[v][i] && !visit[i] ){
				s.push(i);
			}
		}						
	}	
	delete[] visit;
	return visited;
}

list<int> graph::dfs_strictly_list(int start){
	stack<int> s;
	list<int> visited;
	
	s.push(start);
	
	while(!s.empty()){
		int v = s.top();
		//find returns the iterator where v is found in the list from beginning to end
		//if v is not found in the list from beginning to end, find returns the end()
		//find is found in the algorithm library
		list<int>::iterator search = find(visited.begin(),visited.end(),v);		
		if(search==visited.end()){ //simply checks whether v has been visited or not
			visited.push_back(v);
		}
		s.pop();
		
		for(int i=n-1; i>=0; i--){
			list<int>::iterator search = find(visited.begin(),visited.end(),i);
			if(adj[v][i] && search==visited.end()){
				s.push(i);
			}
		}						
	}	
	return visited;
}

list<int> graph::bfs_strictly_list(int s){
	queue<int> q;
	list<int> visited;
	q.push(s);
	while(!q.empty()){
		int v = q.front();
		list<int>::iterator search = find(visited.begin(),visited.end(),v);		
		if(search==visited.end()){
			visited.push_back(v);
		}
		q.pop();
		for(int i=0; i<n; i++){
			list<int>::iterator search = find(visited.begin(),visited.end(),i);
			if(adj[v][i] && search==visited.end()){
				q.push(i);
			}
		}
	}	
	return visited;
}

void display(list<int> l){
	for(list<int>::iterator it=l.begin(); it!=l.end(); it++)
		cout<<*it<<" ";
	cout<<endl;
}