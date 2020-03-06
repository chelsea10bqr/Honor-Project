#include <stdint.h>
#include <stdio.h>





void main()
{
  int i,j=-1,k,m,a=5-1,p;
  for(i=(5-1)*5;i<=(5-1)*5+(5-1);i++)
  {
    j=j+1;
    for(k=0;k<=j;k++)
    {
      printf("%d,",i-(5+1)*k);
    }
  }
  for(m=(5-1)*5-1;m>=5-1;m=m-5)
  {
    a=a-1;
    for(p=0;p<=a;p++)
    {
      printf("%d,",m-(5+1)*p );
    }
  }
}
