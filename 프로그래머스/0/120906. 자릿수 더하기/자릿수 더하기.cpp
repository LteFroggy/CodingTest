#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    string sN = to_string(n);
    
    int answer(0);
    
    for (int i = 0; i < sN.size(); i++) {
        answer += sN[i] - '0';
    }
    
    return answer;
}