#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/*
    값은 900개 뿐이다. 이진탐색 가자.
    
    비용이 최소인 높이는 하나로 정해져있다. 물론 같은 값이 여러 개 나올 수도 있겠지만,
    높이는 비용과 내리는 비용이 다르다면 어느 정도로 맞췄을 때 가장 적합한 비용이 나오는지가 있을 것.
*/

// 높여야 하는 높이와 낮혀야 하는 높이를 구해주는 함수
pair<long long, long long> getIncDec(const vector<vector<int>> &land, int target) {
    long long toInc(0), toDec(0);
    int N = land.size();
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // 땅을 낮춰야 하는 경우
            if (land[i][j] > target) {
                toDec += land[i][j] - target;
            }
            
            // 땅을 높여야 하는 경우
            else if (land[i][j] < target) {
                toInc += target - land[i][j];
            }
        }
    }
    
    return {toInc, toDec};
}

// 목표 값으로 땅을 맞추려 할 때, 드는 비용을 계산해주는 함수
long long calculateValue(const vector<vector<int>> &lands, int target, int P, int Q) {
    pair<long long, long long> inc_dec = getIncDec(lands, target);
    long long result(0);
    
    result += inc_dec.first * P;
    result += inc_dec.second * Q;
    
    return result;
}

long long solution(vector<vector<int>> land, int P, int Q) {
    long long answer = -1;
    int N = land.size();
    int min_val(1000000001), max_val(0);
    
    
    // 먼저, 최대값과 최소값을 찾아야 한다.
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            min_val = min(min_val, land[i][j]);
            max_val = max(max_val, land[i][j]);
        }
    }
    
    /*
    for (int i = min_val; i <= max_val; i++) {
        cout << i << " : " << calculateValue(land, i, P, Q) << endl;
    }
    */
    
    // 그리고 범위를 잡아서 중간값을 찾은 후, 거기서부터 탐색 진행
    int left = min_val;
    int right = max_val;
    int middle = (left + right) / 2;
    
    while (true) {
        // 중간 양쪽 값 탐색하기
        middle = (left + right) / 2;
        long long left_val = calculateValue(land, middle - 1, P, Q);
        long long right_val = calculateValue(land, middle + 1, P, Q);
        long long middle_val = calculateValue(land, middle, P, Q);
        
        // 내가 제일 작으면 내가 제일 작은 값임
        if (middle_val <= left_val && middle_val <= right_val) {
            answer = middle_val;
            break;
        }
        
        // 왼쪽이 오른쪽부다 작거나 같다면 왼쯕으로
        else if (left_val <= right_val) {
            right = middle - 1;
        }
            
        // 오른쪽이 더 작다면 오른쪽으로
        else if (left_val > right_val) {
            left = middle + 1;
        }
    }
    
    return answer;
}