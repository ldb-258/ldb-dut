#include<stdio.h>
#include <math.h>

// Output integer value
void opint(float a){
	if (a == ceil(a)) printf("%.0f",a);
		else printf("%.2f",a);
}

void fopint(float a, FILE *x){
	if (a == ceil(a)) fprintf(x,"%.0f",a);
		else fprintf(x,"%.2f",a);
}
void run(){
	FILE *input = fopen("E:\\DevC++\\PBL1\\input.txt", "r");
	FILE *output = fopen("E:\\DevC++\\PBL1\\output.txt", "w");
	unsigned int n,m;
	int i,k;
	float c;
	float a[100][100];
	float b[100];

//Input:
	//	Nhap bac cua da thuc :
	fscanf(input, "%u",&n);
	for(i=n;i>=0;i--){
	//	Nhap he so x^%d :
		fscanf(input, "%f",&b[n-i]);
	}
	//	y - " "
	fscanf(input,"%f",&c);
	fclose(input);
//Solve:
	for(i=0;i<=n;i++) a[i][0]=b[0];
	for(i=1;i<=n;i++) a[0][i]=b[i];
	for(i=1;i<=n;i++)
		for(k=1;k<=n-i+1;k++)
			a[i][k] = a[i-1][k] - c*a[i][k-1];

// Output:
	printf("p(x) = ");
	for(i=n;i>=0;i--){
		if ((i<n) && (b[n-i]>0)) printf("+");
		if (!(b[n-i])) continue;
		opint(b[n-i]); 

		if (i>1) printf("*x^%d ",i);
		else if(i==1) printf("*x "); 
	}

	printf("\n1.Xuat ra man hinh \n2.Xuat vao file output.txt \n");
	scanf("%u",&m);
	switch (m){
		case 1:
				printf("\nP(x - "); opint(c); printf(") = ");
				opint(b[0]); printf("*x^%d ",n);
				for(i=n;i>0;i--){
				if (a[i][n+1-i] == 0) continue;
				if (a[i][n+1-i] > 0) printf ("+");
				opint(a[i][n+1-i]);
				if (i>2) printf("*x^%d ",i-1);
				else if(i==2) printf("*x ");
				}
				break;
		
		case 2:
				fprintf(output,"P(x - "); fopint(c,output); fprintf(output,") = ");
				fopint(b[0],output); fprintf(output,"*x^%d ",n);
				for(i=n;i>0;i--){
				if (a[i][n+1-i] == 0) continue;
				if (a[i][n+1-i] > 0) fprintf (output,"+");
				fopint(a[i][n+1-i],output);
				if (i>2) fprintf(output,"*x^%d ",i-1);
				else if(i==2) fprintf(output,"*x ");
				}
				break;
		default: printf("Vui long nhap lua chon 1 hoac 2 !");		
	}
	fclose(output);
			
	
	
}
int main(){
	run();
	return 0;
}
