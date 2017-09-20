#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


void get_next_element_idx(int top_left_row, int top_left_col, 
                          unsigned int max_row, unsigned int max_col, unsigned int rotate_by, 
                          unsigned int *row, unsigned int *col) {
    unsigned int curr_rotate = rotate_by;
    unsigned int prev_rotate = curr_rotate;
    int i = *row;
    int j = *col;
    while(curr_rotate > 0) {
        if(i >= top_left_row && j == top_left_col && i < max_row) {
            int curr_i = i;
            i = i + curr_rotate;
            if(i > max_row) {
                curr_rotate -= (max_row - curr_i);
                i = max_row;                
            } else {
                break;
            }
        }
        if(i == max_row && j < max_col) {
            int curr_j = j;
            j = j + curr_rotate;
            if(j > max_col) {
                curr_rotate -= (max_col - curr_j);
                j = max_col;
            } else {
                break;
            }
        }
        if(j == max_col && i <= max_row && i > top_left_row) {
            int curr_i = i;
            i = i - curr_rotate;
            if(i < top_left_row) {
                curr_rotate -= (curr_i - top_left_row);
                i = top_left_row;
            } else {
                break;
            }
        }
        if(i == top_left_row && j <= max_col && j > top_left_col) {
            int curr_j = j;
            j = j - curr_rotate;
            if(j < top_left_col) {
                //error too many rotates
                curr_rotate -= (curr_j - top_left_col);
                j = top_left_col;
            } else {
                break;
            }                   
        }
        if(prev_rotate == curr_rotate) {
            //infinite loop
            printf("infinite loop\n");
            break;
        }
        prev_rotate = curr_rotate;
    }
    *row = i;
    *col = j;
    return;
}

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    unsigned int n = 0; //cols
    unsigned int m = 0; //rows
    unsigned int r = 0; //rotate by
    unsigned int row_num = 0;
    unsigned int col_num = 0;
    
    scanf("%d %d %d\n", &m, &n, &r);
    
    unsigned int matrix[m][n];
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d ", &matrix[i][j]);
        }
        scanf("\n");
    }
    
    //outermost row and col
    unsigned int elem_size;
    
    unsigned int rotate_by;
    
    unsigned int temp = 0;
    
    int top_left_row = 0;
    int top_left_col = 0;
    int max_row = m - 1;
    int max_col = n - 1;       
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int curr_element;
    unsigned int next_element;
    

    while((max_row - top_left_row) >= 1 && (max_col - top_left_col) >= 1) {
        elem_size = (max_row - top_left_row + max_col - top_left_col)*2;
        
        if(elem_size == 0) {
            break;
        }
        rotate_by = r%elem_size;
        if(rotate_by == 0) {
            top_left_row++;
            top_left_col++;
            max_row -= 1;
            max_col -= 1;
            continue;
        }
        /*if(elem_size%rotate_by == 0) {
            skip_index = elem_size/rotate_by;
            printf("0. skip_index=%d\n", skip_index);
        } else {
            skip_index = 0;
        }*/
        i = top_left_row;
        j = top_left_col;
        curr_element = matrix[i][j];
        int start_i = i;
        int start_j = j;
        int k = 0;
        while(k < elem_size) {
            k++;
            get_next_element_idx(top_left_row, top_left_col, max_row, max_col, rotate_by, &i, &j);            
            next_element = matrix[i][j];
            matrix[i][j] = curr_element;
            curr_element = next_element;
            
            if(i == start_i && start_j == j) {                
                //take next element
                get_next_element_idx(top_left_row, top_left_col, max_row, max_col, 1, &i, &j);
                curr_element = matrix[i][j];
                start_i = i;
                start_j = j;
            }
        }
        top_left_row++;
        top_left_col++;
        max_row -= 1;
        max_col -= 1;
    }
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
