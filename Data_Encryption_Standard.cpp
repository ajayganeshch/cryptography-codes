#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> keys;

void takeInput(string &str, string prompt)
{
  cout << prompt << ": ";
  getline(cin, str);
  cout << "\n";
}

string getCorrectString(string str)
{
  regex non_alpha("[^a-fA-F0-9]");
  str = regex_replace(str, non_alpha, "");

  return str;
}

void changeToUpper(string &str)
{
  int length = str.size();

  for (int i = 0; i < length; i++)
  {
    str[i] = toupper(str[i]);
  }
}

bool checkLengths(string text, string key)
{
  bool areLengthsEqual = text.size() == 16 && key.size() == 16;
  return areLengthsEqual;
}

bool checkIsCorrectStrings(string text, string key)
{
  bool isCorrect = text.compare(getCorrectString(text)) == 0 && key.compare(getCorrectString(key)) == 0;
  return isCorrect;
}

vector<string> splitStrings(string str, int length)
{
  vector<string> matrix;
  for (int i = 0; i < str.size(); i += length)
  {
    matrix.push_back(str.substr(i, length));
  }

  return matrix;
}

vector<int> hexaToBinary(string hex)
{
  vector<int> ans;
  for (char c : hex)
  {
    bitset<4> binary = bitset<4>(c >= 'A' ? c - 'A' + 10 : c - '0'); // '0' value -> 48 ...... '9'-> 57
    for (int i = 3; i >= 0; --i)
    {
      ans.push_back(binary[i]);
    }
  }
  return ans;
}

vector<int> generatePermutation(vector<int> pc, vector<int> matrix)
{
  try
  {
    vector<int> ans;

    for (int i = 0; i < pc.size(); i++)
    {
      if (pc[i] >= 0 && pc[i] <= matrix.size())
      {
        ans.push_back(matrix[pc[i] - 1]); // subtract 1 from pc[i] to convert to 0-based
      }
      else
      {
        cout << "Index out of range: " << pc[i] << " " << i << "\n";
      }
    }

    return ans;
  }
  catch (const exception &e)
  {
    cerr << "Caught exception: " << e.what() << '\n';
  }
}

vector<int> leftShift(vector<int> bits, int n)
{
  rotate(bits.begin(), bits.begin() + n, bits.begin() + 28);
  rotate(bits.begin() + 28, bits.begin() + 28 + n, bits.end());

  return bits;
}

void doShifts(vector<int> bits, vector<int> shifts, vector<int> pc2)
{
  int i = 0;

  vector<vector<int>> tempKeys;

  tempKeys.push_back(bits);

  while (shifts.size() > i)
  {
    vector<int> temp = tempKeys[i];
    tempKeys.push_back(leftShift(temp, shifts[i]));

    i++;
  }

  i = 1;

  while (shifts.size() >= i)
  {
    vector<int> temp = tempKeys[i];
    keys.push_back(generatePermutation(pc2, temp));

    i++;
  }

  tempKeys.clear();
}

vector<int> add(vector<int> m1, vector<int> m2)
{
  vector<int> ans;

  for (int i = 0; i < m1.size(); i++)
  {
    if (m1[i] == m2[i])
    {
      ans.push_back(0);
    }
    else
    {
      ans.push_back(1);
    }
  }

  return ans;
}

