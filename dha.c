#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define Path "C:/Users/manik/Desktop/transmission.txt"
#define MAX_ITERATIONS 50

int no_pr, proots[10], keylen, communication_index = 0;
unsigned long long int a, b, g, private_key, partner_public_key, my_public_key, common_key, seed;
char binary_buffer[8], key[MAX_ITERATIONS], message[400];

//these functions are for session creation
void DHA_for_Alice();
void DHA_for_Bob();
void generate_publickey();
void generate_commonkey();
void compute_primitive_roots();
int is_prime(unsigned long long int);
int make_a_choice();
unsigned long long int order(int);
unsigned long long int exp_mod(unsigned long long int, unsigned long long int);




//these functions are for after a session is established
void begin_symmetric_encryption();
void message_encode();
void message_decode();
void get_a_random_key();
void convert_char_to_binary(char);
int convert_binary_to_decimal(char *);
unsigned long long int get_a_random_number(int, unsigned long long int);
void simulate_delay(int);

int main()
{
    int choice;
    printf("\n\n\n\t\t\t\t-------------------------\n");
    printf("\t\t\t\t|    You are :\t\t|\n\t\t\t\t|    1. Alice\t\t|\n\t\t\t\t|    2. Bob\t\t|\n");
    printf("\t\t\t\t-------------------------\n");
    scanf("%d", &choice);
    system("cls");
    switch (choice)
    {
    case 1:
        DHA_for_Alice();
        break;
    case 2:
        DHA_for_Bob();
        break;
    default:
        printf("\n\n\tPlease enter a valid choice!\n\n\n");
        return 0;
        break;
    }
    seed = common_key;
    // seed = 352962;
    // begin_symmetric_encryption();
    return 0;
}

void DHA_for_Alice()
{
    printf("\n==================: Start of DHA :=========================\n");
    printf("Enter the prime base    :   ");
    scanf("%llu", &b);
    if (!is_prime(b))
    {
        printf("---------------------------------------------------------");
        printf("\n\nThe base entered is not a prime number !\nPlease try again.\n\n\n");
        exit(0);
    }
    compute_primitive_roots();
    system("cls");
    printf("\n===================: Start of DHA :=====================\n");
    printf("Choose a prime base  :   %llu\n", b);
    printf("The generator   :   %llu", g);
    printf("\n-----------------------< Confidential >--------------------------\n");
    printf("Enter the private key   :   ");
    scanf("%llu", &private_key);
    printf("\n-----------------------< Confidential >--------------------------\n");
    generate_publickey();
    generate_commonkey();
    printf("\n===================: End of DHA :=====================\n");
}

void DHA_for_Bob()
{
    printf("\n=================: Start of DHA :=============================\n");
    printf("Enter the prime base  :   ");
    scanf("%llu", &b);
    if (!is_prime(b))
    {
        printf("--------------------------------------------------------------------------");
        printf("\n\nThe base entered is not a prime number! Please try again.\n\n\n");
        exit(0);
    }
    printf("The generator   :   ");
    scanf("%llu", &g);
    printf("\n-----------------------< Confidential >--------------------------\n");
    printf("Enter the private key   :   ");
    scanf("%llu", &private_key);
    printf("\n-----------------------< Confidential >--------------------------\n");
    generate_publickey();
    generate_commonkey();
    printf("\n=================: End of DHA :=============================\n");
}

