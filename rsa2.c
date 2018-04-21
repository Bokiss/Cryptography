#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#define maxNumber 18446744073709551615
#define range 512
#define primeTestRepeats 50


gmp_randstate_t state;
void initializevariables();
void generateRandom();
void generateRandominRange(mpz_t *,mpz_t);
void menu();
void rsa();
int checkprime();
void euclidianGCD(mpz_t,mpz_t,double *);
void extendedEuclidean(int ,int );
int main(void)
{
  initializevariables();
  menu();
  
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

  //create seed 
  srand((unsigned) time(&timeseed));

  tempseed = rand() % maxNumber;
  printf("Time seed : %llu\n",tempseed);

  //initialize seed
  mpz_set_ui(seed,tempseed);

  gmp_randseed(state,seed);
}
void menu()
{
  int choice=-1;
  mpz_t random;
  mpz_init(random);
  do {
    printf("\n\n1)Generate Random Prime\n");
    printf("2) RSA \n");
    printf("3) GCD\n");
    printf("0)Exit\n");
    scanf("%d",&choice);

    if(choice == 1){
      generateRandom(&random);
      gmp_printf("Randomzz = %Zd\n", random);
      while( checkprime(&random) == 0)
      {
        mpz_nextprime(random,random);
        gmp_printf("Randomww = %Zd\n", random);

      }
    }
    else if(choice == 2)
    {
      rsa();
    }
    else if(choice == 3)
    {
      /*
      mpz_t a,b;
      mpz_init(a);
      mpz_init(b);
      */
      int a,b;
      printf("A = \n");
      scanf("%d",&a);
      printf("B = \n");
      scanf("%d",&b);
      extendedEuclidean(a,b);
      
    }
  }
  while(choice != 0 );

  mpz_clear(random);

}
void generateRandom(mpz_t *random)
{
  mpz_urandomb(*random, state, range);
  gmp_printf("Randomz = %Zd\n", *random);
}
void generateRandominRange(mpz_t *random,mpz_t max)
{
  gmp_printf("max = %Zd\n", max);
  mpz_urandomm(*random, state, max);
  gmp_printf("Random in Range = %Zd\n", *random);
}
int checkprime(mpz_t *random)
{
  int primetest = 99;
  primetest = mpz_probab_prime_p(*random,primeTestRepeats);
  //printf("checkprime - %d\n",primetest);
  return primetest;
}
void rsa()
{
  double gcd;
  //declare and init 2 large randoms
  mpz_t p,q,n,f,e,temp,random,tempf;
  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_init(f);
  mpz_init(e);
  mpz_init(temp);
  mpz_init(tempf);
  mpz_init(random);
  //create randoms
  generateRandom(&p);
  generateRandom(&q);
  //gmp_printf("RSA-randoms created\n");
  //gmp_printf("RSA - First random : %Zd\n",p);
  //gmp_printf("RSA - Second random : %Zd\n",q);
  
  //check if they are prime
  while( checkprime(&p) == 0 )
  {
    mpz_nextprime(p,p);
    gmp_printf("RSA - First PRIME : %Zd\n",p);
  }
  while( checkprime(&q) == 0)
  {
    mpz_nextprime(q,q);
    gmp_printf("RSA - Second PRIME : %Zd\n",q);
  }
  unsigned long size ;
  size =(unsigned long) mpz_sizeinbase(p,2);
  printf("%lu\n",size);


  //calculate n = pq
  mpz_mul(n,p,q);
  gmp_printf("RSA - n=p*q : %Zd\n",n);

  mpz_set_ui(temp,1);
  //calculate f = (p-1)(q-1)
  mpz_sub(p,p,temp);
  mpz_sub(q,q,temp);

  mpz_mul(f,p,q);

  gmp_printf("RSA - f= (p-1)(q-1) %Zd\n",f);
 
  //generate random int e  1 < e < f && gcd(e,f)=1
  while(gcd != 1)
  {
    mpz_set(tempf,f);
    gmp_printf("RSA tempf %Zd\n",tempf);
    generateRandominRange(&random,f);
    euclidianGCD(random,tempf,&gcd);
    printf("GCD = %lf\n",gcd);
    //if(gcd != 1){mpz_add_ui(random,random,1);}
  }
  

  //clear before exit
  mpz_clear(p);
  mpz_clear(q);
  mpz_clear(n);
  mpz_clear(f);
  mpz_clear(e);
  mpz_clear(temp);
  mpz_clear(tempf);
  mpz_clear(random);
}

void euclidianGCD(mpz_t a,mpz_t b,double *gcd)
{
    mpz_t temp;
    mpz_init(temp);
    //gmp_printf("E-GCD while a = %Zd b = %Zd\n",a,b);
    if( a < 0){mpz_abs(a,a);}
    else if( b < 0){mpz_abs(b,b);}
    if(b > a)
    {
      //printf("E-GCD - b > a \n");
      mpz_clear(temp);
      return euclidianGCD(b,a,gcd);
    }
    else if(a >= b)
    {
      //printf("E-GCD - a >= b\n");
      while( mpz_cmp_d(b,0) > 0)
      {
        //gmp_printf("E-GCD while a = %Zd b = %Zd\n",a,b);
        mpz_mod(temp,a,b);
        mpz_set(a,b);
        mpz_set(b,temp);
        //gmp_printf("E-GCD while a = %Zd b = %Zd\n",a,b);
        sleep(0.2);
      }
      *gcd = mpz_get_d(a);
      return ;
      
    }
    else
    {
      printf("E-GCD - uncatched else\n");
    }

}
void extendedEuclidean(int a,int b)
{
  if(b == 0)
  {

  }
  else
  {
    int x,x1,x2,y,y1,y2,r,q,d;
    x1 = 0;
    x2 = 1;
    y1 = 1;
    y2 = 0;
    while( b > 0)
    {
      //3.1
      q = a/b;
      r = a - (q*b);
      x = x2 - (q*x1);
      y = y2 - (q*y1);
      printf("q = %d,r = %d,x = %d,y = %d,a = %d,b=%d\n",q,r,x,y,a,b);
      //3.2
      a = b;
      b = r;
      x2 = x1;
      x1 = x;
      y2 = y1;
      y1 = y;
      printf("q = %d,r = %d,x = %d,y = %d,a = %d,b=%d\n\n",q,r,x,y,a,b);
    }

    d = a;
    x = x2;
    y = y2;

    printf("ax+by=d\n");
    printf("%d*%d+%d*%d=%d",a,x,b,y,d);
  }
}