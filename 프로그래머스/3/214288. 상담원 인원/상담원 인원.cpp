#include <cmath>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

/*
    채용설명회 한다. 1:1 상담 가능
    멘토 n명 있고, 1 ~ k번까지 상담 유형이 있다.
    멘토는 자신이 담당하는 유형의 상담만 가능. 멘토는 한명만, 참가자가 요청한 시간만큼 걸림
    
    1. 상담 원하는 참가자가 상담 요청하면, 멘토 중 한 명이 상담 들어감
    2. 모두 하는 중이라면, 큐에 들어가서 기다림
    3. 모든 멘토는 대기자가 있으면 쉬지 않는다.
    
    
    풀이
    1. 상담 i에 j명의 상담원이 있을 때의 대기시간을 waiting[i][j]로 설정한다
    2. 이를 기반으로, n번째 상담까지 m명을 배치했을 때의 대기시간의 최소값을 dp[n][m]로 저장
    3. dp[i][j+1] = min(dp[i-1][j+1], dp[i][j-1] + cost[i][j-1]) 이 된다.
*/

int solution(int k, int n, vector<vector<int>> reqs) {
    int answer = 0;
    
    int maxCounselorCount = n - k + 1;
    
    vector<vector<vector<int>>> counsels(k + 1);
    
    // 상담 유형별로 분리
    for (auto req : reqs) {
        int time = req[0];
        int duration = req[1];
        int type = req[2];
        
        counsels[type].push_back({time, duration});
    }
    
    // i번째 상담에 j명의 상담원을 배치했을 때의 대기시간
    // 최대 배치 명수는 n - k + 1
    vector<vector<int>> costs(k + 1, vector<int>(maxCounselorCount + 1));
    
    // costs[0]는 있으면 안되는 상황이므로, 큰 값으로 지정
    for (int i = 1; i <= k; i++) costs[i][0] = 1e8;
    
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= maxCounselorCount; j++) {
            // 상담원 종료 시간 저장용 큐
            priority_queue<int, vector<int>, greater<>> que;
            
            // 정해진 상담원 수만큼 상담원 넣기
            for (int k = 0; k < j; k++) que.push(0);
            
            int waitingTime(0);
            // 해당 상담 유형 값 가져오기
            for (auto counsel : counsels[i]) {
                int time = counsel[0];
                int duration = counsel[1];
                
                // 바로 상담 가능한 상담원이 있으면, 상담 시작
                if (que.top() <= time) {
                    que.pop();
                    que.push(time + duration);
                }
                
                // 상담이 불가능하면, 끝나고 바로 진행하도록 하기
                else {
                    int endTime = que.top();
                    que.pop();
                    que.push(endTime + duration);
                    
                    waitingTime += endTime - time; // 기다린 시간 계산
                }
            }
            
            // 계산 종료되면, 저장
            costs[i][j] = waitingTime;
        }
    }
    /*
    // 확인용 출력
    for (int i = 1; i < k + 1; i++) {
        for (int j = 1; j <= maxCounselorCount; j++) cout << "costs[" << i << "][" << j << "] = " << costs[i][j] << endl;
    }
    */
    
    vector<vector<int>> dp(k + 1, vector<int>(n + 1, 1e9));
    // 초기값 할당
    for (int i = 0; i <= maxCounselorCount; i++) {
        dp[1][i] = costs[1][i];
    }
    
    // dp 계산
    // type은 상담의 유형
    for (int type = 1; type <= k; type++) {
        // usedCount는 총 사용된 상담원 수
        for (int usedCount = 1; usedCount <= n; usedCount++) {
            // m은 이번 상담에 사용될 상담원 수. 1명부터 가능하며, 총 사용된 상담원 수보다 클 수 없다.
            for (int m = 1; m <= maxCounselorCount && m <= usedCount; m++) {
                // 예를 들어 2번째 상담에 2명이 들어갔을 경우, dp[2][i] = dp[1][i - 2] + cost[2][2] 이다.
                // 모든 상담에서는 상담원을 1 ~ (최대 상담원 수 - 나머지 상담 개수)만큼 쓸 수 있다. 
                // 이 때, n 명을 여기서 사용했다면 dp[i][j] = dp[i - 1][j - n] + cost[i][n]이 된다.
                // 이를 다시 풀어서 설명하면, n명의 상담원을 i번째 상담에서 사용했다면 그 비용은 이전에 j - n명을 사용한 상담 비용 + 현재 상담 비용이다.
                dp[type][usedCount] = min(dp[type][usedCount], dp[type - 1][usedCount - m] + costs[type][m]);
            }
        }
    }
    
    /*
    // dp 확인용 출력
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= k; j++) cout << "dp[" << j << "][" << i << "] = " << dp[j][i] << " ";
        cout << endl;
    }
    */
    
    return dp[k][n];
}







/*
    
    // 유형별로 상담원 인원수 저장
    int counselerSum = k;
    vector<int> counselerCount(k, 1);
    vector<priority_queue<int, vector<int>, greater<>>> counselerQueue(k);
    
    while (counselerSum <= n) {
        // 대기시간 초기화
        answer = 0;
        vector<int> waitingTime(k, 0);
        
        // 상담원 배치
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < counselerCount[i]; j++) {
                counselerQueue[i].push(0);
            }
        }
        
        // 상담 보면서 처리해보기
        for (auto req : reqs) {
            int time = req[0];
            int duration = req[1];
            int type = req[2] - 1;
            
            // 내 타입의 상담원이 남아있으면, 바로 상담 들어가기
            if (counselerQueue[type].top() <= time) {
                counselerQueue[type].pop();
                counselerQueue[type].push(time + duration);
            }
            
            // 지금 상담원이 부족하면, 대기시간 기록해두고 그 뒤로 들어가기
            else if (counselerQueue[type].top() > time) {
                int endTime = counselerQueue[type].top();
                waitingTime[type] += endTime - time;
                answer += endTime - time;
                counselerQueue[type].pop();
                counselerQueue[type].push(endTime + duration);
            }
        }
        
        int maxWaitingTime = 0;
        int maxWaitingIdx = -1;
        
        // 제일 오래 기다린 상담 유형 찾기
        for (int i = 0; i < k; i++) {
            if (maxWaitingTime < waitingTime[i]) {
                maxWaitingTime = waitingTime[i];
                maxWaitingIdx = i;
            }
        }
        
        // 제일 오래 걸린 곳에 상담원 추가
        counselerCount[maxWaitingIdx]++;
        counselerSum++;
        
        // 아무도 기다리지 않았으면, 대기시간 0 반환
        if (maxWaitingIdx == -1) return 0;
        
        // 상담원 상태 초기화
        for (int i = 0; i < k; i++) {
            while (!counselerQueue[i].empty()) counselerQueue[i].pop();
        }
    }
    */