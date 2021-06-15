//Graph implementation using adjacency List
//DFS using recursion
#include <iostream>
#include <queue>
#include<stack>
using namespace std;
vector <vector<int>> adjList;
vector<bool> visited(5, false);
const int N = 5;

void addEdge(int n1, int n2)
{
    adjList.resize(N);
    adjList[n1].push_back(n2);
}
void PrintList()
{
    for (size_t i=0; i<N; i++)
    {
        cout << i << "->";
        for(auto x: adjList[i])
        {
            cout << x<<" ";
        }
        cout << endl;
    }
}
void dfs(int u) {
    visited[u] = true;
    for (int v : adjList[u])
        if (!visited[v])
            dfs(v);
    cout <<u << endl;
}
int main()
{
    addEdge(0, 1);
    addEdge(1, 4);
    addEdge(1, 2);
    addEdge(2, 0);
    addEdge(2, 3);
    addEdge(4, 3);
    dfs(0);
    cout << endl;
    PrintList();

}