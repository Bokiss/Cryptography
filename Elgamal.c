#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "linkedList.h"
#include "utility.h"

#define primetestrepeat 50
#define bits 20


int main(void)
{
	mpz_t p,generator,a,temp;

	mpz_init(p);
	mpz_init(generator);
	mpz_init(a);
	mpz_init(temp);
	//printf("asd");
	//STEP 1
	initializevariables();
	printf("asd\n");
	/*
	do
	{
		//generate random 199 bits
		generateRandomBits(p,200);
		//find the first prime 
		randomtoprime(p);
		//save the generator
		mpz_set(generator,p);
		// find 2p
		mpz_mul_ui(p,p,2);
		// 2p + 1
		mpz_add_ui(p,p,1);
		//check if its prime
	}while( mpz_probab_prime_p(p,primetestrepeat) == 0);
	*/

	//printf("asd");
	//STEP 2cl
	//Generate a, 1 <= a <= p-2 

	//temp = p
	//mpz_set(temp,p);
	// temp = temp - 3
	//mpz_sub_d(temp,3);
	// generate in range [0,p-3] and add 1
	//generateRandominRange(a,temp);
	//mpz_set_d(temp,1);
	//mpz_add(a,temp);

	//Compute generator*a mod p
	mpz_t test;
	mpz_t *t;
	unsigned long int  binary[bits];
	//mpz_init(t);
	mpz_init(test);
	t = &test;
	generateRandomBits(test,bits);
	//gmp_printf("test = %Zd\n",test);
	//gmp_printf("test2 = %Zd\n",*t);
	gmp_printf("test = %Zd\n",test);
	tobinary(test,binary);
	printf("\n\n\n");
	for(int i=0;i<bits;i++)
	{
		printf("%lu",binary[i]);
	}
	printf("\n");

	//gmp_printf("t = %Zd\n",t);
	//printf("test3 = %d\n",t);
	//char binary[5000];
	//int as = 892;
	//int b;
	//b = convertd(as);
	//printf("%d\n",b);



	//printf("test = %d\n",t);
	/*
	t = &test ;
	printf("asd");
	while( t != NULL )
	{
		printf("==asd");
		printf("%d",t);
		printf("asd");
		t++;
		printf("asd");
	}
	*/
}