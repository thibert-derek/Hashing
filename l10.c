// Derek Thibert
// 07/26/2022
// 110080944

/*
Insert 10,000 keys
Size of the table = 10,000/alpha
alpha = final load factor (comes from the user)

average # of probes = total # of probes/10,000

next prime = 10,000/(10,000/alpha)

theoretical result: (1+(1/1-alpha)/2) (average number of probes in a successful search)

size of table is going to be a prime number >= 10,000/alpha

Linear Probing: h0(k) = h(k) = k mod n (n = tablesize)
hi(k) = (h(k)+i) mod n, i = 1,2,...

Quadratic Probing: h0(k) = h(k) = k mod n;s
hi(k) = (h(k)i^2) mod n, i=1,2,...

i^2 <= n -> i <= sqrt(n) (square both sides).
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 10000
// #define QSIZE 10000
clock_t start, end;

int isPrime(int);
int nextPrime(int);
int insertLinearProbe(int, int hashTable[], int);
int insertQuadraticProbe(int, int hashTable[], int);

int main(void) {
    int key;
    int i;
    srand(time(NULL));
    float loadFactor;
    int numberOfProbes = 0;
    printf(" Please print in the load factor less than 1.0: \n");
    scanf("%f", &loadFactor);

    if(loadFactor >= 1){
        printf(" Sorry, load factor must be less than 1.0.\n");
        return 0;
    }

    int listSize = (int)((SIZE)/loadFactor);
    int listSizePrime = nextPrime(listSize);

    int *hashTable = (int*)calloc(listSizePrime, sizeof(int));
    
    for (i =0; i < listSizePrime; i++){
        hashTable[i] = -1;
        // printf("%d ", i);
    }
start = clock();
    int total=0;
    for (i =0; i < SIZE; i++){
        key = rand();
        // printf("%d ", key);
        total += insertLinearProbe(key,hashTable,listSizePrime);
    }
    // printf("total: %d", total);

    printf("\n\n LINEAR PROBING\n\n");
    float practProbes;
    practProbes = (float)total / 10000;
    printf(" Practical number of probes are: %f.\n", practProbes);
    float avgNumber = (1 + 1/(1-loadFactor))/2;
    printf(" Theoretical number of probes are: %f.\n\n", avgNumber);

    int qListSize = (int)((SIZE)/loadFactor);
    int qListSizePrime = nextPrime(qListSize);
    int qKey;

    int *qHashTable = (int*)calloc(qListSizePrime, sizeof(int));
     int qTotal = 0;

    for (i =0; i < qListSizePrime; i++){
        qHashTable[i] = -1;
        // printf("%d ", i);
    }

    for (int i =0; i < SIZE; i++){
        qKey = rand();
        qTotal += insertQuadraticProbe(qKey,qHashTable,qListSizePrime);
    }

    printf("\n QUADRATIC PROBING\n\n");
    float qPracProbes;
    qPracProbes = (float)qTotal / 10000;
    printf(" Practical number of probes are: %f.\n\n", qPracProbes);
    // float qAvgNumber = ((1 + 1/(1-loadFactor))/2);
    // printf("Theoretical number of probes are: %f.\n", qAvgNumber);
    end = clock();
    double elapsedTime = (double)(end-start) / CLOCKS_PER_SEC;
    printf("\n Time it took in seconds is: %.5f\n", elapsedTime);
   
   return 0;
}

int isPrime(int n) {
    if(n == 2 || n == 3){
        return 1;
    }
    if (n == 1 || n % 2 == 0) {
        return 0;
    }
    for (int i = 3; i * i <= n; i += 2){
        if(n%i == 0){
        return 0;
        }
    }
    return 1;
}

int nextPrime(int n){
    if(n%2 == 0) {
        n++;
    }
    for (; !isPrime(n); n += 2){
        return n;
    }
}

int insertLinearProbe(int key, int hashTable[], int listSize) {
    int collisions = 0;
    int currentPos = (key) % listSize;
    int increment = 1;
    // printf("\nCurrent position = %d", currentPos);
    // printf("\nvalue at hashtable = %d", hashTable[currentPos]);
    // printf("\n%d", listSize);
    while(hashTable[currentPos] != -1){
        collisions=collisions+1;
        currentPos=currentPos+increment;
    // printf("%d ", currentPos);
        if(currentPos >= listSize){
            currentPos -= listSize;
        }
    }
    hashTable[currentPos] = key;
    // printf("%d ", collisions);
    return collisions+1;
}

int insertQuadraticProbe(int key, int hashTable[], int listSize) {
    int qcollisions = 0;
    int qcurrentPos = (key) % listSize;
    int qincrement = 1;

    while(hashTable[qcurrentPos] != -1){
        qcollisions=qcollisions+1;
        qcurrentPos = qcurrentPos+(qincrement*qincrement);
        qincrement++;
//    printf("%d ", qcollisions);
        if(qcurrentPos >= listSize){
            qcurrentPos -= listSize;
        }
    }
    hashTable[qcurrentPos] = key;
    return qcollisions + 1;
}