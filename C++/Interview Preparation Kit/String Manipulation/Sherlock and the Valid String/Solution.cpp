//Link to the task: https://www.hackerrank.com/challenges/sherlock-and-valid-string/problem
#include <bits/stdc++.h>

using namespace std;

//--------------------- Solution code START ------------------------------------
string isValid(string s) {
    std::map<char, int> str_map;
    str_map.clear();
    for (auto itr: s) {
        auto f = str_map.find(itr);
        if(f == str_map.end()) {
          str_map.insert(pair<char,int>(itr, 1));
        }
        else { f->second++; }
    }

    int real_sum = 0;
    int prev = str_map.begin()->second;
    int base = prev;
    for(auto itr: str_map) {
        std::cout << itr.second << " ";
        if(abs(itr.second - prev) > 1 &&
            (min(itr.second, prev) != 1 ||
            (min(itr.second, prev) == 1 && max(itr.second, prev) != base)))
        {
          return "NO";
        }
        if(itr.second == prev) base = prev;

        real_sum+=itr.second;
        prev = itr.second;
    }
    int pro_sum = base * str_map.size();
    std::cout << base - abs(pro_sum - real_sum) << endl;
    if(abs(pro_sum - real_sum)>1 && (base - abs(pro_sum - real_sum)) != 1)
    {
      return "NO";
    }
    return "YES";
}
//--------------------- Solution code END ------------------------------------

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = isValid(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
