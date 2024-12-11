#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    1을 모두 제거한다.
    그 길이를 2진수로 표현한다.
    1길이가 1이될때까지 반복한다.
*/

string int_to_2(int val) {
    string s = "";
    while (val != 0) {
        s += to_string(val % 2);
        val /= 2;
    }
    
    reverse(s.begin(), s.end());
    return s;
}

vector<int> solution(string s) {
    vector<int> answer;
    int count = 0;
    int removed_0 = 0;
    
    while (s != "1") {
        int length = 0;
        count++;
        for (auto v : s) {
            if (v == '1') {
                length++;
            }
            
            else {
                removed_0++;
            }
        }
        // cout << "length = " << length << endl;
        // cout << "변환 후 s : " << s << endl;
        s = int_to_2(length);
    }
    answer.push_back(count);
    answer.push_back(removed_0);
    
    return answer;
}