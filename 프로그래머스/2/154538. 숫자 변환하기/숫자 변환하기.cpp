#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

/*
    징검다리 건너기 같은 느낌으로!
*/

int MAX = 1000001;

int solution(int x, int y, int n) {
    int answer = 0;
    
    vector<int> move_count(y + 1, MAX);
    move_count[x] = 0;
    
    for (int i = x; i <= y - n; i++) {
        // 매 칸에서 2배, 3배, n더하기를 모두 실행해본다.
        // 단 갈 수 있는 칸이어야 함
        if (move_count[i] != MAX) {
            if (i * 2 <= y) 
                move_count[i * 2] = min(move_count[i * 2], move_count[i] + 1);
            
            if (i * 3 <= y) 
                move_count[i * 3] = min(move_count[i * 3], move_count[i] + 1);
            
            if (i + n <= y) 
                move_count[i + n] = min(move_count[i + n], move_count[i] + 1);
            
            /*
            cout << "기준 : " << i << " = " << move_count[i] << endl;
            cout << i * 2 << " = " << move_count[i * 2] << endl;
            cout << i * 3 << " = " << move_count[i * 3] << endl;
            cout << i + n << " = " << move_count[i + n] << endl << endl;
            */
        }
    }
    
    // 다 봤다면, 결과를 출력한다.
    if (move_count[y] == MAX) {
        return -1;
    }
    
    else {
        return move_count[y];
    }
}