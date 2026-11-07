class Solution {
  public:
    vector<int> findOrder(int V, vector<vector<int>>& prerequisites) {
        vector<int> adj[V];
        for(auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }

        vector<int> indegree(V, 0);
        for(int i = 0; i < V; i++) {
            for(auto nbr : adj[i]) {
                indegree[nbr]++;
            }
        }

        queue<int> q;
        for(int i = 0; i < V; i++) {
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

        if(topo.size() != V) return {}; // cycle detection if all nodes are not in topological sort
        return topo;
    }
};
