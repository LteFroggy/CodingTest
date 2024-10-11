#include <iostream>

using namespace std;

/*
     나머지와 몫이 같으려면, 그냥 가능한 모든 값을 구해서 더하면 된다.
     나머지는 그 값 -1까지니까, 값이 커질수록 그렇게그렇게된다.
*/

int main() {
    int N;
    cin >> N;
    
    long long answer = 0;
    
    for (int i = 0; i < N; i++) {
        answer += long(N * i) + i;
    }
    
    
    cout << answer << endl;
    return 0;
}