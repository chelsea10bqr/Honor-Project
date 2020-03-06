#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"

#define MY_INFINITY   1000000000
/*introductory paragraph!!!!!!!!!!!!!
implement a request
matching and pathfinding subroutines for a
tool that helps people to find walking partners.
In particular,  writing C subroutines
that identify possible starting and ending
points and that find the shortest path between
any pair of starting and ending points. For this
purpose,  use of a ‘pyramid tree’
and write code to implement a heap for use by
Dijkstra’s
single-source
shortest-paths
algorithm.
*/


void
find_nodes (locale_t* loc, vertex_set_t* vs, pyr_tree_t* p, int32_t nnum)
{
    // Do not modify the following line nor add anything above in the function.
    record_fn_call ();
    if(vs->count==0)
    {
      int32_t* copy;
      copy = (int32_t*)malloc(sizeof(int32_t));
      if(copy == NULL)
      {
        return;
      }
      vs->id = copy;
      vs->id_array_size = 1;
    }
    if( nnum >= p->n_nodes)                   /*the stooping condition*/
    {
      return;
    }
    if(4*nnum+1>=p->n_nodes)                                                 /*if 4*num+1 is greater than the number of nodes, it is a leaf node*/
    {
      if(in_range(loc, p->node[nnum].x,p->node[nnum].y_left)==1)           /*check if it is in the range of locale. if it is, count add1, written the index value into vertex_set_t  */
      {
        vs->count = vs->count + 1;
        if(vs->count > vs-> id_array_size)
        {
          int32_t* copy_1;
          copy_1 = (int32_t*)realloc(vs->id, 2*vs->id_array_size*sizeof(int32_t));
          if(copy_1 == NULL)
          {
            return;
          }
          vs->id = copy_1;
          vs->id_array_size=2*vs->id_array_size;
        }

        vs->id[vs->count-1] = p->node[nnum].id;
      }
            return;
    }

    int32_t left = loc->x-loc->range;                                          /*get the boundary of the range*/
    int32_t right = loc->x + loc->range;
    int32_t down = loc->y + loc-> range;
    int32_t up = loc->y - loc->range;
    if (right >= p->node[nnum].x) {                                           /*check some situations for recursion to find_nodes in four quadrant*/
        if (up <= p->node[nnum].y_right)
            find_nodes(loc,vs,p,4*nnum+2);
        if (down >= p->node[nnum].y_right)
            find_nodes(loc,vs,p,4*nnum+4);
    }
    if (left <= p->node[nnum].x) {
        if (up <= p->node[nnum].y_left)
            find_nodes(loc,vs,p,4*nnum+1);
        if (down >= p->node[nnum].y_left)
            find_nodes(loc,vs,p,4*nnum+3);
    }
    int i,j;
    for(i=0;i<vs->count-1;i++)
    {
      for(j=0;j<vs->count-1-i;j++)
      {
        if(vs->id[j]>vs->id[j+1])
        {
          int temp = vs->id[j];
          vs->id[j]=vs->id[j+1];
          vs->id[j+1]=temp;
        }
      }
    }

}


void
trim_nodes (graph_t* g, vertex_set_t* vs, locale_t* loc)
{
  int32_t i;
      for (i = 0; i<vs->count; i++){                                                                        /*checkt whether the vertex is in other requests' range*/
        while (vs->count>i&&(!(in_range(loc,g->vertex[vs->id[i]].x,g->vertex[vs->id[i]].y)))){              /*use while to remove the vertex in place and decrease the count*/
          vs->id[i] = vs->id[vs->count-1];
          vs->count --;
        }
      }
}

