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

int main(){
	int len;
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

	for(int i=0;i<len;++i)
		cout<<sa[i]<<endl;

	for(int i=0;i<len; ++i)
		cout<<(str+sa[i])<<endl;
	

	return 0;
}


