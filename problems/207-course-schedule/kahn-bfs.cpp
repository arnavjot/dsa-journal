class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> adj[numCourses];
        for(auto pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }

        vector<int> indegree(numCourses, 0);
        for(int i = 0; i < numCourses; i++) {
            for(auto nbr : adj[i]) {
                indegree[nbr]++;
            }
        }

        queue<int> q;
        for(int i = 0; i < numCourses; i++) {
            if(indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo;
        while(!q.empty()) {
            int front = q.front();
            q.pop();
            topo.push_back(front);

            for(auto nbr : adj[front]) {
                indegree[nbr]--;
                if(indegree[nbr] == 0) {
                    q.push(nbr);
                }
            }
        }

        if(topo.size() != numCourses) return false; // cycle detection if all nodes are not in topological sort
        return true;
    }
};
