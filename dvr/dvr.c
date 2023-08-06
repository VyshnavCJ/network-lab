#include<stdlib.h>
#include<stdio.h>

struct node{
    int from[20];
    int dist[20];
}rt[20];

int main(){
    int n;
    printf("Enter the no nodes: ");
    scanf("%d",&n);
    printf("Enter the distance between nodes: \n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           scanf("%d",&rt[i].dist[j]);
           rt[i].from[j] = j;
        }
    } 

    int count=0;
    do{
        count=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                for(int k=0;k<n;k++){
                    if(rt[i].dist[j]>rt[i].dist[k]+rt[k].dist[j]){
                        rt[i].dist[j] = rt[i].dist[k]+rt[k].dist[j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    }while(count!=0);

    for(int i=0;i<n;i++){
        printf("\n\nFor router %d distance to\n",i+1);
        for(int j=0;j<n;j++){
            printf("%d is %d\n",j+1,rt[i].dist[j]);
        }
    }

}
