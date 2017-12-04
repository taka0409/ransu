#include <stdio.h>
#include <time.h>
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL
#define UPPER_MASK 0x80000000UL
#define LOWER_MASK 0x7fffffffUL
#define D 60
#define X 10
#define Y 30
static unsigned long mt[N];
static int mti=N+1;
void init_genrand(unsigned long s){
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++){
        mt[mti] = 
      (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        mt[mti] &= 0xffffffffUL;
    }
}
unsigned long genrand_int32(void){
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};

    if (mti >= N) {
        int kk;

        if (mti == N+1)
            init_genrand(5489UL);

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

        mti = 0;
    }
  
    y = mt[mti++];

    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}
double genrand_real2(void){
    return genrand_int32()*(1.0/4294967296.0); 
}
int main(){
  int n,i,j,k,count,num[D],param,win;
  unsigned long int seed;
  init_genrand(seed=(unsigned long)time(NULL));
  for(i=0;i<10;i++){
    win=0;
    for(j=0;j<100000;j++){
      for(n=7;n>3;n--){
        for(k=0;k<D;k++)
          num[k]=0;
        count=0;
        for(k=0;k<n;k++){
          do{
            param=(int)(genrand_real2()*D);
          }while(num[param]!=0);
          if(param<20)
            count+=1;
          else if(param<40)
            count+=10;
          else
            count+=100;
          num[param]=1;
        }
        if(count%10>0 && (count/10)%10>0 && count/100>1){
          win++;
          break;
        }
      }
    }
    printf("%.1lf\n",(double)win/j*100);
  }
}