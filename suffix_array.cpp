#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

char str[2003];
int sa[2003];
int r1[2003];
int r2[2003];

int cmp(int a,int b){
	return str[a] < str[b];
}

int cmp2(int* r, int a, int b, int delta){
	return r[a+delta] < r[b+delta];
}

int cmpp(int* r, int a, int b, int delta){
	return r[a] == r[b] && r[a+delta] == r[b+delta];
}

int len;
int getHeight(int x, int from){
	if(!x)
		return 0;
	for(int i=from; i<len; ++i)
		if( str[sa[x]+i] != str[sa[x-1]+i])
			return i;
}

int main(){
	cin>>str;
	for(len=0; str[len]; ++len)
		sa[len]=len;
	std::sort(sa, sa+len, cmp);
	int tmp=0;
	int *rank=r1;
	int *tmp_rank=r2;

	rank[sa[0]]=tmp=0;
	for(int i=1;i<len; ++i){
		if(str[sa[i-1]]!=str[sa[i]])
			++tmp;
		rank[sa[i]] = tmp;
	}

	for(int i=1;i<len; i<<=1){
		int beg=0;
		int end=0;
		while( end < len ){
			++end;
			while(end < len && rank[ sa[end]] == rank[sa[end-1]])
				++end;
			std::sort(sa+beg, sa+end, std::bind(cmp2, rank, std::placeholders::_1, std::placeholders::_2, i));
			beg=end;
		}

		swap(rank, tmp_rank);
		rank[sa[0]]=tmp=0;
		for(int j=1;j<len;++j){
			if(!cmpp(tmp_rank, sa[j-1], sa[j], i))
				++tmp;
			rank[sa[j]] = tmp;
		}
	}

	int h[2003];
	int height[2003];
	h[0]=getHeight(rank[0], 0);
	for(int i=1; i<len; ++i)
		h[i]=getHeight(rank[i], max(0, h[i-1]-1));
	for(int i=0;i<len;++i)
		height[i]=h[sa[i]];

	for(int i=0;i<len; ++i)
		cout<<height[i]<<' '<<(str+sa[i])<<endl;
	

	return 0;
}


