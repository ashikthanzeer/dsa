#include<stdio.h>

struct Term{
    int coeff;
    int exp;
};

int main(){
    int n;
    printf("Enter no of non-zero terms in the message: ");
    scanf("%d",&n);
    struct Term m[n];
    for(int i=0;i<n;i++){
        printf("Enter coefficient: ");
        scanf("%d",&m[i].coeff);
        printf("Enter exponent: ");
        scanf("%d",&m[i].exp);
    }
    int p;
    printf("Enter no of non-zero terms in private key: ");
    scanf("%d",&p);
    struct Term k[p];
    for(int i=0;i<p;i++){
         printf("Enter coefficient: ");
        scanf("%d",&k[i].coeff);
        printf("Enter exponent: ");
        scanf("%d",&k[i].exp);
    }
    struct Term c[n+p];
    int count=0;
    for(int i=0;i<n;i++){
        c[count]=m[i];
        count++;
    }

    for(int i=0;i<p;i++){
        int found=0;
        for(int j=0;j<count;j++){
            if(c[j].exp==k[i].exp){
                found =1;
                c[j].coeff = (c[j].coeff+k[i].coeff)%3;
                break;
            }
        }
        if(!found){
            c[count].coeff = k[i].coeff % 3;
            c[count].exp = k[i].exp;
            count++;
        }
    }
    int newCount =0;
    for(int i=0;i<count;i++){
        if(c[i].coeff!=0){
            c[newCount] = c[i];
            newCount++;
        }
    }
    count = newCount;
    struct Term temp;
    for(int i=0;i<count-1;i++){
        for(int j=0;j<count-i-1;j++){
            if(c[j].exp<c[j+1].exp){
                temp = c[j];
                c[j]=c[j+1];
                c[j+1]=temp;
            }
        }
    }
    printf("Cipher polynomial: \n");

    for(int i=0;i<count;i++){
        if(c[i].coeff!=1 && c[i].exp!=0){
        printf("%dx^%d",c[i].coeff,c[i].exp);
        }
        else if(c[i].exp==0){
            printf("%d",c[i].coeff);
        }
        else{
            printf("x^%d",c[i].exp);
        }

        if(i!=count-1){
            printf(" + ");
        }
    }

    printf("\n");
    return 0;
}