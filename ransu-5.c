  int  n=7,i,count,num[D],param,win=0;
  unsigned long int seed;
  init_genrand(seed=(unsigned long)time(NULL));

  for(i=0;i<1000;i++){
    for(n=7;n>3;n--){
      for(j=0;j<D;j++)
        num[j]=0;
      count=0;
      for(j=0;j<n;j++){
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