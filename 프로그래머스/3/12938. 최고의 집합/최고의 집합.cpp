#include <string>
#include <vector>

using namespace std;

/*
    자연수 n개로 이루어진 중복 집합 중 다음 두 조건을 만족하면 최고의 집합이 된다
    1. 각 원소의 합이 S가 되는 수의 집합
    2. 위 조건을 만족하며 원소의 곱이 최대가 되는 집합
    
    가능한 한 동일하게 나누면 된다..
*/

vector<int> solution(int n, int s) {
    // 애초에 안 되는 조건이면, -1 반환하기
    if (n > s) return vector<int>{-1};
    
    vector<int> answer;
    int leftover = s % n;
    
    int val = s / n;
    
    for (int i = 0; i < n - leftover; i++)
        answer.push_back(val);
    for (int i = 0; i < leftover; i++)
        answer.push_back(val + 1);
    
    return answer;
}