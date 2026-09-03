using System;
using System.Collections.Generic;

public class Solution {
    public int solution(string[,] clothes) {
        int answer = 0;
        
        Dictionary<string, List<string>> dict = new Dictionary<string, List<string>>();
        
        for (int i = 0; i < clothes.GetLength(0); i++) {
            if (!dict.ContainsKey(clothes[i, 1])) {
                dict[clothes[i, 1]] = new List<string>();
            }
            
            dict[clothes[i, 1]].Add(clothes[i, 0]);
        }
        
        answer = 1;
        
        foreach (var clothList in dict.Values) {    
            answer *= clothList.Count + 1;
        }

        return --answer;
    }
}