
//this lib use to do input and output and also display the msg
#include <iostream>
//this lib used to handle the word.txt
#include <string>
//this lib used to shrink the size of word. we dont know how many word in that file
#include <vector>
//this lib used to handle file system it write or read the file
#include <fstream>
#include <random>
#include <ctime>
#include <cctype>
#include <cstdlib>
using namespace std;

vector<string> loadWords(const string& filename);

void drawHangman(int triesLeft);

int main(){
	cout <<"Welcome to hangman"<<endl;
     string fileName="word.txt";
	vector<string> wordList = loadWords(fileName);
	
	if(wordList.empty()){
		cerr<<"No word were loaded. The game can not start"<<endl;
		return 1;
	}
	
	cerr << wordList.size() << "words loaded successfully"<<endl;
	for(const string& words:wordList){
		cout <<words<<endl;
		
	}
	
	mt19937 engine(static_cast<unsigned int>(time(0)));
	uniform_int_distribution<int> distribution(0,static_cast<int>(wordList.size() - 1));
	int randomIndex=distribution(engine);
	const string secretWord=wordList[randomIndex];
	
	string guessedWord(secretWord.length(),'-');
	int triesLeft=6;
	string incorrectGuess;
	string allGuessedLetter;
	
	
	while(triesLeft > 0 && guessedWord != secretWord){
		
		char playerGuess;
		
		#ifdef _WIN32
            system("cls"); // For Windows
        #else
            system("clear"); // For Linux, macOS, etc.
        #endif
        
		drawHangman(triesLeft);    
          cout <<"\nWords"<<endl;
          for(char c:guessedWord){
               cout <<c<<' ';
          }    
          cout <<endl;
          cout <<"Tries remaining: "<<triesLeft<<endl;
          if(!incorrectGuess.empty()){
               cout <<"Incorrect Guess: ";
               for(char c:incorrectGuess){
                    cout <<c<<' ';
               }
               cout <<endl;

          }
		
		cout <<"[Debug] Secret word: "<<secretWord[0]<<endl;
		cout <<"[Debug] Guess word: "<<guessedWord<<endl;
		cout <<"[Debug] Tries left: "<<triesLeft<<endl;
		cout <<"Guess a letter: ";cin >>playerGuess;
		// cout <<"[Debug] You guess "<<playerGuess<<endl;
		if(!isalpha(playerGuess)){
			cout <<"Invalid input. Please enter a letter"<<endl;
			continue;
		}
		cout <<"[Debug] You guessed a valid letter"<<endl;
		playerGuess=tolower(playerGuess);
		cout <<"[Debug] Normalized guess: "<<playerGuess<<endl;
		
		if(
			guessedWord.find(playerGuess) !=
			string::npos ||
			incorrectGuess.find(playerGuess) !=
			string::npos
		 ){
		 	cout <<"You have already guessed that letter. Please try again"<<endl;
		 	continue;
		 }
		 
		bool isGuessCorrect=false;
		for(size_t i=0;i<=secretWord.length();++i){
			if(secretWord[i] == playerGuess){
				guessedWord[i]=playerGuess;
				isGuessCorrect=true;
			}
		}
		
		if(isGuessCorrect) cout << "Good guessed"<<endl;
		else{
			cout << "Sorry! This letter is not in the word"<<endl;	
			triesLeft--;
			
			incorrectGuess += playerGuess;	
		} 
		
		allGuessedLetter += playerGuess;
	}

	
	// cout <<"-----Game Over-----"<<endl;
//	cout <<"\t\tGame state initialize"<<endl;
//	cout <<"============================"<<endl;
//	cout <<"[Debug] Secret word: "<<secretWord<<endl;
//	cout <<"[Debug] Guess word: "<<guessedWord<<endl;
//	cout <<"[Debug] Tries left: "<<triesLeft<<endl;
//	cout <<"[Debug] Incorrect Guesses: "<<incorrecctGuess<<" (currently empty)"<<endl;
//	
	
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

void drawHangman(int triesLeft){
//	cout <<"--- Hangman Drawing (Tries Left: "<<triesLeft<<") ---"<<endl;
	switch(triesLeft){
		case 6:{
			cout <<R"( 
                            +---+
					   |   |
					       |
					       |
					       |
					       |
					  =========)" <<endl;
			break;
		}
		case 5:{
			cout <<R"( 
                            +---+
					   |   |
					   0   |
					       |
					       |
					       |
					  =========)" <<endl;
			break;
		}
		case 4:{
			cout <<R"( 
                            +---+
					   |   |
					   0   |
					   |   |
					       |
					       |
					  =========)" <<endl;
			break;
		}
		case 3:{
			cout <<R"( 
                            +---+
					   |   |
					   0   |
					  /|   |
					       |
					       |
					  =========)" <<endl;
			break;
		}
		case 2:{
			cout <<R"( 
                            +---+
					   |   |
					   0   |
					  /|\  |
					       |
					       |
					  =========)" <<endl;
			break;
		}
		case 1:{
			cout <<R"( 
                            +---+
					   |   |
					   0   |
					  /|\  |
					  /    |
					       |
					  =========)" <<endl;
			break;
		}
		case 0:{
			cout <<R"( 
                            +---+
					   |   |
					   0   |
					  /|\  |
					  / \  |
					       |
					  =========)" <<endl;
			break;
		}
		default:{
			cout <<"an error occured in drawing hangman"<<endl;
			break;
		}
		
	}
}