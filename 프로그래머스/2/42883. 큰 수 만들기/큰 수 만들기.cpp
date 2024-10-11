#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    어떤 숫자에서 k개의 수를 제거해서 가장 큰 숫자를 구하자
    가장 큰 숫자는 어떻게 만들까?
    
    어차피 K개를 제거하면 같다. 그러니 제일 작은 수들을 제거해주는게 좋다.
    근데 또 앞에서 큰 수가 나와야 더 좋다. 그러니 제일 작은 수를 순서대로 없애면 큰 수를 장담할 수 없음.
    
    가능한 한 앞에서부터 큰 수를 남겨야 함.
    다시 스택 사용해보자
    
    1 9 2 4
    2개까지 뺄 수 있다
    1 넣는다.
    9 만났다. 제일 크다! 뺀다
    9 2
    
    4 만났다. 2보다 크니 뺀다!
    9 4 끝!
*/

string solution(string number, int k) {
    string answer = "";
    
    stack<char> stk;
    
    for (auto v : number) {
        if (stk.empty()) {
            stk.push(v);
        }
        
        else {
            // 뺄 수 있는 기회가 남았고, 지금 값이 stk.top보다 크다면 값을 뺴줘야 한다.
            while (!stk.empty() && k > 0 && stk.top() < v) {
                stk.pop();
                k--;
            }
            
            stk.push(v);
        }
    }
    
    // 만약 K가 남았다면(뺄 수 있는 값이 남았다면), 모두 같은 수여서 그런 것이다.
    // 그냥 뺀다.
    while (k != 0) {
        stk.pop();
        k--;
    }
    
    while (!stk.empty()) {
        answer += stk.top();
        stk.pop();
    }
    
    // 반환은 뒤집어서!
    reverse(answer.begin(), answer.end());
    
    return answer;
    
}