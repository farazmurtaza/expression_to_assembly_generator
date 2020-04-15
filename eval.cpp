#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;

int indexOfToken = 0;
vector<string> tokens; //22*(50+(36/12)-16)

string factor();
string expr();
string expr2();
string term();
string term2();
void createASMFile(string expr);

string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

void tokenize(string expression)
{
    for (int i = 0; i < expression.length(); i++)
    {
        if (!isdigit(expression.at(i)))
        {
            string s(1, expression.at(i));
            tokens.push_back(s);
        }
        else
        {
            int j = i;
            int skip = 0;
            while (i < expression.length() && isdigit(expression.at(i)))
            {
                i++;
                skip++;
            }
            i--;
            string num = expression.substr(j, skip);
            tokens.push_back(num);
        }
    }
}

string expr()
{
    string s = term();
    s += expr2();
    return s;
}

string expr2()
{
    if (indexOfToken >= tokens.size())
        return "";

    if (tokens[indexOfToken] == "+")
    {
        indexOfToken++;
        string s = term();
        s += expr2();
        s += "POP AX\nPOP BX\nADD AX, BX\nPUSH AX\n";
        return s;
    }
    else if (tokens[indexOfToken] == "-")
    {
        indexOfToken++;
        string s = term();
        s += expr2();
        s += "POP BX\nPOP AX\nSUB AX, BX\nPUSH AX\n";
        return s;
    }
    else
    {
        return "";
    }
}

string term()
{

    string s = factor();
    s += term2();
    return s;
}

string term2()
{

    if (indexOfToken >= tokens.size())
        return "";
    if (tokens[indexOfToken] == "*")
    {
        indexOfToken++;
        string s = factor();
        s += term2();
        s += "POP AX\nPOP BX\nMUL BX\nPUSH AX\n";
        return s;
    }
    else if (tokens[indexOfToken] == "/")
    {
        indexOfToken++;
        string s = factor();
        s += term2();
        s += "POP BX\nPOP AX\nMOV DX, 0\nDIV BX\nPUSH AX\n";
        return s;
    }
    if (tokens[indexOfToken] == "%")
    {
        indexOfToken++;
        string s = factor();
        s += term2();
        s += "POP AX\nPOP BX\nMOV DX, 0\nDIV BX\nPUSH DX\n";
        return s;
    }
    else
    {

        return "";
    }
}

string factor()
{

    if (isdigit(tokens[indexOfToken].at(0)))
    {
        indexOfToken++;
        return "MOV AX, " + tokens[indexOfToken - 1] + "\nPUSH AX\n";
    }
    else if (tokens[indexOfToken] == "(")
    {
        indexOfToken++;
        string s = expr();
        if (tokens[indexOfToken] == ")")
        {
            indexOfToken++;
            return s;
        }
        else
        {
            cout << "ERROR" << endl;
        }
    }
    else
    {
        cout << "ERROR" << endl;
    }
    return "";
}

void createASMFile(string expr)
{
    ofstream myfile;
    myfile.open("output.asm");
    myfile << "includelib C:\\Irvine\\Kernel32.Lib\nincludelib C:\\Irvine\\User32.Lib\nincludelib C:\\Irvine\\Irvine32.lib\nINCLUDE C:\\Irvine\\Irvine32.inc\n.data\n.code\nmain PROC\nMOV EAX, 0\n"
           << expr << "\ncall writedec\nexit\nmain ENDP\nEND main\n";
    myfile.close();
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        cout << "Usage: program.exe \"expression\"";
    }
    else
    {
        string expression = argv[1];

        //expression  = "22*(50+(36/12)-16)";
        //cout << "Enter the expression: ";
        //getline(cin, expression);
        cout << expression << endl;

        expression = removeSpaces(expression);
        cout << expression << endl;
        tokenize(expression);
        for (int i = 0; i < tokens.size(); i++)
        {
            cout << "token[" << i << "] = " << tokens[i] << endl;
        }

        string result = expr();

        createASMFile(result);

        cout << result << endl;
    }

    return 0;
}