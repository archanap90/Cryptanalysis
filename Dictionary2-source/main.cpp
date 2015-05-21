/*
* Title: Project 1 (Cryptanalysis of substitution ciphers using Dictionary2).
* Purpose: This cryptanalysis project consists of a software implementation of an algorithm that tries to decrypt an L-symbol challenge
*          ciphertext using a plaintext dictionary and within a reasonable amount of time.
* Description:	1. Input - <'t' number of key symbols, (1...24)
'L-symbol' ciphertext challenge, (100)>
2. Message/Ciphertext Space - {<space>,a,..,z}^L, m[1]...m[L], c[1]....c[L]
3. Key space - {0,....,26}^t, k[1]....k[t]
4. Dictionary1 and Dictionary2 - Candidates of plaintext
5. Output- 'L-symbol' plaintext
* Author: Archana P and Prashanth
* Date: 03/04/2015
* Version: 1.0
*/

#include"Cryptanalysis2.h"

using namespace std;

int Exit();
void Cryptanalysis::inputData()
{
	string input = "";
	fflush(stdin);
	cout << "Enter the ciphertext: ";
	getline(std::cin, ciphertext);
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
void Cryptanalysis::hackCipher()
{
	// Variables declaration and initialization
	int difference;
	int i = 0, j = 0;
	int cipher_length, start = 0;

	// = "ccmcxbkjsbeymrfqtlbitjucnmghabwtteeagqebccmotxltbzcnwbtlhxlciptgbdmjghgznhpbgbrutesyjbexncp";
	//"scwjtjacecekc yyyy abcjasdhdsajhdagdhsgahgdhasgdhaskg";
	//"fzktgsvoyqgnvckyfnayiewoqdnscxloyaecvbzgjcaxcgeobauwpjgdgsjiwjtmmuvbihlvseqhmukwgrfenrnfsvseiwemon";
	//"liywbdmuenhhkqsiqgsztxendeniuhaoxshphzyzlgsubbepvwxitjdhpzmhtlnwidijkjekzjrxeoattgsvvkeoqmicdqdesbcg";
	string key = "";
	

	clock_t begin = clock();

	cipher_length = ciphertext.length();

	//Number of Blocks in the ciphertext
	const int NumOfComp = ceil(cipher_length / t);
	int count = 0, prevcount = 0, round = 1;

	//Untill the entire Dictionary is parsed or entire block is parsed 
	//words- word in the Dictionary, j- position in the ciphertext, i-position in the word
	//checkpoint- last point to restart parsing in ciphertext
	srand(time(NULL));
	int words = rand() % 25, checkpoint = 0;

	bool whitespace = false;
	for (i = 0, j = 0; words < 100 && j < cipher_length;)
	{

		if (whitespace && i == 0)
			difference = ciphertext[j] - ' ';
		else
			difference = ciphertext[j] - DICTIONARY2[words][i];
		if (abs(difference) >33 && abs(difference) < 91)
		{
			difference = (difference < 0) ? 91 - abs(difference) : difference - 64;
		}
		else if (difference < 0)

			difference += 26;
		stringstream ss;
		ss << difference;
		if (find(keys.begin(), keys.end(), difference) == keys.end() && count < t)
		{
			key += ss.str() + " ";
			if (whitespace && i == 0)
				whitespace = false;
			else
			{
				i++;
			}
			keys.push_back(difference);
			count++; j++;

			compare_result = true;
		}
		else if (count >= t && find(keys.begin(), keys.end(), difference) == keys.end())
		{
			words++; i = 0;
			j = checkpoint;
			compare_result = false;
			key.clear();
			for (int i = prevcount; i < count; i++)
				keys.pop_back();

			count = prevcount;
		}
		else
		{
			if (whitespace && i == 0)
				whitespace = false;
			else
			{
				i++;
			}
			j++;
			compare_result = true;

		}
		if (compare_result == true && (DICTIONARY2[words][i] == '\0' || j == cipher_length))
		{
			text.push_back(DICTIONARY2[words].substr(0, i));
			if (text.size() == 1)
				start = words;
			prevcount = count;
			words++; i = 0;
			checkpoint = j + 1;
			whitespace = true;

		}
		//Reiterate to find other combination
		if (words == 100 && compare_result == false)
		{
			if (t > 10 && start < 75)
			{
				keys.clear();
				key.clear(); text.clear();
				i = 0; j = 0; count = 0;
				prevcount = 0; whitespace = false;
				words = start + (rand() % 10);
				round++;
			}
		}

	}// for ji

	if (compare_result == true && j == cipher_length)
	{
		cout << "found ,Possible key symbols - " << key << "\nPlain Text : ";

	}
	else
		cout << "Not found in the Dictionary, Partial match -" << endl;
	//Display the plaintext
	for (int j = 0; j < text.size(); j++)
	{
		cout << text.at(j) << " ";
	}

	clock_t end = clock();

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


	cout << "\nTotal time taken: " << elapsed_secs;

}


// Main entry of this application.
int main()
{
	

	Cryptanalysis cryptoObj;
	cryptoObj.inputData();

	
	// Do you want to exit or repeat again?
	if (cryptoObj.Exit() == 1)
		return 0;
	else
		main();
}


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