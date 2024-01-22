#include <iostream>
#include <cctype>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

void takeInputString(string &str, const string &prompt)
{
  cout << prompt;
  getline(cin, str);
  cout << "\n";
}

void getAlpha(string &str)
{
  regex non_alpha("[^a-zA-Z]");
  str = regex_replace(str, non_alpha, "");
}

void changeToUpper(string &str)
{
  int length = str.size();

  for (int i = 0; i < length; i++)
  {
    str[i] = toupper(str[i]);
  }
}

string removeDuplicates(string str)
{
  unordered_map<char, bool> charMap;
  string result = "";
  for (char c : str)
  {
    if (charMap.count(c) == 0)
    {
      result += c;
      charMap[c] = true;
    }
  }
  return result;
}

void fillMatrix(char matrix[5][5], string key)
{
  int t = 0;
  string matrixComb = "";

  int keySize = key.size();

  string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // Removed J

  key = removeDuplicates(key);

  for (char c : key)
  {
    size_t found = alphabet.find(c);
    if (found != string::npos)
      alphabet.erase(found, 1);
  }

  alphabet = key + alphabet;

  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      matrix[i][j] = alphabet[t];
      t++;
    }
  }
}

void splitMessage(string &message, vector<string> &messageArr)
{
  char uniqueChar = 'X';
  for (int i = 0; i < message.size(); i += 2)
  {
    if (i + 1 < message.size())
    {
      if (message[i] == message[i + 1])
      {
        messageArr.push_back({message[i], uniqueChar});
        i--;
      }
      else
      {
        messageArr.push_back({message[i], message[i + 1]});
      }
    }
    else
    {
      messageArr.push_back({message[i], uniqueChar});
    }
  }
}

int findWordsInMessage(string words, vector<string> messageArr)
{
  for (int i = 0; i < 5; i++)
  {
    if (messageArr[i] == words)
    {
      return i;
    }
  }
  return -1;
}

void findWordsInMatrix(string words, char matrix[5][5], int (*pos)[2])
{
  int t = 0;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (words[t] == matrix[i][j])
      {
        pos[t][0] = i;
        pos[t][1] = j;
        t++;
        i = -1;
        break;
      }
    }

    if (t == 2)
    {
      break;
    }
  }
}

void sameRow(vector<string> &encryptedArr, char matrix[5][5], int (*pos)[2], int value)
{
  string temp = "";

  for (int i = 0; i < 2; i++)
  {
    int colValue = (pos[i][1] + value) % 5;
    temp += string(1, matrix[pos[i][0]][colValue]);
  }

  encryptedArr.push_back(temp);
}

void sameCol(vector<string> &encryptedArr, char matrix[5][5], int (*pos)[2], int value)
{
  string temp = "";

  for (int i = 0; i < 2; i++)
  {
    int rowValue = (pos[i][0] + value) % 5;
    temp += string(1, matrix[rowValue][pos[i][1]]);
  }

  encryptedArr.push_back(temp);
}

void other(vector<string> &encryptedArr, char matrix[5][5], int (*pos)[2])
{
  string temp = string(1, matrix[pos[0][0]][pos[1][1]]) + string(1, matrix[pos[1][0]][pos[0][1]]);
  encryptedArr.push_back(temp);
}

void splitDecrypted(vector<string> &decryptedArr, string encryptedMessage)
{
  for (int i = 0; i < encryptedMessage.size(); i += 2)
  {
    decryptedArr.push_back(encryptedMessage.substr(i, 1) + encryptedMessage.substr(i + 1, 1));
  }
}

