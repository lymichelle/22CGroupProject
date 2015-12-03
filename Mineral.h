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
	Mineral(){name = "NULL"; crystalSystem = "NULL";
        cleavage = "NULL"; color = "NULL"; formula = "NULL";
        hardness = 0.0;}
    Mineral(string n, string t, string clv, string col, string v, double h);

	// destructor
	~Mineral(){};

	// mutators
	void setName(string n);
	void setCystalSystem(string t);
	void setCleavage(string clv);
	void setColor(string col);
	void setHardness(double h);
	void setFormula(double v);

	// accessors
	double getHardness() const { return hardness; }
	string getFormula() const { return formula; }
	string getName() const { return name; }
	string getCystalSystem() const { return crystalSystem; }
	string getCleavage() const { return cleavage; }
	string getColor() const { return color; }


    	//Overloaded Comparison operators so the Employee type works with the BST
	bool operator< (const Mineral& emp) const{
		return name < emp.getName();
	}
	bool operator> (const Mineral& emp) const{
		return name > emp.getName();
	}
		bool operator<= (const Mineral& emp) const{
		return name <= emp.getName();
	}
	bool operator>= (const Mineral& emp) const{
		return name >= emp.getName();
	}
	bool operator== (const Mineral& emp) const{
		return name == emp.getName();
	}


	//Overloaded copy constructor
	Mineral& operator= (const Mineral& min) {
		name = min.getName();
		crystalSystem = min.getCystalSystem();
		cleavage = min.getCleavage();
		color = min.getColor();
		formula = min.getFormula();
        hardness = min.getHardness();
        return *this;
	}

	//Overloaded stream insertion operator so the Employee type is printable
	//friend ostream& operator<<(ostream& os,  Employee& emp);
	friend inline ostream& operator<<(ostream& os, Mineral& min)
	{
		os << "Name:\t" << min.getName() << endl
            << "CrystSyst:\t" << min.getCystalSystem() << endl
            << "Formual:\t" << min.getFormula() << endl
            << "Cleav:\t" << min.getCleavage() << endl
            << "Color:\t" << min.getColor() << endl
            << "Hardness:\t" << min.getHardness() << endl;
    		return os;
	}
};
    Mineral::Mineral(string n, string t, string clv, string col, string v, double h){
        name = n;
        crystalSystem = t;
        cleavage = clv;
        color = col;
        formula = v;
        hardness = h;
    }

#endif
