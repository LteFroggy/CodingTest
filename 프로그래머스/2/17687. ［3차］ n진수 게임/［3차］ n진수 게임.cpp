#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
    읽어야 하는 숫자를 string으로 표현하고, 계속 더해가면서 문자열의 길이가 t * (m - 1) + p가 될 때까지 구하면 된다.
    
    n진수 변환은 함수를 만들어 따로 표현할 것
    하나씩 구해봐야 하는 것은 변하지 않을 듯? 바로바로 알아낼 방법이 생각나는 것이 없음
*/

// 0 ~ 16의 값에 대한 매핑을 수행해주는 vector
vector<char> mapping = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

string formation_change(int n, int number);


string solution(int n, int t, int m, int p) {
    string answer = "";
    string num_str = "";
    
    // 값은 0부터 시작한다
    int value(0);
    
    while (num_str.length() < (t - 1) * m + p) {
        string tmp = formation_change(n, value++);
        num_str += tmp;
    }
    
    // 이제 완성된 문자열을 보고, 내 차례인 것만 answer에 더한다
    for (int i = 0; i < t; i++) {
        // cout << num_str[(i * m) + p - 1];
        answer += num_str[(i * m) + p - 1];
    }
    
    return answer;
}


string formation_change(int n, int number) {
    string result = "";
    int exp = 1;
    
    // 먼저 몇 자리 수가 될지 판단해야 한다.
    while (number / int(pow(n, exp)) != 0) { exp++; };
    
    // 그리고, 거기서부터 자리 값을 판단해 나간다.
    while (--exp >= 0) {
        int value = number / int(pow(n, exp));
        number -= value * int(pow(n, exp));
        
        
        // 매핑을 보고, result에 더해준다
        result += mapping[value];
    }
    
    return result;
}