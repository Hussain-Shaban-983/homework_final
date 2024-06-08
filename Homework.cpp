#include <bits/stdc++.h>
using namespace std;
const int M = 1e3 , N = 1e3;
int n , m;
int a[M] , b[M];
vector<vector<int>> adj ;
vector <int> o_stack;
vector <int> r_stack;
queue<int> q;
set<int> st1 , st2;
vector <int> dfs_tree ;
vector<pair<int , int>> back_word , back_word1;
vector <int> parent;
vector<pair<int , int>> pa; 
bool node_has_back_edge[N];
int comp[N];
bool state[N];
int dfs_counter[N];
int dfs_count = 0;
vector<vector<int>> chains ;
vector<pair<int , int>> tree_edges; 
//حسن حسن - حسن الجمال
void dfs1 (int y ){
    dfs_count++; 
    dfs_counter[y] = dfs_count;
    pa.push_back({dfs_counter[y] , y}); 
    int x = 0;
    if (state[y] == 1) return ;
    state[y] = 1;
    chains[x].push_back(y);
    dfs_tree.push_back(y); 
    for (int i = 0 ; i < adj[y] ; i ++ ){
        if (!state[y]){
            tree_edges.push_back({y , adj[i]}); 
            dfs1(y);
        }
        else {
            back_word.push_back({y , adj[i]}); 
            x++;
        }
    }
}
//حبيب بهلول - بنان حمادة
void dfs (int node){
    dfs_count++;
    dfs_counter[node] = dfs_count;
    if (state[node] == 1) return ;
    state[node] = 1;
    for (int i = 0 ; i < adj[node] ; i++ ){
        if (state[adj[i]] == 0)
            dfs(adj[i]);
        else {
            if (st1.count(adj[i])){
                while(dfs_counter[adj[i]] < dfs_counter[r_stack.back()])
                    r_stack.pop_back();
            }
        }
        if (node == r_stack.back()){
            while (node != adj[i]){
                adj[i] = o_stack.back();
                o_stack.pop_back(); 
                comp[adj[i]] = node ;
            }
        }
    }
    o_stack.push_back(node);
    st1.insert(node);
    r_stack.push_back(node);
    st2.insert(node);
}


//حسين شعبان - كرم فاقي
void gabow(){
    for (int i = 0 ; i < n ; i ++ ){
        if(!state[i])
            dfs(i);
    }

    if (!o_stack.size()){
        cout << "the gragh is strongly conected" << endl;
        return ;
    }
    cout << "the gragh is not strongly connected" << endl;
    return;
}
//أحمد حسين - أسامة خدام
void transfer_to_undirected_gragh(){ /// this to transfer to undirected gragh; 
    adj.clear(); 
    for (int i = 0 ; i < m ; i ++ ){
        adj[a[i]] = b[i];
        adj[b[i]] = a[i];
    }
    dfs_counter.clear();
    dfs_tree.clear();
    dfs_count = 0; 
}
//علي صبيح - أنس القرحالي
void jens_schmidt(){
    transfer_to_undirected_gragh(); 
    for (int i = 0 ; i < n ; i ++ ){
        if (!state[i])
            dfs1(i);
    }
    
    vector<pair<int , int>> v; /// this to riflex the tree edges   
    for (int i = 0 ; i < tree_edges.size() ; i ++ ){
        v.push_back({tree_edges[i].second , tree_edges[i].first});
        adj.clear();
        adj[tree_edges[i].second].push_back(tree_edges[i].first);  
    }
    vector<pair<int , int>> v1; /// this to riflex the back_word edges ; 
    for (int i = 0 ; i < back_word.size() ; i ++ ){
        v1.push_back({back_word[i].second , back_word[i].first});
        node_has_back_edge[v1.first] = 1;  
        adj[back_word[i].second].push_back(back_word[i].first]);
    }
    
    sort(pa.begin() , pa.end()); 
    for (int i = 0 ; i < pa.size() ; i ++ ){
        if(node_has_back_edge[pa[i].second]){
            dfs1(pa[i].second); 
        }
    }
    bool ok = 0 ;
    for (int i = 0 ; i < chains.size() ; i ++ ){
         sort(chains[i].begin(), chains[i].end());

    }
    for (int i = 1 ; i < chains.size() ; i ++ ){
        if (chains[0] == chains[i]) continue;
        ok = 1 ;
    }
    if (!ok) {
         cout << "this gragh is  2_vertex_strongly_biconnected" << endl;
         return ;
    }
    else {
         cout << "this gragh is not 2_vertex_strongly_biconnected" << endl;
         return ;
    }
}
int main()
{

    cin >> n >> m ;
    for (int i = 0 ;i < m ; i ++ ){
        cin >> a[i] >> b[i];
        adj[a[i]].push_back(b[i]) ;
    }

    gabow();
    jens_schmidt();

    return ;

}
