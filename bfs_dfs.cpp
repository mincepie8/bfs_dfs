#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
public:
	int e_num = 0;
	const int INF = 1e9;
	vector<vector<int>> graph; //храним граф списком смежности
	vector<int> visited;
	vector<int> dist;
	queue<int> q;
	Graph(int v_num) {
		graph.resize(v_num);
		visited.resize(v_num);
		dist.resize(v_num);
		fill(dist.begin(), dist.end(), INF);
	}
	void fill_graph() {
		ifstream in;
		in.open("test.txt"); //тестовый файл представлен в формате списка рёбер, где нумерация рёбер начинается с 1
		int a, b;
		while (in >> a && in >> b) {
			a--;
			b--;
			graph[a].push_back(b);
			graph[b].push_back(a);
			e_num++;
		}
		in.close();
	}
	void dfs(int v) {
		visited[v] = 1;
		for (int to : graph[v]) {
			if (!visited[to]) {
				dfs(to);
			}
		}
	}
	void bfs(int start) {
		visited[start] = 1;
		dist[start] = 0;
		q.push(start);
		while (!q.empty()) {
			int v = q.front();
			q.pop();
			for (int to : graph[v]) {
				if (!visited[to]) {
					visited[to] = 1;
					dist[to] = dist[v] + 1;
					q.push(to);
				}
			}
		}
	}
};
int main() {
	int v_num, start;
	cin >> v_num;
	Graph A(v_num);
	A.fill_graph();
	for (int i = 0; i < A.e_num; i++) {
		if (!A.visited[i]) {
			A.dfs(i);
		}
	}
	for (int i = 0; i < v_num; i++) {
		cout << A.visited[i] << " ";  //проверяем, что прошли по всем вершинам
	}
	fill(A.visited.begin(), A.visited.end(), 0);
	cout << "\nEnter start vertex: ";
	cin >> start;
	A.bfs(start - 1);
	for (int i = 0; i < v_num; i++) {
		cout << A.dist[i] << " ";
	}
	return 0;
}