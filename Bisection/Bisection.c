#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

const double limitEps = 0.00000000000001;		// Limite de precision 1e-14
const int nMax = 200;

// Function prototypes
double biseccion(double a, double b, double epsilon, int nVeces);
int checkEpsilon(double epsilon);
int checkInt(int nVeces);
double f_x(double x);

int main()
{
    char buffer[256];					// Input buffer
	char funcion[256];					// String to save the input function
	double epsilon; 					// Tolerance
	double a, b;						// Starter points
	int nVeces;							// Iteration limit
	
	// String init
	memset(buffer, '\0', sizeof(buffer));
	memset(funcion, '\0', sizeof(funcion));
	
	// I'm working on it
	// This part of the code reads the input function
	// and interprets each of the terms
	/*
    printf("Ingresar funcion: ");
    scanf("%[^\n]%*c", buffer);
    
    printf("\nNumero de caracteres: %d\n", strlen(buffer));
    
    // Guardamos funcion original
    strcpy(funcion, buffer);
    
    // Separar funcion en tokens por espacios en blanco
	char *token = strtok(buffer, " ");
	int nTokens = 0;
	int i;
	
	while(token != NULL)
	{
	    printf("Token: %s\n", token);
	    token = strtok(NULL, " ");
	    nTokens++;
	}
    
    printf("\nno. Tokens: %d\n", nTokens);
    */
    
    // Input precision
    printf("\nIngrese tolerancia: ");
    scanf("%[^\n]%*c", buffer);
    
    epsilon = atof(buffer);
    
    // Check that the given value is valid
    if(checkEpsilon(epsilon))
    	return -1;
    
    // Input number of iterations
    printf("\nIngrese numero maximo de iteraciones: ");
    scanf("%[^\n]%*c", buffer);
    
    nVeces = atoi(buffer);
    
    // Check that the given value is valid
    if(checkInt(nVeces))
    	return -1;
    
    // Input starter points
    printf("\nIngrese puntos iniciales:\n");
    printf("\nPunto a: ");
    scanf("%[^\n]%*c", buffer);
    
    a = atof(buffer);
    
    printf("\nPunto b: ");
    scanf("%[^\n]%*c", buffer);
    
    b = atof(buffer);
    
    // Check that the given values are valid
    if(checkPoints(a,b))
    	return -1;
    
    // Summary of the given inputs
    printf("\n\n----------------------------------------------------");
	printf("\nEpsilon = %g", epsilon);
    printf("\nIteraciones = %d", nVeces);
    printf("\nPunto a = %f", a);
    printf("\nPunto b = %f", b);
    printf("\n----------------------------------------------------\n");
    
    // Calculate the root
    double res = biseccion(a, b, epsilon, nVeces);
    
    printf("\nRaiz aproximada = %.14f", res);
    
    return 0;
}

// Method to calculate the root
double biseccion(double a, double b, double epsilon, int nVeces)
{
	double m, f_m, f_a;					// Punto medio, funcion evaluada en punto medio "f(m)", funcion evaluada en punto a "f(a)"
	int i = 0;
	
	f_a = f_x(a);
	
	while(i < nVeces)
	{
		m = a+(b-a)/2;			// Calculamos punto medio
		f_m = f_x(m);			// Calculamos f(m)
		
		printf("\np = %.14f", m);
		
		// Si encontramos la raiz o superamos el nivel de precision
		if(f_m == 0) //|| (b-a)/2 < epsilon)
		{
			printf("\n\n------- Raiz encontrada -------\n", i);
			printf("Iteraciones realizadas: %d", i);
			return m;
		}
		
		if((b-a)/2 < epsilon)
		{
			printf("\n\n------- Precision alcanzada -------\n", i);
			printf("Iteraciones realizadas: %d", i);
			return m;
		}
		
		i++; 	// Avanzamos 1 iteracion
		
		// Si hay cambio de signo
		if(f_a*f_m > 0)
		{
			a = m;
			f_a = f_m;
		}
		else
			b = m;
	}
	
	printf("\n------- El metodo fallo despues de %d iteraciones -------\n", i);
	
	return 0;
}

// f(x) = x^3 - x^2 - 5
/*
double f_x(double x)
{
	//double res = pow(x,3) - (x*x) - 5;
	
	return(pow(x,3) - (x*x) - 5);
}*/

// x^3 - 47.3
/*
double f_x(double x)
{
	//double res = pow(x,3) - (x*x) - 5;
	
	return(pow(x,3) - 47.3);
}
*/

// x^4 - 5x^3 + x^2 -8x +15

// Function to calculate
double f_x(double x)
{
	double res = pow(x,4) - (5*x*x*x) + (x*x) - (8*x) + 15;
	
	return(res);
}

// f(x) = x - 0.8 - 0.2sen(x)
/*
double f_x(double x)
{
	return(x - 0.8 -0.2*sin(x));
}
*/

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

int checkPoints(double a, double b)
{
	if(a >= b)
	{
    	printf("\nEl punto a debe ser menor al b | %.3f > %.3f ", a, b);
    	return 1;
	}
	
	return 0;
}
