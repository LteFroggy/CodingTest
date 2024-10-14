#include <iostream>
#include <algorithm>

using namespace std;

/*
    자동차를 생산하는 A라인과 B라인이 있다.
    각각 N개의 작업장이 존재하고, A_i 와 B_i로 표현한다.

    각 모든 A_i와 B_i는 같은 작업을 수행하나, 시간이 다를 수 있다.
    모두 N개의 공정을 완료해야 자동차가 완성된다!
    A_i에서 B_i로의 이동은 가능하나, 이동시간이 추가된다.
    자동차 1대의 가장 빠른 조립 시간을 구해라.
*/

int main(int argc, char** argv) {
    int N;
    cin >> N;

    // i번째 작업이 끝났을 때 A에 있을지, B에 있을지만 중요하다.
    // 각 작업장에서 i번째 작업을 끝내고, i+1번째 작업장에 도착했을 때의 제일 짧은 시간을 구한다.
    int A_time_now(0);
    int B_time_now(0);
    int A_time_next(0);
    int B_time_next(0);

    // 작업 하나씩 진행하기
    for (int i = 0; i < N; i++) {
        int a_time, b_time;
        cin >> a_time >> b_time;

        // 현재 A작업장에 있을 경우, A에서 작업을 먼저 수행해야 한다
        A_time_now += a_time;
        // B에 있으면 B에서 작업하기
        B_time_now += b_time;


        // 마지막 작업장이 아니라면, 다음으로 넘겨야 한다.
        if (i != N - 1) {
            // 먼저 이동시간 입력받기
            int AtoB, BtoA;
            cin >> AtoB >> BtoA;

            // 이제, 다음 A작업장으로 이 작업물을 넘긴다.
            // A작업물을 사용하면 시간이 그대로이고, B작업물을 사용하면 이동시간이 걸린다.
            // 둘 중 짧은걸 사용
            A_time_next = min(A_time_now, B_time_now + BtoA);

            // B작업장도 같은 방법으로 작업물을 넘긴다
            B_time_next = min(B_time_now, A_time_now + AtoB);

            // 갱신된 시간을 적용한다.
            A_time_now = A_time_next;
            B_time_now = B_time_next;
        }
    }

    // 과정이 완료되었다면, 둘 중 더 짧은걸 출력한다
    cout << min(A_time_now, B_time_now) << endl;
    
    return 0;
}
