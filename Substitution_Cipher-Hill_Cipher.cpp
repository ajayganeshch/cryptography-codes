#include <bits/stdc++.h>
#include <cctype>

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

void fillMatrix(string message, vector<vector<int>> &matrix, int m, int n, int dupValue)
{
  int t = 0;

  for (int i = 0; i < m; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (message[t])
      {
        matrix[i][j] = (int)message[t] - 65;
        t++;
      }
      else
      {
        matrix[i][j] = dupValue - 65;
      }
    }
  }
}

string matrixMultiplication(vector<vector<int>> matrix, vector<vector<int>> keyMatrix, int n)
{
  vector<int> ans;

  for (int i = 0; i < n; i++)
  {
    int temp = 0;
    for (int j = 0; j < n; j++)
    {
      temp += (keyMatrix[i][j] * matrix[j][0]);
    }
    ans.push_back(temp % 26);
  }

  string finaAns = "";

  for (int i = 0; i < ans.size(); i++)
  {
    finaAns += char(ans[i] + 65);
  }

  return finaAns;
}

string doCalculation(string message, vector<vector<int>> keyMatrix, int n, int dupValue)
{
  vector<vector<int>> matrix(n, vector<int>(1));

  fillMatrix(message, matrix, n, 1, dupValue);

  return matrixMultiplication(matrix, keyMatrix, n);
}

bool isMatrixEmpty(vector<vector<int>> matrix)
{
  int n = matrix.size();
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (matrix[i][j] != 0)
      {
        return false;
      }
    }
  }
  return true;
}

void transposeMatrix(vector<vector<int>> &matrix)
{
  int n = matrix.size();
  for (int i = 0; i < n; i++)
  {
    for (int j = i; j < n; j++)
    {
      swap(matrix[i][j], matrix[j][i]);
    }
  }
}

int multiplicativeInverse(int a, int m)
{
  a = a % m;
  for (int x = 1; x < m; x++)
    if ((a * x) % m == 1)
      return x;
  return -1;
}

vector<vector<int>> inverseOfMatrix3(vector<vector<int>> keyMatrix)
{
  int n = 3;
  vector<vector<int>> matrix(n, vector<int>(n));

  int det = ((keyMatrix[0][0] * keyMatrix[1][1] * keyMatrix[2][2]) + (keyMatrix[1][0] * keyMatrix[2][1] * keyMatrix[0][2]) + (keyMatrix[2][0] * keyMatrix[0][1] * keyMatrix[1][2]) - (keyMatrix[2][0] * keyMatrix[1][1] * keyMatrix[0][2]) - (keyMatrix[1][0] * keyMatrix[0][1] * keyMatrix[2][2]) - (keyMatrix[0][0] * keyMatrix[2][1] * keyMatrix[1][2])) % 26;
  det = (det + 26) % 26;

  det = multiplicativeInverse(det, 26);

  if (det == 0 || det == -1)
  {
    return vector<vector<int>>(n, vector<int>(n, 0));
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int value = (keyMatrix[(i + 1) % 3][(j + 1) % 3] * keyMatrix[(i + 2) % 3][(j + 2) % 3]) - (keyMatrix[(i + 1) % 3][(j + 2) % 3] * keyMatrix[(i + 2) % 3][(j + 1) % 3]);
      value = (value % 26 + 26) % 26;
      matrix[i][j] = (det * value) % 26;

      /*
      00 01 02
      10 11 12
      20 21 22

      00: (i=0; j=0)
      11 12
      21 22

      11 * 22 - 12*21

      01: (i=0; j=1)
      10 12
      20 22

      -(10*22 - 20*12) = 20*12 - 10*22

      */
    }
  }

  transposeMatrix(matrix);

  return matrix;
}

vector<vector<int>> inverseOfMatrix2(vector<vector<int>> keyMatrix)
{
  int n = 2;

  vector<vector<int>> matrix(n, vector<int>(n));

  int det = ((((keyMatrix[0][0] * keyMatrix[1][1]) - (keyMatrix[0][1] * keyMatrix[1][0])) % 26) + 26) % 26;
  // Just to make det positive we are doing this ( __+ 26 ) % 26

  det = multiplicativeInverse(det, 26);

  if (det == 0 || det == -1)
  {
    return vector<vector<int>>(n, vector<int>(n, 0));
  }

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int value = keyMatrix[(i + 1) % 2][(j + 1) % 2];

      if ((i + j) % 2 != 0)
      {
        value = value * -1;
      }

      value = (value % 26 + 26) % 26;
      matrix[i][j] = (det * value) % 26;

      /*
      00 01
      10 11

      00:11
      */
    }
  }

  transposeMatrix(matrix);

  return matrix;
}

