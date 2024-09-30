#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define PI 3.141592653589793
#define EMAIL_MX 255
#define EMAIL_PL 63
char c_val[] = "!#$%&'*+/=?^_{|}~";

float dist_norm(float md, float de)
{
	float U1, U2, Z1;
	U1 = (float)rand()/RAND_MAX;
	U2 = (float)rand()/RAND_MAX;
	Z1 = sqrt(-2*log(U1))*sin(2*PI*U2);
	return (Z1*de+md);
}

int imprimir2(float x[], int n)
{
	printf("%f\n", x[0]);
	if(n-1)
		return imprimir2(x+1, n-1);
	else
		return 0;
}

float suma_x(float x[], int n)
{
	//return n-1?x[0]+suma_x(x+1,n-1):x[0];
	if(n-1)
		return x[0]+suma_x(x+1,n-1);
	else
		return x[0];
}

float media2(float x[], int n)
{
	return suma_x(x, n)/n;
}

float media1(float x[], int n)
{
	int i;
	float md;
	for(i=1, md=x[0]; i<n; i++)
		md+=x[i];
	return md/n;
}

float suma_x2(float x[], float md, int n)
{
	if(n-1)
		return (x[0]-md)*(x[0]-md)+suma_x2(x+1, md, n-1);
	else
		return (x[0]-md)*(x[0]-md);
}

float varianza2(float x[], int n)
{
	float md;
	md = media2(x, n);
	return suma_x2(x, md, n)/(n-1);
}

float varianza1(float x[], int n)
{
	int i;
	float md, vr;
	for(i=0, md = media1(x, n), vr=0; i<n; i++)
		vr+=((x[i]-md)*(x[i]-md));
	return vr/(n-1);
}

void generar(float x[], int n, float min, float max)
{
	int i;
	for(i=0; i<n; i++)
		x[i] = (max-min)*((float)rand())/RAND_MAX+min;
}

void imprimir(float x[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("x[%d] = %f\n", i+1, x[i]);
}

float suma(float a, float b)
{
	return a+b;
}

int cambio(int E, int A, int B)
{
	int Zi;
	Zi = (E/A)*B;
	return Zi?Zi+cambio(Zi+E-(Zi*A)/B,A,B):0;
}

int chocolate(int X, int Y, int A, int B)
{
	return X/Y+cambio(X/Y,A,B);
}

float potencia(float x, int n)
{
	return n?x*potencia(x,n-1):1;
}

long int factorial(long int n)
{
	return n?n*factorial(n-1):1;
}

float exp1(float x, int n)
{
	return n?potencia(x,n)/factorial(n)+exp1(x,n-1):1;
}

float fct(float x, int n)
{
	return n?(x/n)*fct(x,n-1):1;
}

float exp3(float x, int n)
{
	return n?fct(x,n)+exp3(x,n-1):1;
}

float exp4(float x, int n)
{
	static float fct1=1;
	static int i=0;
	fct1*=(x/(i+1));
	if(n-i++)
		return fct1+exp4(x,n);
	else
	{
		fct1=1;
		i=0;
		return 1;
	}
}

int isce(char c, char c_val[])
{
	if(c==c_val[0])
		return 1;
	else if(c_val[0]!='\0')
		return isce(c,c_val+1);
	else
		return 0;
}

int validar(char email[])
{
	int nc, da, i, nce;
	char *bc;
	nc = strlen(email);
	nce = strlen(c_val);
	if(nc>EMAIL_MX)
		return 0;
	bc = strchr(email, '@');
	if(bc==NULL)
		return 0;
	da = (int)(bc-email);
	if(da>EMAIL_PL)
		return 0;
	for(i=0; i<da; i++)
		if(!isalnum(email[i])&&!isce(email[i],c_val))
			return 0;
	return 1;
}
	
