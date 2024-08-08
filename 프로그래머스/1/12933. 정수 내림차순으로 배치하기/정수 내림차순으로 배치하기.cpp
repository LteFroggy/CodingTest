#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(char a, char b) {
    return a > b;
}

long long solution(long long n) {
    long long answer = 0;
    string sN = to_string(n);
    
    sort(sN.begin(), sN.end(), compare);
    
    answer = stoll(sN);
    return answer;
}