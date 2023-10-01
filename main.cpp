#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <regex>
using namespace std;


//Using regex for Regular Expressions
const regex LITERAL("\\s*\"(?:[^\"\\\\]|\\\\.)*\"\\s*");
const regex INTEGERS("\\s*\\d+\\s*");
const regex IDENTIFIER("\\s*[a-zA-Z_][a-zA-Z0-9_]*\\s*");
const regex KEYWORD("\\s*(int|float|bool|true|false|if|else|then|endif|while|whileend|do|doend|for|forend|input|output|and|or|not)\\s*");
const regex OPERATORS("\\s*(\\+|\\-|\\*|\\/|\\%|\\=|\\<|\\>|\\<=|\\>=|\\==|\\!=)\\s*");
const regex SEPARATORS("\\s*[\\(\\)\\{\\}\\[\\];,]\\s*");


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
                cout << "Keyword\t" << match[0] << endl;
                //cout << match.str(0) <<endl;
                current = match.suffix().str();
                continue;

            }
            else if (regex_search(current, match, SEPARATORS)){
                outPutFile << "SEPARATOR\t" << match[0] << endl;
                cout << "Separator\t" << match[0] << endl;
                current = match.suffix().str();
                continue;
            }


            //Works
            else if (regex_search(current, match, INTEGERS)){
                outPutFile << "INTEGERS\t" << match[0] << endl;
                //cout << match.str(0);
                current = match.suffix().str();
                continue;
            }


            //There is a bug here
            // else if (regex_search(current, match, OPERATORS)){
            //     outPutFile << "OPERATORS\t" << match[0] << endl;
            //     current= match.suffix().str();
                
            // }

            //Bug here as well
            // else if (regex_search(current, match, SEPARATORS)){
            //     outPutFile << "SEPARATORS\t" << match[0] << endl;
            //     current = match.suffix().str();
            // }

            // else if (regex_search(current, match, IDENTIFIER)){
            //     outPutFile << "IDENTIFER\t" << match[0] << endl;
            //     current = match.suffix().str();
            // }
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