#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 44100
#define PI 3.14159265358989

//2バイト作成
void put2byte (int n, FILE* fp){
	int mask = 0xff;
	putc( n&mask, fp);
	n>>=8;
	putc( n&mask, fp);
}

//4バイト作成
void put4byte (int n, FILE* fp){
	int mask = 0xff;
	putc( n&mask, fp);
	n>>=8;
	putc( n&mask, fp);
	n>>=8;
	putc( n&mask, fp);
	n>>=8;
	putc( n&mask, fp);
}

FILE* fp;

int main(void){
	int i;
	double x;
	int d;
	//ファイルサイズの計算
	int dsize = 4 + 4 + 4 + 4 + (2 * N);
	int fsize = 2 + 2 + 4 + 4 + 2 + 2;
	
	fp = fopen( "a.wav", "wb");//ファイルオープン
	//RIFF チャンクID
	putc( 'R', fp);
	putc( 'I', fp);
	putc( 'F', fp);
	putc( 'F', fp);
	

	
	put4byte(dsize, fp);
	
	//フォーマットタイプ
	putc( 'W', fp);
	putc( 'A', fp);
	putc( 'V', fp);
	putc( 'E', fp);
	
	//fmt チャンクID
	putc( 'f', fp);
	putc( 'm', fp);
	putc( 't', fp);
	putc( ' ', fp);
	
	//fmtチャンクサイズ
	put4byte(fsize, fp);
	
	
	//WAVEフォーマット構造体
	//
	put2byte(1, fp); //フォーマットタグ非圧縮PCM
	put2byte(1, fp); //チャンネル数
	put4byte(N, fp); //サンプル
	put4byte(N * 2, fp); //バイト
	put2byte(2, fp); //データサイズ
	put2byte(16, fp); //量子化ビット数
	
	//データチャンクID
	putc( 'd', fp);
	putc( 'a', fp);
	putc( 't', fp);
	putc( 'a', fp);
	
	put4byte(2 * N, fp);
	
	for(i = 0; i < N; i++){
		x = 2.0 * PI * 440 * i / N;
		d = (int)32767 * sin(x);
		put2byte(d, fp);
	}
	
	fclose( fp );
	return 0;
}

