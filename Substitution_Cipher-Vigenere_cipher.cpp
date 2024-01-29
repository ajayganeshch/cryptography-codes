#include <bits/stdc++.h>
using namespace std;

void takeInput(string &str, string prompt)
{
    cout << prompt << ": ";
    getline(cin, str);
    cout << "\n";
}

void getAlpha(string &str)
{
    regex non_alpha("[^a-zA-Z]");
    str = regex_replace(str, non_alpha, "");
}

// 65-90 , 97-122

vector<int> fillMatrix(string str)
{
    vector<int> matrix;

    for (int i = 0; i < str.size(); i++)
    {
        int temp = (int)str[i];
        if (temp <= 90 && temp >= 65)
        {
            matrix.push_back(temp - 65);
        }
        else
        {
            matrix.push_back(temp - 97);
        }
    }

    return matrix;
}

string correctString(string str, string key)
{
    int strSize = str.size();
    int keySize = key.size();

    string tempKey = key;

    int i = 0;

    if (strSize < keySize)
    { // keySize more
        key = key.substr(0, strSize);
    }
    else
    { // String Message more
        while (strSize > keySize)
        {
            key += tempKey[i];
            i++;

            if (i >= tempKey.size())
            {
                i = 0;
            }

            keySize++;
        }
    }

    return key;
}

vector<char> matrixCalculation(vector<int> messageArr, vector<int> keyArr, bool plus)
{
    vector<char> matrix;

    for (int i = 0; i < messageArr.size(); i++)
    {
        int ans = messageArr[i] + (plus ? keyArr[i] : -keyArr[i]);
        ans = (ans % 26 + 26) % 26;
        matrix.push_back(char(ans + 65));
    }

    return matrix;
}

void answer(bool method)
{
    cout << "\n";

    string userInput, key;

    takeInput(userInput, "Enter the string");
    takeInput(key, "Enter the key");

    getAlpha(userInput);
    getAlpha(key);

    key = correctString(userInput, key);

    vector<int> userInputArr = fillMatrix(userInput);
    vector<int> keyArr = fillMatrix(key);

    vector<char> result = matrixCalculation(userInputArr, keyArr, method);

    cout << "Answer is: \n";

    for (int i = 0; i < userInputArr.size(); i++)
    {
        cout << result[i];
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
                // If the input operation failed, this clears the error flag on cin. This allows future input operations to work correctly.
                cin.clear();

                // wrong input will be ignored up to 1000 characters or until it encounters a newline
                cin.ignore(1000, '\n');

                throw invalid_argument("\nInvalid input. Please enter 1 for Encryption or 2 for Decryption. For exit of program enter 0.");
            }

            // To ignore next character in the input buffer. This is often used to ignore the newline character that remains in the buffer after reading an integer.
            cin.ignore();

            if (whatToDo == 0)
            {
                return 0;
            }

            answer(whatToDo == 1);
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
For exit of program enter 0

Enter Value : 1

Enter the string: Cryptography and Network Security

Enter the key: CSE

Answer is:
EJCRLSIJERZCCFHPWXYGVMKIEMVKLC

-------------------------------------------------

Test Case 2:

For Encryption enter 1
For Decryption enter 2
For exit of program enter 0

Enter Value : 2

Enter the string: EJCRLSIJERZCCFHPWXYGVMKIEMVKLC

Enter the key: CSE

Answer is:
CRYPTOGRAPHYANDNETWORKSECURITY

-------------------------------------------------

Test Case 3:

For Encryption enter 1
For Decryption enter 2
For exit of program enter 0

Enter Value : 1

Enter the string: Feb Apr Jan

Enter the key: Deny Allow

Answer is:
IIOYPCUOJ

-------------------------------------------------

*/