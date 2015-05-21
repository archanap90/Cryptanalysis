#include<string>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<vector>

#include"Dictionary2.h"

//Length of the ciphertext and plaintext.
#define LENGTH 100
using namespace std;

class Cryptanalysis
{
private:
	int t; //Key length
	string ciphertext;
	bool compare_result;

	vector<int> keys;
	vector<string> text;

	void hackCipher();
public:
	Cryptanalysis()
	{
		t = 0;
		compare_result = false;
	}
	~Cryptanalysis()
	{}
	void inputData();
	int Exit();

};