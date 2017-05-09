#include "City.h"
#include <iostream>
using namespace std;

City::City(string cityName, int xCoor, int yCoor){
	this->cityName = cityName;
	this->xCoor = xCoor;
	this->yCoor = yCoor;
}

string City::getName(){
	return cityName;
}

int City::getXCoor(){
	return xCoor;
}

int City::getYCoor(){
	return yCoor;
}

list<City*> City::getAdjacent(){
	return edges;
}

bool City::operator< (City &c){
	if(cityName < c.getName())
		return true;
	return false;
} 

void City::addAdj(City* c){
	edges.push_back(c);

}
