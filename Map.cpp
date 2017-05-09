#include "Map.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <climits>
using namespace std;

Map::Map(string filename){
	ifstream myFile;
	myFile.open(filename.c_str());
	if(myFile.is_open()){
		string cityInfo;
		while(getline(myFile, cityInfo)){
			istringstream iss;
			iss.str(cityInfo);
			string name;
			int x, y;
			iss >> name >> x >> y;
			allCities.push_back(new City(name, x, y));
		}
	}

	makeAdj();
}



Map::~Map(){
	while(allCities.size()!=0){
		City* temp = allCities.back();
		allCities.pop_back();
		delete temp;
	}
}



City* Map::findByName(string cityName){
	for(vector<City*>::iterator it = allCities.begin(); it != allCities.end(); it++){
		if((*it)->getName().compare(cityName)==0)
			return *it;
	}
	return NULL;
	
}



void Map::makeAdj(){
	for(vector<City*>::iterator it = allCities.begin(); it != allCities.end(); it++){
		City* Xpos = NULL;
		City* Ypos = NULL;
		City* Xneg = NULL;
		City* Yneg = NULL;
		for(vector<City*>::iterator i = allCities.begin(); i != allCities.end(); i++){
			if(i!=it){
				if(((*it)->getXCoor()==(*i)->getXCoor())){ 
					if((*it)->getYCoor() < (*i)->getYCoor()){
						if(Ypos && Ypos->getYCoor() > (*i)->getYCoor()){
							Ypos = *i;
						}else if(!Ypos){
							Ypos = *i;	
						}	
					}else{
						if(Yneg && Yneg->getYCoor() < (*i)->getYCoor()){
							Yneg = *i;
						}else if(!Yneg){
							Yneg = *i;	
						}	
					}
				}else if(((*it)->getYCoor() == (*i)->getYCoor())){
					if((*it)->getXCoor() < (*i)->getXCoor()){
						if(Xpos && Xpos->getXCoor() > (*i)->getXCoor()){
							Xpos = *i;
						}else if(!Xpos){
							Xpos = *i;	
						}	
					}else{
						if(Xneg && Xneg->getXCoor() < (*i)->getXCoor()){
							Xneg = *i;
						}else if(!Xneg){
							Xneg = *i;	
						}	
					}
				}
			}
		}
		if(Xpos){
			(*it)->addAdj(Xpos);
		}
		if(Xneg){
			(*it)->addAdj(Xneg);
		}
		if(Ypos){
			(*it)->addAdj(Ypos);
		}
		if(Yneg){
			(*it)->addAdj(Yneg);
		}
	}
	
}



vector<City*> Map::shortestPath(City* start, City* dest){

	int startindex = find(allCities.begin(), allCities.end(), start) - allCities.begin();
		
	int dist[allCities.size()];
	int op[allCities.size()];

	Dijkstra(startindex, dist, op);
	

	int endindex = find(allCities.begin(), allCities.end(), dest) - allCities.begin();
	
	vector<City*> retVal;
	while(op[endindex] >= 0 && endindex != startindex){
		retVal.push_back(allCities.at(endindex));
		endindex = op[endindex];
	}
	
	if(endindex == startindex)
		retVal.push_back(start);

	reverse(retVal.begin(), retVal.end());	
	
	return retVal;
}



unsigned int Map::pathDistance(City* start, City* dest){
	
	int startindex = find(allCities.begin(), allCities.end(), start) - allCities.begin();
		
	int dist[allCities.size()];
	int op[allCities.size()];

	Dijkstra(startindex, dist, op);

	int endindex = find(allCities.begin(), allCities.end(), dest) - allCities.begin();
	return (dist[endindex]==INT_MAX)? -1 : dist[endindex];
}



void Map::Dijkstra(int start, int* dist, int* op){

	bool expl[allCities.size()];

	for(int i = 0; i < allCities.size(); i++){
		dist[i] = INT_MAX;
		op[i] = -1;
		expl[i] = false;
	}

	dist[start] = 0;
	for(int i = 0; i < allCities.size(); i++){
		int vertex = minVertex(dist, expl);
		setExplored(vertex, expl);
		if(dist[vertex] == INT_MAX)
			return;
		list<City*> cityadj = allCities.at(vertex)->getAdjacent();
		vector<City*> adj { begin(cityadj), end(cityadj)}; 
 	      	for(int j = 0; j < adj.size(); j++){
			int index =  find(allCities.begin(), allCities.end(), adj.at(j)) - allCities.begin();
			if(dist[index] > (dist[vertex]+ weight(vertex, index))){
				dist[index]= dist[vertex] + weight(vertex, index);
				op[index] = vertex;
			}
		}
	}
}



int Map::minVertex(int* dist, bool* expl){
	int min = INT_MAX;			
	int min_index = -1;
	for(int x = 0; x < allCities.size(); x++){
		if(expl[x] == false && dist[x] <= min){
			min = dist[x];
			min_index = x;
		}
	}
	return min_index;
}



void Map::setExplored(int vertex, bool* expl){
	expl[vertex] = true;
}



int Map::weight(int vertex, int index){
	int xCoorIndex = allCities.at(index)->getXCoor();
	int yCoorIndex = allCities.at(index)->getYCoor();
	int xCoorVer = allCities.at(vertex)->getXCoor();
	int yCoorVer = allCities.at(vertex)->getYCoor();

	return sqrt(pow((xCoorIndex-xCoorVer),2) + pow((yCoorIndex-yCoorVer),2));
}
