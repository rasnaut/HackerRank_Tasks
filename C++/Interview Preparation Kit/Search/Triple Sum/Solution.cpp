//Link to the task: https://www.hackerrank.com/challenges/triple-sum/problem
#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

long pairCounter (vector<int> &l, vector<int> &r) {
    long pairCounter = 0;
    set<int> left;
    left.clear();
    set<int> right;
    right.clear();
    for (auto itr_l: l) { left.insert(itr_l); }
    for (auto itr_r: r) { right.insert(itr_r); }
    for (auto itr_r: right) {
        pairCounter += count_if(left.begin(),left.end(),
                [&itr_r](int _l) {
                    return (_l <= itr_r);
                });
    }

    return pairCounter;
}

//--------------------- Solution code START ------------------------------------
long triplets(vector<int> a, vector<int> b, vector<int> c) {
    long tripls_counter = 0;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    vector<int> set_a, set_c;
    set_a.clear();
    set_a.reserve(a.size());

    set_c.clear();
    set_c.reserve(c.size());
    int prev = 0;
    for (auto itr_a: a) {
        if(prev != itr_a) {
            prev = itr_a;
            set_a.push_back(itr_a);
        }
    }
    prev = 0;
    for (auto itr_c: c) {
        if(prev != itr_c) {
            prev = itr_c;
            set_c.push_back(itr_c);
        }
    }
    int lMax = max(set_a[0], set_c[0]);
    std::cout << "lMax: " << lMax << std::endl;
    auto itr_b = std::lower_bound(b.rbegin(),b.rend(), lMax);
    auto itr_b_rev = b.rbegin();
    auto a_end = set_a.end();
    auto c_end = set_a.end();
    prev = 0;
    while (itr_b_rev != b.rend()) {
        if (prev != *itr_b_rev)
        {
            prev = *itr_b_rev;
            if(*(set_a.end()-1) > *(itr_b_rev)) {
                a_end = std::upper_bound(set_a.begin(), set_a.end(), *itr_b_rev);
                set_a.erase(a_end, set_a.end());
            }
            if(*(set_c.end()-1) > *(itr_b_rev)) {
                c_end = std::upper_bound(set_c.begin(), set_c.end(), *itr_b_rev);
                set_c.erase(c_end, set_c.end());
            }
            long a_counter = set_a.size();
            long c_counter = set_c.size();
            tripls_counter += a_counter * c_counter;
        }
        itr_b_rev++;
    }
    return tripls_counter;
}
//--------------------- Solution code END ------------------------------------

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string lenaLenbLenc_temp;
    getline(cin, lenaLenbLenc_temp);

    vector<string> lenaLenbLenc = split_string(lenaLenbLenc_temp);

    int lena = stoi(lenaLenbLenc[0]);

    int lenb = stoi(lenaLenbLenc[1]);

    int lenc = stoi(lenaLenbLenc[2]);

    string arra_temp_temp;
    getline(cin, arra_temp_temp);

    vector<string> arra_temp = split_string(arra_temp_temp);

    vector<int> arra(lena);

    for (int i = 0; i < lena; i++) {
        int arra_item = stoi(arra_temp[i]);

        arra[i] = arra_item;
    }

    string arrb_temp_temp;
    getline(cin, arrb_temp_temp);

    vector<string> arrb_temp = split_string(arrb_temp_temp);

    vector<int> arrb(lenb);

    for (int i = 0; i < lenb; i++) {
        int arrb_item = stoi(arrb_temp[i]);

        arrb[i] = arrb_item;
    }

    string arrc_temp_temp;
    getline(cin, arrc_temp_temp);

    vector<string> arrc_temp = split_string(arrc_temp_temp);

    vector<int> arrc(lenc);

    for (int i = 0; i < lenc; i++) {
        int arrc_item = stoi(arrc_temp[i]);

        arrc[i] = arrc_item;
    }

    long ans = triplets(arra, arrb, arrc);

    fout << ans << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
