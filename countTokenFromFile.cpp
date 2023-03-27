#include<vector>
#include<iostream>
#include<string>
#include<map>
#include<fstream>

using namespace std;
typedef map<string, int> tokensMap;
void printMap(tokensMap &inputMap);
void addTokens(string inputToken);

char *tempLinePtr;

tokensMap tokens;



void addTokens(string inputToken) {
    // check if the token already exists

    int tokenCount = 1;

    tokensMap::iterator keyFoundItr = tokens.find(inputToken);
    //tokensMap::iterator keyFoundItr = tokensMap.find(inputToken);

    if(keyFoundItr != tokens.end()) {
        // token found in map
        int prevTokenCount = keyFoundItr->second;
        cout<<"TOKEN FOUND ! UPDATING IT "<<inputToken<<endl;
        tokens.erase(inputToken);
        tokenCount = prevTokenCount + 1;
    }

    tokens.insert(std::pair(inputToken, tokenCount));

}

string generateTokenFromLine(char *bufferLine)
{
    char *charPtr = bufferLine;
    bool isOperator = false;
    string generatedToken = "";

    while(*charPtr != '\0')
    {
        char newLine = (char) *charPtr;
           // printf("----Test : %c\n", newLine);

        //skip newline character

        if(newLine == '\n') {
                printf("newline character detected. so skipping it :)\n");
                charPtr++;
                tempLinePtr = charPtr;
                return NULL;
        }

        // skip spaces or new line
        while(isspace(*charPtr))
        {
            charPtr++;
        }

        // check for keyword or identifier
        if (isalpha(*charPtr)) {

            char token[20];
            int i = 0;
            while (isalnum(*charPtr)) {
                token[i++] = *charPtr++;
            }
            token[i] = '\0';
            generatedToken = token;
            tempLinePtr = charPtr;
            printf("Identifier or keyword: %s\n", token);
            break;

        }
        // check for numeric literals
        else if (isdigit(*charPtr)) {
            char token[20];
            int i = 0;
            while (isdigit(*charPtr)) {
                token[i++] = *charPtr++;
            }
            token[i] = '\0';
            generatedToken = token;
            tempLinePtr = charPtr;
            printf("Numeric literal: %s\n", token);
            break;
        }
        // check for operators and punctuation
        else {

            if(*charPtr == '%') {
                std::cout<<"percentage detected"<<std::endl;
            }

            char token = *charPtr++;
            generatedToken += token;
            tempLinePtr = charPtr;
//            string validCharToken = *charPtr++;
//            char *stringToken = (char *) malloc(sizeof(char *));
//            *stringToken = validCharToken;

            printf("Operator or punctuation: %c\n", token);
            break;
        }

    }

    return generatedToken;
}

void tokenBuilder(char line[]) {

    while(*tempLinePtr != '\0') {
        string generatedToken = generateTokenFromLine(tempLinePtr);

        std::cout<<"Token :: "<<generatedToken<<std::endl;

        // document token into map
        addTokens(generatedToken);
    }

}



int main() {
    vector<string> intVector;

    // read file

    std::ifstream inputFileStream;
    inputFileStream.open("twoSum.c");

    const int lineSize = 100;
    char line[lineSize];

    while(inputFileStream) {
        inputFileStream.getline(line, lineSize);

        // token builder makes sure all token from line is extracted
        std::cout<<"Generating token for line :\t"<<line<<std::endl;
        std::cout<<"---------------------------------------------------\n";

        tempLinePtr = line;
        tokenBuilder(line);

        std::cout<<endl;
//        std::cout<<line<<std::endl;
    }


    printMap(tokens);
    return 0;
}

void printMap(tokensMap &inputMap){
    tokensMap::iterator itr;

    std::cout<<"Total tokens with their occurence "<<std::endl;
    std::cout<<"------------------------------------------------------------\n";

    for(itr=inputMap.begin(); itr != inputMap.end(); ++itr) {
        std::cout<<itr->first<<" => "<<itr->second<<std::endl;
    }
}
