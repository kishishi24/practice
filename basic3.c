#include<stdio.h>
#include<string.h>//文字列をいじる関数を使うのに必要
#include<stdlib.h>//rand乱数関数を使うのに必要
#include<math.h>//pow（累乗)を使うのに必要
#include<time.h>//timeを使う

#define DELTA 1.0e-10//数値微分に使うデルタ
typedef struct {//複素数を表現する構造体の定義
    double real;
    double imag;
} complex;
int di;//方程式の次数
double coe[100];//係数を入れる配列
double sol[100];//解を入れる配列(実数)
complex sol_c[100];//解を入れる配列(複素数)
double Fx(double);//入力の値(実数）に対する関数値を返す
complex conv_c(double);//実数を複素数で扱うための関数
complex add_c(complex,complex);//複素数の和を返す
complex mul_c(complex,complex);//複素数の積を返す
complex div_c(complex,complex);//複素数の商を返す
complex pow_c(complex,int);//複素数の累乗を返す
double val_c(complex);//複素数の大きさを返す
void show_c(complex);//複素数を表示する
complex Fx_c(complex);//入力の値(複素数)に対する関数値を返す
int comp_c(complex,complex);//複素数が一致するかの判定
complex dif_c(complex (*Fx_c)(complex),complex);//関数の微分を返す
//void newtonMethod(double a,double e,double *result,double *num);//ニュートンラフソン（実数)
complex newtonMethod_c(complex a,double e);//  ニュートンラフソン(複素数)
void get_sign(double a){//値の符号を得る関数（数式表示用）
    if(a>=0){printf("+");}
}
complex conv_c(double a){//double型をcomplex型に変換する関数
    complex b;
    b.real=a;
    b.imag=0;
    return (b);
}
complex add_c(complex a,complex b){//complexの和
    complex c;
    c.real=a.real+b.real;
    c.imag=a.imag+b.imag;
    return(c);
}
complex mul_c(complex a,complex b){//complexの積
    complex c;
    c.real=a.real*b.real-a.imag*b.imag;
    c.imag=a.real*b.imag+a.imag*b.real;
    return(c);
}
complex div_c(complex a,complex b){//complexの商
    complex c,d;
    c.real=b.real;
    c.imag=-b.imag;
    d.real =mul_c(a,c).real/(b.real*b.real+b.imag*b.imag);
    d.imag =mul_c(a,c).imag/(b.real*b.real+b.imag*b.imag);
    return (d);
}
complex pow_c(complex a,int n){//complexの累乗
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
void show_c(complex a){//complexの表示
    printf("%.5f",a.real);
    get_sign(a.imag);
    printf("%.5fi\n",a.imag);
}
double val_c(complex a){//complexの大きさ
    return(sqrt(pow(a.real,2)+pow(a.imag,2)));
}
double Fx(double a){//関数の値を返す（実数に限る）
    double sum=0;
    for(int i=0;i<=di;i++){
        sum+=coe[i]*pow(a,(double)(di-i));
        //printf("%lf\n",sum);
    }
    return sum;
}
complex Fx_c(complex a){//関数の値を返す(虚数)
    complex sum;
    sum.real=0;
    sum.imag=0;
    for(int i=0;i<=di;i++){
        sum=add_c(sum,mul_c(conv_c(coe[i]),pow_c(a,di-i)));
        //show_c(sum);//確認
    }
    return (sum);
}
complex dif_c(complex (*Fx_c)(complex),complex xd){//関数の微分
    complex DIF,deno;
    deno = add_c(Fx_c(add_c(xd,conv_c(DELTA))),mul_c(conv_c(-1),Fx_c(add_c(xd,conv_c(-DELTA)))));
    DIF = div_c(deno,conv_c(2*DELTA));
    return DIF;
}
int comp_c(complex a,complex b){//complexの比較（大きさが等しいなら1を返す）（”等しい”の基準は緩めにした）
    if(fabs(a.real-b.real)<0.01&&fabs(a.imag-b.imag)<0.01){
        return 1;
    }else{
        return 0;
    }
}
complex newtonMethod_c(complex a,double e){//ニュートン法(虚数対応)
    int i=0;
    complex aa;
    while(i<1000){
        i++;
        aa=add_c(a,mul_c(conv_c(-1),div_c(Fx_c(a),dif_c(Fx_c,a))));
        if(val_c(Fx_c(aa))<e){
            break;
        }if(i==999){
            aa=sol_c[0];
        }
        a=aa;
    }
    return a;
}

int main(){//メイン
    printf("対象とする方程式は何次式ですか。整数で入力してください(100以下）\n次数:");
    scanf("%d",&di);//方程式の次数を決定
    printf("各次数の係数を入力してください。（整数、負数および小数は可、分数は不可）\n");
    for(int i=0;i<=di;i++){//係数を受け取り、用意していた配列に格納
        printf("x^%d:",di-i);
        scanf("%lf",&coe[i]);
        //printf("%lf\n",coe[i]);//確認
    }
    printf("対象とする方程式は     \n");//方程式の表示
    for(int j=0;j<=di;j++){
        get_sign(coe[j]);
        printf("%fx^%d",coe[j],di-j);
    };//(数式表示用)
    printf("=0\n");
    //printf("%lf",Fx(2.0));
    printf("答えは、\n");
    unsigned int seed;
    seed = (unsigned int)time(NULL);//ランダム初期値を、時間を種にして生成
    srand(seed);
    int r=1;
    sol_c[0]=conv_c(100000);//局所解を避けるための避け用の値
    for(int i=0;i<8000;i++){//なんとなく8000回まわす
        complex x;
        x.real=(rand()%1001)-500;//なんとなく初期値の範囲は-500～500にした
        x.imag=(rand()%1001)-500;
        sol_c[r]=newtonMethod_c(x,DELTA);//r=1からnewtonMethodの値を入れていく
        for(int j=0;j<r;j++){//その一個前のループまでに入れた値と同じなら、rを進めないようにする
            if(comp_c(sol_c[r],sol_c[j])==1){
                break;
            }if(j==r-1){//一個前のループまでに入れた値と全て異なることが確認出来たら、rを進める
                r++;break;
            }
        }
    }
    for(int i=1;i<r;i++){//答えの表示
        if(val_c(sol_c[i])<1000){//10000といった大きな実数が間違った解として算出されることがあるため、その対策。なぜこのようなミスが起こるのかは不明。
        printf("%dつ目:",i);
        show_c(sol_c[i]);
        }
    }
    return 0;
}