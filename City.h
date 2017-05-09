#ifndef CITY_H
#define CITY_H

#include <cstdlib>
#include <string>
#include <list> //linkedlist
	
class City{

	private:
		std::string cityName;
		int xCoor;
		int yCoor;
		std::list<City*> edges;	
	public:
		City(std::string cityName, int xCoor, int yCoor);
		std::string getName();
		int getXCoor();
		int getYCoor();
		std::list<City*> getAdjacent();
		bool operator< (City &c);
		void addAdj(City* c);
};

#endif
