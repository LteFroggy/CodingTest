#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/*  
    최대 및 최소 찾기
    스페이스 단위로 잘려있으니, 그걸 구현하자
*/

vector<string> split(string target, char deli = ' ') {
    vector<string> result;
    string tmp;
    stringstream ss(target);
    
    while (getline(ss, tmp, deli)) {
        result.push_back(tmp);
    }
    
    return result;
}

string solution(string s) {
    int min_val = 1e9;
    int max_val = -1e9;
    
    vector<string> splited = split(s);
    
    for (auto v : splited) {
        int val = stoi(v);
        
        min_val = min(min_val, val);
        max_val = max(max_val, val);
    }
    
    string answer = "";
    
    answer += to_string(min_val);
    answer += ' ';
    answer += to_string(max_val);
    return answer;
}