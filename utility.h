#define maxNumber 18446744073709551615
#define range 64
#define primeTestRepeats 50
gmp_randstate_t state;

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
void generateRandomBits(mpz_t random,unsigned long int maxBit)
{
  do
  {
    mpz_urandomb(random, state, maxBit);
    //printf("Random\n");
  }while(mpz_sizeinbase(random,2) < maxBit); //accept only maxBit randoms
  
    //gmp_printf("Random spec.Bits = %Zd\n", random);
}
void generateRandominRange(mpz_t random,mpz_t max)
{
  mpz_urandomm(random, state, max);
    //gmp_printf("Random in Range = %Zd\n", random);
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
    gmp_printf("String->Int : %Zd",temp);
  }
  mpz_clear(temp);
}
void inttostring(struct Node** head,char *string)
{

}
// 2.143
void RSMA(mpz_t a,mpz_t b,mpz_t n,int *k,int size)
{
  int i=1;
  mpz_t tempA,temp;

  mpz_init(tempA);
  mpz_init(temp);


  //if k = 0 return b=1
  /*
  if( mpz_cmp_d(k,0) == 0)
  {
    mpz_set_d(b,1);
    return;
  }
  */
  //set b = 1
  mpz_set_d(b,1);
  //set A = a
  mpz_set(tempA,a);

  // if k0 = 1 set b = a
  if( k[0] == 1)
  {
    mpz_set(b,a);
  }
  for(int i=1;i<=size;i++)
  {
    // A  = A^2 ;
    mpz_mul(tempA,tempA,tempA);
    // A = A mod n
    mpz_mod(tempA,tempA,n);
    if( k[i] == 1)
    {
      mpz_mul(temp,tempA,b);
      mpz_mod(b,temp,n);
    }
  }

}
mpz_t* convert(mpz_t *dec)
{
  mpz_t temp,tempb,tempc;
  mpz_t *p;
  mpz_init(temp);
  mpz_init(tempb);
  mpz_init(tempc);

  if ( mpz_cmp_d(*dec,1) == 0)
  {
    printf("dec = 0\n");
    mpz_set_d(*dec,0);
    return dec;
  }
  else
  {
    printf("1\n");
    mpz_set(temp,*dec);
    printf("2\n");
    mpz_mod_ui(temp,temp,2);
    printf("3\n");
    mpz_set_d(tempb,2);
    printf("4\n");
    mpz_cdiv_q(*dec,*dec,tempb);
    gmp_printf("DEC = %Zd\n",dec);
    printf("5\n");
    sleep(0.8);
    convert(dec);
    mpz_mul_ui(*dec,*dec,10);
    printf("6\n");
    mpz_add(tempc,temp,*dec);
    printf("7\n");
    p = &tempc;
    return p;
  }
}
void tobinary(mpz_t random, int *binary)
{
  int tempd;
  unsigned long int mod;
  int i=0;
  mpz_t temp;
  mpz_init(temp);
  //printf("1\n");
  while( mpz_cmp_d(random,1) > 0)
  {
    //printf("while\n");
  //gmp_printf("Random = %Zd\n",random);
    mod = mpz_mod_ui(temp,random,2);
    //printf("MOD = %lu\n",mod);
    //gmp_printf("TEMP = %Zd\n",temp);
    //printf("while2\n");
    //tempd = mpz_get_d(temp);
    binary[i] = (int) mod;
    //printf("while3\n");
    mpz_set_d(temp,2);
    //round towards -infinity
    mpz_fdiv_q(random,random,temp);

    i++;
  }
  printf("\n=========\n");
  binary[i]=1;
  for (int j = 0; j <= i; j++)
  {
      printf("%d",binary[j]);
  }
  printf("\n");
  return;
}
void extendedEuclidean(mpz_t a,mpz_t b,mpz_t d,mpz_t x,mpz_t y)
{
  gmp_printf("A = %Zd\n",a);
  mpf_t tempA,tempB,q,x1,x2,y1,y2,r,temp,tempx,tempy;
  //set default precision
  mpf_set_default_prec(36);
  //init variables
  mpf_init(tempA);
  mpf_init(tempB);
  mpf_init(q);
  mpf_init(x1);
  mpf_init(x2);
  mpf_init(y1);
  mpf_init(y2);
  mpf_init(r);
  mpf_init(temp);
  mpf_init(tempx);
  mpf_init(tempy);

  mpf_set_z(tempA,a);
  gmp_printf("TEMPA = %Zf\n",tempA);
  mpf_set_z(tempB,b);
  mpf_set_z(tempx,x);
  mpf_set_z(tempy,y);
  printf("vars seted\n");
  //Step 1 if b = 0 
  if( mpf_cmp_d(tempB,0) == 0 )
  {
    printf("tempb = 0\n");
    mpz_set(d,a);
    //x=1 y=0;
    return;
  }

  //Step 2 x2 = 1 y1=1
  printf("1\n");
  mpf_set_d(x2,1);
  printf("1\n");
  mpf_set_d(y1,1);
  printf("1\n");
  //Step 3 while b>0
  while( mpf_cmp_d(tempB,0) > 0)
  {
    //3.1
    // q = a/b
    printf("1\n");
    mpf_div(q,tempA,tempB);
    gmp_printf("Q = %Zf\n",q);
    // temp = q*b
    mpf_mul(temp,q,tempB);
    // r = a - temp;
    mpf_sub(r,tempA,temp);
    gmp_printf("R = %Zf\n",r);
    // temp = q*x1
    mpf_mul(temp,q,x1);
    // x = x2 - temp
    mpf_sub(tempx,x2,temp);
    gmp_printf("X = %Zf\n",tempx);
    // temp = q * y1
    mpf_mul(temp,q,y1);
    //y = y2 - temp
    mpf_sub(tempy,y2,temp);
    gmp_printf("Y = %Zf\n",tempy);
    //3,2
    // a = b
    mpf_set(tempA,tempB);
    // b = r
    mpf_set(r,tempB);
    //x2 = x1
    mpf_set(x2,x1);
    //x1 = x
    mpf_set(x1,tempx);
    //y1 = y1
    mpf_set(y2,y1);
    //y1 = y
    mpf_set(y1,tempy);    
    sleep(1);
  }
  //Step 4
  gmp_printf("F,D = %Zf\n",tempA);
  mpz_set_f(d,tempA);
  gmp_printf("Z,D = %Zd\n",d);
  mpz_set_f(x,x2);
  mpz_set_f(y,y2);
  return;

}