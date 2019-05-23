#include <iostream>
#include "BitField.h"
#include "Eratosthenes.h"
#include <fstream>
#include <conio.h>
using namespace std;



int main(int argc, char* argv[])
{
	int BitLength{ 0 };
	if (argc > 1)
	{
			BitLength = atoi(argv[1]);
	}
	else
	{
		cout << "Input the length of Bit Field" << endl;
		cin >> BitLength;
	}
	//Битовое поле со всеми загруженными битами
	BitField IdentityBF(BitLength);
	IdentityBF.load_AllBits();
	//Битовое поле с битами, загруженными положении простых чисел
	BitField BFPrimes = Eratosthenes(IdentityBF);
	
	
	for (int i = 0; i < BFPrimes.size(); ++i)
	{
		cout << "pos " << i << " = " << BFPrimes[i] << endl;
	}
	cout << "non zero =  " << BFPrimes.nonzero_count() << endl;
	
	ofstream PrimesFile("Primes_File.txt");
	for (int i = 0; i < BFPrimes.size(); ++i)
	{
		if (BFPrimes[i])
		PrimesFile << i << ", ";
	}
	PrimesFile << endl << "num of loaded bits = " << BFPrimes.nonzero_count();
	PrimesFile.close();
	
	_getch();

}