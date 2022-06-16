#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include "SemesterProjectHeader.h"
using namespace std;

void MyCharacter::DisplayCharacterMap()
{
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numColumn; j++)
			cout << characterMap[i][j] << "\t";
		cout << endl;
	}
}





void MyMap::ReadTextMap(string s)
{
	MyGraph* myGraph = new MyGraph;
	MyCharacter* myCharacter = new MyCharacter;
	std::ifstream myFile;
	myFile.open(s);

	//Sets the row and column value for the matrix
	char temp;
	myFile >> numRow >> numColumn;
	myFile >> characterIndex;
	myFile >> targetIndex;


	//Initialize size of the matrix
	myMap = new char* [numRow];
	for (int i = 0; i < numRow; i++)
		myMap[i] = new char[numColumn];

	//Populates the matrix with the values from the text file
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numColumn; j++)
		{
			myFile >> temp;
			myMap[i][j] = temp;
		}
	myFile.close();

	numOfVertices = numRow * numColumn;
	myGraph->numRow = numRow;
	myGraph->numColumn = numColumn;
	myCharacter->numRow = numRow;
	myCharacter->numColumn = numColumn;

	delete myGraph;
	delete myCharacter;
}

void MyMap::AutomaticTraverse(MyCharacter* character, vector<int>& nodePath)
{
	SetCharacter(character, characterIndex, targetIndex);
	character->DisplayCharacterMap();
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	for (int i = 0; i < nodePath.size(); i++)
	{
		SetCharacter(character, nodePath[i], targetIndex);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("cls");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		character->DisplayCharacterMap();
	}
	nodePath.clear();
	cout << "Press W,A,S, or D to move the target" << endl;
	cout << "Press 2 for automatic traversal to the new target" << endl;
	cout << "Press q to quit" << endl;
}

void MyMap::SetCharacter(MyCharacter* character, int currentCharIndex, int currentTargetIndex)
{
	//Initialized the character map
	character->characterMap = new char* [numRow];
	for (int i = 0; i < numRow; i++)
		character->characterMap[i] = new char[numColumn];

	//Gives the target and character index a single int vertex value
	int index;
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numColumn; j++)
		{
			index = j + i * numRow;
			character->characterMap[i][j] = myMap[i][j];
			if (index == currentCharIndex)
				character->characterMap[i][j] = 'O';
			else if (index == currentTargetIndex)
				character->characterMap[i][j] = 'X';
		}

	character->numColumn = numColumn;
	character->numRow = numRow;

}

void MyMap::UpdateTarget(MyCharacter* character, int** myGraph, char direction)
{
	int index;
	int updatedTargetIndex = targetIndex;
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numColumn; j++)
		{
			index = j + i * numRow;
			if (index == targetIndex)
			{
				if (direction == 'w')
				{
					updatedTargetIndex -= numRow;
					if (updatedTargetIndex < 0)
					{
						updatedTargetIndex += numRow;
						cout << "Can't move up anymore!" << endl;
					}
				}
				if (direction == 's')
				{
					updatedTargetIndex += numRow;
					if (updatedTargetIndex > numOfVertices)
					{
						updatedTargetIndex -= numRow;
						cout << "Can't move down anymore!" << endl;
					}
				}
				if (direction == 'a')
				{
					updatedTargetIndex -= 1;
					if (updatedTargetIndex < i * numRow)
					{
						updatedTargetIndex += 1;
						cout << "Can't move left anymore!" << endl;
					}
				}
				if (direction == 'd')
				{
					updatedTargetIndex += 1;
					if (updatedTargetIndex > numRow - 1 + i * numRow)
					{
						updatedTargetIndex -= 1;
						cout << "Can't move right anymore!" << endl;
					}
				}

			}
		}
	targetIndex = updatedTargetIndex;
	SetCharacter(character, characterIndex, targetIndex);
}

void MyMap::DisplayMap()
{
	for (int i = 0; i < numRow; i++)
	{
		for (int j = 0; j < numColumn; j++)
			cout << myMap[i][j] << "\t";
		cout << endl;
	}
}





int MyGraph::GetVertex(int i, int j, int n)
{
	//Makes sure the vertex isn't outside the rows and columns.
	if ((i < 0) || (j < 0) || (i >= n) || (j >= n))
		return -1;
	else
		return (j + i * n);
}

int MyGraph::GetEdgeWeight(char utype, char vtype)
{
	if (utype == 'M' && vtype == 'M')
		return 0;
	else if (utype == 'M' && vtype == 'P')
		return 0;
	else if (utype == 'M' && vtype == 'F')
		return 0;
	else if (utype == 'P' && vtype == 'M')
		return 1;
	else if (utype == 'P' && vtype == 'P')
		return 1;
	else if (utype == 'P' && vtype == 'F')
		return 3;
	else if (utype == 'F' && vtype == 'F')
		return 3;
	else if (utype == 'F' && vtype == 'P')
		return 1;
	else if (utype == 'F' && vtype == 'M')
		return 3;
}