vector<int> getSvalue(vector<int> matrix)
{
  vector<vector<int>> s = {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
                            0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
                            4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
                            15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
                           {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
                            3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
                            0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
                            13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
                           {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
                            13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
                            13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
                            1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
                           {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
                            13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
                            10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
                            3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
                           {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
                            14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
                            4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
                            11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
                           {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
                            10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
                            9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
                            4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
                           {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
                            13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
                            1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
                            6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
                           {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
                            1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
                            7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
                            2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

  vector<int> ans;

  int t = 0;

  for (int i = 0; i < matrix.size(); i = i + 6)
  {
    string tempLeft = to_string(matrix[i]) + to_string(matrix[i + 5]);
    string tempRight = to_string(matrix[i + 1]) + to_string(matrix[i + 2]) + to_string(matrix[i + 3]) + to_string(matrix[i + 4]);

    int row = stoi(tempLeft, nullptr, 2);
    int col = stoi(tempRight, nullptr, 2);

    int num = s[t][row + (15 * row) + col];

    bitset<4> binary(num);

    for (int j = 3; j >= 0; --j)
    {
      ans.push_back(binary[j]);
    }

    t++;
  }

  return ans;
}

vector<int> performFunction(vector<int> ep, vector<int> message, vector<int> key)
{
  int size = message.size() / 2;

  vector<int> left(message.begin(), message.begin() + size);
  vector<int> right(message.begin() + size, message.end());

  vector<int> tempRight = generatePermutation(ep, right);

  vector<int> arrAdd = add(key, tempRight);

  vector<int> arrS = getSvalue(arrAdd);

  vector<int> p = {16, 7, 20, 21, 29, 12, 28, 17,
                   1, 15, 23, 26, 5, 18, 31, 10,
                   2, 8, 24, 14, 32, 27, 3, 9,
                   19, 13, 30, 6, 22, 11, 4, 25};

  vector<int> arrP = generatePermutation(p, arrS);

  vector<int> arrAns = add(left, arrP);

  // The right half of the message in the current round becomes the left half in the next round
  left = right;

  // The result of the function becomes the new right half
  right = arrAns;

  // Concatenate left and right to form the new message for the next round
  left.insert(left.end(), right.begin(), right.end());

  return left;
}

vector<int> reverseArr(vector<int> arr)
{
  int size = arr.size() / 2;

  vector<int> left(arr.begin(), arr.begin() + size);
  vector<int> right(arr.begin() + size, arr.end());

  right.insert(right.end(), left.begin(), left.end());

  return right;
}

vector<string> binToHex(vector<int> matrix, int n)
{
  vector<string> hexValues;
  string hexChars = "0123456789ABCDEF";
  for (int i = 0; i < matrix.size(); i += n)
  {
    int value = 0;
    for (int j = 0; j < n; ++j)
    {
      value = value * 2 + matrix[i + j];
    }
    string hexValue;
    hexValue.push_back(hexChars[value / 16]);
    hexValue.push_back(hexChars[value % 16]);
    hexValues.push_back(hexValue);
  }
  return hexValues;
}

void doCalculation(vector<int> ep, vector<int> messageArr, int rounds, bool isDecrypt)
{
  int i = 0;

  vector<int> arr;
  vector<int> tempArr = messageArr;

  if (isDecrypt)
  {
    for (i = rounds - 1; i >= 0; i--)
    {
      arr = performFunction(ep, tempArr, keys[i]);
      tempArr = arr;
    }
  }
  else
  {
    for (i = 0; i < rounds; i++)
    {
      arr = performFunction(ep, tempArr, keys[i]);
      tempArr = arr;
    }
  }

  arr = reverseArr(arr);

  vector<int>
      ip_inverse = {40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41, 9, 49, 17, 57, 25};

  vector<int> ans = generatePermutation(ip_inverse, arr);

  vector<string> finalAns = binToHex(ans, 8);

  cout << "\nFinal Ans is\n";

  for (int i = 0; i < finalAns.size(); i++)
  {
    cout << finalAns[i];
  }
}

void answer(bool isDecrypt)
{
  cout << "\n";

  string message, key;

  takeInput(message, "Enter the string");
  takeInput(key, "Enter the key");

  changeToUpper(key);
  changeToUpper(message);

  if (!checkLengths(message, key) || !checkIsCorrectStrings(message, key))
  {
    cout << "Wrong Input Try Again";
    return;
  }

  vector<int> keyArr = hexaToBinary(key);
  vector<int> messageArr = hexaToBinary(message);

  vector<int> pc1 = {57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4};

  vector<int> key_0 = generatePermutation(pc1, keyArr);

  vector<int> shifts = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

  vector<int> pc2 = {14, 17, 11, 24, 1, 5,
                     3, 28, 15, 6, 21, 10,
                     23, 19, 12, 4, 26, 8,
                     16, 7, 27, 20, 13, 2,
                     41, 52, 31, 37, 47, 55,
                     30, 40, 51, 45, 33, 48,
                     44, 49, 39, 56, 34, 53,
                     46, 42, 50, 36, 29, 32};

  doShifts(key_0, shifts, pc2);

  vector<int> ip = {58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17, 9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7};

  vector<int> ip_message = generatePermutation(ip, messageArr);

  vector<int> ep = {32, 1, 2, 3, 4, 5, 4, 5,
                    6, 7, 8, 9, 8, 9, 10, 11,
                    12, 13, 12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21, 20, 21,
                    22, 23, 24, 25, 24, 25, 26, 27,
                    28, 29, 28, 29, 30, 31, 32, 1};

  int rounds = 16;

  doCalculation(ep, ip_message, rounds, isDecrypt);
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

      answer(whatToDo == 2);

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

----------------------------------------------------

Test Case 1:

For Encryption enter 1
For Decryption enter 2
For exit of program enter 0

Enter Value : 1

Enter the string: 123456ABCD132536

Enter the key: AABB09182736CCDD


Final Ans is
C0B7A8D05F3A829C

----------------------------------------------------

Test Case 2:

For Encryption enter 1
For Decryption enter 2
For exit of program enter 0

Enter Value : 1

Enter the string: 0123456789ABCDEF

Enter the key: 133457799BBCDFF1


Final Ans is
85E813540F0AB405

----------------------------------------------------

Test Case 3:

For Encryption enter 1
For Decryption enter 2
For exit of program enter 0

Enter Value : 2

Enter the string: 85E813540F0AB405

Enter the key: 133457799BBCDFF1


Final Ans is
0123456789ABCDEF

----------------------------------------------------

Test Case 4:

For Encryption enter 1
For Decryption enter 2
For exit of program enter 0

Enter Value : 2

Enter the string: C0B7A8D05F3A829C

Enter the key: AABB09182736CCDD


Final Ans is
123456ABCD132536
*/