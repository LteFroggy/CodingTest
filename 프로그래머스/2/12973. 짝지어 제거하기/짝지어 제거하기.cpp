#include <iostream>
#include <string>
#include <stack>
using namespace std;

/*
    알파벳 소문자 문자열이 하나 나온다.
    문자열에서 같은 알파벳이 2개 붙어있는 짝 찾기
    
    둘을 제거하고, 앞뒤로 문자열 이어붙이기
    이 과정을 반복해서 모두 제거하면, 짝지어 제거하기 종료됨
    
    짝지어 제거하기 성공 여부를 반환해보자.
    
    앞뒤 제거하기를 연속해서 하면 된다.
    스택 사용하자.
*/

int solution(string s)
{
    stack<char> stk;
    
    for (auto v : s) {
        // 스택 비어있으면 그냥 넣기
        if (stk.empty()) {
            stk.push(v);
        }
        
        // 비어있지 않으면, 제거 가능한지 확인하고 제거
        else if (stk.top() == v) {
            stk.pop();
        }
        
        // 아니면 넣기
        else {
            stk.push(v);
        }
    }
    
    if (stk.empty()) 
        return true;
    else 
        return false;
}