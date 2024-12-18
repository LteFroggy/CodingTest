#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    110을 다 찾아서 뽑는다
    111이 보이면, 그 앞에다 놓는다
    그럼 111이 아니고 1이면?
    
    맨 뒤가 0으로 끝났다는건, 적어도 그 앞에 1이 두개 연속으로 존재하지는 않는다는 뜻이다. 따라서 다 나보다 작은 값들임. 맨 뒤에 붙인다.
    맨 뒤가 1로 끝났다는건, 그 앞에 무슨 값일지 모른다. 최대한 빠른 0뒤에 가져다 붙인다.
*/

vector<string> solution(vector<string> s) {
    vector<string> answer;
    
    // 각 문자열별 처리를 진행한다.
    for (auto &v : s) {       
        int count = 0;
        /// cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        /// cout << v << endl;
        
        // 스택에 각 문자열을 넣어가면서 체크할 것
        stack<char> stk;
        for (int i = 0; i < v.size(); i++) {
            if (v[i] != '0' || stk.size() < 2) stk.push(v[i]);
            else {
                if (stk.top() == '1') {
                    stk.pop();
                    if (stk.top() == '1') {
                        stk.pop();
                        count++;
                    }
                    
                    else {
                        stk.push('1');
                        stk.push(v[i]);
                    }
                }
                
                else stk.push(v[i]);
            }
        }
        
        // 스택에 남은 문자열들을 뽑아서 string을 재정리한다.
        string str = "";
        while (!stk.empty()) {
            str = stk.top() + str;
            stk.pop();
        }
        
        /// cout << str << endl;
        /// cout << count << endl;
        
        // 이제, 넣을 자리를 골라야 한다.
        int loc = 0;
        
        // 맨 뒤가 0이라면, 그 앞에 1이 두개 연속으로 존재하는 일은 없다는 뜻 -> 나보다 작다는 것. 맨 뒤에 가져다 붙인다.
        if (str[str.length() - 1] == '0') loc = str.length();
        
        // 맨 뒤가 1이라면, 제일 나중 0의 위치를 찾고 그 앞에 꽃으면 된다.
        else {
            if (str.find('0') == string::npos) loc = 0;
            else loc = str.rfind('0') + 1;
        }
        
        for (int i = 0; i < count; i++) str.insert(loc, "110");
        
        answer.push_back(str);
    }
    
    return answer;
}