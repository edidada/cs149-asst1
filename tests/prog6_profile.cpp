#include <vector>
#include <cstdio>
#include <cmath>
#include <chrono>
extern void kMeansBaseline(double*,double*,int*,int,int,int,double);
extern void kMeansThread(double*,double*,int*,int,int,int,double);
int main(){
 const int M=100000,N=100,K=10;
 std::vector<double> data(M*N), centers(K*N);
 std::vector<int> assignments(M,-1);
 for(int k=0;k<K;k++) for(int n=0;n<N;n++) centers[k*N+n]=k*10.0;
 for(int m=0;m<M;m++) for(int n=0;n<N;n++)
  data[m*N+n]=(m%K)*10.0+((m*13+n*7)%17-8)*0.01;
 auto reference=centers;
 std::vector<int> expected(M,-1);
 auto start=std::chrono::steady_clock::now();
 kMeansBaseline(data.data(),reference.data(),expected.data(),M,N,K,1e-8);
 auto middle=std::chrono::steady_clock::now();
 kMeansThread(data.data(),centers.data(),assignments.data(),M,N,K,1e-8);
 auto finish=std::chrono::steady_clock::now();
 if(expected!=assignments || reference!=centers)return 3;
 double oldms=std::chrono::duration<double,std::milli>(middle-start).count();
 double newms=std::chrono::duration<double,std::milli>(finish-middle).count();
 printf("baseline_ms=%.6f optimized_ms=%.6f speedup=%.4f exact_assignments_centroids=true\n",oldms,newms,oldms/newms);
 for(int m=0;m<M;m++) if(assignments[m]!=m%K)return 1;
 for(double x:centers)if(!std::isfinite(x))return 2;
 printf("PASS synthetic fixture M=%d N=%d K=%d; not official data.dat\n",M,N,K);
}
