#include <string>
#include <iostream>
using namespace std;

enum Token // 열거형
{
  tok_eof = -1,
  tok_def = -2,
  tok_extern = -3,
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr; // C#에서 std::string 타입의 변수를이용하여 문자열을 사용
static double NumVal;

static int gettok()
{
  static int LastChar = ' ';

  // 공백을 건너 뛰고 숫자를 일치 시키려함
  while (isspace(LastChar))
  {                       // isspace  문자가 공백인지 탭인지 개행인지 등을 검사하는 함수
    LastChar = getchar(); // 입력받음
  }

  // 렉서를 구문 분석하는 부분
  if (isalpha(LastChar))
  {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
    {
      IdentifierStr += LastChar;
    } // int isalnum( int _C );_C가 알파벳이거나 숫자인지를 판별하게 됩니다.

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.')
  { // Number: [0-9.]+
    std::string NumStr;
    do
    {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  if (LastChar == '#')
  {
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  if (LastChar == EOF)
  {
    return tok_eof;
  }

  int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

int main()
{
  while (true)
  {
    int tok = gettok();
    cout << "got token: " << tok << endl;
  }
}