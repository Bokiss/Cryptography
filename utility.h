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
    printf("Random\n");
  }while(mpz_sizeinbase(random,2) < 512); //accept only 512bit randoms
  
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