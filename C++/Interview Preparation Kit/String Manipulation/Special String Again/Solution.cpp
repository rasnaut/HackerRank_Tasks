//Link to the task: https://www.hackerrank.com/challenges/special-palindrome-again/problem
#include <bits/stdc++.h>

using namespace std;

typedef pair<char, long> letterCounter;

long countSum (long counter) {
    return (counter * (counter + 1)) / 2;
}

//--------------------- Solution code START ------------------------------------
long substrCount(int n, string s) {
    vector<letterCounter> l;
    l.clear();
    long count = 1;
    char ch = s[0];
    for(int i = 1; i <= n ; i++) {
        if(ch == s[i]) {
          count++;
        } else {
            l.push_back(letterCounter(ch, count));
            count = 1;
            ch = s[i];
        }
    }
    count = 0;
    if(l.size() >= 3) {
        auto prev = l.begin();
        auto curr = ++prev;
        auto next = ++prev;
        count = countSum(l.begin()->second);
        for(prev = l.begin(); next != l.end(); prev++) {
            count += countSum(curr->second);
            if(prev->first == next->first && curr->second == 1)
                count += min(prev->second, next->second);

            curr = next++;
        }
        count += countSum(curr->second);
    } else {
        for(auto curr: l) { count += countSum(curr.second); }
    }
    return count;
}
//--------------------- Solution code END ------------------------------------

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string s;
    getline(cin, s);

    long result = substrCount(n, s);

    fout << result << "\n";

    fout.close();

    return 0;
}
