/* Author@raghu
 * breadth first search class to recursively search a connected Graph
 * PRE-CONDN: Must be a connected graph
 * LIMITATION: doesn't work on unconnected graph
 * RETURNS: NONE, you could make it return something
 */
struct Graph{
private:
	int current_vertex;
public:
	std::vector<vector<int>> graph;

	Graph(std::vector<std::vector<int>> graph) :  graph(graph) {}

	void edge(int u, int v) 
	{	
		graph[u].push_back(v);
	}

	void bfs(std::queue<int>& Queue, bool *is_visited)
	{
		while( !Queue.empty()) {
			current_vertex = Queue.front(); // print to play around and see the way it behaves
			is_visited[current_vertex] = true;
			for (auto reachable_vertex = 0; 
				 reachable_vertex < graph[current_vertex].size(); 
				 reachable_vertex++) 
				if (is_visited[graph[current_vertex][reachable_vertex]] 
						== false)
					Queue.push(graph[current_vertex][reachable_vertex]);
			Queue.pop();
			bfs(Queue, visited);
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
 *		graph.edge(0, 1), graph.edge(1, 3), graph.edge(2, 0), graph.edge(2, 3),	graph.edge(3, 2), graph.edge(3, 1);
 *
 *		queue<int> Queue;
 *		bool visited[4] = {false};
 *
 *		Queue.push(2), graph.bfs(Queue, visited);
 *		return 0;
 *	}
 *
 */

