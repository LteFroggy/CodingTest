#include <string>
#include <vector>

using namespace std;


/*
    JadenCase만들기.
    모든 단어의 첫 문자 대문자, 그 외의 알파벳은 모두 소문자.
    첫 문자가 알파벳이 아니라면, 이어지는 알파벳은 소문자로.
*/

string solution(string s) {
    string answer = "";
    int idx = 0;
    // flag가 
    bool uppercaseFlag = true;
    
    while (idx < s.length()) {
        // 공백을 만났다면, 다음 단어로 넘어가는 것. 다음 문자는 대문자여야 함
        if (s[idx] == ' ') {
            uppercaseFlag = true;
            answer += s[idx];
        }
        
        // 지금 대문자가 나와야 할 상황인가?
        else if (uppercaseFlag) {
            // 대문자가 나와야 하는데, 소문자가 나왔다면 대문자로 올리기
            if (s[idx] >= 'a' && s[idx] <= 'z') answer += 'A' + (s[idx] - 'a');
            
            // 소문자가 아니라면, 그냥 넣기
            else answer += s[idx];
            
            uppercaseFlag = false;
        }

        // 소문자가 나와야 하는 타이밍이라면, 대문자는 소문자로 바꿔 넣기
        else {
            if (s[idx] >= 'A' && s[idx] <= 'Z') answer += 'a' + (s[idx] - 'A');
            else answer += s[idx];
        }
        
        idx++;
    }
    
    return answer;
}