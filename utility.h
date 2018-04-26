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
void RSMA(mpz_t a,mpz_t k,mpz_t b)
{
  mpz_t tempA;

  mpz_init(tempA);


  //if k = 0 return b=1
  if( mpz_cmp_d(k,0) == 0)
  {
    mpz_set_d(b,1);
    return;
  }

  //set A = a
  mpz_set(tempA,a);

  // if k0 = 1 ( k =1 )
  if( mpz_cmp_d(k,1) == 0 )
  {
    mpz_set(b,a);
  }
  //for(int i=1)

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
void tobinary(mpz_t random,unsigned long int  *binary)
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
  gmp_printf("Random = %Zd\n",random);
    mod = mpz_mod_ui(temp,random,2);
    printf("MOD = %lu\n",mod);
    gmp_printf("TEMP = %Zd\n",temp);
    //printf("while2\n");
    //tempd = mpz_get_d(temp);
    binary[i] = mod;
    //printf("while3\n");
    mpz_set_d(temp,2);
    //round towards -infinity
    mpz_fdiv_q(random,random,temp);

    i++;
  }
  printf("\n=========\n");
  binary[i]=1;
  for (int j = 0; j < i; j++)
  {
      printf("%lu",binary[j]);
  }
  printf("\n");
  return;
}
int convertd(int dec)

{

    if (dec == 0)

    {

        return 0;

    }

    else

    {

        return (dec % 2 + 10 * convertd(dec / 2));

    }

}