int getDupValue()
{
  char dupValueChar;

  cout << "\nEnter the duplicate Character to use/you used (if nothing enter 1,by default we use 'X'): ";

  cin >> dupValueChar;

  if (isalpha(dupValueChar) != 0)
  {
    dupValueChar = toupper(dupValueChar);

    return (int)dupValueChar;
  }
  else
  {
    return 88;
  }
}

void decrypt()
{
  string message, key;
  takeInputString(message, "Enter the encrypted message: ");
  takeInputString(key, "Enter the key String: ");

  int n;
  cout << "Enter the n value (2/3): ";

  cin >> n;

  int dupValue = getDupValue();

  if (n != 2 && n != 3)
  {
    cout << "Only For n = 2 and 3, this code works :(";
    return;
  }

  getAlpha(message);
  getAlpha(key);

  changeToUpper(message);
  changeToUpper(key);

  vector<vector<int>> keyMatrix(n, vector<int>(n)); // n*n matrix
  vector<vector<int>> inverseKeyMatrix(n, vector<int>(n));

  fillMatrix(key, keyMatrix, n, n, dupValue);

  string answer = "";

  if (n == 3)
  {
    inverseKeyMatrix = inverseOfMatrix3(keyMatrix);

    if (isMatrixEmpty(inverseKeyMatrix))
    {
      cout << "The matrix is not invertible. Check key and try again!!!";
      return;
    }
  }
  else
  {
    inverseKeyMatrix = inverseOfMatrix2(keyMatrix);

    if (isMatrixEmpty(inverseKeyMatrix))
    {
      cout << "The matrix is not invertible. Check key and try again!!!";
      return;
    }
  }

  int t = 0;
  string finalAns = "";

  while (t < message.size())
  {
    finalAns += doCalculation(message.substr(t, n), inverseKeyMatrix, n, dupValue);
    t += n;
  }

  cout << "\n"
       << "Decryped Value is : " << finalAns;
}

void encrypt()
{

  string message, key;
  takeInputString(message, "Enter the message: ");
  takeInputString(key, "Enter the key: ");

  int n;
  cout << "Enter the n value: ";

  cin >> n;

  int dupValue = getDupValue();

  getAlpha(message);
  getAlpha(key);

  changeToUpper(message);
  changeToUpper(key);

  vector<vector<int>> keyMatrix(n, vector<int>(n));

  fillMatrix(key, keyMatrix, n, n, dupValue);

  int t = 0;
  string finalAns = "";

  while (t < message.size())
  {
    finalAns += doCalculation(message.substr(t, n), keyMatrix, n, dupValue);
    t += n;
  }

  cout << "\n"
       << "Final Ans is: " << finalAns;
}

int main()
{
  cout << "\n\n------ Ch. Ganesh Sri Naga Venkata Ajay [21BDS0269] ------\n";

  int whatToDo;

  cout << "\nFor Encryption enter 1\nFor Decryption enter 2\n\nEnter Value: ";

  cin >> whatToDo;
  cin.ignore();

  cout << "\n";
  while (true)
  {
    if (whatToDo == 1)
    {

      encrypt();
      break;
    }
    else if (whatToDo == 2)
    {
      decrypt();
      break;
    }
    else
    {
      cout << "Enter the correct number: ";
      cin >> whatToDo;
      cin.ignore();
      cout << "\n";
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

Enter the message: safe messages

Enter the key: ciphering

Enter the n value: 3

Enter the duplicate Character you use/to use (if nothing enter 1): 1

Final Ans is: HDSIOEYQOCAA

-------------------------------------------------

Test Case 2: (Extra Value: z)

For Encryption enter 1
For Decryption enter 2

Enter Value: 1

Enter the message: sathish

Enter the key: dbgf

Enter the n value: 2

Enter the duplicate Character you use/to use (if nothing enter 1): z

Final Ans is: CEMTQIUL

-------------------------------------------------

Test Case 3:

For Encryption enter 1
For Decryption enter 2

Enter Value: 2

Enter the encrypted message: POH

Enter the key String: GYBNQKURP

Enter the n value (2/3): 3

Enter the duplicate Character you use/to use (if nothing enter 1): 1

Final Ans is: ACT

-------------------------------------------------

Test Case 4:

For Encryption enter 1
For Decryption enter 2

Enter Value: 1

Enter the message: I LOVE CRYPTO

Enter the key: VIT

Enter the n value: 2

Enter the duplicate Character you use/to use (if nothing enter 1): 1

Final Ans is: WLULWWDNZGAH

-------------------------------------------------

Test Case 5:

For Encryption enter 1
For Decryption enter 2

Enter Value: 2

Enter the encrypted message: WLULWWDNZGAH

Enter the key String: VIT

Enter the n value (2/3): 2

Enter the duplicate Character you use/to use (if nothing enter 1): 1

Decryped Value is : ILOVECRYPTOZ

-------------------------------------------------

*/