#include <vector>
#include <cmath>
#include <cstdio>
#include "sqrt_ispc.h"
extern void sqrtSerial(int,float,float*,float*);
int main(){
 int cases=0;
 for(int n : {0,1,7,8,9,63,64,65,127,257}){
  std::vector<float> x(n),serial(n+2,-7),simd(n+2,-7),tasks(n+2,-7);
  for(int i=0;i<n;i++) x[i]=i%3==0 ? 2.999f : (i%3==1 ? .001f : 1.f);
  sqrtSerial(n,1,x.data(),serial.data()+1);
  ispc::sqrt_ispc(n,1,x.data(),simd.data()+1);
  ispc::sqrt_ispc_withtasks(n,1,x.data(),tasks.data()+1);
  for(auto *v : {&serial,&simd,&tasks}){
   if(v->front()!=-7 || v->back()!=-7) return 1;
   for(int i=0;i<n;i++) if(!std::isfinite((*v)[i+1]) || std::fabs((*v)[i+1]-std::sqrt(x[i]))>1e-4) return 2;
  }
  cases++;
 }
 printf("PASS: %d sqrt sizes, three implementations and output guards\n",cases);
}
