#include<stdio.h>
#include<string.h>//文字列をいじる関数を使うのに必要
#include<stdlib.h>//rand乱数関数を使うのに必要
void hello(void);
void tasu(int,int);//プロトタイプ宣言:予め関数の形を宣言しておけば、その中身の記述は後からでも大丈夫
int main() {
 
  printf("Hello, World\n");//printf
  char var;//変数の宣言
  var='A';
  int a,b,c;
  a=0;b=1;c=2;
  tasu(a,b);
  printf("%d %d %dです\n",a,a+b,c);
  float x;
  x=33.33;
  printf("\a%f\n",x);
  char moji[1000];
 
  /* 文字列の入力 */
  printf("文字列を入力してください。\n");
  scanf("%[^\n]", moji);//改行を除くすべての標準入力に対応（スキャン集合[]の否定^を使用）
  /* 文字列の出力 */
  printf("%s\n", moji);
  char mojiretu[10];
  strcpy(mojiretu, "ABCDE");//文字列関数を一度に代入する方法(<string.h>が先頭に必要)
  printf("%s\n", mojiretu);
//strcpy(s1,s2):s2をs1にコピーする
//strcat(s1,s2):s1の後にs2を連結
//strlen(s):sの長さを取得
//strcmp(s1,s2):s1とs2の長さが同じなら0を取得、異なる場合はそれ以外。
  hello();
  return 0;
}
void hello(void){
    printf("Hello,World\n");
}//引数なし、戻り値なしの関数
void tasu(int a, int b){
  int c;
  c = a + b;
  printf("%d\n", c);
}//引数あり、戻り値なしの関数