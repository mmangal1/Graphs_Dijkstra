#ifndef MAP_H
#define MAP_H

#include "City.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>

class Map{
	
	private:
		std::vector<City*> allCities;
		void makeAdj();
	public:
		Map(std::string filename);
		std::vector<City*> shortestPath(City* start, City* dest);
		unsigned int pathDistance(City* start, City* dest);
		City* findByName(std::string cityName);
		void Dijkstra(int start, int* dest, int* op);
		int weight(int vertex, int index);
		void setExplored(int vertex, bool* expl);
		int minVertex(int* dist, bool* expl);
		~Map();
};

#endif
