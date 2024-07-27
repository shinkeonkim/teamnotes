void computeFail(Trie *root) {
    queue<Trie *> q;
    root->fail = root;
    q.push(root);
    while (!q.empty()) {
        Trie *here = q.front();
        q.pop();
        for (int i = 0; i < ALPHABETS; i++) {
            Trie *child = here->chil[i];
            if (!child) continue;
            if (here == root) child->fail = root;
            else {
                Trie *t = here->fail;
                while (t != root && t->chil[i] == NULL) t = t->fail;
                if (t->chil[i]) t = t->chil[i];
                child->fail = t;
            }
            child->output = child->fail->output;
            if (child->terminal != -1) child->output.push_back(child->terminal);
            q.push(child);
        }
    }
}
vector<pair<int, int>> ahoCorasick(string &s, Trie *root) {
    vector<pair<int, int>> ret;
    Trie *state = root;
    for (int i = 0; i < s.size(); i++) {
        int idx = chToIdx(s[i]);
        while (state != root && state->chil[idx] == NULL) state = state->fail;
        if (state->chil[idx]) state = state->chil[idx];
        for (int j = 0; j < state->output.size(); j++) ret.push_back({i, state->output[j]});
    }
    return ret;
}