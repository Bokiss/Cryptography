#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "linkedList.h"
#include "rsa_keys.h"

#define maxNumber 18446744073709551615
#define range 64
#define primeTestRepeats 50

gmp_randstate_t state;
void getText(char *);
void stringtoint(struct Node**,char *);
char* inttostring(struct Node**);
void initializevariables();
void generateRandom();
void generateRandominRange(mpz_t *,mpz_t);
void menu();
void rsa();
int checkprime();
void euclidianGCD(mpz_t,mpz_t,double *);
void extendedEuclidean(mpz_t ,mpz_t,mpz_t);
int main(void)
{
  initializevariables();
  menu();
  
}
void getText(char* text)
{
  printf("Enter text: ");
  scanf("%s",text);
}
void stringtoint(struct Node** head,char *string)
{
  int data;
  while( *string != '\0')
  {
    data = (int) *string;
    append(head,data);
    *(string)++;
  }
}
char* inttostring(struct Node** head)
{
  char data[500];
  char *str;
  int temp=1,counter=0;
  while( (temp > 0) || (counter>=500))
  {
    temp = popfirstNode(head);
    if(temp > 0)
    {
      data[counter]= temp;
      printf("%c",temp);
      counter++;
     } 
  }
  printf("\n");
  str = (char*) malloc(sizeof(char)*counter);
  str = data ;
  return str;
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
      //stringtoint("asdg asd");
      //pri();
      char text[500];
      getText(text);
      struct Node* head = NULL;
      stringtoint(&head,text); 
      printList(head);
      printf("BACK %s\n",inttostring(&head));
      /*
      printf("Poping\n");
      while( ch2 >= 0)
      {
        ch2 = popfirstNode(&head);
        printf("%d->",ch2);        
      }
      
      mpz_t a,b;
      mpz_init(a);
      mpz_init(b);
      
      int a,b;
      printf("A = \n");
      scanf("%d",&a);
      printf("B = \n");
      scanf("%d",&b);
      extendedEuclidean(a,b);
      */
      
    }
  }
  while(choice != 0 );

  //mpz_clear(random);

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
  mpz_t p,q,n,f,e,d,temp,random,tempf;
  mpz_init(p);
  mpz_init(q);
  mpz_init(n);
  mpz_init(f);
  mpz_init(e);
  mpz_init(temp);
  mpz_init(tempf);
  mpz_init(random);
  mpz_init(d);
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
  //save e
  mpz_set(e,random);
  int testinvert = 0;
  while( testinvert == 0)
  {
    //mpz_set(tempf,e);
    generateRandominRange(&random,f);
    gmp_printf("New Random = %Zd\n",random);
    testinvert = mpz_invert(d,e,f);
    gmp_printf("D = %Zd\n",d);
    //euclidianGCD(random,e,&gcd);
  }
  struct public_key* pubkey;
  struct private_key* privkey;
  printf("hello");
  mpz_init(pubkey->n);
  mpz_init(pubkey->e);
  mpz_set(pubkey->n,n);
  mpz_set(pubkey->e,e);
  printf("hello");
  mpz_init(privkey->d);
  //mpz_init(privkey->n);
  //mpz_set(privkey->d,d);
  //mpz_set(privkey->n,n);
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
    mpz_t temp,tempa,tempb;
    mpz_init(temp);
    mpz_init(tempa);
    mpz_init(tempb);

    //copy values
    mpz_set(tempa,a);
    mpz_set(tempb,b);

    //gmp_printf("E-GCD while a = %Zd b = %Zd\n",a,b); FIX
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
      while( mpz_cmp_d(tempb,0) > 0)
      {
        //gmp_printf("E-GCD while a = %Zd b = %Zd\n",a,b);
        mpz_mod(temp,tempa,tempb);
        mpz_set(tempa,tempb);
        mpz_set(tempb,temp);
        //gmp_printf("E-GCD while a = %Zd b = %Zd\n",a,b);
        sleep(0.2);
      }
      *gcd = mpz_get_d(tempa);
      return ;
      
    }
    else
    {
      printf("E-GCD - uncatched else\n");
    }

}
void extendedEuclidean(mpz_t a,mpz_t b,mpz_t d)
{
  if(mpz_cmp(b,a) > 0 ){printf("b>a\n");return extendedEuclidean(b,a,d);}
  //create new vars
  mpz_t tempa,tempb,x,x1,x2,y,y1,y2,q,r,save;
  //float vars
  //mpf_t q;
  //initiate vars
  mpz_init(tempa);
  mpz_init(tempb);
  mpz_init(x);
  mpz_init(x1);
  mpz_init(x2);
  mpz_init(y);
  mpz_init(y1);
  mpz_init(y2);
  mpz_init(r);
  mpz_init(q);
  mpz_init(save);

  //copy a and b
  mpz_set(tempa,a);
  mpz_set(tempb,b);
  gmp_printf("tempa=%Zd\ntempb=%Zd\n",tempa,tempb);
  if(mpz_cmp_d(tempb,0) == 0)
  {
    printf("Extended-- tempb == 0\nn");
  }
  else
  {
    mpz_set_ui(x2,1);
    mpz_set_ui(y1,1);
    while( mpz_cmp_d(tempb,0) > 0)
    {
      //3.1
      //q = a - b
      mpz_cdiv_q(q,tempa,tempb);
      gmp_printf("q = %Zd\n",q);
      //r = a - (q*b)
      mpz_mul(save,q,b);
      mpz_sub(r,tempa,save);
      gmp_printf("r = %Zd\n",r);
      //x = x2 - (q*x1)
      mpz_mul(save,q,x1);
      mpz_sub(x,x2,save);
      gmp_printf("x = %Zd\n",x);
      //y = y2 - (q*y1)
      mpz_mul(save,q,y1);
      mpz_sub(y,y2,save);
      gmp_printf("y = %Zd\n",y);
      //gmp_printf("q = %Zd,r = %Zd,x = %Zd,y = %Zd,a = %Zd,b=%Zd\n",q,r,x,y,a,b);
      //3.2
      //a = b;
      mpz_set(tempa,tempb);
      gmp_printf("tempa = %Zd\n",tempa);
      //b = r;
      mpz_set(tempb,r);
      gmp_printf("tempb = %Zd\n",tempb);
      //x2 = x1;
      mpz_set(x2,x1);
      gmp_printf("x2 = %Zd\n",x2);
      //x1 = x;
      mpz_set(x1,x);
      gmp_printf("x1 = %Zd\n",x1);
      //y2 = y1;
      mpz_set(y2,y1);
      gmp_printf("y2 = %Zd\n",y2);
      //y1 = y;
      mpz_set(y1,y);
      gmp_printf("y1 = %Zd\n",y1);
      //gmp_printf("q = %Zd,r = %Zd,x = %Zd,y = %Zd,a = %Zd,b=%Zd\n",q,r,x,y,a,b);
    }

    //d = a;
    mpz_set(d,tempa);
    gmp_printf("d = %Zd\n",d);
    //x = x2;
    mpz_set(x,x2);
    gmp_printf("x = %Zd\n",x);
    //y = y2;
    mpz_set(y,y2);
    gmp_printf("y = %Zd\n",y);

    //printf("ax+by=d\n");
    //gmp_printf("%Zd*%Zd+%Zd*%Zd=%Zd",a,x,b,y,d);
    gmp_printf("D = %Zd\n",d);
  }

  //clear variables
  mpz_clear(tempa);
  mpz_clear(tempb);
  mpz_clear(x);
  mpz_clear(x1);
  mpz_clear(x2);
  mpz_clear(y);
  mpz_clear(y1);
  mpz_clear(y2);
  mpz_clear(r);
  mpz_clear(q);
  mpz_clear(save);
  sleep(5);
}
