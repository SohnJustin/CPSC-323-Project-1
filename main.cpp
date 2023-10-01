#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <regex>
using namespace std;


//Using regex for Regular Expressions
const regex LITERAL("\"(?:[^\"\\\\]|\\\\.)*\"");
const regex INTEGERS("\\d+");
const regex IDENTIFIER("[a-zA-Z_][a-zA-Z0-9_]*");
const regex KEYWORD ("(int|float|bool|true|false|if|else|then|endif|while|whileend|do|doend|for|forend|input|output|and|or|not)");
const regex OPERATORS ("(\\+|\\-|\\*|\\/|\\%|\\=|\\<|\\>|\\<=|\\>=|\\==|\\!=)");

const regex SEPARATORS("[(){}\\[\\];,]");

void lexer(istream& inputFile, ofstream& outPutFile) {
    smatch match;
    string input;


    //Test each case one by one to see if the Regular Expressions work
    while(getline(inputFile, input)){
        string current = input;
        while (!current.empty()){

            //Works
            if (regex_search(current, match, KEYWORD)){
                outPutFile << "KEYWORD\t" << match[0] << endl;
                //cout << match.str(0) <<endl;
                current = match.suffix().str();

            }

            //Works
            else if (regex_search(current, match, INTEGERS)){
                outPutFile << "INTEGERS\t" << match[0] << endl;
                //cout << match.str(0);
                current = match.suffix().str();
            }

            //There is a bug here
            else if (regex_search(current, match, OPERATORS)){
                outPutFile << "OPERATORS\t" << match[0] << endl;
                current= match.suffix().str();
                
            }

            //Bug here as well
            else if (regex_search(current, match, SEPARATORS)){
                outPutFile << "SEPARATORS\t" << match[0] << endl;
                current = match.suffix().str();
            }
        }
     }

    
     
}


int main() {
    //Reading and writing to files
    fstream input("input_scode.txt");
    ofstream output("output_scode.txt");

    //Lexer function
    lexer(input, output);


    //Closing files
    input.close();
    output.close();

    return 0;
}