void MyGraph::SetEdge(int u, int v, int weight)
{
	myGraph[u][v] = weight;
}

void MyGraph::AdjacencyMatrix(MyMap* map)
{
	//Sets the value of the numRow and numColumn from MyMap
	numColumn = map->numColumn;
	numRow = map->numRow;
	numOfVertices = map->numOfVertices;

	//initialized myGraph
	myGraph = new int* [numOfVertices];
	for (int i = 0; i < numOfVertices; i++)
		myGraph[i] = new int[numOfVertices];
	
	//Gives everything a 0 value in myGraph 
	for (int i = 0; i < numOfVertices; i++)
		for (int j = 0; j < numOfVertices; j++)
			myGraph[i][j] = 0;

	//Used for searching through myMap and finding all the vertex and edges
	for (int i = 0; i < numRow; i++)
		for (int j = 0; j < numColumn; j++)
		{
			int u = GetVertex(i, j, numRow);
			char utype = map->myMap[i][j];

			//Checks all the different possibilities for a vertex.
			int v1 = GetVertex(i - 1, j, numRow);
			int v2 = GetVertex(i + 1, j, numRow);
			int v3 = GetVertex(i, j - 1, numRow);
			int v4 = GetVertex(i, j + 1, numRow);

			if (v1 != -1)
			{
				int vtype = map->myMap[i - 1][j];
				SetEdge(u, v1, GetEdgeWeight(utype, vtype));
			}
			if (v2 != -1)
			{
				int vtype = map->myMap[i + 1][j];
				SetEdge(u, v2, GetEdgeWeight(utype, vtype));
			}
			if (v3 != -1)
			{
				int vtype = map->myMap[i][j - 1];
				SetEdge(u, v3, GetEdgeWeight(utype, vtype));
			}
			if (v4 != -1)
			{
				int vtype = map->myMap[i][j + 1];
				SetEdge(u, v4, GetEdgeWeight(utype, vtype));
			}
		}
}

// Used in dijkstra function, finds the vertex with the minimum distance 
//from the set of vertices that haven't been included yet.
int MyGraph::MinDistance(int dist[], bool vertSet[])
{
	int min = INT_MAX;
	int min_index = 0;

	for (int i = 0; i < numOfVertices; i++)
		if (vertSet[i] == false && dist[i] <= min)
		{
			min = dist[i];
			min_index = i;
		}
	return min_index;
}

void MyGraph::Dijkstra(int source, MyMap* myMap)
{
	distance = new int[numOfVertices];                         
	pi = new bool[numOfVertices];

	path = new int[numOfVertices];
	// set the nodes with infinity distance
	// except for the initial node and mark
	// them unvisited.  
	for (int i = 0; i < numOfVertices; i++)
	{
		distance[i] = INT_MAX;
		pi[i] = false;

	}

	// Source vertex distance is set to zero. 
	//and path source is set to -1 (keeps track of the pathing of nodes)
	distance[source] = 0;    
	path[source] = -1;

	for (int i = 0; i < numOfVertices; i++)
	{
		// vertex not yet included.
		int m = MinDistance(distance, pi); 
		// m with minimum distance included in pi.
		pi[m] = true; 
		for (int j = 0; j < numOfVertices; j++)
		{
			// Updating the minimum distance for the particular node.
			if (!pi[j] && myGraph[m][j] && distance[m] != INT_MAX && distance[m] + myGraph[m][j] < distance[j])
			{
				path[j] = m;
				distance[j] = distance[m] + myGraph[m][j];
			}
		}
	}
	CalculatePath(path, myMap->targetIndex);
	delete [] distance;
	delete [] pi;
	delete [] path;
	for (int i = 0; i < numOfVertices; i++)
		delete [] myGraph[i];
	delete [] myGraph;
}

void MyGraph::CalculatePath(int* parent, int targetIndex)
{
	for (int i = 1; i < numOfVertices; i++)
	{
		//only keeps the path of the nodes need to go to the current target index.
		if (i == targetIndex)
		{
			PrintPath(parent, i);
		}
	}
}

void MyGraph::PrintPath(int* parent, int j)
{
	// Base Case : If j is source, also basically takes care of the duplicates.
	nodePath.clear();
	if (parent[j] == -1)
		return;
	PrintPath(parent, parent[j]);
	//nodes are pushed into a vector where they get passed to the setCharacter function
	nodePath.push_back(j);
}

void MyGraph::DisplayGraph()
{
	for (int i = 0; i < numOfVertices; i++)
	{
		for (int j = 0; j < numOfVertices; j++)
			cout << myGraph[i][j] << "  ";
		cout << endl;
	}
}
