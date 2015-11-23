/*
	Mineral header file by John Dwyer
*/

#ifndef MINERAL_H
#define MINERAL_H

#include <string>
using namespace std;

class Mineral
{
private:
	string	name,
		crystalSystem,
		cleavage,
		color,
		formula;
	double hardness;
public:
	// constructor
	Mineral();

	// destructor
	~Mineral();

	// mutators
	void setName(string n);
	void setCystalSystem(string t);
	void setCleavage(string clv);
	void setColor(string col);
	void setHardness(double h);
	void setFormula(double v);

	// accessors
	double getHardness() { return hardness; }
	double getFormula() { return formula; }
	string getName() { return name; }
	string getCystalSystem() { return crystalSystem; }
	string getCleavage() { return cleavage; }
	string getColor() { return color; }
};

#endif
