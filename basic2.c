#include<stdio.h>
#include<string.h>//文字列をいじる関数を使うのに必要
#include<stdlib.h>//rand乱数関数を使うのに必要
#include<math.h>//pow（累乗)を使うのに必要

#define DELTA 1.0e-9//数値微分に使うデルタ
typedef struct {//複素数を表現する構造体の定義
    double real;
    double imag;
} complex;
int di;//di:方程式の次数
double coe[100];//coe[]:係数を入れる配列
double Fx(double);//入力の値(実数）に対する関数値を返す
complex conv_c(double);//実数を複素数で扱うための関数
complex add_c(complex,complex);//複素数の和を返す
complex mul_c(complex,complex);//複素数の積を返す
complex div_c(complex,complex);//複素数の商を返す
complex pow_c(complex,int);//複素数の累乗を返す
double val_c(complex);//複素数の大きさを返す
void show_c(complex);//複素数を表示する
complex Fx_c(complex);//入力の値(複素数)に対する関数値を返す
complex dif_c(complex (*Fx_c)(complex),complex);//関数の微分を返す
//void newtonMethod(double a,double e,double *result,double *num);//ニュートンラフソン（実数)
complex newtonMethod_c(complex a,double e);//  ニュートンラフソン(複素数)
void get_sign(int a){//値の符号を得る関数（数式表示用）
    if(a>=0){printf("+");}
}
complex conv_c(double a){
    complex b;
    b.real=a;
    b.imag=0;
    return (b);
}
complex add_c(complex a,complex b){
    complex c;
    c.real=a.real+b.real;
    c.imag=a.imag+b.imag;
    return(c);
}
complex mul_c(complex a,complex b){
    complex c;
    c.real=a.real*b.real-a.imag*b.imag;
    c.imag=a.real*b.imag+a.imag*b.real;
    return(c);
}
complex div_c(complex a,complex b){
    complex c,d;
    c.real=b.real;
    c.imag=-b.imag;
    d.real =mul_c(a,c).real/(b.real*b.real+b.imag*b.imag);
    d.imag =mul_c(a,c).imag/(b.real*b.real+b.imag*b.imag);
    return (d);
}
complex pow_c(complex a,int n){
    complex b;
    b.real=1;
    b.imag=0;
    if(n>0){
        for(int i=0;i<n;i++){
            b=mul_c(b,a);
        }
    }else if(n<0){
        for(int i=0;i<n;i++){
            b=div_c(b,a);
        }
    }
    return (b);
}
void show_c(complex a){
    printf("%lf+i%lf",a.real,a.imag);
}
double val_c(complex a){
    return(sqrt(pow(a.real,2)+pow(a.imag,2)));
}
double Fx(double a){
    double sum=0;
    for(int i=0;i<=di;i++){
        sum+=coe[i]*pow(a,(double)(di-i));
        //printf("%lf\n",sum);
    }
    return sum;
}
complex Fx_c(complex a){
    complex sum;
    sum.real=0;
    sum.imag=0;
    for(int i=0;i<=di;i++){
        sum=add_c(sum,mul_c(conv_c(coe[i]),pow_c(a,di-i)));
        //show_c(sum);//確認
    }
    return (sum);
}
complex dif_c(complex (*Fx_c)(complex),complex xd){
    complex DIF,deno;
    deno = add_c(Fx_c(add_c(xd,conv_c(DELTA))),mul_c(conv_c(-1),Fx_c(add_c(xd,conv_c(-DELTA)))));
    DIF = div_c(deno,conv_c(2*DELTA));
    return DIF;
}
complex newtonMethod_c(complex a,double e){
    int i=0;
    complex aa;
    while(i<1000){
        i++;
        aa=add_c(a,mul_c(conv_c(-1),div_c(Fx_c(a),dif_c(Fx_c,a))));
        if(val_c(Fx_c(aa))<e){
            break;
        }
        a=aa;
    }
    return a;
}

int main(){
    printf("対象とする方程式は何次式ですか。整数で入力してください(100以下）\n次数:");
    scanf("%d",&di);
    printf("各次数の係数を入力してください。（整数、負数および小数は可、分数は不可）\n");
    for(int i=0;i<=di;i++){
        printf("x^%d:",di-i);
        scanf("%lf",&coe[i]);
        //printf("%lf\n",coe[i]);//確認
    }
    printf("数式は     \n");
    for(int j=0;j<=di;j++){
        get_sign(coe[j]);
        printf("%fx^%d",coe[j],di-j);
    };//(数式表示用)
    printf("\n");
    //printf("%lf",Fx(2.0));
    printf("答えは、");
    show_c(newtonMethod_c(conv_c(2),DELTA));
    return 0;
}



