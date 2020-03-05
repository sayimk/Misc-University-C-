/*
 * Path.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#include <iostream>
#include <exception>
#include "Path.h"

using std::ostream;
using std::pair;
using std::make_pair;
using std::vector;

Path::Path()
{
	currentX = 0;
	currentY=0;

}

Path::Path(const Path& other)
{
	currentX = other.currentX;
	currentY = other.currentY;
	visitedPositions=other.visitedPositions;
	directionVector = other.directionVector;
}

Path::Path(Path&& other)
{
	currentX = other.currentX;
	currentY = other.currentY;
	visitedPositions=other.visitedPositions;
	directionVector = other.directionVector;

	//resetting other vals
	other.currentX = 0;
	other.currentY = 0;
	other.directionVector.clear();
	other.visitedPositions.clear();
}

Path& Path::operator=(const Path& other)
{
	return *this;
}

Path& Path::operator=(Path&& other)
{
	return *this;
}

Path::Path(std::vector<Direction> path)
{
	currentX=0;
	currentY=0;

	for(int i =0; i<path.size(); i++){
		move(path.at(i));
	}

}

Path::~Path()
{
}

pair<int,int> Path::current() const
{
	return make_pair(0,0);
}

void Path::move(const Direction& d)
{
	int incrementVal = 1;

	if( (d==N)||(d==S)||(d==E)||(d==W)||(d==NE)||(d==NW)||(d==SE)||(d==SW)){

		if (d==N){

			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(N);
			currentY = currentY+1;

		}else if(d==E){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(E);
			currentX = currentX+1;

		}else if(d==W){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(W);
			currentX = currentX-1;
		}else if(d==S){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(S);
			currentY = currentY-1;
		}else if (d==NE){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(NE);
			currentX = currentX+1;
			currentY = currentY+1;
		}else if (d==NW){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(NW);
			currentX = currentX-1;
			currentY = currentY+1;
		}else if (d==SE){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(SE);
			currentX = currentX+1;
			currentY = currentY-1;
		}else if (d==SW){
			visitedPositions.push_back(std::make_pair(currentX, currentY));
			directionVector.push_back(SW);
			currentX = currentX-1;
			currentY = currentY-1;
		}

	} else{
		//throw an exception
		throw new std::exception();
	}
}

bool Path::operator==(const Path& other) const {

	if (currentX != other.currentX)
		return false;

	if (currentY != other.currentY)
		return false;

	if (visitedPositions.size()!=other.visitedPositions.size())
		return false;

	for(int i =0; i<visitedPositions.size(); i++){

		if(visitedPositions.at(i).first!=other.visitedPositions.at(i).first)
			return false;

		if(visitedPositions.at(i).second!=other.visitedPositions.at(i).second)
			return false;
	}

	if (directionVector.size()!=other.directionVector.size())
		return false;

	for(int i =0; i<directionVector.size(); i++){

		if(directionVector.at(i)!=other.directionVector.at(i))
			return false;
	}

	return true;
}

bool Path::operator!=(const Path& other) const {
	if ((currentX == other.currentX)&&(currentY==other.currentY))
		return false;


	if(visitedPositions.size()!=other.visitedPositions.size()){
		for(int i =0; i<visitedPositions.size(); i++){

			if(visitedPositions.at(i).first==other.visitedPositions.at(i).first)
				return false;

			if(visitedPositions.at(i).second==other.visitedPositions.at(i).second)
				return false;
		}
	}else{
		return true;
	}

	if (directionVector.size()!=other.directionVector.size()){

		for(int i =0; i<directionVector.size(); i++){

			if(directionVector.at(i)==other.directionVector.at(i))
				return false;
		}
	}else{
		return true;
	}
	return true;
}

bool Path::operator<(const Path& other) const {

	if (other.directionVector.size()<=directionVector.size())
		return false;

	int iterator = (directionVector.size()-1);

	for (int i=(other.directionVector.size()-1); (i >=0); i--){

		if (directionVector.at(iterator)!=other.directionVector.at(i))
			return false;

		if(iterator >0)
			iterator = iterator-1;
		else
			return true;
	}

	return false;
}

bool Path::operator<=(const Path& other) const {

	bool equalityTest = true;

	if (other.directionVector.size()<directionVector.size())
		return false;

	//Equality Check
		if (currentX != other.currentX)
			equalityTest =  false;

		if (currentY != other.currentY)
			equalityTest =  false;

		if (visitedPositions.size()!=other.visitedPositions.size())
			equalityTest =  false;

		for(int i =0; i<visitedPositions.size(); i++){

			if(visitedPositions.at(i).first!=other.visitedPositions.at(i).first)
				equalityTest =  false;

			if(visitedPositions.at(i).second!=other.visitedPositions.at(i).second)
				equalityTest =  false;
		}

		if (directionVector.size()!=other.directionVector.size())
			equalityTest =  false;

		for(int i =0; i<directionVector.size(); i++){

			if(directionVector.at(i)!=other.directionVector.at(i))
				equalityTest =  false;
		}


		if (equalityTest==true)
			return true;
		//if fail then check extension

	//Extension Test
	int iterator = (directionVector.size()-1);

	for (int i=(other.directionVector.size()-1); (i >=0); i--){

		if (directionVector.at(iterator)!=other.directionVector.at(i))
			return false;

		if(iterator >0)
			iterator = iterator-1;
		else
			return true;
	}



	return true;
}

bool Path::operator>(const Path& other) const {

	if (other.directionVector.size()>=directionVector.size())
		return false;

	int iterator = (other.directionVector.size()-1);

	for (int i=(directionVector.size()-1); (i >=0); i--){

		if (other.directionVector.at(iterator)!=directionVector.at(i))
			return false;

		if(iterator >0)
			iterator = iterator-1;
		else
			return true;
	}

	return false;
}

bool Path::operator>=(const Path& other) const {
	bool equalityTest = true;

	if (other.directionVector.size()<directionVector.size())
		return false;

	//Equality Check
		if (currentX != other.currentX)
			equalityTest =  false;

		if (currentY != other.currentY)
			equalityTest =  false;

		if (visitedPositions.size()!=other.visitedPositions.size())
			equalityTest =  false;

		for(int i =0; i<visitedPositions.size(); i++){

			if(visitedPositions.at(i).first!=other.visitedPositions.at(i).first)
				equalityTest =  false;

			if(visitedPositions.at(i).second!=other.visitedPositions.at(i).second)
				equalityTest =  false;
		}

		if (directionVector.size()!=other.directionVector.size())
			equalityTest =  false;

		for(int i =0; i<directionVector.size(); i++){

			if(directionVector.at(i)!=other.directionVector.at(i))
				equalityTest =  false;
		}


		if (equalityTest==true)
			return true;
		//if fail then check extension

	//Extension Test
		int iterator = (other.directionVector.size()-1);

			for (int i=(directionVector.size()-1); (i >=0); i--){

				if (other.directionVector.at(iterator)!=directionVector.at(i))
					return false;

				if(iterator >0)
					iterator = iterator-1;
				else
					return true;
			}



	return true;
}

Path Path::operator+(const Path& other) const {
	Path res;


	res.currentX = currentX;
	res.currentY = currentY;
	res.directionVector = directionVector;
	res.visitedPositions = visitedPositions;



	for(int i =0; i <other.visitedPositions.size(); i++){

		if (i != 0){
		res.visitedPositions.push_back(std::make_pair(res.currentX,	res.currentY));

		res.currentX = 	res.currentX +other.visitedPositions.at(i).first;
		res.currentY = 	res.currentY + other.visitedPositions.at(i).second;
		}

		//if this line causes null ptr error seperate and add
		res.directionVector.push_back(other.directionVector.at(i));
	}

	res.visitedPositions.push_back(std::make_pair(res.currentX,	res.currentY));

	res.currentX = 	res.currentX + other.currentX;
	res.currentY = 	res.currentY + other.currentY;


	return res;
}

Path Path::operator-(const Path& other) const {
	Path res;

	Path sub;

	Path original;

	if(other.directionVector.size()>directionVector.size()){

		original.currentX = other.currentX;
		original.currentY = other.currentY;
		original.directionVector = other.directionVector;
		original.visitedPositions = other.visitedPositions;

		sub.currentX = currentX;
		sub.currentY = currentY;
		sub.directionVector = directionVector;
		sub.visitedPositions = visitedPositions;

	}else{

		sub.currentX = other.currentX;
		sub.currentY = other.currentY;
		sub.directionVector = other.directionVector;
		sub.visitedPositions = other.visitedPositions;

		original.currentX = currentX;
		original.currentY = currentY;
		original.directionVector = directionVector;
		original.visitedPositions = visitedPositions;
	}



	res.currentX = original.currentX;
	res.currentY = original.currentY;
	res.directionVector = original.directionVector;
	res.visitedPositions = original.visitedPositions;




	int iterator = (original.directionVector.size()-1);

	for (int i=(sub.directionVector.size()-1); (i >=0); i--){

		if (original.directionVector.at(iterator)!=sub.directionVector.at(i))
			throw new std::exception();

		if(iterator >=0)
			iterator = iterator-1;
		else
			iterator = (original.directionVector.size()-1);
	}

	res.directionVector.pop_back();

	for (int i =0; i <sub.directionVector.size()-1; i++){
		res.directionVector.pop_back();
		res.visitedPositions.pop_back();
	}



	res.currentX = res.visitedPositions.at((res.visitedPositions.size()-1)).first;
	res.currentY = res.visitedPositions.at((res.visitedPositions.size()-1)).second;
	res.visitedPositions.pop_back();

	return res;
}

int Path::minX() const {

	int lowestX = currentX;

	for(int i =0; i <visitedPositions.size(); i++){
		if(visitedPositions.at(i).first<lowestX){
			lowestX = visitedPositions.at(i).first;
		}
	}

	return lowestX;
}

int Path::maxX() const {
	int highestX = currentX;

	for(int i =0; i <visitedPositions.size(); i++){
		if(visitedPositions.at(i).first>highestX){
			highestX = visitedPositions.at(i).first;
		}
	}

	return highestX;
}

int Path::minY() const {
	int lowestY = currentY;

	for(int i =0; i <visitedPositions.size(); i++){
		if(visitedPositions.at(i).second<lowestY){
			lowestY = visitedPositions.at(i).second;
		}
	}
	return lowestY;
}

int Path::maxY() const {
	int highestY = currentY;

	for(int i =0; i <visitedPositions.size(); i++){
		if(visitedPositions.at(i).second>highestY){
			highestY = visitedPositions.at(i).second
					;
		}
	}

	return highestY;
}

unsigned int Path::visited(int x, int y) const {

	int found = -1;

	for(int i =0; i <visitedPositions.size(); i++){
		if((visitedPositions.at(i).first == x)&&(visitedPositions.at(i).second==y)){
			found = i;
		}
	}

	if ((currentX ==x)&&(currentY==y))
		return visitedPositions.size();


	if(found==-1)
		throw new std::exception();


	return found;
}

int Path::length() const
{
	//+1 because adding current x and y
	return (visitedPositions.size()+1);
}

int Path::space() const
{
	int totalSpace = 0;
	vector<std::pair<int, int>> ignore;
	bool added = false;
	bool toBeIgnored = false;

	for (int i=0; i< visitedPositions.size(); i++){

		for (int k=0; k<ignore.size(); k++){
			if ((ignore.at(k).first==visitedPositions.at(i).first)&&(ignore.at(k).second==visitedPositions.at(i).second))
				toBeIgnored = true;
		}

		if (!toBeIgnored){
			for (int j =0; j <visitedPositions.size(); j++){

				if(!added){
					if((visitedPositions.at(i).first==visitedPositions.at(j).first)
							&&(visitedPositions.at(i).second==visitedPositions.at(j).second)){

						ignore.push_back(std::make_pair(visitedPositions.at(i).first, visitedPositions.at(i).second));
						added = true;
						totalSpace = totalSpace+1;
					}
				}
			}
		}
		toBeIgnored = false;
		added = false;
	}


	bool checkCurrent = false;

	for (int i=0; i <visitedPositions.size(); i++){

		if ((currentX==visitedPositions.at(i).first)&&(currentY==visitedPositions.at(i).second))
			checkCurrent = true;

	}

	if (!checkCurrent){
		return (totalSpace+1);
	}

	return totalSpace;
}

ostream& operator<<(ostream& o, const Path& p) {

	//contruct top border

	std::string topBorder;
	std::string topSpace;
	std::string bottomSpace;
	std::string bottomBorder;
	std::string row;
	int leftEdge = ((p.minX()-2)*3);
	int rightEdge =((p.maxX())*3);

	for (int i= ((p.minX()-2)*3); i<=((p.maxX())*3); i++){
		topBorder = topBorder+"*";

		if ((i ==leftEdge)||(i==rightEdge))
			topSpace = topSpace+"*";
		else
			topSpace = topSpace+" ";

	}

	o<<topBorder<<std::endl;

	//Adding path rows
	row="";



	bool visited = false;

	for (int k = (p.maxY()); k>= (p.minY()); k--){

		o<<topSpace<<std::endl;

		row = row +"* ";

		//begin of row
		for(int i = p.minX(); i<=p.maxX(); i++){

			//begin of visited Pos check
			for (int j = 0; j<p.visitedPositions.size(); j++){

				if ((p.visitedPositions.at(j).first==i)&&(p.visitedPositions.at(j).second==k)&&(!visited)){
					//if a valid visited Position
					visited = true;
				}
			}
			//end of visit pos check

			if ((p.currentX == i)&&(p.currentY==k))
				visited = true;

			//checking if the position was visited by the path
			if (visited){
				if ((k==0)&&(i==0))
					row = row+" s ";
				else if ((p.currentX==k)&&(p.currentY==i))
					row=row+" e ";
				else
					row = row+" o ";

			}else {
				row = row + "   ";
			}
			visited = false;
		}//end of row


		row = row +" *";


		o<<row<<std::endl;
		o<<topSpace<<std::endl;
		row = "";

	}


	//end of path rows and adding end Space
	o<<topBorder<<std::endl;


	return o;
}

/*
 * Path.h
 *
 *  Created on: Nov 23, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
