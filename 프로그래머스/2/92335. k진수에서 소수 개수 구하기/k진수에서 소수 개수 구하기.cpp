#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

/*
    정수 n이 있다.
    숫자를 k진수로 변환했을 때, 소수 찾기
    
    그런데 모든 소수가 아니라 특정 조건에 맞는 소수여야 한다.
    1. 양쪽에 0이 있는 경우 -> 0P0
    2. 오른쪽에만 0이 있고 왼쪽엔 아무것도 없는 경우 -> P0
    3. 왼쪽에만 0이 있고 오른쪽엔 아무것도 없는 경우 -> 0P
    4. 양쪽에 아무것도 없는 경우 -> P
    단, P는 자리수에 0을 포함하지 않아야만 한다.
    
    그러므로 처음부터 0이 나올때까지의 값, 0과 0사이의 값, 0부터 마지막까지의 각 값이 소수인지만 판단하자.
    
    N을 K진법으로 변환하는 부분은 별도 함수로 구현
*/

// 10진수 값인 N을 K진법으로 변환해준다
string convert_formation(int N, int K) {
    if (K == 10) return to_string(N);
    string tmp = "";
    int exp = 0;
    
    // 변환 수행, 그런데 0제곱부터 나눠가므로 마지막에 뒤집어야 한다.
    while ((N / long(pow(K, exp)) > 0)) {
        tmp += char('0' + (N % long(pow(K, exp + 1))) / long(pow(K, exp++)));
    }
    
    // 마지막 뒤집기
    string result("");
    for (auto v : tmp) result = v + result;
    
    return result;
}

// 어떤 수가 소수인지 체크하는 함수
bool checkPrime(long long N) {
    if (N == 1) return false;
    
    int i = 2;
    while (long(pow(i, 2) <= N)) {
        if (N % i++ == 0) return false;
    }
    return true;
}

int solution(int n, int k) {
    long answer = 0;
    
    string value = convert_formation(n, k);
    // cout << value << endl;
    
    // 0 찾아서 보기
    string tmp = "";
    for (int i = 0; i <= value.length(); i++) {
        // 0의 값을 만났거나, 마지막 값에 도달했다면, 지금까지 저장된 내용들이 소수인지 확인한다.
        if ((value[i] == '0' || i == value.length())) {
            // 만약 저장된 내용이 하나도 없다면, 아무것도 할 필요 없음.
            if (tmp == "") continue;
            
            
            // 저장한 내용 체크하기
            if (checkPrime(stoll(tmp))) answer++;
            /// cout << "TMP : " << tmp << endl;
            tmp = "";
        }
        
        // 아니면 그냥 tmp에 더한다.
        else {
            tmp += value[i];
        }
    }
    
    return answer;
}