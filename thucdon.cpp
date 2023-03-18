#include<stdio.h>
#include<string.h>
struct thucdon{
	int maso;
	char ten[100];
	int gia;
	int soluong=0;
};
void tron(thucdon a[],const char b[][100]){
	int i;
	for(i=0;i<10;i++)a[i].maso=i+1;
	for(i=0;i<10;i++)strcpy(a[i].ten,b[i]);
}
void thuchien_menu(thucdon nuoc[],int nc[],int n){
	int i;
	printf("***************************************************************************************\n");
	printf("  MS |                   Mat hang                     |             gia ca            *\n");
	for(i=0;i<n;i++){
		if(nuoc[i].maso<10)printf("  %d  | ",nuoc[i].maso);
		else printf(" %d  | ",nuoc[i].maso);
		int j;
		for(j=0;j<strlen(nuoc[i].ten);j++)printf("%c",nuoc[i].ten[j]);
		for(j=0;j<47-strlen(nuoc[i].ten);j++)printf(" ");
		printf("|           ");
		printf("%d VND           *\n",nuoc[i].gia);
	}
	printf("***************************************************************************************\n");
}
void chon(int nc[],int *n,thucdon nuoc[]){
	int i=0;
	while(1){
		printf("\nMa so: ");
		scanf("%d",&nc[i]);
		if(nc[i]==0)break;
		printf("So luong: ");
		if(nuoc[nc[i]-1].soluong!=0){	
			int a;
			scanf("%d",&a);
			nuoc[nc[i]-1].soluong=nuoc[nc[i]-1].soluong+a;
			}
		else scanf("%d",&nuoc[nc[i]-1].soluong);
		i++;
	}
	*n=i;
}
void lap(int nc[],int*n){
	int i;
	for(i=0;i<*n-1;i++){
		int j;
		for(j=0;j<*n;j++){
			if(nc[i]==nc[j] && i!=j){
				int k;
				for(k=j;k<*n-1;k++)nc[k]=nc[k+1];
				*n=*n-1;
				j--;
			}
		}
	}
}
void lam(thucdon nuoc[],int nc[],int n,int*c,FILE*fb){
	int i;
	*c=0;
	fprintf(fb,"**************************************************************************************************\n");
	fprintf(fb,"|                   Mat hang\t\t\t\t|  so luong\t|\tgia ca\t*\n");
	for(i=0;i<n;i++){
		int j;
		fprintf(fb,"|");
		for(j=0;j<strlen(nuoc[nc[i]-1].ten);j++)fprintf(fb,"%c",nuoc[nc[i]-1].ten[j]);
		for(j=0;j<47-strlen(nuoc[nc[i]-1].ten);j++)fprintf(fb," ");
		fprintf(fb,"|\t%d\t|\t",nuoc[nc[i]-1].soluong);
		fprintf(fb,"%d VND\t*\n",nuoc[nc[i]-1].gia*nuoc[nc[i]-1].soluong);
		*c=*c+nuoc[nc[i]-1].gia*nuoc[nc[i]-1].soluong;
	}
	fprintf(fb,"**************************************************************************************************\n");
	}
int dem(FILE*fb){
	char a[100];
	char*c;
	int p=0;
	if(fb==NULL)return 0;
	while(fgets(a,100,fb)!=NULL){
		c=a;
		while((c=strstr(c,"tong tien"))!=NULL){
			p++;
			c+=strlen("tong tien");
		}
	}
	return p;
}
void copy(FILE*f1,FILE*f2){
	char c;
	while((c=fgetc(f1))!=EOF)fputc(c,f2);
}
void thuchien(){
	thucdon chinh[10],trangmieng[10],nuoc[10];
	char a[100][100]={"ca vien chien","ho lo chien","xuc xich chien","hotdog(co nho)","hotdog(co vua)","hotdog(co lon)","ga ran (mot mieng)","combo ga gan va khoai tay chien","hamburger ga gion","banh mi hai san"};
	char b[100][100]={"nuoc ngot(coca,pepsi)","tra dao","tra chanh day","tra vai","tra dau","tra sua chan chau","sua chan chau duong den","sinh to dau","matcha da xay","oreo da xay",};
	char c[100][100]={"che buoi","sua chua","kem chocolate","kem vani"};
	int i,d=10000;
	for(i=0;i<10;i++){
		chinh[i].gia=d;
		d=d+5000;
	}
	d=10000;
	for(i=0;i<10;i++){
		nuoc[i].gia=d;
		d=d+2000;
	}
	for(i=0;i<4;i++)trangmieng[i].gia=15000;
	tron(chinh,a);
	tron(trangmieng,c);
	tron(nuoc,b);
	int nc[100],mon[100],tr[100];
	printf("****************************************************Menu****************************************************************\n");
	printf("---------------------------------------Nuoc--------------------------------------------\n");
	thuchien_menu(nuoc,nc,10);
	printf("-------------------------------------Mon chinh-----------------------------------------\n");
	thuchien_menu(chinh,mon,10);
	printf("----------------------------------Mon trang mieng--------------------------------------\n");
	thuchien_menu(trangmieng,tr,4);	
	int x,y,z,m,n,k;
	printf("*Nuoc ");
	chon(nc,&x,nuoc);
	printf("\n*Mon chinh ");
	chon(mon,&y,chinh);
	printf("\n*Mon trang mieng ");
	chon(tr,&z,trangmieng);
	FILE*fb;
	fb=fopen("hoadon.txt","w");
	fprintf(fb,"*************************************************HOA DON****************************************************************\n");
	fprintf(fb,"------------------------------------------Nuoc----------------------------------------------------\n");
	lap(nc,&x);
	lam(nuoc,nc,x,&m,fb);
	fprintf(fb,"----------------------------------------Mon chinh-------------------------------------------------\n");
	lap(mon,&y);
	lam(chinh,mon,y,&n,fb);
	fprintf(fb,"-------------------------------------Mon trang mieng----------------------------------------------\n");
	lap(tr,&z);
	lam(trangmieng,tr,z,&k,fb);
	fprintf(fb,"| tong tien         \t\t\t\t\t\t\t|\t%d VND\n",m+n+k);
	if(m+n+k>=2000000)fprintf(fb,"| ban duoc giam gia 25%% \t\t\t\t\t\t|\t%0.0f VND",(float)(m+n+k)*(1-(float)25/100));
	fclose(fb);
	fb=fopen("hoadon.txt","r");
	FILE*fp;
	fp=fopen("lichsu.txt","a+");
	i=dem(fp);
	fprintf(fp,"\n#Khach Hang %d\n",i+1);
	copy(fb,fp);
	fclose(fb);
	fclose(fp);
}
int main(){
	thuchien();
	return 0;
	}
