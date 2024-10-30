#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
    라이언은 우승자에게 상금을 한다.
    3가지의 연산문자로 이루어진 연산 수식이 전달되고, 미션은 전달받은 수식에 포함된 우선순위를 새로 저리한다.
    
    계산 결과가 음수이면, 절대값으로 올린다.
    6가지 모두 체크하면 될 듯?
    
    체크 방법은 재귀함수로 하자.
    
*/

// 값 두개, 연산기호를 넣어주면 숫자로 계산한 후 string으로 돌려주는 함수
string calc_result(string num1, string num2, string operation) {
    long long result_int;
    if (operation == "+") {
        result_int = stoll(num1) + stoll(num2);
    }
    else if (operation == "-") {
        result_int = stoll(num1) - stoll(num2);
    }
    else {
        result_int = stoll(num1) * stoll(num2);
    }
    
    return to_string(result_int);
}

// 값을 다 나눈다.
vector<string> split(string s) {
    vector<string> result;
    
    int idx_before(0);
    int idx_now(0);
    while (idx_now++ < s.length()) {
        char tmp = s[idx_now];
        
        // 연산기호를 찾았다면, 지금 이전까지의 값은 숫자, 여기는 기호이다.
        if (tmp == '-' || tmp == '+' || tmp == '*') {
            result.push_back(s.substr(idx_before, idx_now - idx_before));
            
            // 기호에 맞게 넣는다
            if (tmp == '-') result.push_back("-");
            else if (tmp == '+') result.push_back("+");
            else if (tmp == '*') result.push_back("*");
            idx_before = idx_now + 1;
        }
    }
    
    // 마지막 숫자까지 넣어준다
    result.push_back(s.substr(idx_before, idx_now - idx_before - 1));
    
    return result;
}

// 제일 큰 값을 찾기 위한 함수.
void backTrack(vector<bool> &used, vector<string> result, string symbol_now, int loop_count, long long &answer) {
    /*  0 -> +
        1 -> -
        2 -> *
    */
    
    // 만약 첫 루프라면, 3가지 전부 보내고 끝낸다
    if (loop_count == 0) {
        for (int i = 0; i < 3; i++) {
            used[i] = true;
            if (i == 0) backTrack(used, result, "+", loop_count + 1, answer);
            else if (i == 1) backTrack(used, result, "-", loop_count + 1, answer);
            else backTrack(used, result, "*", loop_count + 1, answer);
            used[i] = false;
        }
    }
    
    // 아직 loop_count가 3(3가지 모두 시도하고 답을 볼 차례)가 아니라면, 내 계산을 수행하고 다음으로 넘긴다.
    else if (loop_count < 4) {
        for (int i = 0; i < result.size(); i++) {
            // 이번에 내가 계산할 차례인 값이 나왔다면, 내 앞뒤값을 계산해 나에게 저장하고, 앞뒤값을 삭제한다.
            if (result[i] == symbol_now) {
                result[i] = calc_result(result[i-1], result[i+1], result[i]);
                result.erase(result.begin() + i + 1);
                result.erase(result.begin() + i - 1);
                i--;
            }
        }
        
        // 모든 계산을 다 했다면, answer과 비교하고 출력한다.
        if (result.size() == 1) {
            answer = max(abs(stoll(result[0])), answer);
            return;
        }
        
        // 계산이 끝났다면, 아직 안해본거 다 해보기 위해 넘긴다.
        for (int i = 0; i < 3; i++) {
            if (used[i]) continue;
            
            used[i] = true;
            if (i == 0) backTrack(used, result, "+", loop_count + 1, answer);
            else if (i == 1) backTrack(used, result, "-", loop_count + 1, answer);
            else backTrack(used, result, "*", loop_count + 1, answer);
            used[i] = false;
        }
    }
}

long long solution(string expression) {
    long long answer = 0;
    
    // 일단, 값을 나눈다.
    vector<string> result = split(expression);
    
    vector<bool> used(3, false);
    
    // 잘 나눴다면, 이제 backtrack을 수행한다.
    backTrack(used, result, "", 0, answer);
    
    return answer;
}