void decrypt()
{

  cout << "\n";

  string encryptedMessage, key;

  takeInputString(encryptedMessage, "Enter the encrypted text: ");
  takeInputString(key, "Enter the key text: ");

  for (int i = 0; i < encryptedMessage.size(); i++)
  {
    if (encryptedMessage[i] == 'J')
    {
      encryptedMessage[i] = 'I';
    }
  }

  getAlpha(key);
  getAlpha(encryptedMessage);

  changeToUpper(key);
  changeToUpper(encryptedMessage);

  char matrix[5][5];

  fillMatrix(matrix, key);

  vector<string> decryptedArr;

  splitDecrypted(decryptedArr, encryptedMessage);

  int pos[2][2];

  vector<string> decryptedArrAns;

  string finalAns;

  for (int i = 0; i < decryptedArr.size(); i++)
  {
    findWordsInMatrix(decryptedArr[i], matrix, pos);

    if (pos[0][1] == pos[1][1])
    {
      sameCol(decryptedArrAns, matrix, pos, -1);
    }
    else if (pos[0][0] == pos[1][0])
    {
      sameRow(decryptedArrAns, matrix, pos, -1);
    }
    else
    {
      other(decryptedArrAns, matrix, pos);
    }

    finalAns += decryptedArrAns[i];
  }

  cout
      << "Decryped Value is : " << finalAns;
}

void encrypt()
{

  cout << "\n";

  string message, key;

  // 1. Input
  takeInputString(message, "Enter a Message: ");
  takeInputString(key, "Enter key value: ");

  // 2. Get Only Alpha characters
  getAlpha(message);
  getAlpha(key);

  // 3. Convert all to uppercase
  changeToUpper(message);
  changeToUpper(key);

  // 4. Fill Matrix
  char matrix[5][5] = {};
  string matrixComb = "";

  fillMatrix(matrix, key);

  // 5. Have to divide the message
  vector<string> messageArr;
  int pos[2][2];

  splitMessage(message, messageArr);

  int messageArrSize = messageArr.size();
  vector<string> encryptedArr;

  for (int i = 0; i < messageArrSize; i++)
  {
    findWordsInMatrix(messageArr[i], matrix, pos);

    if (pos[0][1] == pos[1][1])
    {
      sameCol(encryptedArr, matrix, pos, 1);
    }
    else if (pos[0][0] == pos[1][0])
    {
      sameRow(encryptedArr, matrix, pos, 1);
    }
    else
    {
      other(encryptedArr, matrix, pos);
    }
  }

  cout
      << "Encryped Value: "
      << "\n";

  for (int i = 0; i < encryptedArr.size(); i++)
  {
    cout << encryptedArr[i] << " "; // Spaces
  }
}

int main()
{
  cout << "\nFor Encryption enter 1\nFor Decryption enter 2\nFor exit of program enter 0\n";

  int whatToDo;

  while (true)
  {
    try
    {
      cout << "\nEnter Value : ";

      cin >> whatToDo;
      if (cin.fail() || (whatToDo != 1 && whatToDo != 2 && whatToDo != 0))
      {

        cin.clear();

        cin.ignore(1000, '\n');

        throw invalid_argument("\nInvalid input. Please enter 1 for Encryption or 2 for Decryption. For exit of program enter 0.");
      }

      cin.ignore();

      if (whatToDo == 0)
      {
        return 0;
      }

      if (whatToDo == 1)
      {
        encrypt();
      }
      else
      {
        decrypt();
      }

      break;
    }
    catch (const exception &e)
    {
      cout << e.what() << endl;
    }
  }

  return 0;
}

/*

-------------------------------------------------

Test Case 1:

For Encryption enter 1
For Decryption enter 2

Enter Value: 1

Enter a Message: hide the gold in the tree stump!!!

Enter key value: playfair example

Encryped Value:
BM OD ZB XD NA BE KU DM UI XM MO UV IF

-------------------------------------------------

Test Case 2:

For Encryption enter 1
For Decryption enter 2

Enter Value: 1

Enter a Message: Hello World!!

Enter key value: Security

Encryped Value:
FU OQ MP XN SP HQ

-------------------------------------------------

Test Case 3:

For Encryption enter 1
For Decryption enter 2

Enter Value: 2

Enter the encrypted text: FU OQ MP XN SP HQ

Enter the key text: Security

Decryped Value is : HELXLOWORLDX

-------------------------------------------------
*/
