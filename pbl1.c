#include<stdio.h>
#include <math.h>

// Output integer value
void opint(float a){
	if (a == ceil(a)) printf("%.0f",a);
		else printf("%.2f",a);
}
void run(){
	unsigned int n;
	int i,k;
	float c;
	float a[100][100];
	float b[100];

//Input:
	printf("Nhap bac cua da thuc : ");
	scanf("%u",&n);
	for(i=n;i>=0;i--){
		printf("Nhap he so x^%d : ",i);
		scanf("%f",&b[n-i]);
	}
	printf("y - ");
	scanf("%f",&c);
	
//Solve:
	for(i=0;i<=n;i++) a[i][0]=b[0];
	for(i=1;i<=n;i++) a[0][i]=b[i];
	for(i=1;i<=n;i++)
		for(k=1;k<=n-i+1;k++)
			a[i][k] = a[i-1][k] - c*a[i][k-1];

// Output:

	printf("P(y - "); opint(c); printf(") = ");
	opint(b[0]); printf("*x^%d ",n);
	for(i=n;i>0;i--){
		if (a[i][n+1-i] == 0) continue;
		if (a[i][n+1-i] > 0) printf ("+");
		opint(a[i][n+1-i]);
		if (i>2) printf("*x^%d ",i-1);
		else if(i==2) printf("*x ");
		}			
	
}
int main(){
	run();
}