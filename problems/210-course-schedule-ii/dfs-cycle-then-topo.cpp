class Solution {
  public:
    bool checkCycle(int node, vector<int> adj[], unordered_map<int,bool>& visited, unordered_map<int,bool>& dfstrack) {
        visited[node] = true;
        dfstrack[node] = true;

        for(auto nbr : adj[node]) {
            if(!visited[nbr]) {
                if(checkCycle(nbr, adj, visited, dfstrack)) {
                    return true;
                }
            } else if(dfstrack[nbr]) {
                return true;
            }
        }

        dfstrack[node] = false;
        return false;
    }

    void topoSort(int node, vector<int> adj[], unordered_map<int,bool>& visited, stack<int>& st) {
        visited[node] = true;

        for(auto nbr : adj[node]) {
            if(!visited[nbr]) {
                topoSort(nbr, adj, visited, st);
            }
        }

        st.push(node);
    }

    vector<int> findOrder(int V, vector<vector<int>>& prerequisites) {
        vector<int> adj[V];
        for(auto& pre : prerequisites) {
            adj[pre[1]].push_back(pre[0]);
        }

        unordered_map<int,bool> visited;
        unordered_map<int,bool> dfstrack;

        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                if(checkCycle(i, adj, visited, dfstrack)) {
                    return {};
                }
            }
        }

        visited.clear();
        stack<int> st;

        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                topoSort(i, adj, visited, st);
            }
        }

        vector<int> ans;
        while(!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};
