
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

string ans_list[12];
int ans_ct;
//void readandwriteFile(string fn);
void testingdoWordsMatch(string s1, string s2);
void testingfindGs(string s1,string s2, char chararr[], bool foundarr[]);
void testingfindYs(string s1,string s2, char chararr[], bool foundarr[]);
int getSize(string fn);
void readFile(string fn, string arr[], int num_words);
void playGame(int num_words, string arr[]);
string getWord(int num, string arr[]);
bool startGuessing(string curr_word);
void printResults();
bool checkWord(string guess, string curr_word);
bool doWordsMatch(string guess, string curr_word);
void findGs(string guess, string curr_word,char ans[], bool found[]);
void findYs(string guess, string curr_word,char ans[], bool found[]);
void reset_ans_list();

int main() {
	srand(time(NULL));

	int num_words = getSize("wordlist.txt");
	string arr[num_words];
	readFile("wordlist.txt", arr, num_words);

    playGame(num_words, arr);

	return 0;
}



bool doWordsMatch(string guess, string curr_word) {
	bool same = true;
	for (int i = 0; i < 5; i++) {
		if (guess[i] != curr_word[i]) {
			same = false;
		}
	}
	return same;
}

void findGs(string guess, string curr_word,char ans[], bool found[]) {
	for (int i = 0; i < 5; i++) {
		if (guess[i] == curr_word[i]) {
			ans[i] = 'G';
			found[i] = true;
		}
		else{
			ans[i] = ' ';
			found[i] = false;
		}
	}
}

void findYs(string guess, string curr_word,char ans[], bool found[]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (guess[i] == curr_word[j] && found[j] != true) {
				ans[i] = 'Y';
				found[j] = true;
				break;
			}
		}
	}
}



void testingdoWordsMatch(string s1, string s2) {
	if (doWordsMatch(s1, s2)) {
		cout << s1 << " and "<< s2 << " are matches!! :-)" << endl;
	}
	else {
		cout << s1 << " and "<< s2 << " do not match :-(  " << endl;
	}
}

void testingfindGs(string s1,string s2, char chararr[], bool foundarr[]) {
	findGs(s1,s2,chararr,foundarr);
	for (int i = 0; i < 5; i++){
		cout << s1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << s2[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << chararr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << foundarr[i] << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	for (int i = 0; i < 5; i++ ) {
		chararr[i] = ' ';
		foundarr[i] = 0;
	}


}

void testingfindYs(string s1,string s2, char chararr[], bool foundarr[]) {
	findYs(s1,s2,chararr,foundarr);
	for (int i = 0; i < 5; i++){
		cout << s1[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << s2[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << chararr[i] << " ";
	}
	cout << endl;
	for (int i = 0; i < 5; i++){
		cout << foundarr[i] << " ";
	}
	cout << endl;
	cout << "**********************************" << endl;
	for (int i = 0; i < 5; i++ ) {
		chararr[i] = ' ';
		foundarr[i] = 0;
	}
}


void playGame(int num_words, string arr[]) {
	string keepPlaying = "Y";
	while ((keepPlaying == "Y") || (keepPlaying == "y")) {
		reset_ans_list();
		string curr_word = getWord(num_words, arr);
		//cout << curr_word<< endl;
		bool f = startGuessing(curr_word);
		if (f) {
			cout << "You won!!  You guessed: " << curr_word << endl;
			cout << endl;
		}
		else {
			cout << "Sorry, you did not win.  The word was: " << curr_word << endl;
			cout << endl;
		}
		cout << "Play Again (Y\\N)?  ";
		cin >> keepPlaying;
	}
	cout << "Thanks for playing! " << endl;
}

bool startGuessing(string curr_word) {
	bool flag = false;
	int i = 0;
	while (i < 5 && !flag) {
		string s;
		cout << "Guess a 5-letter word:   ";
		cin >> s;
		flag = checkWord(s, curr_word);
		i++;
	}
	return flag;
}

bool checkWord(string guess, string curr_word) {
	if (doWordsMatch(guess,curr_word)) {
		return true;
	}
	else {
		char ans[5] = {' ',' ',' ',' ',' '};
		bool found[5] = {0,0,0,0,0};

		findGs(guess, curr_word,ans, found);

		findYs(guess, curr_word, ans, found);

		ans_list[ans_ct*2] = guess;
		ans_list[ans_ct*2 + 1] = ans;

		ans_ct++;

		printResults();
	}
	return false;
}

void printResults() {
	for (int j = 0; j < ans_ct*2; j+=2) {
		for (int i = 0; i < 5; i++) {
			if (ans_list[j+1][i] == ' ') {
				system("Color EF");
				cout << ans_list[j][i] << " ";
			}
			else if (ans_list[j+1][i] == 'G') {
				system("Color AE");
				cout << ans_list[j][i] << " ";
			}
			else {
				system("Color AD");
				cout << ans_list[j][i] << " ";
			}
		}

		cout << endl;
		for (int i = 0; i < 5; i++) {
			cout << ans_list[j+1][i] << " ";
		}
		cout << endl;
	}
}

string getWord(int num, string arr[]) {
	int x = rand() % num;
	string word;
	word = arr[x];
	return word;
}

void readFile(string fn, string arr[], int num_words) {
	ifstream infile(fn.c_str(),ios::in);
	string size;
	infile>>size;
	for (int i = 0; i < num_words; i++) {
		infile>>arr[i];
	}
	infile.close();
}

int getSize(string fn) {
	ifstream infile(fn.c_str(),ios::in);
	string size;
	infile>>size;
	int size_int = stoi(size);
	infile.close();
	return size_int;
}


void reset_ans_list() {
	for (int i = 0; i < 12; i++) {
		ans_list[i] = "";
	}
	ans_ct = 0;
}
