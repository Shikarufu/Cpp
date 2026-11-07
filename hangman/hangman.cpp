//this lib use to do input and output and also display the msg
#include <iostream>
//this lib used to handle the word.txt
#include <string>
//this lib used to shrink the size of word. we dont know how many word in that file
#include <vector>
//this lib used to handle file system it write or read the file
#include <fstream>
using namespace std;

vector<string> loadWords(const string& filename);

int main(){
	cout <<"Welcome to hangman"<<endl;
	
	vector<string> wordList=loadWords("word.txt");
	
	if(wordList.empty()){
		cerr<<"No word were loaded. The game can not start"<<endl;
		return 1;
	}
	
	cerr << wordList.size() << "words loaded successfully"<<endl;
	for(const string& words:wordList){
		cout <<words<<endl;
		
	}
	
	return 0;
}

vector<string> loadWords(const string& filename){
	ifstream file(filename);
	
	if(!file.is_open()){
		cerr << "Error: Could not open file name "<<filename<<"! Make sure it is exists."<<endl;
//		early return
		return {};
	}
	
	vector<string> words;
	string currentWord;
	
	while(getline(file,currentWord)){
		
		if(!currentWord.empty()){
			words.push_back(currentWord);
		}
	}
	
	return words;
}