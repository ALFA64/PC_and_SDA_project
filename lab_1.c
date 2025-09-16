#include <stdio.h>
#include <math.h>

float type_1(float x, float b){
	return ((cos(x)+1)/(b-x)); 
}

float type_2(float a, float b, float c, float x){
	return ((a*pow(x,2)-b*x+c)/sin(x));
}

float type_3(float b, float c, float x){
	return (log10(x+c)/(2*b));
}

int main(){
float x1,x2,px,a,b,c,x,F;
int n;

printf("Introdu x1 >>> "); scanf("%f",&x1);
printf("Introdu x2 >>> "); scanf("%f",&x2);
printf("Introdu px >>> "); scanf("%f",&px);
printf("Introdu a >>> "); scanf("%f",&a);
printf("Introdu b >>> "); scanf("%f",&b);
printf("Introdu c >>> "); scanf("%f",&c);

x=x1;
n=0;
printf("\n\t <<< Result >>>\n");
while(x<x2){
n+=1;
if ((x-10)<0 && a==0){
	F = type_1(x,b); 
}
else if((x-10)<0 || a != 0) {
	F = type_2(a,b,c,x);
 }
else {
	F = type_3(b,c,x);
}

printf("%i: x =  %.3f \t F = %.3f \n", n,x,F);
x+=px;
}
return 0;
}
