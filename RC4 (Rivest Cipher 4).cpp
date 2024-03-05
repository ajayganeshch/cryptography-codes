#include <bits/stdc++.h>
#include <cctype>
#include <numeric>

using namespace std;

vector<int> takeInput(string text)
{

  cout << "\n";

  int n;
  vector<int> matrix;
  cout << "Provide the byte size of the " << text << ": ";
  cin >> n;

  int k;

  cout << "Enter " << text << ": ";

  for (int i = 0; i < n; i++)
  {
    cin >> k;
    matrix.push_back(k);
  }

  return matrix;
}

// KSA (KEY SCHEDULING ALGORITHM)
vector<int> key_scheduling(int state_vector_len, int keyLen, vector<int> key)
{

  // 1. Initialization
  vector<int> s(state_vector_len);
  iota(s.begin(), s.end(), 0);

  vector<int> k;

  int i = 0;

  while (k.size() != s.size())
  {
    k.push_back(key[i % keyLen]);
    i++;
  }

  // 2. Permutation
  int j = 0;

  for (i = 0; i < state_vector_len; i++)
  {
    j = (j + s[i] + k[i % keyLen]) % state_vector_len;
    swap(s[i], s[j]);
  }

  // 3. Permutation print
  // for (i = 0; i < state_vector_len; i++)
  // {
  //   cout << s[i] << " ";
  // }

  return s;
}

// Pseudo Random Generator Algorithm (PRGA)
vector<int> pseudo_random_generator(int state_vector_len, vector<int> s, int utLen, vector<int> user_text)
{
  int i = 0;
  int j = 0;

  vector<int> cipher_text;

  while (cipher_text.size() != utLen)
  {
    i = (i + 1) % state_vector_len;
    j = (j + s[i]) % state_vector_len;

    swap(s[i], s[j]);

    int k = s[(s[i] + s[j]) % state_vector_len];

    cipher_text.push_back(user_text[cipher_text.size()] ^ k);
  }

  return cipher_text;
}

void answer(string text)
{
  text[0] = std::tolower(text[0]);
  vector<int> user_text = takeInput("text");
  vector<int> key = takeInput("key");
  int keyLen = key.size();
  int utLen = user_text.size();

  int state_vector_len;
  cout << "\nProvide the byte size of the state vector (length 1-256): ";
  cin >> state_vector_len;

  vector<int> s = key_scheduling(state_vector_len, keyLen, key);
  vector<int> cipher_text = pseudo_random_generator(state_vector_len, s, utLen, user_text);

  cout << "\n"
       << text << "text is: ";

  for (int i = 0; i < cipher_text.size(); i++)
  {
    cout << cipher_text[i] << " ";
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

      answer(whatToDo == 1 ? "Encrypted" : "Decrypted");

      break;
    }
    catch (const exception &e)
    {
      cout << e.what() << endl;
    }
  }

  return 0;
}