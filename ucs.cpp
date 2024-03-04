#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    char name;
    int cost;

    Node(char n, int c) : name(n), cost(c) {}

    bool operator>(const Node& other) const {
        return cost > other.cost;
    }
};

class Graph {
public:
    unordered_map<char, vector<pair<char, int>>> adjacencyList;

    void addEdge(char from, char to, int cost) {
        adjacencyList[from].push_back({to, cost});
        adjacencyList[to].push_back({from, cost}); // Assuming the graph is undirected
    }

    int uniformCostSearch(char start, char goal) {
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        unordered_map<char, int> visited;

        pq.push({start, 0});

        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();

            if (current.name == goal) {
                return current.cost;
            }

            if (visited.find(current.name) != visited.end()) {
                continue;
            }

            visited[current.name] = current.cost;

            for (const auto& neighbor : adjacencyList[current.name]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    pq.push({neighbor.first, current.cost + neighbor.second});
                }
            }
        }

        return -1; // If goal is not reachable
    }
};

int main() {
    Graph graph;
    graph.addEdge('S', 'G', 12);
    graph.addEdge('S', 'A', 1);
    graph.addEdge('A', 'B', 3);
    graph.addEdge('A', 'C', 1);
    graph.addEdge('B', 'D', 3);
    graph.addEdge('C', 'D', 1);
    graph.addEdge('C', 'G', 2);
    graph.addEdge('D', 'G', 3);

    char start = 'S';
    char goal = 'G';

    int result = graph.uniformCostSearch(start, goal);

    if (result != -1) {
        cout << "Minimum cost from " << start << " to " << goal << " is: " << result << endl;
    } else {
        cout << "Goal " << goal << " is not reachable from " << start << endl;
    }

    return 0;
}
