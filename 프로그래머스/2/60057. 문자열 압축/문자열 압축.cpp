#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
    문자열을 잘라서 압축함으로써 가장 짧게 만든다.
    하나의 길이로만 자를 수 있다.
    
    잘라서 겹치는 여부만 확인하자..
*/

int solution(string s) {
    int N = s.length();
    int half_N = N / 2;
    int length = s.length();
    
    for (int i = 1; i <= half_N; i++) {
        int cursor = 0;
        int now_length = s.length();
        // 겹치는 것이 있는지 확인한다.
        while (cursor + i < N) {
            // 겹친다면, 그 다음에 또 겹치는지 확인한다.
            if (s.substr(cursor, i) == s.substr(cursor + i, i)) {
                int mul = 2;
                cursor = cursor + i;
                while (s.substr(cursor, i) == s.substr(cursor + i, i)) {
                    mul++;
                    now_length -= i;
                    cursor = cursor + i;
                }
                cursor = cursor + i;
                now_length -= i;
                // 반복 횟수를 확인하고 더해준다
                now_length += to_string(mul).length();
            }
            // 겹치지 않는다면, cursor를 i만큼 증가시켜서 반복한다.
            else {
                cursor += i;
            }
        }
        length = min(length, now_length);
    }
    
    
    return length;
}