#include <vector>
#include <cstdio>
#include "mandelbrot_ispc.h"
extern void mandelbrotSerial(float,float,float,float,int,int,int,int,int,int*);
int main(){
 int cases=0;
 for(int w : {1,3,7,9,31}) for(int h : {1,2,3,7,19}){
  std::vector<int> ref(w*h),simd(w*h+2,-7),tasks(w*h+2,-7);
  mandelbrotSerial(-2,-1,1,1,w,h,0,h,137,ref.data());
  ispc::mandelbrot_ispc(-2,-1,1,1,w,h,137,simd.data()+1);
  ispc::mandelbrot_ispc_withtasks(-2,-1,1,1,w,h,137,tasks.data()+1);
  if(simd.front()!=-7 || simd.back()!=-7 || tasks.front()!=-7 || tasks.back()!=-7) return 1;
  for(int i=0;i<w*h;i++) if(ref[i]!=simd[i+1] || ref[i]!=tasks[i+1]) return 2;
  cases++;
 }
 printf("PASS: %d odd-size SIMD/task images and output guards\n",cases);
}
