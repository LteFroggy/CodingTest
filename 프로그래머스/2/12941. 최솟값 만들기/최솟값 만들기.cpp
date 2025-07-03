#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    자연수 배열
    하나씩 뽑아 두 수 곱하기
    배열의 길이만큼 반복, 곱해 더하기
    누적된 값이 최소가 되도록
    
    두 수의 곱을 최소로 맞춰야 한다
    그럼 하나는 큰 값부터, 하나는 작은 값부터
    정렬하고 하나씩 곱하기 하자.
    
    1000log(1000) 이니까 상관없다.
*/

int solution(vector<int> A, vector<int> B) {
    int answer = 0;
    
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), greater<>());
    
    for (int i = 0; i < A.size(); i++) {
        answer += A[i] * B[i];
    }

    return answer;
}