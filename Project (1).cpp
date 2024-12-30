/*
    Sample Input
    6 7
    1 2 2
    2 5 3
    5 6 1
    1 4 1
    1 3 1
    3 6 3
    4 6 3
    1 6
    Sample Output
    2
    1 3 6
    4

    4 5
    1 4 5
    1 2 4
    2 4 5
    1 3 2
    3 4 3
    1 4
    Sample Output
    2
    1 4
    5

*/
#include <bits/stdc++.h>
using namespace std;


const int INF = 1e9;
const int MAXN = 1e5 + 1;
vector<pair<int, int>>g[MAXN];
vector<int> dist(MAXN);
vector<int> route(MAXN);
vector<int> pred(MAXN);
vector<int> path;

// Function to count number of shortest
// paths from node 1 to node N
void countDistinctShortestPaths(int n, int m)
{


	for (int i = 2; i <= n; ++i) {
		dist[i] = INF;
	}

	// Initialize a priority queue
	priority_queue<pair<int,int>,
            vector<pair<int,int> >,
            greater<pair<int,int> >>pq;
	pq.push({ 0, 1 });

	// Base Cases
	dist[1] = 0;
	route[1] = 1;
	pred[1] = -1;


	while (!pq.empty()) {
		int d = pq.top().first;
		int u = pq.top().second;
		pq.pop();

		// if d is greater than distance
		// of the node
		if (d > dist[u])
			continue;

		// Traversing all its neighbours
		for (int i = 0; i < g[u].size(); ++i) {
            int v = g[u][i].first;
            int c = g[u][i].second;
			if (c + d > dist[v])
            continue;

			// Path found of same distance
			if (c + d == dist[v]) {
				route[v] += route[u];
			}

			// New path found for lesser
			// distance
			if (c + d < dist[v]) {
				dist[v] = c + d;
				route[v] = route[u];
				pred[v] = u;  // Update the predecessor of v


				pq.push({ dist[v], v });
			}
		}
	}

}

// Function to print the shortest path from node s to node t

void printShortestPath(int s, int t) {
	// If the destination is not reachable from the source
	if (pred[t] == -1) {
		cout << "There is no path from " << s << " to " << t << endl;
		return;
	}

	// Stack to store the nodes in the shortest path
	stack <int> path;


	int curr = t;
	while (curr != s) {
		path.push(curr);
		curr = pred[curr];
	}
	path.push(s);

	// Print the shortest path
	while (!path.empty()) {
		cout << path.top() << " ";
		path.pop();
	}
	cout << endl;
}

	int main()
{
    int n,m;

    // Read the number of nodes and edges
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;

        cin >> u >> v >> w;

        g[u].push_back({ v, w });
    }

    int s, t;
    cin >> s >> t;


    countDistinctShortestPaths(n, m);
    cout << route[t] << endl;
    printShortestPath(s, t);
    cout << "The cost of the shortest path is: " << dist[n] << endl;


    return 0;
}


