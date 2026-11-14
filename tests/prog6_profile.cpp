#include <vector>
#include <cstdio>
#include <cmath>
extern void kMeansThread(double*,double*,int*,int,int,int,double);
int main(){
 const int M=100000,N=100,K=10;
 std::vector<double> data(M*N), centers(K*N);
 std::vector<int> assignments(M,-1);
 for(int k=0;k<K;k++) for(int n=0;n<N;n++) centers[k*N+n]=k*10.0;
 for(int m=0;m<M;m++) for(int n=0;n<N;n++)
  data[m*N+n]=(m%K)*10.0+((m*13+n*7)%17-8)*0.01;
 kMeansThread(data.data(),centers.data(),assignments.data(),M,N,K,1e-8);
 for(int m=0;m<M;m++) if(assignments[m]!=m%K)return 1;
 for(double x:centers)if(!std::isfinite(x))return 2;
 printf("PASS synthetic fixture M=%d N=%d K=%d; not official data.dat\n",M,N,K);
}
