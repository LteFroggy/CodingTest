#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

/*
    두 개씩 모아 앨범 출시
    노래가 많이 재생된 장르 장르, 그 중에서도 많이 재생된 것
    재생 횟수가 같다면, 고유 번호가 낮은 것이 먼저
*/

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    
    unordered_map<string, vector<pair<int, int>>> map_song;
    unordered_map<string, long> map_sum;
    int n = genres.size();
    
    for (int i = 0; i < n; i++) {
        // 아직 없는 장르라면 넣기 
        if (map_sum.find(genres[i]) == map_sum.end()) {
            map_song.insert({genres[i], vector<pair<int, int>>()});
            
            // 합계에도 정산하기
            map_sum.insert({genres[i], 0});
        }
        
        // 이후에 값 합산해주기
        map_song[genres[i]].push_back({i, plays[i]});
        map_sum[genres[i]] += plays[i];
    }
    
    // 다 넣으면 장르별로 정렬해두기
    for (auto it = map_song.begin(); it != map_song.end(); it++) {
        cout << it->first << endl;
        sort(it->second.begin(), it->second.end(), [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
            // 만약 재생수가 같으면, 고유번호가 낮은 순으로 가야 함
            if (a.second == b.second) return a.first < b.first;
            else return a.second > b.second;
        });
        
        /*
        for (auto v : it->second) cout << v.first << " : " << v.second << endl;
        cout << endl;
        */
    }
    
    // 이제, 장르별 합산을 벡터에 넣고 정렬해서 어떤 장르가 앞으로 올지 정한다
    vector<pair<string, long>> genre_sum;
    for (auto it = map_sum.begin(); it != map_sum.end(); it++) {
        genre_sum.push_back({it->first, it->second});
    }
    
    sort(genre_sum.begin(), genre_sum.end(), [](const pair<string, long> &a, pair<string, long> &b) -> bool {
        return a.second > b.second;
    });
    
    // 제일 많이 재생된 장르부터 두개씩 넣는다
    for (auto v : genre_sum) {
        string genre = v.first;
        
        // 저장이 <곡명, 재생수> 순이므로 first를 넣어줘야 함.
        answer.push_back(map_song[genre][0].first);
        // 곡이 하나라면 하나만 넣어줘야 한다
        if (map_song[genre].size() == 1) continue;
        // 아니라면 하나 더 넣기
        else answer.push_back(map_song[genre][1].first);
    }
    
    return answer;
}