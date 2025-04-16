#include <string>
#include <vector>

/*
    n개의 괄호 쌍이 주어질 때, n개의 괄호 쌍으로 만들 수 있는 모든 괄호 문자열의 갯수 반환
    최대 14개인걸 보니 백트래킹으로 처리 가능
    최대 2^14
*/

using namespace std;

void backtrack(int open_count, int close_count, int &answer) {
    // 괄호 다 썼으면 answer++하고 종료한다.
    if (open_count == 0 && close_count == 0) answer++;
    
    // 아직 괄호 더 써야 하면, close_count와 open_count 보고 확인한다.
    else {
        // 아직 열린 괄호가 있으면, 언제나 열기는 가능하다
        if (open_count > 0) {
            backtrack(open_count - 1, close_count, answer);
        }
        
        // 그리고, 열린 괄호가 닫힌 괄호보다 적으면 닫기도 가능
        if (open_count < close_count) {
            backtrack(open_count, close_count - 1, answer);
        }
    }
}

int solution(int n) {
    int answer = 0;
    
    int open_count = n;
    int close_count = n;
    
    // 백트래킹한다.
    backtrack(open_count, close_count, answer);
    
    return answer;
}