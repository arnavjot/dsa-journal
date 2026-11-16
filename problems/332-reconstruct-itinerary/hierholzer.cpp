// Hierholzer's algorithm: DFS that adds an airport to the route only when it has no tickets left - O(E log E) time, O(E) space
class Solution {
public:
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;   // smallest destination on top
    vector<string> route;

    void dfs(const string& airport) {
        auto& dests = graph[airport];
        while (!dests.empty()) {
            string next = dests.top();     // use the smallest unused ticket from here
            dests.pop();
            dfs(next);
        }
        route.push_back(airport);          // stuck: every ticket from here is used
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        for (auto& t : tickets) {
            graph[t[0]].push(t[1]);
        }
        dfs("JFK");
        reverse(route.begin(), route.end());   // airports were added from the end of the trip backwards
        return route;
    }
};
