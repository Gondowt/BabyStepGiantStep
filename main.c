#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int partition(int **tableau, int p, int r) {
    int pivot = tableau[p][1], i = p-1, j = r+1;
    int* temp;
    while (1) {
        do
            j--;
        while (tableau[j][1] > pivot);
        do
            i++;
        while (tableau[i][1] < pivot);
        if (i < j) {
            temp = tableau[i];
            tableau[i] = tableau[j];
            tableau[j] = temp;
        }
        else
            return j;
    }
}

void quickSort(int **tableau, int p, int r) {
    int q;
    if (p < r) {
        q = partition(tableau, p, r);
        quickSort(tableau, p, q);
        quickSort(tableau, q+1, r);
    }
}

int modpow(int base, int exp, int m) {

    int result = 1;

    while (exp > 0) {
        if ((exp & 1) > 0) result = (result * base) % m;
        exp >>= 1;
        base = (base * base) % m;
    }

    return result;

}

int indexOfArray(int** array,int elem,int borninf,int bornsup){

    int m=(borninf+bornsup) / 2;

    if(array[m][1]==elem)
        return array[m][0];
    else if(bornsup <= borninf)
        return -1;
    else if(elem<array[m][1])
        return indexOfArray(array,elem,borninf,m-1);
    else
        return indexOfArray(array,elem,m+1,bornsup);


}


int main(int argc, char* argv[]){
    int generator = atoi(argv[1]);
    int groupSize = atoi(argv[2]);
    int value = atoi(argv[3]);

    double giantStepDouble = sqrt((double) (groupSize - 1));
    int giantStep = (giantStepDouble - ((int) giantStepDouble) > 0) ? ((int) giantStepDouble) + 1 : ((int) giantStepDouble);


    int** left = (int**) malloc(sizeof(int*) * giantStep);
    int right = value;
    int negativePow = modpow(generator,groupSize-1-giantStep,groupSize);
    int find = 0;
    int i = 1;

    left[0] = (int*) malloc(sizeof(int) * 2);
    left[0][0] = 0;
    left[0][1] = 1;

    for(i = 1; i < giantStep; i++){
        left[i] = (int*) malloc(sizeof(int) * 2);
        left[i][0] = i;
        left[i][1] = (left[i-1][1]*generator)%groupSize;
    }

    quickSort(left, 0, giantStep-1);

    int res = indexOfArray(left, right, 0, giantStep-1);

    for(i = 1; i < giantStep; i++){
        right = (right*negativePow)%groupSize;
        res = indexOfArray(left, right, 0, giantStep-1);
        if(res != -1){
            printf("%d\n", giantStep*i+res);
        }
    }
}
