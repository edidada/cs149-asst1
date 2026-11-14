#include <vector>
#include <cstdio>
#include <cmath>
extern void kMeansThread(double*,double*,int*,int,int,int,double);
extern void kMeansBaseline(double*,double*,int*,int,int,int,double);
int main(){
 int cases=0;
 for(int m : {1,2,7,17,31}) for(int n : {1,3,9}) for(int k : {1,2,5}){
  std::vector<double> x(m*n),a(k*n),b;
  std::vector<int> p(m,-1),q(m,-1);
  for(int i=0;i<m*n;i++)x[i]=double((i*37+13)%101-50)/8;
  for(int i=0;i<k*n;i++)a[i]=double((i*17)%31-15)/4;
  b=a;
  kMeansBaseline(x.data(),a.data(),p.data(),m,n,k,1e-8);
  kMeansThread(x.data(),b.data(),q.data(),m,n,k,1e-8);
  if(p!=q || a!=b)return 1;
  for(double v:b)if(!std::isfinite(v))return 2;
  cases++;
 }
 // Duplicate centroids and zero-valued points exercise ties/empty clusters.
 std::vector<double>x(21,0),a(12,0),b=a;
 std::vector<int>p(7,-1),q(7,-1);
 kMeansBaseline(x.data(),a.data(),p.data(),7,3,4,1e-8);
 kMeansThread(x.data(),b.data(),q.data(),7,3,4,1e-8);
 if(p!=q || a!=b)return 3;
 for(int v:q)if(v!=0)return 4;
 printf("PASS: %d exact baseline cases plus ties/empty clusters\n",cases);
}
