#include<stdio.h>
#include<string.h>//文字列をいじる関数を使うのに必要
#include<stdlib.h>//rand乱数関数を使うのに必要
#include<math.h>//pow（累乗)を使うのに必要

#define DELTA 1.0e-8
int di;float coe[100];
double FUNCTION(double);
void get_sign(int a){
    if(a>=0){printf("+");}
}
int main(){
    printf("対象とする方程式は何次式ですか。整数で入力してください(100以下）\n次数:");
    scanf("%d",&di);
    printf("各次数の係数を入力してください。（整数、負数および小数は可、分数は不可）\n");
    for(int i=0;i<=di;i++){
        printf("x^%d:",di-i);
        
        scanf("%f",&coe[i]);
        //printf();
    }
    for(int j=0;j<=di;j++){
        get_sign(coe[j]);
        printf("%fx^%d",coe[j],di-j);
    };
    printf("\n");
    return 0;
}
double FUNCTION(double a){
    double sum;
    for(int i=0;i<=di;i++){
        sum+=coe[i]*pow(a,(double)(di-i));
    }
    return sum;
}



