#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "linkedList.h"
#include "utility.h"
#include "rsa_keys.h"

void createRSAkeypair(struct public_key*,struct private_key*);
void encrypt(struct public_key,char*,struct Node**,struct Node**);
void decrypt(struct private_key,struct Node**);

int main(void)
{
	//initialize SEED and STATE
	initializevariables();
	int choice = -1;
	struct public_key pubkey,*p;
	struct private_key privkey,*pp;
	struct Node *head = NULL;
	struct Node *encryptedhead = NULL;
	p = &pubkey;
	pp = &privkey;
	while(choice != 0)
	{
		printf("\n\n1)Create RSA keys\n");
    	printf("2) Encrypt with RSA \n");
    	printf("3) Decrypt with RSA\n");
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
  			//send text for encryption
    		encrypt(pubkey,data,&head,&encryptedhead);
    		printList(encryptedhead);
    	}
    	else if(choice == 3)
    	{
    		decrypt(privkey,&encryptedhead);
    		printList(encryptedhead);
    	}
	}
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
	gmp_printf("END D = %Zd\n",d);
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

void encrypt(struct public_key pubkey,char *data,struct Node **head,struct Node **encryptedhead)
{
	mpz_t d,ciphertext;

	mpz_init(d);
	mpz_init(ciphertext);
	// make text integers
	stringtoint(head,data);
	int size = mpz_sizeinbase(pubkey.e,2);
	int binary[size];
	while( mpz_cmp_d(d,-1) != 0)
	{
		popfirstNode(head,d);
		//compute ciphertext 
		if( mpz_cmp_d(d,-1) != 0)
		{
			tobinary(pubkey.e,binary);
			RSMA(d,ciphertext,pubkey.n,binary,size);
			append(encryptedhead,ciphertext);
		}
	}
}

void decrypt(struct private_key privkey,struct Node** head)
{
	mpz_t plaintext,ciphertext;
	int size = mpz_sizeinbase(privkey.d,2);
	int binary[size];
	mpz_init(plaintext);
	mpz_init(ciphertext);

	while( mpz_cmp_d(ciphertext,-1) != 0)
	{
		popfirstNode(head,ciphertext);
		if( mpz_cmp_d(ciphertext,-1) != 0)
		{
			gmp_printf("Ciphertext = %Zd\n",ciphertext);
			tobinary(privkey.d,binary);
			RSMA(ciphertext,plaintext,privkey.n,binary,size);
			gmp_printf("Plaintext = %Zd\n",plaintext);
		}
		
	}
}
