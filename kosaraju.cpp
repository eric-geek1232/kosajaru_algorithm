/*By Eric 24/01/2021 -KOSARAJU ALGORITHM- */
#include <iostream>
#include <stack>

#define CONVERT_CHAR_TO_INDEX(caracter) (caracter - 'A') 
#define CONVERT_INT_TO_CHAR(integer) (char(integer + 65))

using namespace std;

// LINKED LIST STRUCTURE
struct Node
{
	char vertex;
	Node *next;
};

class Graph
{
	private:
		Node **adjacencyList;
		Node **adjacencyList_aux;
		stack<Node*> myStack;
		bool *isVisited;
		int nVertices;
		
		Node *createVertex(char vertex);
		void insertList(Node *&edges, char vertex);
		void printList(Node *edges);
		void startDFS(int start);
		void startDFS2(int start);
		void resetNodesVisited();
		void DFS(Node *edges);
		void DFS2(Node *edges);
		void startReverse();
		void reverse(Node *edges, Node *parent);
		void showStronglyConectedComponents();
		
	public:
		Graph();
		Graph(int nVertices);
		void setAdjacencyList();
		void showAdjacencyList();
		void startkosarajuAlgo();
		bool isEmpty();
};

Graph::Graph()
{
	nVertices = 0;
}

Graph::Graph(int nVertices)
{
	this->nVertices = nVertices;
	isVisited = new bool[nVertices];
	adjacencyList = new Node*[nVertices];
	adjacencyList_aux = new Node*[nVertices];
	
	for (int v = 0; v < nVertices; v++) {
		// CREATE HASH TABLE
		adjacencyList[v] = NULL;
		adjacencyList_aux[v] = NULL;
		
		insertList(adjacencyList[v], CONVERT_INT_TO_CHAR(v));
		insertList(adjacencyList_aux[v], CONVERT_INT_TO_CHAR(v));
	}
}

Node *Graph::createVertex(char vertex)
{
	Node *newNode = new Node();
	
	newNode->vertex = vertex;
	newNode->next = NULL;
	
	return newNode; 
}

void Graph::setAdjacencyList()
{
	char vertex;
	char noPath;
	char currentVertex;
	
	for (int v = 0; v < nVertices; v++) {
		currentVertex = CONVERT_INT_TO_CHAR(v);
		cout<< "\n\n\t Add the routes of "<< currentVertex<< endl;
		
		// CREATE ROUTE
		do {
			cout<< "\n [Warning]-Would you like to add routes? [s/n]: ";
			cin>> noPath;
			
			noPath = toupper(noPath);
			
			if (noPath != 'S') {
				break;
			}
			
			cout<< "\n\n "<< currentVertex<< "--> ";
			cin>> vertex;
			
			vertex = toupper(vertex);
			
			// INSERT ROUTE
			insertList(adjacencyList[v], vertex);
			
		} while (noPath == 'S');
		
		cout<< "\n";
	}
}

void Graph::insertList(Node *&edges, char point)
{
	// INSERT ALWAYS AT THE END OF THE LIST
	if (edges == NULL) {
		Node *newNode = createVertex(point);
		edges = newNode;
		
		return;		
	}
	
	// KEEP ITERATING
	insertList(edges->next, point);
}

void Graph::showAdjacencyList()
{
	cout<< "\n\n\t\tShowing Adjacency List...\n"<< endl;
	cout<< "\n\tVertices\n"<< endl;
	
	// ITERATE EACH OF THE LISTS
	for (int v = 0; v < nVertices; v++) {
		printList(adjacencyList[v]);
		cout<< "\n\n";	
	}	
}

void Graph::printList(Node *edges)
{
	// END OF THE LIST
	if (edges == NULL) return;
	
	cout<< " ("<< edges->vertex<< ")   ";
	
	// KEEP ITERATING
    printList(edges->next);
}

