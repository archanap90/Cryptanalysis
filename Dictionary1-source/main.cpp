/*
* Title: Project 1 (Cryptanalysis of Polyalphabetic substitution ciphers).
* Purpose: This cryptanalysis project consists of a software implementation of an algorithm that tries to decrypt an L-symbol challenge
*          ciphertext using a plaintext dictionary and within a reasonable amount of time.
* Description:	1. Input - <'t' number of key symbols, (1...24)
'L-symbol' ciphertext challenge, (100)>
2. Message/Ciphertext Space - {<space>,a,..,z}^L, m[1]...m[L], c[1]....c[L]
3. Key space - {0,....,26}^t, k[1]....k[t]
4. Dictionary1 and Dictionary2 - Candidates of plaintext
5. Output- 'L-symbol' plaintext
* Authors: Archana Purushothama and Prashanth
* Date: 03/04/2015
* Version: 1.0
*/

#include"Cryptanalysis.h"


void Cryptanalysis::inputData()
{
	string input = "";
	fflush(stdin);
	cout << "Enter the ciphertext: ";
	getline(std::cin,ciphertext);
	fflush(stdin);

	while (true) {
		cout << "Enter the size of key (t): ";
		cin >> input;

		// This code converts from string to number safely.
		stringstream myStream(input);
		if (myStream >> t && (t > 0 && t < 25))
			break;
		cout << "Invalid number, please try again" << endl;
	}

	cout << "\nEntered ciphertext: " << ciphertext << " and size of key: " << t << endl;
	hackCipher();
}

/*Method hackCipher - Based on the difference/number of shifts between the ciphertext and plaintext in Dictionary1. 
						Possible keyset is determined and count is checked to verify the correct plaintext */
void Cryptanalysis::hackCipher()
{
	// Variables declaration and initialization
	string key = "";
	int count = 0;
	int difference;
	int i = 0, j = 0;
	int cipher_length = ciphertext.length();
	clock_t begin = clock();

	
	//Untill the entire Dictionary is parsed or entire ciphertext is parsed 
	//i- position in the Dictionary, j- position in the ciphertext
	for (i = 0, j = 0; i < dict_length1 && j < cipher_length;)
	{
		difference = ciphertext[j] - DICTIONARY1[i + j];

		//Handling Whitespace in substitution
		if (abs(difference) >33 && abs(difference) < 91)
		{
			difference = (difference<0) ? 91 - abs(difference) : difference - 64;
		}
		else if (difference < 0)

			difference += 26;

		stringstream ss;
		ss << difference;

		//Check if the key symbol is already in 'key'
		if (find(keys.begin(), keys.end(), difference) == keys.end() && count < t)
		{
			key += ss.str() + " ";
			keys.push_back(difference);
			count++; j++;
			compare_result = true;
		}
		//count exceeds the keylength and hence its an incorrect plaintext, so restart the process 
		else if (count >= t && find(keys.begin(), keys.end(), difference) == keys.end())
		{
			i++; j = 0; count = 0;
			compare_result = false;
			key.clear();
			keys.clear();
		}
		else
			j++;

	}// for loop to parse entire dictionary and cipher

	//Plaintext found in Dictionary1 & the possible key symbols
	if (compare_result == true)
	{
		cout << "found ,Possible key symbols - " << key << "\nPlain Text : ";
		//Display the plaintext
		for (int j = i; j<i + cipher_length; j++)
			cout << DICTIONARY1[j];
	}
	else
		cout << "Not found in the Dictionary" << endl;


	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	//time taken for cryptanalysis
	cout << "\nTotal time taken: " << elapsed_secs<<" seconds"<<endl;
}
// Main entry of this application.
int main()
{
		//applied cryptography course spring nyu polytechnic school of engineering computer science modern tec 
	//"fzktgsvoyqagnavckyafnayiewaoqdnascaxloyaecvabzgajcaxcgeoabauwpjgdgsajiwjatmmuvbaihalvseaqhmukwgrafea";
	//"fzktguzmclbqwbbpmc";"liywbdmuenhhkqsiqgsztxendeniuhaoxshphzyzlgsubbepvwxitjdhpzmhtlnwidijkjekzjrxeoattgsvvkeoqmicdqdesbcg";//giuhrirrykizvi";//egsfpgqpuifwvf";
	Cryptanalysis cryptoObj;
	cryptoObj.inputData();
		

	// Do you want to exit or repeat again?
	if (cryptoObj.Exit() == 1)
		return 0;
	else
		main();
}

//Exit from the program based on user input
int Cryptanalysis::Exit() {
	char exit;
	cout << "\n";
exitloop:
	cout << "\nDo you want to quit the program? (y/n)";
	cin >> exit;

	switch (exit) {
	case 'y':
	case 'Y':
		return 1;
		break;
	case 'n':
	case 'N':
		system("cls");
		return 0;
		break;
	default:
		goto exitloop;
		break;
	}
}