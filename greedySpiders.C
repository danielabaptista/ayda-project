# include <iostream>
# include <fstream>
# include <tpl_graph.H>
# include <generate_graph.H>
# include <Dijkstra.H>
# include <tpl_find_path.H>
# include "greedySpiders.H"

using namespace std;


int main()
{
	GT Graph;
	Build_Graph(Graph);
	
	play(Graph);
}
