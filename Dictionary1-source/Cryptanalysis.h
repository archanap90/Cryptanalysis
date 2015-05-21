#include<string>
#include<sstream>
#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<vector>

#include"Dictionary1.h"

//Length of the ciphertext and plaintext.
#define LENGTH 100
using namespace std;

class Cryptanalysis
{
private:
	int t; //Key length
	int dict_length1; //Dictionary1 size
	string ciphertext;
	bool compare_result;

	vector<int> keys;

	void hackCipher();
public:
	Cryptanalysis()
	{
		t = 0;
		dict_length1 = strlen(DICTIONARY1);
		compare_result = false;
	}
	~Cryptanalysis()
	{}
	void inputData();
	int Exit();

};