class Solution {
public:
    bool checkCycle(int node, vector<int> adj[], vector<bool>& visited, vector<bool>& dfstrack) {
        visited[node] = true;
        dfstrack[node] = true;                 // node is on the current DFS path

        for(auto nbr : adj[node]) {
            if(!visited[nbr]) {
                if(checkCycle(nbr, adj, visited, dfstrack)) {
                    return true;
                }
            } else if(dfstrack[nbr]) {         // back to a node still on the path → cycle
                return true;
            }
        }

        dfstrack[node] = false;                // leaving the path
        return false;
    }

    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        for(auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }
        vector<bool> visited(numCourses, false), dfstrack(numCourses, false);
        for(int i = 0; i < numCourses; i++) {
            if(!visited[i] && checkCycle(i, adj, visited, dfstrack)) {
                return false;
            }
        }
        return true;
    }
};