int32_t
dijkstra (graph_t* g, heap_t* h, vertex_set_t* src, vertex_set_t* dest,                     /*this dijkstra main fucntion use following subroutines to realize dijkstra algorithm*/
          path_t* path)
{

  if (!src->count || !dest->count)                                                      /* if src and dest is empty set, return 0*/
  {
          return 0;
  }
    h->n_elts = 0;
    int32_t i,final_idx;
    for (i = 0; i<g->n_vertices; i++){
      g->vertex[i].heap_id = -1;                                                       /*give the value -1 to the index for meaning less*/
      g->vertex[i].pred = -1;
      g->vertex[i].from_src = 0;
      g->vertex[i].processed = 0;
    }
    for (i = 0; i< src->count; i++){                                                 /*use for loop to insert distance into heap*/
      insert (src->id[i],g,h);
    }
    while ((final_idx=process(g,h,dest))==-1);

    path->tot_dist = g->vertex[final_idx].from_src;
    int32_t tmp_idx = final_idx;
    path->n_vertices = 0;
    int size = 0
    while (tmp_idx != -1) {                                                        /*  check whether nodes exceed MAX_PATH_LENGTH*/
        if (path->n_vertices == 0)
            {  int32_t* copy;
              copy = (int32_t*)malloc(sizeof(int32_t));
              if(copy == NULL)
              {
                return 0;
              }
              paht->id = copy;
               size = 1;
            }
            path->n_vertices++;
            if(path->n_vertices > size)
            {
              int32_t* copy_1;
              copy_1 = (int32_t*)realloc(path->id, 2*size*sizeof(int32_t));
              if(copy_1 == NULL)
              {
                return 0;
              }
              path->id = copy_1;
              size=2*size;
            }
        path->id[path->n_vertices-1] = tmp_idx;

        tmp_idx = g->vertex[tmp_idx].pred;
    }

    return 1;
}

void insert (int32_t idx, graph_t* g, heap_t* h)                                     /*use a subroutine to insert a vertex in to the last index of the heap array*/
{
    h->elt[h->n_elts] = idx;
    g->vertex[idx].heap_id = h->n_elts;
    h->n_elts ++;

}

int32_t pop_out (graph_t* g, heap_t* h)                                             /*use a sburoutine to pop out the top vertex in the tree*/
{
    int32_t temp_index,i;
    int32_t min = MY_INFINITY;
    for (i = 0; i<h->n_elts; i++){
      if (g->vertex[h->elt[i]].from_src<min){
        min = g->vertex[h->elt[i]].from_src;
        temp_index = i;
      }
    }
    int32_t temporary;                                                              /*initialize a temporary to store the value in heap array*/
    temporary = h->elt[temp_index];
    h->elt[temp_index] = h->elt[h->n_elts-1];
    h->elt[h->n_elts-1] = temporary;
    h->n_elts--;
    g->vertex[h->elt[h->n_elts]].heap_id = -1;
    g->vertex[h->elt[temp_index]].heap_id = temp_index;
    return h->elt[h->n_elts];
}

int32_t process (graph_t* g, heap_t* h, vertex_set_t* dest)                         /*this function is used to get a node from the heap array, and put it's neighbor */
{
    int32_t idx = pop_out(g,h);                                                     /*in the heap array, if this neighbor has been viewed, skip it.*/
    if (in_dest (g,idx,dest))
      return idx;
    g->vertex[idx].processed = 1;
    int32_t i;
    for (i=0; i<g->vertex[idx].n_neighbors; i++){
      int32_t nei_idx = g->vertex[idx].neighbor[i];
      if(g->vertex[nei_idx].processed)
        continue;
      if (update(g,h,idx,i)){
        g->vertex[nei_idx].pred = idx;
      }
    }
    return -1;
}

int in_dest (graph_t* g, int32_t idx, vertex_set_t* dest)                        /*this function  is used for checking whether the vertex in the destination vertex set*/
{
    int32_t i;
    for (i=0; i< dest->count; i++){
      if (idx==dest->id[i])
        return 1;
    }
    return 0;
}

int update (graph_t* g, heap_t* h, int32_t curr_idx, int32_t nei_arr_idx)                          /*this fuction is to update the newset shortest path from starting point to*/
{
    int32_t new_dist = g->vertex[curr_idx].from_src+g->vertex[curr_idx].distance[nei_arr_idx];     /*one of its neighbor */
    int32_t nei_idx = g->vertex[curr_idx].neighbor[nei_arr_idx];
    if (g->vertex[nei_idx].heap_id==-1){
      g->vertex[nei_idx].from_src = new_dist;
      insert (nei_idx,g,h);
      return 1;
    }
    else if (g->vertex[nei_idx].from_src>new_dist){
      g->vertex[nei_idx].from_src = new_dist;
      return 1;
    }
    else{
      return 0;
 }
}
