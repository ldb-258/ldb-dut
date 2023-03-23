#include<stdio.h>
#include<string.h>
#include <windows.h>
void color (int x)
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}
struct menu{
	int id;
	char name[100];
	int price;
	int sl=0;
};
// Ke dong ngang
void line(char c, int n){
	int i;
	for (i=0; i<n; i++) printf("%c",c);
}
// Ke dong ngang trong file
void fline(FILE *op, char c, int n){
	int i;
	for (i=0; i<n; i++) fprintf(op,"%c",c);
}

void tron(menu a[],const char b[][100]){
	int i;
	for(i=0;i<10;i++)	a[i].id=i+1;
	for(i=0;i<10;i++)	strcpy(a[i].name,b[i]);
}
void run_menu(menu nuoc[],int nc[],int n){
	int i;
	line('-',87); printf("\n");
	printf("  MS |                   Mat hang                     |             gia ca            *\n"); 
	line('-',87); printf("\n");
	for(i=0;i<n;i++){
		if(nuoc[i].id<10)printf("  %d  | ",nuoc[i].id);
		else printf(" %d  | ",nuoc[i].id);
		int j;
		for(j=0;j<strlen(nuoc[i].name);j++) 	printf("%c",nuoc[i].name[j]);
		for(j=0;j<47-strlen(nuoc[i].name);j++)printf(" ");
		printf("|           ");
		printf("%d VND           *\n",nuoc[i].price);
	}
	line('-',87); printf("\n");
}
// Chon mon + so luong
void pick(int nc[],int *n,menu nuoc[]){
	int i=0;
	while(1){
		printf("\nMa so: ");
		scanf("%d",&nc[i]);
		if(nc[i]==0)break;
		printf("So luong: ");
		if(nuoc[nc[i]-1].sl!=0){	
			int a;
			scanf("%d",&a);
			nuoc[nc[i]-1].sl=nuoc[nc[i]-1].sl+a;
			}
		else scanf("%d",&nuoc[nc[i]-1].sl);
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

// In hoa don
void work(menu nuoc[],int nc[],int n,int*c,FILE*fb){
	int i;	*c=0;
	fline(fb,'-',79); fprintf(fb,"\n");
	fprintf(fb,"|                   Mat hang\t\t\t\t|  so luong\t|\tgia ca\t|\n");
	fline(fb,'-',79); fprintf(fb,"\n");
	for(i=0;i<n;i++){
		int j;
		fprintf(fb,"| ");
		for(j=0;j<strlen(nuoc[nc[i]-1].name);j++)fprintf(fb,"%c",nuoc[nc[i]-1].name[j]);
		for(j=0;j<46-strlen(nuoc[nc[i]-1].name);j++)fprintf(fb," ");
		fprintf(fb,"|\t%d\t|\t",nuoc[nc[i]-1].sl);
		fprintf(fb,"%d VND\t|\n",nuoc[nc[i]-1].price*nuoc[nc[i]-1].sl);
		*c=*c+nuoc[nc[i]-1].price*nuoc[nc[i]-1].sl;
	}
	fline(fb,'-',79); fprintf(fb,"\n");
	}
	
// Dem so khach hang = "TONG TIEN"
int count(FILE*fb){
	char a[100], *c;	int p=0;
	if(fb==NULL)return 0;
	while(fgets(a,100,fb)!=NULL){
		c=a;
		while((c=strstr(c,"TONG TIEN"))!=NULL){
			p++;
			c+=strlen("TONG TIEN");
		}
	}
	return p;
}
// Copy hoa don -> lich su
void copy(FILE*f1,FILE*f2){
	char c;
	while((c=fgetc(f1))!=EOF)fputc(c,f2);
}
void run(){
	menu chinh[10],trangmieng[10],nuoc[10];
	char a[100][100]={"ca vien chien","ho lo chien","xuc xich chien","hotdog(co nho)","hotdog(co vua)","hotdog(co lon)","ga ran (mot mieng)","combo ga gan va khoai tay chien","hamburger ga gion","banh mi hai san"};
	char b[100][100]={"nuoc ngot(coca,pepsi)","tra dao","tra chanh day","tra vai","tra dau","tra sua chan chau","sua chan chau duong den","sinh to dau","matcha da xay","oreo da xay",};
	char c[100][100]={"che buoi","sua chua","kem chocolate","kem vani"};
	int i,d=10000;
	for(i=0;i<10;i++){
		chinh[i].price=d;
		d=d+5000;
	}
	d=10000;
	for(i=0;i<10;i++){
		nuoc[i].price=d;
		d=d+2000;
	}
	for(i=0;i<4;i++)trangmieng[i].price=15000;
	tron(chinh,a);
	tron(trangmieng,c);
	tron(nuoc,b);
	int nc[100],mon[100],tr[100];
	color(2); 	line('*',41);	printf("HOA DON");	line('*',41);	printf("\n");
	color(3);	line(' ',41); 	printf("nuoc");		line(' ',41);	printf("\n");
	color(7);	run_menu(nuoc,nc,10);
	color(3);	line(' ',39); 	printf("Mon chinh");		line(' ',39);	printf("\n");
	color(7);	run_menu(chinh,mon,10);
	color(3);	line(' ',37); 	printf("Mon trang mieng");		line(' ',37);	printf("\n");
	color(7); run_menu(trangmieng,tr,4);	
	int x,y,z,m,n,k;
	printf(">Nuoc ");				pick(nc,&x,nuoc);
	printf("\n>Mon chinh ");		pick(mon,&y,chinh);
	printf("\n>Mon trang mieng ");	pick(tr,&z,trangmieng);

// file
	FILE*fb;	fb=fopen("hoadon.txt","w");
	fline(fb,'*',36);	fprintf(fb,"HOA DON");	fline(fb,'*',36);	fprintf(fb,"\n");
	fline(fb,' ',37);	fprintf(fb,"Nuoc");	fline(fb,' ',37);	fprintf(fb,"\n");
	lap(nc,&x); 	work(nuoc,nc,x,&m,fb);
	fline(fb,' ',35);	fprintf(fb,"Mon chinh");	fline(fb,' ',35);	fprintf(fb,"\n");
	lap(mon,&y);	work(chinh,mon,y,&n,fb);
	fline(fb,' ',32);	fprintf(fb,"Mon trang mieng");	fline(fb,' ',32);	fprintf(fb,"\n");
	lap(tr,&z);		work(trangmieng,tr,z,&k,fb);
	fprintf(fb,"| TONG TIEN         \t\t\t\t\t\t\t|\t%d VND\t|\n",m+n+k);
	if(m+n+k>=2000000)fprintf(fb,"| ban duoc giam gia 25%% \t\t\t\t\t\t|\t%0.0f VND",(float)(m+n+k)*(1-(float)25/100));
	fclose(fb);
	fb=fopen("hoadon.txt","r");
	FILE*fp;
	fp=fopen("lichsu.txt","a+");
	i=count(fp);
	fprintf(fp,"\n#Khach Hang %d\n",i+1);
	copy(fb,fp);
	fclose(fb);
	fclose(fp);
}

int main(){
	run();
	return 0;
	}
