#include <string>
#include <vector>

using namespace std;

// 그냥 하나씩 나눠보기

int solution(vector<int> arr) {
    int answer = 0;
    
    
    for (int i = 2; i <= 1e9; i++) {
        bool flag = true;
        for (auto v : arr) {
            if (i % v != 0) {
                flag = false;
                break;
            }
        }
        if (flag) return i;
    }
    return answer;
}