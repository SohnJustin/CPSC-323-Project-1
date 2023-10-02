#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstring>
#include <regex>
using namespace std;


//Using regex for Regular Expressions
//const regex LITERAL("\\s*\"(?:[^\"\\\\]|\\\\.)*\"\\s*");


const regex DIGITS("[0-9]");
const regex REAL ("[0-9]+(\\.[0-9]+)?");
const regex IDENTIFIER("[a-zA-Z][a-zA-Z0-9]*");
const regex KEYWORD("(int|float|bool|true|false|if|else|then|endif|while|whileend|do|doend|for|forend|input|output|and|or|not)");
//const regex OPERATORS("\\s*(\\+|\\-|\\*|\\/|\\%|\\=|\\<|\\>|\\<=|\\>=|\\==|\\!=)\\s*");
//const regex OPERATORS("(\\+|\\-|\\*|\\/|\\%|\\=|\\<|\\>|\\<=|\\>=|\\==|\\!=)");
const regex OPERATORS("(\\+|\\-|\\*|\\/|\\%|\\=|\\<|\\>|\\<=|\\>=|\\==|\\!=)");
const regex SEPARATORS("\\s*[\\(\\)\\{\\}\\[\\];,]\\s*");


void lexer(istream& inputFile, ofstream& outPutFile) {
    smatch match;
    string input;
    int i = 0;

    outPutFile << "TOKEN\t\tLEXEMES\n";


    //Test each case one by one to see if the Regular Expressions work
    while(getline(inputFile, input)){
        string current = input;
        while (!current.empty()){
            cout << current << endl;
            cout << i++ << endl;

            //Keywords
            if (regex_search(current, match, KEYWORD)){
                outPutFile << "KEYWORD\t\t" << match[0] << endl;
                cout << "\nKeyword\t\t" << match[0] << endl;
                current = match.suffix().str();
                //cout << current << endl << endl;
                continue;

            }
            //SEPARATORS
            else if (regex_search(current, match, SEPARATORS)){
                outPutFile << "SEPARATOR\t" << match[0] << endl;
                cout << "\nSeparator\t" << match[0] << endl;
                current = match.suffix().str();
                //cout << current << endl << endl;
                continue;
            }

            //Letters
            else if (regex_search(current, match, IDENTIFIER)){
                cout << "Testing if in IDENTIFIER";
                outPutFile << "IDENTIFIER\t" << match[0] << endl;
                cout << "\nIdentifier\t" << match[0] << endl;
                current = match.suffix().str();
                //cout << current << endl << endl;
                continue;
            }

            else if (regex_search(current, match, OPERATORS)){
                outPutFile << "OPERATOR\t" << match[0] << endl;
                cout << "\nOPERATOR\t" << match[0] << endl;
                current = match.suffix().str();
                //cout << current << endl << endl;    //Printing out current line to parse
                continue;
            }
            
            else
                current = current.substr(1);
                continue;

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