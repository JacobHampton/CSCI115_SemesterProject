#pragma once
#include <string>
#include <vector>

class MyCharacter {
public:
	int numRow = 0;
	int numColumn = 0;
	char** characterMap;
	void DisplayCharacterMap();

};

class MyMap {
public:
	int numRow = 0;
	int numColumn = 0;
	int numOfVertices = numRow * numColumn;
	int targetIndex = 0;
	int characterIndex = 0;
	int* nodePath = new int;
	char** myMap;

	void ReadTextMap(std::string mapName);
	void SetCharacter(MyCharacter* character, int charIndex, int targetIndex);
	void AutomaticTraverse(MyCharacter* character, std::vector<int> &nodePath);
	void DisplayMap();
	void UpdateTarget(MyCharacter* character, int**, char direction);
};

class MyGraph {
public:
	int numRow = 0;
	int numColumn = 0;
	int numOfVertices = numRow * numColumn;
	int count = 0;
	int** myGraph;
	bool* pi = new bool;
	int* distance = new int;
	int* path = new int;
	std::vector<int> nodePath;


	void CalculatePath(int* parent, int targetIndex);
	void PrintPath(int parent[], int j);
	int GetVertex(int i, int j, int n);
	int GetEdgeWeight(char utype, char vtype);
	int MinDistance(int dist[], bool vertSet[]);
	void Dijkstra(int source, MyMap* myMap);
	void AdjacencyMatrix(MyMap* myMap);
	void SetEdge(int u, int v, int weight);
	void DisplayGraph();
};


