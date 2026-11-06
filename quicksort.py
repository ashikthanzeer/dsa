def partition(L,lower,upper):
    pivot = L[lower]
    i = lower
    for j in range(lower+1,upper+1):
        if L[j]<=pivot:
            i+=1
            L[i],L[j]=L[j],L[i]
    L[lower],L[i]=L[i],L[lower]
    return i

def quicksort(L,lower,upper):
    pivot_point = partition(L,lower,upper)
    if(lower<upper):
        quicksort(L,lower,pivot_point-1)
        quicksort(L,pivot_point+1,upper)
    return L

print(quicksort([3,2,5,4,7,6,9],0,6))