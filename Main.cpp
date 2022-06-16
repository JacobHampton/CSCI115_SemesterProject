#include <iostream>
#include <fstream>
#include <string>

#include "SemesterProjectHeader.h"
using namespace std;

int main()
{
	int mapAns;	
	string chosenMap;
	MyGraph* graph = new MyGraph;
	MyMap* map = new MyMap;
	MyCharacter* character = new MyCharacter;

	cout << "CSCI 115 - Project" << endl;
	cout << "Map 1 is: " << endl;
	map->ReadTextMap("Map1.txt");
	map->DisplayMap();
	cout << endl;

	cout << "Map 2 is: " << endl;
	map->ReadTextMap("Map2.txt");
	map->DisplayMap();
	cout << endl;

	cout << "Map 3 is: " << endl;
	map->ReadTextMap("Map3.txt");
	map->DisplayMap();
	cout << endl;

	cout << "Map 4 is: " << endl;
	map->ReadTextMap("Map4.txt");
	map->DisplayMap();
	cout << endl;

	cout << "Map 5 is: " << endl;
	map->ReadTextMap("Map5.txt");
	map->DisplayMap();
	cout << endl;

	cout << "Choose which map you want(1, 2, 3, 4, or 5): ";
	cin >> mapAns;
	if (mapAns == 1)
	{
		chosenMap = "Map1.txt";
		map->ReadTextMap(chosenMap);	
		graph->AdjacencyMatrix(map);
		graph->Dijkstra(map->characterIndex, map);
		map->SetCharacter(character, map->characterIndex, map->targetIndex);
		character->DisplayCharacterMap();	
	}
	if (mapAns == 2)
	{
		chosenMap = "Map2.txt";
		map->ReadTextMap(chosenMap);
		graph->AdjacencyMatrix(map);
		graph->Dijkstra(map->characterIndex, map);
		map->SetCharacter(character, map->characterIndex, map->targetIndex);
		character->DisplayCharacterMap();
	}
	if (mapAns == 3)
	{
		chosenMap = "Map3.txt";
		map->ReadTextMap(chosenMap);
		graph->AdjacencyMatrix(map);
		graph->Dijkstra(map->characterIndex, map);
		map->SetCharacter(character, map->characterIndex, map->targetIndex);
		character->DisplayCharacterMap();
	}
	if (mapAns == 4)
	{
		chosenMap = "Map4.txt";
		map->ReadTextMap(chosenMap);
		graph->AdjacencyMatrix(map);
		graph->Dijkstra(map->characterIndex, map);
		map->SetCharacter(character, map->characterIndex, map->targetIndex);
		character->DisplayCharacterMap();
	}
	if (mapAns == 5)
	{
		chosenMap = "Map5.txt";
		map->ReadTextMap(chosenMap);
		graph->AdjacencyMatrix(map);
		graph->Dijkstra(map->characterIndex, map);
		map->SetCharacter(character, map->characterIndex, map->targetIndex);
		character->DisplayCharacterMap();
	}

	cout << "Press W,A,S, or D for manual traversal" << endl;
	cout << "Press 2 for automatic traversal" << endl;
	bool finish = false;
	while (!finish)
	{
		char input;
		cin >> input;
		system("cls"); // clear the commandline (to refresh the screen)
		switch (input)
		{
		case 'q': 
			finish = true; 
			break;

		case '2':
			map->AutomaticTraverse(character, graph->nodePath);
			break;

		case 'w':
			map->UpdateTarget(character, graph->myGraph, 'w');
			graph->AdjacencyMatrix(map);
			graph->Dijkstra(map->characterIndex, map);
			character->DisplayCharacterMap();
			cout << "Press W,A,S, or D to move the target" << endl;
			cout << "Press 2 for automatic traversal to the new target" << endl;
			cout << "Press q to quit" << endl;
			break;

		case 'a':
			map->UpdateTarget(character, graph->myGraph, 'a');
			graph->AdjacencyMatrix(map);
			graph->Dijkstra(map->characterIndex, map);
			character->DisplayCharacterMap();
			cout << "Press W,A,S, or D to move the target" << endl;
			cout << "Press 2 for automatic traversal to the new target" << endl;
			cout << "Press q to quit" << endl;
			break;

		case 's':
			map->UpdateTarget(character, graph->myGraph, 's');
			graph->AdjacencyMatrix(map);
			graph->Dijkstra(map->characterIndex, map);
			character->DisplayCharacterMap();
			cout << "Press W,A,S, or D to move the target" << endl;
			cout << "Press 2 for automatic traversal to the new target" << endl;
			cout << "Press q to quit" << endl;
			break;

		case 'd':
			map->UpdateTarget(character, graph->myGraph, 'd');
			graph->AdjacencyMatrix(map);
			graph->Dijkstra(map->characterIndex, map);
			character->DisplayCharacterMap();
			cout << "Press W,A,S, or D to move the target" << endl;
			cout << "Press 2 for automatic traversal to the new target" << endl;
			cout << "Press q to quit" << endl;
			break;
		}
	}
	delete character;
	delete graph;
	delete map;
}