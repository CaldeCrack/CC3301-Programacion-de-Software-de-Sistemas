#include <string.h>

int strCmp(char *s1, char *s2) {
    char c1=1, c2=0;
    char conv[] = {'n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f','g','h','i','j','k','l','m'};
    while(c1){
      c1=*s1; c2=*s2;
      if(97<=c1 && c1<=122) c1=conv[c1-97];
      if(97<=c2 && c2<=122) c2=conv[c2-97];
      if(c1-c2) break;
      s1++; s2++;
    }
    return c1-c2;
}

void sort(char **a, int n) {
  char **ult= &a[n-1];
  char **p= a;
  while (p<ult) {
    int t1= strCmp(p[0], p[1]);
    if (t1 <= 0)
      p++;
    else {
      char *tmp= p[0];
      p[0]= p[1];
      p[1]= tmp;
      p= a;
    }
  }
}