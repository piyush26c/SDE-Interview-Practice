// 最优解，有学术价植，太长不适考
/// Disjoint set class
class DS {
    vector<int> sets;
public:
    DS(int n) { sets.resize(n, -1); }

    // Find set with path compression
    int find(int u) {
        if (sets[u] < 0) return u;

        int s = find(sets[u]);
        sets[u] = s;
        return s;
    } // end-findSet

    void join(int u, int v) {
        if (u == v) return;
        if (sets[u] < sets[v]) {
            sets[u] += sets[v];
            sets[v] = u;
        }
        else {
            sets[v] += sets[u];
            sets[u] = v;
        } //end-else
    } // end-join

    // Assume that "u" is a valid set head
    int size(int u) { return -sets[u]; }

    int noSets() {
        int count = 0;
        for (int i = 0; i < sets.size(); i++)
            if (sets[i] < 0) count++;
        return count;
    } // end-noSets
}; // end-DS

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<pair<int, int>> myEdges;

        for (int i = 0; i < edges.size(); i++) {
            myEdges.push_back({ edges[i][2], i });
        } // end-for

        // Sort wrt. weight
        std::sort(myEdges.begin(), myEdges.end());

        enum { NONE, MST, PSEUDO };
        vector<int> edgeType(myEdges.size(), NONE);
        vector<vector<pair<int, int>>> mst(n);
        DS ds(n);

        int prevWeight = myEdges[0].first - 1;
        for (auto [currWeight, index]: myEdges) {
            int u = edges[index][0];
            int v = edges[index][1];

            int s1 = ds.find(u);
            int s2 = ds.find(v);

            if (s1 != s2) {
                ds.join(s1, s2);
                edgeType[index] = MST;
                mst[u].push_back({ v, index });
                mst[v].push_back({ u, index });
            }
            else if (currWeight == prevWeight) {
                // (u, v) causes a loop & has the same weight as the prev. edge
                // All edges on the path from "u" to "v" with a 
                // weight == prevWeight are pseudo MST edges
                vector<pair<int, int>> pred(n, { -1, -1 });
#define BLACK 0
#define WHITE 1
                vector<int> color(n, WHITE);

                // BFS from "u" to "v"
                queue<int> Q;
                Q.push(u);
                color[u] = BLACK;
                while (!Q.empty()) {
                    auto node1 = Q.front(); Q.pop();
                    for (auto [node2, edgeIndex] : mst[node1]) {
                        if (color[node2] == WHITE) {
                            color[node2] = BLACK;
                            pred[node2] = { node1, edgeIndex };
                            Q.push(node2);
                            if (node2 == v) goto out;
                        } // end-if
                    } // end-for
                } // end-while

                out:
                // Walk back from v to u and mark the pseudo edges
                int node1 = v;
                while (node1 != u) {
                    auto [node2, edgeIndex] = pred[node1];
                    if (edges[edgeIndex][2] == prevWeight) {
                        edgeType[edgeIndex] = PSEUDO;
                        edgeType[index] = PSEUDO;                
                    } // end-if
                    node1 = node2;
                } // end-while
            } // end-else

            prevWeight = currWeight;
        } // end-for

        vector<vector<int>> result(2);
        for (int i = 0; i < edges.size(); i++) {
            if (edgeType[i] == MST) result[0].push_back(i);
            else if (edgeType[i] == PSEUDO) result[1].push_back(i);
        } // end-for

        return result;
    } // end-findCriticalAndPseudoCriticalEdges
};
