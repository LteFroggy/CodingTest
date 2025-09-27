#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

/*
    중심이 다른 서로 다른 크기의 두 원 주어진다
    r1, r2가 주어질 때 x y좌표가 모두 정수인 점의 개수 return하도록 완성하기
    
    x좌표상의 점 모두 센다. *4 해준다
    x = y인 점 모두 센다. *4 해준다
    0 ~ 45도 사이의 점을 모두 센다. 그리고 *8해주면 됨
    
    원 내부에 존재하려면, x^2 + y^2 <= r2^2 여야 함(원 위의 점도 포함)
*/

bool isInside(long long y, long long x, long long r1, long long r2) {
    return ((y * y) + (x * x) <= r2 * r2) && ((y * y) + (x * x) >= r1 * r1);
}

long long solution(int r1, int r2) {
    long long answer = 0;
    
    // x좌표상의 점 세기
    long long dotsOnAxis = r2 - r1 + 1;
    answer += dotsOnAxis * 4;
    
    /// cout << "좌표축 상의 점은 " << dotsOnAxis << "개" << endl;
    
    // x = y인 점 세기
    long long dotsOn45 = 0;
    for (int pos = 1; pos < r2; pos++) {
        if (isInside(pos, pos, r1, r2)) {
            dotsOn45++;
            /// cout << pos << ", " << pos << " 는 원 사이에 있음" << endl;
        }
    }
    answer += dotsOn45 * 4;
    
    /// cout << "45도 상의 점은 " << dotsOn45 << "개" << endl;
    
    // 이제 0 ~ 45도 사이의 점 세기
    long long dotsBetween0And45 = 0;
    // x값을 1씩 늘려가면서 보기
    for (int x = floor(sqrt(r1)); x < r2; x++) {
        // 가능한 최대값 확인하기. 45도까지의 사이어야 하므로 x보단 작아야 한다.
        double yMax = min(double(x - 1), sqrt((1LL * r2 * r2) - (1LL * x * x)));
        double yMin = r1 <= x ? 1 : sqrt((1LL * r1 * r1) - (1LL * x * x));
        
        // yMax가 yMin보다 작으면, 아예 되는 값 없음
        if (floor(yMax) < ceil(yMin)) continue;
        
        // yMax가 1보다 작아지면, 가능성 없음
        if (yMax < 1) break;
        
        /// cout << "x = " << x << "일 때, yMax = " << yMax << ", yMin = " << yMin << endl;
        
        // yMax와 yMin사이의 값들 더하기
        dotsBetween0And45 += floor(yMax) - ceil(yMin) + 1;
        
        /// cout << "사이의 값 갯수는 " << floor(yMax) - ceil(yMin) + 1 << "개" << endl;
    }
    
    answer += dotsBetween0And45 * 8;
    
    return answer;
}