//gcc -Ofast
#include <stdio.h>
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL
#define D 60
#define X 10
#define Y 30
static unsigned long mt[N]; /* the array for the state vector  */
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */
void init_genrand(unsigned long s){
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++){
        mt[mti] = 
      (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti); 
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}
unsigned long genrand_int32(void){
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            init_genrand(5489UL); /* a default initial seed is used */

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

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}
double genrand_real2(void){
    return genrand_int32()*(1.0/4294967296.0); 
    /* divided by 2^32 */
}
int main(){
  int n,i,j,count,num[D],param,win;
  unsigned long int seed;
  init_genrand(seed=(unsigned long)time(NULL));
  for(i=0;i<100000000;i++){
    for(n=10;n>6;n--){
      for(j=0;j<D;j++)
        num[j]=0;
      count=0;
      for(j=0;j<n;j++){
        do{
          param=(int)(genrand_real2()*D);
        }while(num[param]!=0);
        if(param<X)
          count+=1;
        else if(param<Y)
          count+=10;
        else
          count+=100;
        num[param]=1;
      }
      if(count%10>0 && (count/10)%10>1 && count/100>3){
        win++;
        break;
      }
    }
  }
  printf("%lf\n",(double)win/i*100);
}
