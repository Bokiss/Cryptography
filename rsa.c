#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "linkedList.h"

#define maxNumber 18446744073709551615
#define range 64
#define primeTestRepeats 50
struct public_key
{
	mpz_t n,e;
};
struct private_key
{
	mpz_t d,n;
};
gmp_randstate_t state;

void initializevariables();
void createRSAkeypair(struct public_key*,struct private_key*);
void randomtoprime();
void encrypt(struct public_key,char*,struct Node**,struct Node**);
void computeCiphertext();
void decrypt();
void stringtoint(struct Node**,char *);
int main(void)
{
	//initialize SEED and STATE
	initializevariables();
	int choice = -1;
	struct public_key pubkey,*p;
	struct private_key privkey,*pp;
	p = &pubkey;
	pp = &privkey;
	while(choice != 0)
	{
		printf("\n\n1)Create RSA keys\n");
    	printf("2) Encrypt with RSA \n");
    	printf("3) GCD\n");
    	printf("0)Exit\n");
    	scanf("%d",&choice);

    	if(choice == 1)
    	{
    		createRSAkeypair(p,pp);
    	}
    	else if(choice == 2)
    	{
    		//get text for encryption
    		char data[500];
    		printf("Enter text to encrypt \n");
    		scanf("%s",data);
    		//initialize linked list 
    		struct Node *head = NULL;
    		struct Node *encryptedhead = NULL;
  			//send text for encryption
    		encrypt(pubkey,data,&head,&encryptedhead);
    		printList(head);
    	}
	}
}
/* Initialize seeds Once */
void initializevariables(){
  //variables
  mpz_t seed;
  unsigned long long int tempseed;
  time_t timeseed;

  //initialize variables
  mpz_init(seed);

  //initialize State 
  gmp_randinit_default(state);
  //initialize precision bits for floats
  mpf_set_default_prec(50);

  //create seed 
  srand((unsigned) time(&timeseed));

  tempseed = rand() % maxNumber;
  printf("Time seed : %llu\n",tempseed);

  //initialize seed
  mpz_set_ui(seed,tempseed);

  gmp_randseed(state,seed);
}
void generateRandominRange(mpz_t random,mpz_t max)
{
	mpz_urandomm(random, state, max);
  	//gmp_printf("Random in Range = %Zd\n", random);
}
void generateRandomBits(mpz_t random,unsigned long int maxBit)
{
	do
	{
		mpz_urandomb(random, state, maxBit);
		printf("Random\n");
	}while(mpz_sizeinbase(random,2) < 512); //accept only 512bit randoms
	
  	//gmp_printf("Random spec.Bits = %Zd\n", random);
}
void createRSAkeypair(struct public_key* pubkey,struct private_key* privkey)
{
	unsigned long int maxBits = 512;
	mpz_t p,q,n,f,e,d,gcd;

	mpz_init(p);
	mpz_init(q);
	mpz_init(n);
	mpz_init(f);
	mpz_init(e);
	mpz_init(d);
	mpz_init(gcd);
	//generate 2 randoms 512 bit
	generateRandomBits(p,maxBits);
	generateRandomBits(q,maxBits);
	gmp_printf("RandomP = %Zd\n",p);
	gmp_printf("RandomQ = %Zd\n",q);

	//check if they are prime
	// if not find next prime
	randomtoprime(p);
	randomtoprime(q);
	gmp_printf("P = %Zd\n",p);
	gmp_printf("Q = %Zd\n",q);

	//calculate n = p*q 
	mpz_mul(n,p,q);
	gmp_printf("N = %Zd\n",n);

	//calculate F = (P - 1)(Q - 1)
	// p = p -1
	mpz_sub_ui(p,p,1);
	// q = q - 1
	mpz_sub_ui(q,q,1);
	// f = p * q
	mpz_mul(f,p,q);
	gmp_printf("F = %Zd\n",f);

	//calculate 1 < E < f where gcd(e,f) = 1
	while( mpz_cmp_d(gcd,1) != 0)
	{
		generateRandominRange(e,f);
		mpz_gcd(gcd,e,f);
		gmp_printf("GCD = %Zd\n",gcd);
	}
	gmp_printf("E = %Zd\n",e);

	//calculate D
	do
	{
		generateRandominRange(d,f);
		gmp_printf("D = %Zd\n",d);
	}while( mpz_invert(d,e,f) == 0);
	
	//printf("=====Nums Created=====\n");

	//create public key
	mpz_init_set(pubkey->n,n);
	mpz_init_set(pubkey->e,n);

	//create private key
	mpz_init_set(privkey->d,d);
	mpz_init_set(privkey->n,n);

	printf("===KEYS CREATED===");
	return;

}
void randomtoprime(mpz_t random)
{
	int primetest;
	primetest = mpz_probab_prime_p(random,primeTestRepeats);
	if(primetest == 0)
	{
		mpz_nextprime(random,random);
	}
}
void encrypt(struct public_key pubkey,char *data,struct Node **head,struct Node **encryptedhead)
{
	mpz_t d,ciphertext;

	mpz_init(d);
	mpz_init(ciphertext);
	// make text integers
	stringtoint(head,data);

	while( mpz_cmp_d(d,-1) != 0)
	{
		popfirstNode(head,d);
		//compute ciphertext 
		if( mpz_cmp_d(d,-1) != 0)
		{
			mpz_powm(ciphertext,d,pubkey.e,pubkey.n);
			append(encryptedhead,ciphertext);
		}
	}
}
void stringtoint(struct Node** head,char *string)
{
	int data;
	mpz_t temp;
	mpz_init(temp);
	while( *string != '\0')
	{
		data = (int) *string;
		mpz_set_ui(temp,data);
		append(head,temp);
		*(string)++;
	}
	mpz_clear(temp);
}