void Graph::startkosarajuAlgo()
{
	resetNodesVisited();
	
	startDFS(0);	
	
	startReverse();
	
	resetNodesVisited();
	
	showAdjacencyList();
	
	showStronglyConectedComponents();
}

void Graph::showStronglyConectedComponents()
{
	int scc_count = 1;
	
	cout<< "\n\n\t Showing... SCCs\n"<< endl;
	
	while (!myStack.empty()) {
		Node *currentNode = myStack.top();
		int index = CONVERT_CHAR_TO_INDEX(currentNode->vertex);
		
		myStack.pop();
		
		if (!isVisited[index]) {
			cout<< " ["<< scc_count<< "] SCC: ";
			startDFS2(index);
			cout<<"\n\n";
			
			scc_count++;
		}
	}
}

void Graph::startDFS(int start)
{	
	isVisited[start] = true;
	DFS(adjacencyList[start]->next);
	
	Node *vertex = createVertex(CONVERT_INT_TO_CHAR(start));
	
	myStack.push(vertex);
}

void Graph::DFS(Node *edges)
{
	// END OF THE LIST
	if (edges == NULL) return;	
    
    // GET NEIGHBOR
    int index = CONVERT_CHAR_TO_INDEX(edges->vertex);
    
    if (!isVisited[index]) {
    	// RECURSIVE FUNCTION
    	startDFS(CONVERT_CHAR_TO_INDEX(adjacencyList[index]->vertex));
    	return;
	}
	
	// GO DEEPLY
	DFS(edges->next);
}

void Graph::startDFS2(int start)
{	
	cout<< CONVERT_INT_TO_CHAR(start)<< " ";
	isVisited[start] = true;
	
	DFS2(adjacencyList_aux[start]->next);	
}

void Graph::DFS2(Node *edges)
{
	if (edges == NULL) return;	
    
    int index = CONVERT_CHAR_TO_INDEX(edges->vertex);
    
    if (!isVisited[index]) {
    	startDFS2(CONVERT_CHAR_TO_INDEX(adjacencyList_aux[index]->vertex));
    	return;
	}
	
	DFS2(edges->next);
}

void Graph::startReverse()
{
	for (int v = 0; v < nVertices; v++) {
		reverse(adjacencyList[v]->next, adjacencyList[v]);
	}
}

void Graph::reverse(Node *edges, Node *parent)
{
	if (edges == NULL) return;
	
	int src = CONVERT_CHAR_TO_INDEX(edges->vertex);
	
	insertList(adjacencyList_aux[src], parent->vertex);
	
	reverse(edges->next, parent);
}

bool Graph::isEmpty() 
{
	return nVertices == 0 ? true : false; 
}

void Graph::resetNodesVisited()
{
	for (int v = 0; v < nVertices; v++) {
		isVisited[v] = false;
	}
}

int main()
{
	Graph *graph = new Graph();
	char start;
	int nVertices;
	
	int option;
	
	do {
		cout<< "\t Kosaraju algorithm\n"<< endl;
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< " [1] Create Graph"<< endl;
		cout<< " [2] Show Strongly Conected Components"<< endl;
		cout<< " [3] Exit"<< endl;
		cout<< "\n Choose: ";
		cin>>option;
		
		switch(option) {
			case 1:
				delete graph;
				
				cout<< "\n\n Type the number of vertices ";
				cin>> nVertices;
				
				graph = new Graph(nVertices);
				
				graph->setAdjacencyList();
				break;
				
			case 2:
				if (!graph->isEmpty()) {
					graph->startkosarajuAlgo();	
				} else {
					cout<< "\n\n [Warning]-there's no a graph\n"<< endl;
				}
				break;
				
			case 3:
				cout<< "\n\n\t**Big thanks for using this program**\n"<< endl;
				break;
				
			default:
				cout<< "\n\n\tWrong option... try again!\n"<< endl;
		}
		
		system("pause");
		system("cls");
	} while (option != 3);
	
	return 0;
}
