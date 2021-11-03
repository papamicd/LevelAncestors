#include "../la_algorithm.h"

#if LA_ALGORITHM == JUMP_LADDER

  #include "jump_ladder.h"
  #include "jump_pointer.h"
  #include "ladder.h"

  #if LA_ALGORITHM == STATIC
    /************************************************************************/
    /* Preprocessing						*/
    /************************************************************************/
    void jump_ladder_preprocessing()
    {
      jump_pointer_preprocessing();
      ladder_preprocessing();
    }
    /************************************************************************/

    /************************************************************************/
    /* Querying						*/
    /************************************************************************/
    int jump_ladder_query(int query_node, int query_level)
    {
      int i, j;
      int mydiff, mypow, mylog;

      if (query_level > tree[query_node].depth) return -1;
      if (query_level == tree[query_node].depth) return query_node;
      mydiff = tree[query_node].depth - query_level;
    /*
      mylog = log_base2((double) mydiff);
    */
      frexp((double)mydiff, &mylog);
      mylog--;
    /*
      mypow = (int) pow((double)2, (double)mylog);
    */
        mypow = 1 << mylog;
      if (mydiff == mypow)
      {
        return jump_table[query_node][mylog];
      }
      else
      {
        return ladder_query(jump_table[query_node][mylog], query_level);
      }
    }
    /************************************************************************/

  #elif LA_ALGORITHM == DYNAMIC
    /************************************************************************/
    /* Preprocessing						*/
    /************************************************************************/
    void jump_ladder_preprocessing()
    {
      jump_pointer_preprocessing();
      ladder_preprocessing();
    }
    /************************************************************************/

    /************************************************************************/
    /* Querying						*/
    /************************************************************************/
    int jump_ladder_query(int query_node, int query_level)
    {
      printf("Error: Function Not Yet Implemented!\n");
      exit(-1);

      return 0;
    }
    /************************************************************************/

    /************************************************************************/
    /* Tree Manipulation						*/
    /************************************************************************/
    void add_jump_ladder_leaf(int parent, int leaf, bool is_left_child){
      printf("Error: Function Not Yet Implemented!\n");
      exit(-1);
    }   

    void remove_jump_ladder_leaf(int leaf){
      printf("Error: Function Not Yet Implemented!\n");
      exit(-1);
    }
    /************************************************************************/
  #endif
#endif