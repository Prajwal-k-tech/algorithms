#include <bits/stdc++.h>
using namespace std;
//Auth : oGhostyyy
vector<vector<int>> adj = {
    {1,2},
    {3},
    {3,4},
    {4},
    {}
}; // adjacency list
vector<bool> visited(5,false); //visited or not
queue<int> q; //a queue


void bfs(int start) {
  visited[start] = true; //set the starting node as visited
  q.push(start); //push it into the queue
  while (!q.empty()) { //keep going until queue is empty 
    int u = q.front(); q.pop(); //pop the first node in the queue 
    cout << u << " ";
    for (int v : adj[u]) {
      if (!visited[v]) { //look at the neighbours, mark them as visited and push theme to the queue 
        visited[v] = true;
        q.push(v);
      }
    }
  }
  cout << endl;
}
int main(){
    int startNode; //user can enter a start node, choose from 0 to 4, dont be stupid 
    cout << "Enter the starting node (0 to 4): ";
    cin >> startNode;
    bfs(startNode);
    return 0;
}