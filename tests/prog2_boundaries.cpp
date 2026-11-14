#include <vector>
#include <cmath>
#include <cstdio>
#include "CS149intrin.h"
extern void clampedExpVector(float*,int*,float*,int);
extern float arraySumVector(float*,int);
int main(){
  int cases=0;
  for(int n=0;n<=3*VECTOR_WIDTH+1;n++){
    std::vector<float> x(n), out(n+2,-777.f);
    std::vector<int> e(n);
    for(int round=0;round<12;round++){
      for(int i=0;i<n;i++){
        x[i]=float((i+round)%9-4)*0.75f;
        e[i]=(i*7+round)%12;
      }
      clampedExpVector(x.data(),e.data(),out.data()+1,n);
      if(out.front()!=-777.f || out.back()!=-777.f) return 1;
      for(int i=0;i<n;i++){
        float want=1.f;
        if(e[i]){want=x[i];for(int j=1;j<e[i];j++) want*=x[i];}
        if(want>9.999999f) want=9.999999f;
        if(out[i+1]!=want) return 2;
      }
      cases++;
    }
  }
  for(int blocks=0;blocks<=7;blocks++){
    std::vector<float> x(blocks*VECTOR_WIDTH);
    float want=0;
    for(unsigned i=0;i<x.size();i++){x[i]=float(int(i%11)-5)/8.f;want+=x[i];}
    if(arraySumVector(x.data(),x.size())!=want) return 3;
  }
  printf("PASS: width=%d, %d exponent cases and 8 exact binary sum cases\n",VECTOR_WIDTH,cases);
}
