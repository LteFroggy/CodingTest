#include <string>
#include <iostream>
#include <stack>

using namespace std;

/*
    스택을 사용해 넣고뺴고한다.    
*/

bool solution(string s)
{
    bool answer = true;
    stack<int> stk;
    
    for (auto v : s) {
        if (v  == '(') stk.push(1);
        else {
            if (stk.empty()) return false;
            else stk.pop();
        }
    }
    
    if (!stk.empty()) return false;


    return true;
}