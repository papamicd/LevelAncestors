#include "../la_algorithm.h"

#if LA_ALGORITHM == MENGHANI_MATANI

  #include "menghani_matani.h"

  /************************************************************************/
  /* Preprocessing						*/
  /************************************************************************/
  void menghani_matani_preprocessing(){

      depth_arr = alloc(n * sizeof(int*));
      depth_metaarray_val = alloc(n * sizeof(int*));
      depth_metaarray_pos = alloc(n * sizeof(int*));

      int d, curr_pos, meta_spaces_left, remaining_nodes;

      // Allocate all of the depth arrays so there is no wasted space
      for(d = 0; d < n; d++){
          
          if(depth_size[d] < 1) break;

          depth_arr[d] = alloc(depth_size[d] * sizeof(int));

          if(depth_size[d] >= SQRT_SEARCH_MINIMUM){
            depth_meta_size[d] = (int)ceil(sqrt((double)depth_size[d]));
            depth_metaarray_val[d] = alloc(depth_meta_size[d] * sizeof(int));
            depth_metaarray_pos[d] = alloc(depth_meta_size[d] * sizeof(int));
          }
      }

      // Fill depth arrays
      for(int i = 0; i < n; i++){

        d = tree[i].depth;
        
        // If depth size is not large enough to benefit from enhanced binary search, then just store it regularly
        if(depth_size[d] < SQRT_SEARCH_MINIMUM){
          depth_arr[d][depth_count[d]] = i;
        }
        else{
          // Current position in depth array is calculated from several variables instead of just depth_count[d]
          // (this is because we don't want to have to do slow sqrt and modulo operations on each number to check if that index is in metaarray)
          curr_pos = (depth_meta_count[d] * depth_meta_size[d]) + depth_count[d];

          depth_arr[d][curr_pos] = i;

          // We've reached the sqrt(depth_size[d]) node, add it to meta array
          if(depth_count[d] == depth_meta_size[d] - 1){

            // Move to first available index in meta array
            while(depth_metaarray_val[d][depth_meta_count[d]] != 0) depth_meta_count[d]++;

            // Store node value and depth array position in metaarrays
            depth_metaarray_val[d][depth_meta_count[d]] = i;
            depth_metaarray_pos[d][depth_meta_count[d]++] = curr_pos;

            // Reset depth_count for this depth (it will be incremented after this if-else statement)
            depth_count[d] = -1;

          }
          else{
            meta_spaces_left = depth_meta_size[d] - depth_meta_count[d];
            remaining_nodes = depth_size[d] - curr_pos;

            if(meta_spaces_left >= remaining_nodes){
              // metaarray was not a size that gave a clean sqrt value so we must fill it in with last main depth array nodes
              depth_metaarray_val[d][depth_meta_size[d] - remaining_nodes] = i;
              depth_metaarray_pos[d][depth_meta_size[d] - remaining_nodes] = curr_pos;
            }

          }

        }

        depth_count[d]++;
      }

      free(depth_count);
      free(depth_meta_count);
  }
  /************************************************************************/

  /************************************************************************/
  /* Querying						*/
  /************************************************************************/

  // Meta binary search figures out a general idea of where to start the binary search.
  // Modifies the l and r pointers to indices of a partition of the main depth_arr
  void meta_binary_search(int d, int* l, int* r, int goal, int max){

      if (*r >= *l) { 

          int mid = *l + (*r - *l) / 2; 
      
          // The level ancestor answer was a metaarray value so just set L and R to be it's position
          if (depth_metaarray_val[d][mid] == goal){
          *l = depth_metaarray_pos[d][mid];
          *r = depth_metaarray_pos[d][mid];
          return;
          }
      
          if ((max < 0 || depth_metaarray_val[d][mid] > depth_metaarray_val[d][max])
          && depth_metaarray_val[d][mid] < goal){
          max = mid;
          }
          
          if (depth_metaarray_val[d][mid] > goal){
          *r = mid - 1;
          }
          
          else  
          *l = mid + 1;
          
          meta_binary_search(d, l, r, goal, max); 
      } 
      else{
          // Set the left and right pointers to the position of node with the max value less than the goal value
          *l = *r = depth_metaarray_pos[d][max];

          // If this value isn't the last value in the meta array, 
          // then set the right pointer so we only binary search a partition of the main depth_arr
          if(max + 1 < depth_meta_size[d]) *r = depth_metaarray_pos[d][max + 1];
      }
    
  }

  // Binary search looking for the goal value or the greatest value less than the goal value
  int binary_search(int d, int l, int r, int goal, int max){

      if (r >= l) { 
          int mid = l + (r - l) / 2; 
    
          if (depth_arr[d][mid] == goal){
            return depth_arr[d][mid];
          }   
    
          if (depth_arr[d][mid] > max && depth_arr[d][mid] < goal){
            max = depth_arr[d][mid];
          }
              
          if (depth_arr[d][mid] > goal){
            return binary_search(d, l, mid - 1, goal, max); 
          }
    
          return binary_search(d, mid + 1, r, goal, max); 
      } 
      
      return max; 
  }

  int menghani_matani_query(int query_node, int query_level){

    int l, r;

    if(tree[query_node].depth == query_level){
      query_answer = query_node;
    }
    else{
      
      l = 0;
      r = depth_size[query_level];

      if(r >= SQRT_SEARCH_MINIMUM){

        r = depth_meta_size[query_level] - 1;

        meta_binary_search(query_level, &l, &r, (query_node - 1), -1);
      }

      query_answer = binary_search(query_level, l, r, (query_node - 1), -1);
    }

    return query_answer;
  }
  /************************************************************************/
#endif