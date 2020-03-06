#include <stdint.h>
#include <stdio.h>

#include "mp10.h"
/*introductory paragraph!!! for MP10
Writing C subroutines that manage dynamic allocation of vertex sets
andpaths, subroutines that enable,calculate and use"mini maps" based
on a high lebel of a pyramid tree, and a subroutine that attempts to find
a partner for a request among a likned list of unparired request,
Successful pairing must then be moved in to a list of paired
requests.*/
int32_t
mark_vertex_minimap (graph_t* g, pyr_tree_t* p)
{   int i,j,k,l;
  if(g->n_vertices<=64)                              /*if the number of vertices is smaller than 64,just put the index in mm_bit8*/
  {
    for(l=0;l<g->n_vertices;l++)
    {
      g->vertex[l].mm_bit=l;
    }
    return 1;
  }
    for(i=21;i<85;i++)                            /*if the number is larger than 64, use 3 for loops to get which level the leaf load is and put the value of ancestor index -21 in mm_bit */
    { int count= 1;
      for(j=4*i+1;j<p->n_nodes;j=4*j+1)
      {
          count = 4*count;
          for(k=j;k<j+count && k < p->n_nodes;k++)
              g->vertex[p->node[k].id].mm_bit=i-21;

      }
     }

    return 1;
}


void
build_vertex_set_minimap (graph_t* g, vertex_set_t* vs)      /*use 1ULL to leftshift 1 by 63-mm_bit*/
{
  int i;
  uint64_t together = 0;
  for(i=0;i<vs->count;i++)
  {
    together = 1ULL<<(63-g->vertex[vs->id[i]].mm_bit) | together; /*ORing together to get minimap */
  }
  vs->minimap = together;
}


void
build_path_minimap (graph_t* g, path_t* p)                        /* the same as vertex set*/
{
  int i;
  uint64_t together = 0;
  for(i=0;i<p->n_vertices;i++)
  {
    together = 1ULL<<(63-g->vertex[p->id[i]].mm_bit) | together;
  }
  p->minimap = together;
}


int32_t
merge_vertex_sets (const vertex_set_t* v1, const vertex_set_t* v2,
		   vertex_set_t* vint)
{
  int i,j;
  vint->count = 0;
  for(i=0;i<v1->count;i++)                              /*use for loops to check whether there are the same vertex */
  {
    for(j=0;j<v2->count;j++)
    {
      if(v1->id[i]==v2->id[j]){                       /*when we find a vertex, add it  in vint */
        vint->count++;
        vint->id[vint->count-1]=v1->id[i];
      }else if(v1->id[i]<v2->id[j])
      {
        break;
      }
    }
  }
  if(vint->count==0)                               /*if no intersection, return 0*/
  {
    return 0;
  }
    return 1;
}
