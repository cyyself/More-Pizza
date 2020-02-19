#include <bits/stdc++.h>
#include <thread>
using namespace std;
const int maxm = 1e9+1;
const int maxn = 1e5+1;
const int max_thread = 16;
int *last,*here;
int a[maxn];
void do_dp(int i,int l,int r) {
	for (int j=l;j>=r;j--) if (!~last[j] && ~last[j-a[i]]) {
		last[j] = j-a[i];
		here[j] = i;
	}
}
int main() {
	last = new int[maxm];
	here = new int[maxm];
	int m,n;
	scanf("%d%d",&m,&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	for (int i=1;i<=m;i++) last[i] = -1;
	last[0] = 0;
	for (int i=0;i<n;i++) {
		
		thread *t[max_thread];
		int len = m - a[i] + 1;
		int bs = len / max_thread;
		int last = len % max_thread;
		t[0] = new thread(do_dp,i,m,m-(bs+last)+1);
		int st = m - (bs + last);
		for (int j=1;j<max_thread;j++) {
			t[j] = new thread(do_dp,i,st,st-bs+1);
			st -= bs;
		}
		for (int j=0;j<max_thread;j++) {
			t[j]->join();
			delete t[j];
		}
		
		/*
		for (int j=m;j>=a[i];j--) if (!~last[j] && ~last[j-a[i]]) {
			last[j] = j-a[i];
			here[j] = i;
		}
		*/
		cerr << i << endl;
	}
	int cur = 0;
	for (int i=m;i>=0;i--) if (~last[i]) {
		cur = i;
		break;
	}
	cerr << cur << endl;
	vector <int> ans;
	while (cur) {
		ans.push_back(here[cur]);
		cur = last[cur];
	}
	printf("%d\n",ans.size());
	reverse(ans.begin(),ans.end());
	for (int i=0;i<ans.size();i++) printf("%d%c",ans[i],(i==ans.size()-1)?'\n':' ');
	return 0;
}