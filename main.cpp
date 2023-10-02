#include <cstring>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

// Using regex for Regular Expressions
// const regex LITERAL("\\s*\"(?:[^\"\\\\]|\\\\.)*\"\\s*");
const regex DIGITS("[0-9]");
const regex REAL("[0-9]+(\\.[0-9]+)?");
const regex IDENTIFIER("[a-zA-Z][a-zA-Z0-9]*");
// const regex
// KEYWORD("\\s*(int|float|bool|true|false|if|else|then|endif|while|whileend|do|doend|for|forend|input|output|and|or|not)\\s*");
const regex KEYWORD("(int|float|bool|true|false|if|else|then|endif|while|"
                    "whileend|do|doend|for|forend|input|output|and|or|not)");
const regex
    OPERATORS("\\s*(\\+|\\-|\\*|\\/|\\%|\\=|\\<|\\>|\\<=|\\>=|\\==|\\!=)\\s*");
const regex SEPARATORS("\\s*[\\(\\)\\{\\}\\[\\];,]\\s*");

void lexer(istream &inputFile, ofstream &outPutFile) {
  smatch match;
  string input;

  outPutFile << "TOKEN\t|\tLEXEMES\n";
  outPutFile << "-----------------\n";

  // Test each case one by one to see if the Regular Expressions work
  while (getline(inputFile, input)) {
    string current = input;
    string space = " ";
    cout << "Current: " << current << endl;
    while (!current.empty()) {

      // Trimming part
      input = regex_replace(input, regex("^\\s+|\\s+$"), "");

      // Real Numbers
      if (regex_search(current, match, REAL)) {
        outPutFile << "REAL\t\t" << match[0] << endl;
        cout << "Real\t\t" << match[0] << endl;
        current = (match.prefix().str() + space) + (match.suffix().str());
        cout << "current after: " << current << endl;
        continue;
      }
      // Keywords
      else if (regex_search(current, match, KEYWORD)) {
        outPutFile << "KEYWORD\t\t" << match[0] << endl;
        cout << "Keyword\t\t" << match[0] << endl;
        // cout << "Hello\n";
        current = (match.prefix().str() + space) + (match.suffix().str());
        cout << "current after: " << current << endl;

        continue;

      }
      // SEPARATORS
      else if (regex_search(current, match, SEPARATORS)) {
        outPutFile << "SEPARATOR\t" << match[0] << endl;
        cout << "Separator\t" << match[0] << endl;
        current = (match.prefix().str() + space) + (match.suffix().str());
        cout << "current after: " << current << endl;
        continue;
      }

      // Operators
      else if (regex_search(current, match, OPERATORS)) {
        outPutFile << "OPERATOR\t" << match[0] << endl;
        cout << "Operator\t" << match[0] << endl;
        current = (match.prefix().str() + space) + (match.suffix().str());
        cout << "current after: " << current << endl;
        continue;
      }
      // Operators
      else if (regex_search(current, match, IDENTIFIER)) {
        outPutFile << "IDENTIFIER\t" << match[0] << endl;
        cout << "IDENTIFIER\t" << match[0] << endl;
        current = (match.prefix().str() + space) + (match.suffix().str());
        cout << "current after: " << current << endl;
        continue;
      }

      else
        current = "";
      break;
    }
  }
}

int main() {
  // Reading and writing to files
  fstream input("input_scode.txt");
  ofstream output("output_scode.txt");

  // Lexer function
  lexer(input, output);

  // Closing files
  input.close();
  output.close();

  return 0;
}
