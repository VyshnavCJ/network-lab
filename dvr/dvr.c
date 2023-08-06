#include<stdlib.h>
#include<stdio.h>


int main(){
    int n;
    printf("Enter the no nodes: ");
    scanf("%d",&n);
    int distance[20][20];
    printf("Enter the distance between nodes: \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           scanf("%d",&distance[i][j]);
        }
    } 

    int count=0;
    do{
        count=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(distance[i][j]>distance[i][k]+distance[k][j]){
                        distance[i][j] = distance[i][k] + distance[k][j];
                        count++;
                    }
                }
            }
        }
    }while(count!=0);

    for(int i=0;i<n;i++){
        printf("\n\nFor router %d distance to\n",i+1);
        for(int j=0;j<n;j++){
            printf("%d is %d\n",j+1,distance[i][j]);
        }
    }

}
