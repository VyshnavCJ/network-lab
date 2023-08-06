#include <stdio.h>
#include <string.h>

int main() {
  int count, src_router, i, j, k, w, v, min;
  int cost_matrix[100][100], dist[100], last[100];
  int flag[100];
  printf("\nEnter the no of routers: ");
  scanf("%d", &count);
  printf("\nEnter the cost matrix values: ");
  for (i = 0; i < count; i++) {
    for (j = 0; j < count; j++) {
      scanf("%d", & cost_matrix[i][j]);
      if (cost_matrix[i][j] < 0) cost_matrix[i][j] = 1000;
    }
  }

  printf("\nEnter the source router: ");
  scanf("%d", &src_router);
  for (v = 0; v < count; v++) {
    flag[v] = 0;
    last[v] = src_router;
    dist[v] = cost_matrix[src_router][v];
  }

  flag[src_router] = 1;
  for (i = 0; i < count; i++) {
    min = 1000;
    for (w = 0; w < count; w++) {
      if (!flag[w])
        if (dist[w] < min) {
          v = w;
          min = dist[w];
        }
    }
    flag[v] = 1;
    for (w = 0; w < count; w++) {
      if (!flag[w])
        if (min + cost_matrix[v][w] < dist[w]) {
          dist[w] = min + cost_matrix[v][w];
          last[w] = v;
        }
    }
  }

  for (i = 0; i < count; i++) {
    printf("\nShortest path cost from %d to %d :%d",src_router, i,dist[i]);
  }
}

