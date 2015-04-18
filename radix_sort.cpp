#include <iostream>
#include <iterator>
using namespace std;

template<unsigned N> void radix_sort(int* beg, int* end, int* rank){
	unsigned tmp[N+1]={};
	for(int* t=beg; t!=end; ++t)
		++tmp[*t];
	for(unsigned i=1; i<=N; ++i)
		tmp[i] += tmp[i-1];
	for(;beg!=end; ++beg)
		*rank++=--tmp[*beg];
}

int main(){
	int a[]={3,4,5,1,4};
	int rank[5];
	int sorted[5];
	radix_sort<5>(a, a+5, rank);
	for(int i=0;i<5;++i)
		cout<<rank[i]<<' ';
	cout<<endl;
	for(int i=0;i<5;++i)
		sorted[ rank[i]]=a[i];
	for(int i=0;i<5;++i)
		cout<< sorted[i] <<' ';
}
