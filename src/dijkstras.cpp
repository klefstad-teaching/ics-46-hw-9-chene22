#include "dijkstras.h"
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Node{
    int vertex;
    int dist;
    Node(int ver, int dis)
        : vertex{ver}, dist{dis}
        {}
};

// we need a custom operator object thing to compare nodes
struct NodeComparer{
    bool operator()(const Node& first, const Node& second) const {
        return first.dist > second.dist;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;

    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, NodeComparer> pq;
    pq.push(Node{source, 0});
    distance[source] = 0;

    while(!pq.empty()){
        Node current = pq.top();
        pq.pop();

        int u = current.vertex;
        if(visited[u]){
            continue;
        }

        visited[u] = true;

        for(const Edge& edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;

            if(!visited[v] && distance[u] != INF && distance[u] + weight < distance[v]){
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> shortest_path;
    if(distances[destination] == INF){
        return shortest_path;
    }

    stack<int> reversed_stack;
    
    for(int i = destination; i != -1; i = previous[i]){
        reversed_stack.push(i);
    }

    while(!reversed_stack.empty()){
        shortest_path.push_back(reversed_stack.top());
        reversed_stack.pop();
    }

    return shortest_path;
}

void print_path(const vector<int>& v, int total){
    for(size_t i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}