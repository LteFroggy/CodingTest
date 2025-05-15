#include <queue>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    처리해야 할 동일한 작업 n개
    처리하기 위한 CPU 존재
    
    CPU에는 코어 여러 개 있고, 코어별로 처리 시간이 다르다
    한 코어에서 작업이 끝나면, 작업 없는 코어가 바로 다음 작업 수행
    
    2개 이상의 코어가 남았을 경우, 앞의 코어부터 작업 처리
    
    마지막 작업을 처리하는 코어의 번호를 return 하자
    
    코어별로 작업을 할당하고, 끝나는 시간을 쓴다.
    빨리 끝나는 순으로 게속 정렬하면 됨 Priority_queue로
    
    
    ##### 시간 초과로 끝났음. Binary Search라고 함
    n시간까지 끝낼 수 있는 작업 개수 확인하기
    정확히 딱 떨어지는 시간을 찾았다면, 마지막 작업을 누가 처리하는지 보기 위해 n-1까지 처리 가능한 작업 갯수와 그 때 하는 마지막 친구 찾기
*/

int solution(int n, vector<int> cores) {
    int answer = 0;
    
    // 일단, 일이 코어 수보다 작으면 바로 코어 수 반환하면 됨
    if (n <= cores.size()) return n;
    
    // 2. Bianry Search 사용
    int start = 0;
    int end = 10000 * 50000;
    int time;
    while (start <= end) {
        int mid = (start + end) / 2;
        
        /// cout << "mid = " << mid << endl;
        
        // mid일 때 몇 개의 작업 수행이 가능한지 확인한다
        long completeWorks = 0;
        for (int i = 0; i < cores.size(); i++) {
            completeWorks += mid / cores[i] + 1;
        }
        
        /// cout << "수행 가능한 작업 개수는 " << completeWorks << "개" << endl;
        
        // 작업이 더 많거나 같다면, 그 아래를 보러 간다
        if (completeWorks >= n) {
            end = mid - 1;
            time = mid;
        }
        
        else {
            start = mid + 1;
        }
    }
    
    /// cout << "필요 시간은 " << time << "초" << endl;
    
    // 끝나면 값이 나왔을 것! 그것보다 1초 전까지 실행되는 작업 갯수를 확인한다.
    long completedWorks = 0;
    for (int i = 0; i < cores.size(); i++) {
        completedWorks += (time - 1) / cores[i] + 1;
    }
    
    // 딱 time초에 작업이 가능한 코어 세기
    int leftWorks = n - completedWorks;
    for (int i = 0; i < cores.size(); i++) {
        if (time % cores[i] == 0) 
            leftWorks--;
        
        if (leftWorks == 0) return (i + 1);
    }
}
