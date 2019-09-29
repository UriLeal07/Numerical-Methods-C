#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <tgmath.h>

const double limitEps = 0.00000000000000000001;		// Limite de precision 1e-20
const int nMax = 500;
int error;

// Prototipos de funciones
double muller(double a, double b, double c, double epsilon, int nVeces);
int checkEpsilon(double epsilon);
int checkInt(int nVeces);
double f(double x);

int main()
{
    char buffer[256];					// Buffer de entrada
	double epsilon; 					// Tolerancia
	double a, b, c;						// Puntos iniciales
	int nVeces;							// Iteraciones maximas
	error = 0;
	
	memset(buffer, '\0', sizeof(buffer));
    
    printf("\nIngrese tolerancia: ");
    scanf("%[^\n]%*c", buffer);
    
    epsilon = atof(buffer);
    
    if(checkEpsilon(epsilon))
    	return -1;
    
    printf("\nIngrese numero maximo de iteraciones: ");
    scanf("%[^\n]%*c", buffer);
    
    nVeces = atoi(buffer);
    
    if(checkInt(nVeces))
    	return -1;
    
    printf("\nIngrese puntos iniciales:\n");
    printf("\nPunto P0: ");
    scanf("%[^\n]%*c", buffer);
    
    a = atof(buffer);
    
    printf("\nPunto P1: ");
    scanf("%[^\n]%*c", buffer);
    
    b = atof(buffer);
    
    printf("\nPunto P2: ");
    scanf("%[^\n]%*c", buffer);
    
    c = atof(buffer);
    
    printf("\n\n----------------------------------------------------");
	printf("\nTolerancia = %g", epsilon);
    printf("\nIteraciones = %d", nVeces);
    printf("\nPunto P0 = %f", a);
    printf("\nPunto P1 = %f", b);
    printf("\nPunto P2 = %f", c);
    printf("\n----------------------------------------------------\n");
    
    // Calcular raiz
    double res = muller(a, b, c, epsilon, nVeces);
    
    if(!error)
    	printf("\nRaiz aproximada = %.14f", res);
    
    return 0;
}

// Method to calculate the root
double muller(double p0, double p1, double p2, double TOL, int nVeces)
{
	double h1, h2, n1, n2, a, h, p, e, b;
	double f_p0, f_p1, f_p2;
	int i = 3;
	double complex d;
	
	// Calculamos f(k) para k-2, k-1, k
	f_p0 = f(p0);
	f_p1 = f(p1);
	f_p2 = f(p2);
	
	// Calculamos deltas Xk
	h1 = p1 - p0;
	h2 = p2 - p1;
	
	// Calculamos numeradores de coeficiente 'a'
	n1 = (f_p1 - f_p0)/h1;
	n2 = (f_p2 - f_p1)/h2;
	
	a = (n2 - n1)/(h2 + h1);
	
	while(i <= nVeces)
	{
		// Calculamos coeficiente 'b'
		b = a*h2 + n2;
		
		// calculamos raiz(b^2 - 4ac)
		d = sqrt((b*b) - (4 * a * f_p2));
		
		// Dependiendo el signo de 'd' sumamos o restamos 'b'
		if(fabs(b - d) < fabs(b + d))
			e = b + d;
		else
			e = b - d;
		
		// Calculamos completo 2c/(b+-raiz(b^2-4ac))
		h = -2*f_p2/e;
		
		// Obtenemos pk+1
		p = p2 + h;
		
		printf("P%d = %.14f\n", i, p);
		
		if(fabs(h) < TOL)
		{
			printf("\nTolerancia alcanzada\n");
			return p;
		}
		
		// Actualizamos variables para siguiente iteración
		p0 = p1;
		p1 = p2;
		p2 = p;
		f_p0 = f(p0);
		f_p1 = f(p1);
		f_p2 = f(p2);		
		/*
		f_p0 = f_p1;
		f_p1 = f_p2;
		f_p2 = f(p2);*/
		h1 = p1 - p0;
		h2 = p2 - p1;
		n1 = (f_p1 - f_p0)/h1;
		n2 = (f_p2 - f_p1)/h2;
		a = (n2 - n1)/(h2 + h1);
		i++;
	}
	
	printf("\nEl metodo fallo despues de %d iteraciones, nVeces = %d\n", i-3, nVeces);
	error = 1;
	
	return 0;
}

// f(x) = x - cos(x) = 0
double f(double x)
{
	return(x - cos(x));
}

int checkEpsilon(double epsilon)
{   
    if(epsilon < limitEps || epsilon > 0.1 || epsilon == 0 )
    {
    	printf("\nValor de epsilon fuera de rango [0.01 - %g]", limitEps);
    	return 1;
    }
    
	return 0;
}

int checkInt(int nVeces)
{
	if(nVeces < 1 || nVeces > nMax)
	{
    	printf("\nValor fuera de rango [1 - %d]", nMax);
    	return 1;
	}
	
	return 0;
}
