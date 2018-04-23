struct public_key
{
	mpz_t n,e;
};
struct private_key
{
	mpz_t d,n;
};