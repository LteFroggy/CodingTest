#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    리모델링 할 것
    레스토랑은 원형이고, 외벽의 총 둘레는 n미터이다.
    
    외벽의 몇몇 지점은 취약하다. 그래서 공사중에도 외벽의 취약 지점이 손상되지는 않는지 점검해야 한다.
    근데, 점검 시간은 1시간만 준다.
    
    점검자별로 이동 속도는 제각각이다. 가능한 최소한의 사람을 투입해 점검하려 한다.
    정북 방향 지점이 0, 취약지점 위치는 정북에서부터 시계방향으로 얼마나 떨어졌나로 나타낸다.
    친구들은 꼭 시계 혹은 반시계 방향으로만 외벽을 따라서 이동 가능하다.
    
    외벽의 길이, 취약 지점 위치 weak, 1시간 동안 인동 가능한 거리 dist가 주어지면
    최소 투입인원 return하자.
    
    원형은 두배로 해서 편다. 그리고 Sliding Window처럼 해서 커버하면 된다.
    다시 말해, 길이가 10이고 1 3 5에 값이 있다면,
    1 3 5 11 13 15 -> 이렇게 두 배로 펴면 된다
    
    그리고 원래 길이가 3이었으니, 윈도우를 미는 것처럼 한다
    [1 3 5]
    [3 5 11]
    [5 11 13]
    
    이렇게 세 구간만 존재하는 것! [11 13 15]는 처음 값과 똑같으니 굳이 해보지 않음
    친구를 넣는 순서에 답이 영향을 받을 수 있으므로, next_permutation을 이용한다.
*/

int solution(int n, vector<int> weak, vector<int> dist) {
    int answer = 1e9;
    
    // 일단 값을 두 배 길이로 편다!
    vector<int> weak_extended;
    // 원본 값 넣기
    for (auto v : weak) weak_extended.push_back(v);
    // 늘려진 값 넣기
    for (auto v : weak) weak_extended.push_back(n + v);
    
    // 일꾼 정렬
    sort(dist.begin(), dist.end());
    
    int len = weak.size();
    
    // 확인
    /// for (auto v : weak_extended) cout << v << " "; cout << endl;
    
    int start = 0;
    
    // 일꾼을 next-permutation으로 처리한다
    do {
        for (int end = weak.size() - 1; end < weak_extended.size() - 1; end++) {
            int start = end - weak.size() + 1;

            int covered_range = 0;
            int worker_num = 0;
            int idx = start;
            // 최대 커버하는 범위가 끝값보다 크거나 같으면 된다.
            while (true) {
                // 지금 커버되지 않은 마지막 지점에 일꾼 넣는다
                // 근데, 일꾼을 다 썼다면 그냥 종료
                if (worker_num >= dist.size()) break;
                covered_range = weak_extended[idx] + dist[worker_num++];

                // 지금 모든 지점 커버에 성공했다면, 답 갱신한다.
                if (covered_range >= weak_extended[end]) {
                    if (answer > worker_num) answer = worker_num;
                    break;
                }

                // 얘가 어디까지 커버할 수 있는지 확인한다
                while (covered_range >= weak_extended[idx]) {
                    idx++;
                }
            }
        }
    } while (next_permutation(dist.begin(), dist.end()));
    
    
    if (answer == 1e9) return -1;
    else return answer;
}