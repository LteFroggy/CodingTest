using System;

/*
    피로도 시스템 있음.
    
    피로도 사용해서 던전 탐험 가능.
    
    최소필요피로도, 소모피로도 있다.
    그냥 완탐으로 다가보자. 최대 8개임
*/

public class Solution {
    public int solution(int k, int[,] dungeons) {
        return DungeonSeeker.FindMostEfficientWay(k, in dungeons);
    }
}

public static class DungeonSeeker {
    public static int FindMostEfficientWay(int k, in int[,] dungeons) {
        bool[] visited = new bool[dungeons.GetLength(0)];
        int maxDungeonCount = 0;
        
        for (int i = 0; i < dungeons.GetLength(0); i++) {
            maxDungeonCount = Math.Max(TryDungeon(i, k, in dungeons, visited, 0), maxDungeonCount);
        }
        
        return maxDungeonCount;
    }
    
    public static int TryDungeon(int dungeonNum, int k, in int[,] dungeons, bool[] visited, int dungeonCount) {
        /// 지금 dungeonNum번에 입장한 것이니 입장 처리
        // 만약 던전 최소필요피로도보다 적은 피로도값이라면, 여기 입장 불가능, 돌아간다
        if (dungeons[dungeonNum, 0] > k) { return dungeonCount; }
        // 가능하면 입장 처리
        visited[dungeonNum] = true;
        k -= dungeons[dungeonNum, 1];
        dungeonCount++;
        
        int maxDungeonCount = dungeonCount;

        // 다음 던전 상태 확인
        for (int i = 0; i < dungeons.GetLength(0); i++) {
            // 이미 방문한 던전이면 가지 않음
            if (visited[i]) continue; 
            // 아니면 일단 보내봄
            maxDungeonCount = Math.Max(TryDungeon(i, k, in dungeons, visited, dungeonCount), maxDungeonCount);
        }
        
        // 상태 되돌리기
        visited[dungeonNum] = false;
        return maxDungeonCount;
    }
}