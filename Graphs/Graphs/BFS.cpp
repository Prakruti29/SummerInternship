//Graph implementation using adjaceny matrix and finding shortest path using bfs.

#include <iostream>
#include <queue>
using namespace std;
int arr[5][5]{ 0 };
//adding edge by using adjaceny matrix
void addEdge(int n1, int n2)
{
    arr[n1][n2] = 1;
    arr[n2][n1] = 1;
}
void PrintMatrix()
{
    for (size_t i{ 0 }; i < 5; i++)
    {
        for (size_t j{ 0 }; j < 5; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
        cout << *i;
    }
}
void bfs()
{
    int v{ 0 }, vertex;
    queue<int> q;
    vector<int> visited(5, false);
    cout << "Enter vertex from which you want to find shortest path??" << endl;
    cin >> vertex;
    q.push(vertex);
    visited.push_back(vertex);
    while (!q.empty())
    {
        v = q.front();
        cout << v;
        q.pop();
        visited[vertex] = true;
        for (int i{ 0 }; i < 5; i++)
        {
            if (arr[v][i] == 1 && (!visited[i]))
            {
                q.push(i);
                visited[i] = true;
            }
        }
    }

}
int main()
{
    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 2);
    addEdge(2, 0);
    addEdge(2, 3);
    addEdge(3, 3);
    PrintMatrix();
    bfs();
}