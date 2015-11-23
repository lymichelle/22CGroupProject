#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define MAX 1000

int main()
{
	ifstream inFile;
	string name[MAX], formula[MAX], color[MAX], crys_system[MAX], cleavage[MAX];
	double hardness[MAX];
	char ch = ' ';
	int count = 0, i = 0;
	inFile.open("mineral.txt");
	if (inFile.fail())
	{
		cout << "No such file!" << endl;
		exit(100);
	}
	while (!inFile.eof())
	{
		getline(inFile, name[count]);
		getline(inFile, formula[count]);
		getline(inFile, color[count]);
		inFile >> hardness[count];
		inFile.get(ch);
		getline(inFile, crys_system[count]);
		getline(inFile, cleavage[count]);
		inFile.get(ch);
		count++;
	}
	while (i < count)
	{
		cout << name[i] << endl;
		cout << formula[i] << endl;
		cout << color[i] << endl;
		cout << hardness[i] << endl;
		cout << crys_system[i] << endl;
		cout << cleavage[i] << endl;
		i++;
	}
	system("pause");
	return 0;
}