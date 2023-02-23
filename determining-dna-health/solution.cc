#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <string>

typedef uint64_t u64;

using namespace std;

struct Node {
	int parent = -1;
	char parent_char = 0;
	int link = -1;
	int exit_link = -1;
	map<char, int> next;
	vector<int> output;
};

// build aho corasick trie
vector<Node> build_aho_corasick(vector<string> &patterns)
{
	// build trie
	vector<Node> trie(1);

	// add all patterns to trie
	for (int i = 0; (size_t)i < patterns.size(); ++i) {
		int node = 0;
		// iterate over all characters in pattern
		for (char c : patterns[i]) {
			// if node does not have a child for this character,
			if (!trie[node].next.count(c)) {
				// add a new node
				trie[node].next[c] = trie.size();
				trie.emplace_back();
				trie.back().parent = node;
				trie.back().parent_char = c;
			}
			// move to next node
			node = trie[node].next[c];
		}
		// add pattern to output of last node
		trie[node].output.push_back(i);
	}

	// build links
	queue<int> q;
	q.push(0);

	// iterate over all nodes in trie
	while (!q.empty()) {
		// get current node
		int node = q.front();
		q.pop();

		// build link
		for (auto &kv : trie[node].next) {
			// get child node
			int child = kv.second;
			// get character
			char c = kv.first;

			// get parent link
			int parent_link = trie[node].link;
			while (parent_link != -1 &&
			       !trie[parent_link].next.count(c)) {
				parent_link = trie[parent_link].link;
			}

			// if we are at root, then we have no match
			if (parent_link != -1) {
				trie[child].link = trie[parent_link].next[c];
			} else {
				trie[child].link = 0;
			}

			// build exit link
			// if this node has output, then we can exit here
			if (trie[trie[child].link].output.size()) {
				trie[child].exit_link = trie[child].link;
			} else {
				trie[child].exit_link =
					trie[trie[child].link].exit_link;
			}

			// add child to queue
			q.push(child);
		}
	}

	return trie;
}

u64 get_health(vector<Node> &trie, string strand, vector<u64> &health,
	       vector<string> &patterns, int first, int last)
{
	// get total health of strand
	int node = 0;
	u64 total_health = 0;
	// iterate over all characters in strand
	for (int i = 0; (size_t)i < strand.size(); ++i) {
		// get current character
		char c = strand[i];

		// find next node
		while (node != -1 && !trie[node].next.count(c)) {
			node = trie[node].link;
		}

		// if we are at root, then we have no match
		if (node != -1) {
			node = trie[node].next[c];
		} else {
			node = 0;
		}

		// get health of all patterns that end at this node
		int exit_node = node;
		while (exit_node != -1) {
			// iterate over all patterns that end at this node
			for (int pattern : trie[exit_node].output) {
				// check if pattern is in range
				if (pattern >= first && pattern <= last)
					total_health += health[pattern];
			}
			// get next exit node
			exit_node = trie[exit_node].exit_link;
		}
	}

	return total_health;
}

int main()
{
	int n;

	cin >> n;

	vector<string> genes(n);
	vector<u64> health(n);
	for (string &gene : genes) {
		cin >> gene;
	}
	for (u64 &h : health) {
		cin >> h;
	}

	int s;
	cin >> s;

	u64 min_health = 0xffffffffffffffff;
	u64 max_health = 0;

	vector<Node> tree = build_aho_corasick(genes);

	while (s--) {
		int first, last;
		cin >> first >> last;

		string strand;
		cin >> strand;

		u64 cur_health =
			get_health(tree, strand, health, genes, first, last);
		if (cur_health < min_health) {
			min_health = cur_health;
		}
		if (cur_health > max_health) {
			max_health = cur_health;
		}
	}

	cout << min_health << " " << max_health << endl;

	return 0;
}
