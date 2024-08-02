#include <string>
#include <vector>

using namespace std;

double solution(vector<int> arr) {
    double answer = 0;
    
    for (auto v : arr) {
        answer += v;
    }
    
    answer /= arr.size();
    
    return answer;
}