#include <stdio.h>
#include <stdlib.h>
#define N 9
#define unassigned 0

int FindUnassigned(int grid[N][N],int *row,int *col){
    for(*row = 0;*row < N;(*row)++){
        for(*col = 0;*col < N;(*col)++){
            if(grid[*row][*col] == unassigned)
                return 1;
        }
    }
    return 0;
}

int UsedInRow(int grid[N][N],int row,int num){
    int i;
    for(i = 0;i < N;i++){
        if(grid[row][i] == num) return 1;
    }
    return 0;
}

int UsedInCol(int grid[N][N],int col,int num){
    int i;
    for(i = 0;i < N;i++){
        if(grid[i][col] == num) return 1;
    }
    return 0;
}

int UsedInBox(int grid[N][N],int BoxStartRow,int BoxStartCol,int num){
    int i,j;
    for(i = 0;i<3;i++){
        for(j = 0;j<3;j++){
            if(grid[i+BoxStartRow][j+BoxStartCol] == num) return 1;
        }
    }
    return 0;
}

int isSafe(int grid[N][N],int row,int col,int num){
    if(UsedInRow(grid,row,num) == 0 && UsedInCol(grid,col,num) == 0 &&
       UsedInBox(grid,(row - row%3),(col - col%3),num) == 0) return 1;
    return 0;
}

int SolveSudoku(int grid[N][N]){
    int row,col;
    if(FindUnassigned(grid,&row,&col) == 0)
        return 1;
    int num;
    for(num = 1;num <= 9;num++){
        if(isSafe(grid,row,col,num) == 1){
            grid[row][col] =  num;
            if(SolveSudoku(grid) == 1) return 1;
            //backtrack here
            grid[row][col] = unassigned;
        }
    }
    return 0;
}

int printGrid(int grid[N][N]){
    int i,j;
    for(i = 0;i < N;i++){
        for(j = 0;j < N;j++){
            printf("%d ",grid[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int grid[N][N] = {
                        {0,0,0,0,0,0,4,5,6},
                        {0,0,0,0,0,0,0,0,0},
                        {0,5,0,0,4,6,0,9,2},
                        {2,8,0,7,0,0,0,0,3},
                        {6,0,0,0,1,0,5,0,0},
                        {0,0,0,0,0,8,0,0,0},
                        {0,0,0,0,0,0,3,0,0},
                        {8,0,0,9,0,4,6,0,0},
                        {0,2,0,8,0,0,0,0,1}
                    };
    if(SolveSudoku(grid) == 1)
        printGrid(grid);
    return 0;
}
