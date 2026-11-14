#include <vector>
#include <cstdio>
#include <cstdlib>
extern void mandelbrotSerial(float,float,float,float,int,int,int,int,int,int*);
extern void mandelbrotThread(int,float,float,float,float,int,int,int,int*);
int main(){
  int cases=0;
  for(const char *policy : {"block","cyclic"}){
    setenv("MANDELBROT_POLICY",policy,1);
    for(int w : {1,3,17,31}) for(int h : {1,2,5,19})
      for(int n : {1,2,3,8,16,32}){
        std::vector<int> ref(w*h), got(w*h+2,-123456);
        mandelbrotSerial(-2,-1,1,1,w,h,0,h,93,ref.data());
        mandelbrotThread(n,-2,-1,1,1,w,h,93,got.data()+1);
        if(got.front()!=-123456 || got.back()!=-123456) return 1;
        for(int i=0;i<w*h;i++) if(ref[i]!=got[i+1]) return 2;
        cases++;
      }
  }
  printf("PASS: %d scheduling cases, remainder rows and output guards\n",cases);
}
