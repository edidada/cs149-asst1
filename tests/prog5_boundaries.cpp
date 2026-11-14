#include <vector>
#include <cstdio>
#include "saxpy_ispc.h"
extern void saxpySerial(int,float,float*,float*,float*);
int main(){
 int cases=0;
 for(int n : {0,1,7,8,9,63,64,65,127,257}) for(float a : {-2.f,0.f,0.5f,2.f}){
  std::vector<float> x(n),y(n),s(n+2,-77),v(n+2,-77),t(n+2,-77);
  for(int i=0;i<n;i++){x[i]=float(i%17-8)/4;y[i]=float(i%13-6)/8;}
  saxpySerial(n,a,x.data(),y.data(),s.data()+1);
  ispc::saxpy_ispc(n,a,x.data(),y.data(),v.data()+1);
  ispc::saxpy_ispc_withtasks(n,a,x.data(),y.data(),t.data()+1);
  for(auto *out : {&s,&v,&t}){
   if(out->front()!=-77 || out->back()!=-77)return 1;
   for(int i=0;i<n;i++)if((*out)[i+1]!=a*x[i]+y[i])return 2;
  }
  cases++;
 }
 printf("PASS: %d SAXPY cases, three implementations and guards\n",cases);
}
