/* Author@raghu
 * depth first search class to recursively search a connected Graph depth wise
 * PRE-CONDN: Must be a connected graph
 * LIMITATION: doesn't work on unconnected graph
 * RETURNS: NONE, you could make it return something, Although the graph holds the data you can use
 */
struct Graph {
private:
	int current_vertex;
	std::vector<std::vector<int>> edge;
public:
	Graph(std::vector<std::vector<int>> edge) : edge(edge) {}

	void connect(int u, int v) 
	{
		edge[u].push_back(v);
	}

	void dfs(std::queue<int>& Queue, bool *is_visited) 
	{
		if (!Queue.empty()) {
			current_vertex = Queue.front();
			Queue.pop();
			if(is_visited[current_vertex] == false) {
				is_visited[current_vertex] = true;
				//cout << current_vertex << " "; // test me
			}
			for (auto reachable_vertex = 0; reachable_vertex < edge[current_vertex].size(); reachable_vertex++)
				if (is_visited[edge[current_vertex][reachable_vertex]] 
						== false) {
					Queue.push(edge[current_vertex][reachable_vertex]);
					dfs(Queue, is_visited);
				}
		}

		return;
	}

};

/* 
 * Driver Stub to test
 * I used C style stub with commas for quick checking, Old habits. 
 * Never mind delete it and try neatly
 * play around, add some more edges, remove some
 * int main(int argc, char ** argv)
 * {
 * 		Graph graph(std::vector<vector<int>>(10, vector<int>(0)));
 *		graph.connect(0, 1), graph.connect(1, 3), graph.connect(2, 0), graph.connect(2, 3),	graph.connect(3, 2), graph.connect(3, 1);
 *
 *		queue<int> Queue;
 *		bool visited[4] = {false};
 *
 *		Queue.push(2), graph.dfs(Queue, visited);
 *		return 0;
 *	}
 *
 */