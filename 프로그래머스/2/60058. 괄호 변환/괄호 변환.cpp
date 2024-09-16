#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    균형잡힌 괄호 문자열의 최소 길이로 1, 2 자르기
    
    만약 1이 올바르다면, 2에 대해서 다시 균형잡힌 괄호 자르기
    1이 올바르지 않다면?
        1. (을 붙이기
        2. v에서 또 균형잡힌 괄호 문자열 잘라 1에 붙이기
        3. )을 마지막에 붙이기
        4. 1에서 첫번쨰, 마지막 문자 제거하고 나머지 문자열의 괄호 방향 뒤집어서 붙이기.
        5. 반환
            
    u, v를 본다.
    u가 올바르다면? 그대로 두고 v에 대해서 재귀 진행
    u가 올바르지 않다면, (v재귀)u앞뒤삭제+뒤집기
    를 붙인다.
*/

// u, v를 사용해 올바른 괄호 문자열 결과를 가져다주는 함수
string Recursive(string p, int depth) {
    string u = "";
    string v = "";
    
    // p 자체가 빈 문자열이면, 그냥 빈 문자열을 반환한다.
    if (p == "") {
        return "";
    }
        
    // bracket_count가 0이 되면 균형잡힌 괄호 쌍이 찾아진 것이다.
    int bracket_count;
    // correct_flag는 이게 올바른 괄호 쌍인지 검사하는 것
    bool correct_flag;
    
    // 먼저 앞에서부터 균형잡힌 괄호 쌍을 찾는다
    // 만약, 열리는 괄호로 시작했다면 무조건 올바른 괄호 쌍이 될 수 밖에 없다.
    if (p[0] == '(')  {
        bracket_count = 1;
        correct_flag = true;
    }
    
    // 반대로 닫히는 괄호로 시작했다면 무조건 올바르지 않음
    else {
        bracket_count = -1;
        correct_flag = false;
    }
    
    int cursor = 0;
    // 올바른 괄호 쌍까지의 길이를 알아낸다.
    do {
       cursor++;
       if (p[cursor] == '(') 
           bracket_count++;
       else    
           bracket_count--;
    } while (bracket_count != 0);
    
    int u_length = cursor + 1;
    
    // 결과를 바탕으로 u와 v값 찾기
    u = p.substr(0, u_length);
    v = p.substr(u_length, p.length() - u_length);
    cout << "depth " << depth << endl;
    cout << "u : " << u << endl;
    cout << "v : " << v << endl;
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
    
    // u가 올바른지, 올바르지 않은지 기준으로 반환하기
    // 올바르다면, u에 v를 재귀적으로 수행한 결과를 붙이면 된다.
    if (correct_flag) {
        string corrected_v = Recursive(v, depth + 1);
        string result = u + corrected_v;
        cout << "depth " << depth << endl;
        cout << "u : " << u << endl;
        cout << "corrected_v : " << corrected_v << endl;
        cout << "result : " << result << endl;
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        return result;
    }
    
    // 올바르지 않다면, ( + v재귀 + ) + u의 처음 마지막 제거, 나머지 뒤집기를 반환한다.
    else {
        string result = "(";
        string corrected_v = Recursive(v, depth + 1);
        result += corrected_v;
        result += ")";
        
        for (int i = 1; i < u.length() - 1; i++) {
            if (u[i] == '(') 
                result += ')';
            else 
                result += '(';
        }
        cout << "depth " << depth << endl;
        cout << "u : " << u << endl;
        cout << "corrected_v : " << corrected_v << endl;
        cout << "result : " << result << endl;
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ" << endl;
        return result;
    }
}

string solution(string p) {
    string answer = Recursive(p, 1);
    
    
    return answer;
}