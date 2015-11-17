/*
	Rock header file by John Dwyer
*/

#ifndef ROCK_H
#define ROCK_H

#include <string>
using namespace std;

class Rock
{
private:
	string	name,
		type,
		cleavage,
		color;
	double hardness,
		value;
public:
	// constructor
	Rock();

	// destructor
	~Rock();

	// mutators
	void setName(string n);
	void setType(string t);
	void setCleavage(string clv);
	void setColor(string col);
	void setHardness(double h);
	void setValue(double v);

	// accessors
	double getHardness() { return hardness; }
	double getValue() { return value; }
	string getName() { return name; }
	string getType() { return type; }
	string getCleavage() { return cleavage; }
	string getColor() { return color; }
};

#endif
