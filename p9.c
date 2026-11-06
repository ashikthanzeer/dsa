#include<stdio.h>

struct Poly{
    int coeff;
    int exp;
};

void main(){
    printf("Enter no of terms in 1st and 2nd curve: ");
    int n1,n2;
    scanf("%d %d",&n1,&n2);
    struct Poly A[n1],B[n2];
    printf("Enter 1st curve: \n");
    for(int i=0;i<n1;i++){
        printf("Coeff: ");
        scanf("%d",&A[i].coeff);
        printf("Exp: ");
        scanf("%d",&A[i].exp);
    }
    printf("Enter 2nd curve: \n");
    for(int i=0;i<n2;i++){
        printf("Coeff: ");
        scanf("%d",&B[i].coeff);
        printf("Exp: ");
        scanf("%d",&B[i].exp);
    }
    struct Poly multiply[n1*n2];
    int k=0;
    for(int i=0;i<n1;i++){
        for(int j=0;j<n2;j++){
            multiply[k].coeff=A[i].coeff*B[j].coeff;
            multiply[k++].exp=A[i].exp+B[j].exp;
        }
    }
    int newK=0;
    for(int i=0;i<k;i++){
        int c = 1;
        for(int j=0;j<newK;j++){
            if(multiply[j].exp==multiply[i].exp){
                    multiply[j].coeff +=multiply[i].coeff;
                    c=0;
                    break;
            }
        }
        if(c==1){
            multiply[newK].exp=multiply[i].exp;
            multiply[newK++].coeff=multiply[i].coeff;
        }
    }
    k=newK;
    newK=0;
    for(int i=0;i<k;i++){
        if(multiply[i].exp!=0){
            multiply[newK].exp=multiply[i].exp;
            multiply[newK++].coeff=multiply[i].coeff;
        }
    }
    k=newK;
    for(int i=0;i<k;i++){
        if(multiply[i].exp==0){
            printf("%d",multiply[i].coeff);
        }
        else if(multiply[i].coeff==1){
            printf("x^%d",multiply[i].exp);
        }
        else{
            printf("%dx^%d",multiply[i].coeff,multiply[i].exp);
        }
        if(i!=k-1){
            printf(" + ");
        }
    }
}