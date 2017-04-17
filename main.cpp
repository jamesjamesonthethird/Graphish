#include <deque>
#include <vector>
#include <bitset>
#include <string>
#include <sstream>
#include <iterator>
#include <iostream>
#include <limits>


using namespace std;

template <class T>
struct Graph_Node
{
    bool state  = 0;
    int max_depth = 0;
    vector<Graph_Node<T>*> neighbors;

    Graph_Node(bool state)
    {
        this->state = state;
    }
};

void DFS(Graph_Node<int>*& theNode, int length, bool visited_state, int flag)
{

    if(flag == 1 && theNode->state != visited_state )
    {
        theNode->state = visited_state;

        for(int i = 0; i < theNode->neighbors.size(); i++)
        {
            DFS(theNode->neighbors[i], -1, visited_state, flag);
        }
    }
    else if(theNode->state != visited_state)
    {
        theNode->state =  visited_state;

        if(theNode->max_depth < length)
        {
            theNode->max_depth = length;
        }

        for(int i = 0; i < theNode->neighbors.size(); i++)
        {
            DFS(theNode->neighbors[i], length +1, visited_state, flag);
        }
    }
}

int main()
{
    int* connect_nodes = new int[2];
    int number_of_nodes  = 0;

    string input;

    getline(cin, input);

    stringstream s(input);
    s >> number_of_nodes;

    // Graph: Vector which contains Graph_Nodes each containing a vector neighbouring nodes.
    vector<Graph_Node<int>*> graph_Nodes(number_of_nodes, NULL);

    Graph_Node<int>* newNode_one;
    Graph_Node<int>* newNode_two;

    int node_i;
    int max_depth_node_i;
    bool node_i_state;

    int node_j;
    int max_depth_node_j;
    bool node_j_state;

    for(int i = 0; i <  number_of_nodes - 1; i++)
    {
        getline(cin, input);
        stringstream ss(input);
        ss >> node_i;
        ss >> node_j;

        // connect nodes appropriately
        if(graph_Nodes[node_i] == NULL && graph_Nodes[node_j] == NULL)
        {// Both nodes not connected to graph, max depth for both is 1
            newNode_one = new Graph_Node<int>(false);
            newNode_two = new Graph_Node<int>(false);

            newNode_one->neighbors.push_back(newNode_two);
            newNode_two->neighbors.push_back(newNode_one);

            newNode_one->max_depth = 1;
            newNode_two->max_depth = 1;

            graph_Nodes[node_i] = newNode_one;
            graph_Nodes[node_j] = newNode_two;

        }
        else if (graph_Nodes[node_i] != NULL && graph_Nodes[node_j] == NULL)
        {// a node not connected and node connected.
            Graph_Node<int>* newNode_two = new Graph_Node<int>(graph_Nodes[node_i]->state);

            graph_Nodes[node_j] = newNode_two;
            graph_Nodes[node_j]->max_depth = graph_Nodes[node_i]->max_depth + 1;

            graph_Nodes[node_i]->neighbors.push_back(graph_Nodes[node_j]);
            graph_Nodes[node_j]->neighbors.push_back(graph_Nodes[node_i]);

        }
        else if(graph_Nodes[node_i] == NULL && graph_Nodes[node_j] != NULL)
        {
            Graph_Node<int>* newNode_one = new Graph_Node<int>(graph_Nodes[node_j]->state);

            graph_Nodes[node_i] = newNode_one;
            graph_Nodes[node_i]->max_depth = graph_Nodes[node_j]->max_depth + 1;

            graph_Nodes[node_i]->neighbors.push_back(graph_Nodes[node_j]);
            graph_Nodes[node_j]->neighbors.push_back(graph_Nodes[node_i]);
        }
        else if(graph_Nodes[node_i] != NULL && graph_Nodes[node_j] != NULL)
        {
            max_depth_node_i = graph_Nodes[node_i]->max_depth;
            max_depth_node_j = graph_Nodes[node_j]->max_depth;

            node_i_state = graph_Nodes[node_i]->state;
            node_j_state = graph_Nodes[node_j]->state;

            DFS(graph_Nodes[node_i], max_depth_node_j+1, !node_i_state, 0);
            DFS(graph_Nodes[node_j], max_depth_node_i+1, !node_j_state, 0);

            if(node_i_state != node_j_state)
            {
                if(max_depth_node_i < max_depth_node_j)
                {
                    DFS(graph_Nodes[node_i], -1, node_i_state, 1);
                }
                else
                {
                    DFS(graph_Nodes[node_j], -1, node_j_state, 1);
                }
            }

            graph_Nodes[node_i]->neighbors.push_back(graph_Nodes[node_j]);
            graph_Nodes[node_j]->neighbors.push_back(graph_Nodes[node_i]);

        }
    }

    cout <<"\n";
    for(int k = 0; k < graph_Nodes.size(); k++)
    {
        cout << graph_Nodes[k]->max_depth << endl;
        cout << graph_Nodes[k]->state << endl;
    }

    cout << "Press ENTER to end program...";
    cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    return 0;
}



