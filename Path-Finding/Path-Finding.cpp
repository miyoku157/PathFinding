// Path-Finding.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
double Distance( point p1,  point p2);
int min(std::vector<std::pair< point, float>*> &vector, std::pair< point, float>* &out);
bool ValidCoordinates(int x, int y, const int& width, const int& height);
bool Containscoord(std::vector<std::pair< point, float>*> &vector, int &x, int &y);
bool Containscoord(std::vector< point> &vector, int &x, int &y);
int FindIndex(std::vector< point> &vector, unsigned int &x, unsigned int &y);
void reverse_array(int* array, int arraylength);
int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,const unsigned char* pMap,
	const int nMapWidth, const int nMapHeight,int* pOutBuffer, const int nOutBufferSize);
 struct point {
	unsigned int x;
	unsigned int y;
	 point* previous;
}init;
int main()
{

	unsigned char pMap[] = { 0, 0, 1, 0, 1, 1, 1, 0, 1 };
	int pOutBuffer[7];
	int test=FindPath(2, 0, 0, 2, pMap, 3, 3, pOutBuffer, 7);
		std::cout << test << std::endl;
	return 0;
}


int FindPath(const int nStartX, const int nStartY, const int nTargetX, const int nTargetY,
	const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
	int* pOutBuffer, const int nOutBufferSize) {
	
	//init algorithm
	std::vector<std::pair< point,float>*> Open = std::vector<std::pair< point,float>*>();
	std::vector< point> Close = std::vector< point>();
	std::pair< point, float>* toKeep=nullptr;
	bool isFinished = false;
	 point target;
	target.x = nTargetX;
	target.y = nTargetY;
	init.x = nStartX;
	init.y = nStartY;
	init.previous = nullptr;
	//Put the starting point in the list
	Open.push_back(new std::pair< point,float>(init,0));
	//loop until we reach the target or until there is no case to test
	while (Open.size() != 0 &&!isFinished) {
		//find the closest point 
		std::pair< point, float>* toRemove;
		int removeIndex=min(Open,toRemove);
		if (toRemove->first.x +toRemove->first.y*nMapWidth == target.x+target.y*nMapWidth) {
			isFinished = true;
		}
		Close.push_back(toRemove->first);

		Open.erase(Open.begin()+removeIndex);
		int coordx;
		int coordy;
		for(int i=0;i<2;i++){
			for (int m = -1; m < 2; m += 2) {
				coordx = toRemove->first.x + (i-1)*m;
				coordy = toRemove->first.y+(i)*m;

				if (ValidCoordinates(coordx, coordy, nMapWidth, nOutBufferSize)) {
					if (pMap[(coordx) + coordy*nMapWidth] != 0) {
						if (!Containscoord(Open, coordx, coordy)
							&& !Containscoord(Close, coordx, coordy)) {
							 point toTest;
							toTest.x = coordx;
							toTest.y = coordy;
							toTest.previous = &toRemove->first;
							Open.push_back(new std::pair< point, float>(toTest, Distance(toTest, target)));

						}
					}
				}
			}
		}
		toKeep = toRemove;
	}
	int index = 0;
	if (toKeep->first.x == target.x&&toKeep->first.y == target.y) {
		 point* temp = &toKeep->first;
		index;
		index++;
		while (temp->previous != NULL) {
			pOutBuffer[index] = temp->x + temp->y*nMapWidth;
			index++;
			temp = temp->previous;
		}
		reverse_array(pOutBuffer, index);
	}
	else {
		index = -1;
	}
	Open.clear();
	Close.clear();
	for (int i = 0; i < index; i++) {
		std::cout << pOutBuffer[i] << std::endl;
	}
	return index;
}
void reverse_array(int* array, int arraylength)
{
	for (int i = 0; i < (arraylength / 2); i++) {
		int temporary = array[i];                 
		array[i] = array[(arraylength - 1) - i];
		array[(arraylength - 1) - i] = temporary;
	}
}
int FindIndex(std::vector< point> &vector,unsigned int &x, unsigned int &y) {

for (size_t i = 0; i < vector.size(); i++) {
		if (vector[i].x == x&&vector[i].y == y) {
			return i;
		}
	}
	return -1;
}
bool Containscoord(std::vector< point> &vector, int &x, int &y) {
	bool isContained = false;
	for (size_t i = 0; i < vector.size(); i++) {
		if (vector[i].x == x&&vector[i].y == y) {
			isContained = true;
		}
	}
	return isContained;
}
bool Containscoord(std::vector<std::pair< point, float>*> &vector, int &x, int &y) {
	bool isContained = false;
	for (size_t i = 0; i < vector.size(); i++) {
		if (vector[i]->first.x == x&&vector[i]->first.y == y) {
			isContained = true;
		}
	}
	return isContained;
}

bool ValidCoordinates(int x, int y,const int& width, const int& buffersize)
{
	if (x < 0||x>2)
	{
		return false;
	}
	if (y < 0)
	{
		return false;
	}
	if (x + y*width > buffersize-1) {
		return false;
	}
	return true;
}
int min(std::vector<std::pair< point,float>*> &vector, std::pair< point, float>* &out) {
	float retour= std::numeric_limits<float>::max();
	int index = 0;
	for (size_t i = 0; i < vector.size(); i++) {
		if (vector[i]->second < retour) {
			retour = vector[i]->second;
			out = vector[i];
			index = i;
		}
	}
	return index;
}

double Distance( point p1,  point p2) {
	int dx = p1.x - p2.x;
	int dy = p1.y - p2.y;
	return sqrt((dx*dx) + (dy*dy));
}