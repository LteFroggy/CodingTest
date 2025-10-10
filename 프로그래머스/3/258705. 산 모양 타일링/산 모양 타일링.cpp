#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    정삼각형 2n + 1개를 이어붙여 사다리꼴 만들기 가능.
    사다리꼴의 윗면과 변을 공유하는 n개의 정삼각형 중, 일부의 위쪽에 세모를 붙여 새로운 모양 만든다.
    
    이렇게 만든 모양을 정삼각형 타일 혹은 마름모 타일로 빈 곳이 없도록 채우려 한다.
    
    빈 칸이 없도록 채우는 경우의 수를 10007로 나눈 나머지를 return
    
    무조건 세모는 하나씩 있고, 그 다음은 2세모냐 1세모냐이다.
    
    세모의 숫자로 세자면 아래와 같다는 것
    
    만약 주어진 값이
      1   1   0   1이라면
    
idx 0 1 2 3 4 5 6 7   
val 1 2 1 2 1 1 1 2
    개의 세모가 있는 것
    
    두 개의 DP를 둔다
    하나는 tri, 하나는 radder
    
    tri는 삼각형으로 n번째 값을 썼을 때, radder는 사다리꼴로 n번째 값을 썼을 때.
    여기서 썼다는 건 아래 삼각형만을 의미한다. 위 삼각형은 신경 안 씀
    
    처음엔 val이 1이므로, 삼각형밖에 안된다
    
    tri[0] = 1;
    rad[0] = 0;
    
    다음 val이 2인데, 세 가지 경우의 수가 있다
    1. 앞의 삼각형과 더해서 마름모 쓰기
    2. 2니까 자체적으로 마름모 쓰기
    3. 둘 다 세모로 처리하기
    
    이 중 1, 2가 마름모를 사용하는 것이니 rad로 가야 함
    2는 나 혼자 할 수 있는 것. 따라서 앞이 세모이던 마름모이던 상관없음
    rad[1] += tri[0] + rad[0] = 1
    1은 앞이 세모여야만 가능.
    rad[1] += tri[0] = 1
    
    따라서 rad[1] = 2
    3은 둘 다 세모로 처리하는것. 앞이 세모이던 마름모이던 상관없음
    tri[1] = tri[0] + rad[0] = 1;
    
    rad[1] = 2, tri[1] = 1;
    
    따라서 총 경우의 수는 rad[1] + tri[1] = 3;
    
    다음은 또 1이다.
    1은 세모 혹은 마름모로 사용 가능
    그냥 세모를 쓰려면, 앞이 세모이든 마름모이든 상관없다
    tri[2] = tri[1] + rad[1] = 3
    
    마름모를 쓰려면, 앞에 세모여야만 함
    rad[2] = tri[1] = 1
    
    tri[2] + rad[2] = 3 + 1 = 4;
    
    이렇게 된다. 반복하기
*/

int solution(int n, vector<int> tops) {
    int answer = 0;
    
    vector<int> triangles;
    
    // 일단 두배짜리 배열을 만든다
    for (int i = 0; i < tops.size(); i++) {
        // tops 앞에는 항상 1개짜리 삼각형이 따라온다
        triangles.push_back(1);
        triangles.push_back(tops[i] + 1);
    }
    
    // 마지막에도 1개짜리 삼각형 있음
    triangles.push_back(1);
    
    n = triangles.size();
    
    // 해당하는 네모를 삼각형으로 사용했다면 triDP, 마름모로 썼다면 radDP
    vector<int> triDP(n, 0);
    vector<int> radDP(n, 0);
    // 초기값 할당
    triDP[0] = 1;
    radDP[0] = 0;
    
    for (int i = 1; i < n; i++) {
        /// cout << i+1 << "번째 삼각형은 " << triangles[i] << "개" << endl;
        // 이번이 삼각형 1개짜리라면
        if (triangles[i] == 1) {
            // 삼각형일 경우엔 앞이 뭐든 상관없음
            triDP[i] += triDP[i - 1] + radDP[i - 1];
            
            // 마름모라면, 앞이 삼각형이어야 함
            radDP[i] += triDP[i - 1];
            
            /// cout << "TRI : " << triDP[i-1] << "+" << radDP[i-1] << " = " << triDP[i] << endl;
            /// cout << "RAD : " << triDP[i-1] << " = " << radDP[i] << endl;
        }
        
        // 삼각형 2개짜리라면
        else {
            // 삼각형은 역시 앞이 뭐든 상관없음
            triDP[i] += triDP[i - 1] + radDP[i - 1];
            
            // 마름모라면, 일단 앞과 함께 마름모 만드는 경우에는 앞이 세모여야만 함
            radDP[i] += triDP[i - 1];
                
            // 나 혼자 마름모 만들수도 있음. 이 경우엔 앞이 뭐든 상관없음
            radDP[i] += triDP[i - 1] + radDP[i - 1];
        }
        
        /// cout << "총합 " << triDP[i] + radDP[i] << "개" << endl;
        
        // 나누기연산
        triDP[i] %= 10007;
        radDP[i] %= 10007;
        
        /// cout << endl << endl;
    }
    
    // 마지막 값을 answer로 낸다.
    return (triDP[n - 1] + radDP[n - 1]) % 10007;
}