int is_prime(unsigned long long int n)
{
    int i;
    if (n <= 1)
        return 0;
    else if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (i = 5; i * i <= n; i += 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

void compute_primitive_roots()
{
    int i, j = 0;
    printf("----------------------------------------------------------------------");
    printf("\n\nChoice of generator under progress....\nPlease wait...\n");
    for (i = 2; i < 30 && i < b; i++)
        if (!j && i >= 15)
        {
            printf("------------------------------------------------------------------");
            printf("\nThe given prime is not suitable for the algorithm. Please enter another one.");
            printf("n----------------------------------------------------------------\n\n\n");
            exit(0);
        }
        else if (j < 4 && order(i) == (b - 1))
        {
            proots[j++] = i;
        }
    printf("\n");
    no_pr = j;
    printf("\n----------------------------------------------------------");
    printf("\nprimitive roots   :   ");
    for (i = 0; i < no_pr; i++)
    {
        printf("%d ", proots[i]);
    }
    g = proots[make_a_choice()];
    printf("\nThe generator chosen  :   %llu", g);
    printf("\n-----------------------------------------------------------\n");
}

void generate_publickey()
{
    my_public_key = exp_mod(g, private_key);
    printf("The public key generated    :   %llu", my_public_key);
}

void generate_commonkey()
{
    printf("\nThe public key received   :   ");
    scanf("%llu", &partner_public_key);
    common_key = exp_mod(partner_public_key, private_key);
    printf("the common key generated    :   %llu", common_key);
}

int make_a_choice()
{
    int x;
    srand((unsigned)time(NULL));
    x = rand();
    x %= no_pr;
    return x;
}

unsigned long long int order(int x)
{
    int ptr = 1;
    a = 0;
    while (ptr)
    {
        a++;
        if (a >= 30000000)
            break;
        if (exp_mod(x, a) == 1)
            ptr = 0;
    }
    printf("\n\"%02d\" checked.", x);
    return a;
}

unsigned long long int exp_mod(unsigned long long int base, unsigned long long int exp)
{
    unsigned long long int ans = 1;
    while (exp != 0)
    {
        if (exp % 2 == 1)
        {
            ans *= base;
            ans %= b;
        }
        base *= base;
        base %= b;
        exp /= 2;
    }
    return ans;
}

// Review 3 code follows

void begin_symmetric_encryption()
{
    // simulate_delay(5);
    int choice;
    system("cls");
    while (1)
    {
        printf("\n============= Symmetric Encryption ==================\n");
        printf("Enter your choice:\n1. \tEncryption\n2. \tDecryption\n3. \tExit\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            message_encode();
            break;
        case 2:
            message_decode();
            break;
        case 3:
            printf("=======================================================================");
            exit(0);
            break;
        default:
            printf("\nEnter a valid choice");
            break;
        }
        simulate_delay(3);
    }
}

void message_encode()
{
    int i, j = 0;
    char ch;
    FILE *fp = fopen(Path, "w");
    printf("===========: Encryption :==============\n");
    printf("Enter the message:\n");
    printf("------------------------------------------------------\n");
    scanf(" %[^\n]s", message);
    get_a_random_key();
    printf("--------------------------------------------------------------");
    printf("\nEncoded Message:\n");
    for (i = 0; message[i] != '\0'; i++)
    {
        ch = message[i] ^ key[i % (keylen / sizeof(char))];
        printf("%c", ch);
        convert_char_to_binary(ch);
        fputs(binary_buffer, fp);
        fputs("\n", fp);
    }
    printf("\n");
    printf("--------------------------------------------------------\n");
    fclose(fp);
}

void message_decode()
{
    int ctr = 0;
    FILE *fp = fopen(Path, "r");
    char ch, str[8];
    printf("===============: Decryption :===============\n");
    while (fgets(str, 9, fp) != NULL)
    {
        ch = convert_binary_to_decimal(str);
        printf("%c", ch);
        ch = ch ^ key[ctr % (keylen / sizeof(char))];
        message[ctr] = ch;
        ctr++;
    }
    printf("\n---------------------------------------------");
    printf("\nDecoded Message :\n");
    printf("%s\n", message);
    printf("---------------------------------------------\n");
    fclose(fp);
}

void get_a_random_key()
{
    int i = 0;
    a = 0;
    while (i < MAX_ITERATIONS - 1)
    {
        if (!a)
        {
            b = get_a_random_number(++communication_index, b);
            a = b;
        }
        key[i++] = a % 100;
        a /= 100;
    }
    key[i++] = a % 100;
    keylen = i;
}

unsigned long long int get_a_random_number(int i, unsigned long long int P)
{
    unsigned long long int next, result;
    seed = seed % 100000000000;
    next = seed ^ i;
    result = P;
    next <<= 7;
    next = next % 100000000000;
    result ^= next;
    result += i;
    result = result % 100000000000;
    seed = next;
    return result;
}

void convert_char_to_binary(char c)
{
    int j;
    for (j = 6; j >= 0; j--)
        binary_buffer[6 - j] = (c & (1 << j)) ? '1' : '0';
}

int convert_binary_to_decimal(char str[])
{
    int i, d = 0;
    for (i = 0; i < 7; i++)
        d += (str[i] - '0') * pow(2, (6 - i));
    return d;
}

void simulate_delay(int seconds)
{
    int ms = 1000 * seconds;
    clock_t start_time = clock();
    while (clock() < start_time + ms);
}
