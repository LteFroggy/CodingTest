#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
    강이 남북으로 흐를 때, 동서로 징검다리가 놓여 있다.

    높이가 점점 높은 돌을 밟다가, 점점 낮은 돌을 밟으면서 개울을 지나갈 것!
    최대로 밟을 수 있는 돌의 개수는?

    돌의 개수는 최대 300000개

    어떤 돌을 밟았을 때의 최대 밟은 돌 개수를 저장하자.
    
    그럼 꺾는 시점은 어떻게 정할까?
    꼭 가장 큰 값에서 꺾는게 좋은 건 아닌 듯 하다.
    -> 한 지점에서 내려가기 시작해야 한다. 따라서 왼쪽에서부터 증가할 때 밟을 수 있는 최대 돌 개수와 오른쪽에서부터 증가할 때 밟을 수 있는 최대 돌 개수를 구하고,
    그 둘의 합이 최대값이 되는 지점을 찾으면 된다.

    https://4legs-study.tistory.com/106 이 페이지를 참고하여 LIS에 대한 개념을 익혔다.
    LIS는 최장 부분 증가 수열로, 수열 내에서 증가하는 수열을 만드는 것이다.
    이진 탐색으로 찾으면 n*log(n)으로 LIS를 구할 수 있다.

    C++이니 vector과 lower_bound를 사용하자.
    내가 LIS내에서 저장될 위치가, 나를 포함한 최대 길이이다

    예를 들어 3 4 5 1 2 3 5 9 2 3이라 치자
    각 값을 보고, LIS내부에서 나보다 작은 값 바로 뒤에 넣는다.

    input -> LIS 의 형태이다
    3 -> '3'
    첫 값은 그냥 들어간다!
    
    4 -> 3 '4'
    4가 LIS의 마지막 원소보다 크므로 뒤에 들어간다(LIS는 증가 수열)
    idx = 1이므로 4를 밟았을 때의 최대 증가 수열은 2이다.

    5 -> 3 4 '5'
    idx = 2이므로 5를 밟았을 떄의 최대 증가 수열은 2이다

    1 -> '1' 4 5
    1보다 작은 값은 없으니, 첫 값을 대체한다. idx = 0이므로 1을 밟았을 때의 최대 증가 수열은 1

    2 -> 1 '2' 5
    2는 1보다 크므로 1바로 뒤에 들어간다. idx = 1이므로 최대 증가 수열은 2
    
    3 -> 1 2 '3'
    최대 증가 수열 3

    5 -> 1 2 3 '5'
    최대 증가 수열 4

    9 -> 1 2 3 5 '9'
    최대 증가 수열 5

    2 -> 1 '2' 3 5 9
    최대 증가 수열 2

    3 -> 1 2 '3' 5 9
    최대 증가 수열 3

    결과적으로 각 돌에서의 최대 증가 수열은 아래와 같이 저장된다.
    3 4 5 1 2 3 5 9 2 3
    1 2 3 1 2 3 4 5 2 3

    반대 방향에서도 같은 일을 수행하고, 더해서 최대가 되는 위치를 구하면 된다.
*/

int update_LIS(vector<int> &LIS, int target) {
    auto bound_iter = lower_bound(LIS.begin(), LIS.end(), target);
    int bound_idx = bound_iter - LIS.begin();

    if (bound_idx == LIS.size()) LIS.push_back(target);
    else LIS[bound_idx] = target;

    return bound_idx + 1;
}

int main(int argc, char** argv) {
    int N;
    cin >> N;

    vector<int> rocks(N);

    vector<int> LIS_front(N, 0);
    vector<int> LIS_back(N, 0);

    vector<int> LIS;

    for (auto &v : rocks) cin >> v;

    // 먼저 앞에서부터 밟았을 때의 돌 별 최대 LIS를 구한다.
    for (int i = 0; i < N; i++) {
        LIS_front[i] = update_LIS(LIS, rocks[i]);
        // cout << i + 1 << "번쨰 값과 최대 증가 수열 : " << rocks[i] << ", " << LIS_front[i] << endl;
    }


    LIS.clear();

    // 뒤에서부터 밟았을 떄의 돌 별 lis도 구한다
    for (int i = 0; i < N; i++) {
        LIS_back[i] = update_LIS(LIS, rocks[N - i - 1]);
        // cout << i + 1 << "번쨰 값과 최대 증가 수열 : " << rocks[N - i - 1] << ", " << LIS_back[i] << endl;
    }

    // 이제 두 값을 합해가며 최대값을 구한다
    int max_val = 0;
    for (int i = 0 ; i < N; i++) {
        int sum = LIS_front[i] + LIS_back[N - i - 1] - 1;
        max_val = max(max_val, sum);
    }


    cout << max_val << endl;
    return 0;
}
