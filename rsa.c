#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <gmp.h>
#include <time.h>

#define maxNumber 18446744073709551615
gmp_randstate_t state;
void generateRandom();
void menu();

int main(void)
{
  menu();
  
}

void menu();
{
  int choice=-1;
  do {
    printf("\n1)Generate Random");
    printf("\n0)Exit");
    scanf("%d",&choice);
  }
  while(choice != 0 )
  {
    if(choice == 1){generateRandom();}
  }

  
}


void generateRandom()
{
  //variables
  mpz_t random,seed;
  unsigned long long int tempseed;
  time_t timeseed;

  //initialize variables
  mpz_init(random);
  mpz_init(seed);

  //initialize State 
  gmp_randinit_default(state);

  //create seed --Must implement 1s cooldown --
  srand((unsigned) time(&timeseed));
  tempseed = rand() % maxNumber;
  printf("\nTime seed : %llu\n",tempseed);

  //initialize seed
  mpz_set_ui(seed,tempseed);

  gmp_randseed(state,seed);


}