#include <stdint.h>
#include <stdlib.h>

#include "mp10.h"

/*introductory paragraph!!! for MP10
Writing C subroutines that manage dynamic allocation of vertex sets
andpaths, subroutines that enable,calculate and use"mini maps" based
on a high lebel of a pyramid tree, and a subroutine that attempts to find
a partner for a request among a likned list of unparired request,
Successful pairing must then be moved in to a list of paired
requests.*/
vertex_set_t*
new_vertex_set ()
{
    vertex_set_t* new = (vertex_set_t*)malloc(sizeof(vertex_set_t));      /*use malloc to return a chunk of memory to vertex set t new*/
    if(new == NULL)                                /*if allocation fails, return NULL*/
    {
      return NULL;
    }
    new->id = (int32_t*)malloc(sizeof(int32_t));              /*use malloc to dynamic allocate id filed in verrtex set t*/
      new->count = 0;                               /*initialize count to 0*/
    if(new->id==NULL)                            /* if id field is NULL, return NULL too */
    {
      free(new);
      return NULL;
    }
     return new;
}


void
free_vertex_set (vertex_set_t* vs)
{
  if(vs==NULL)                   /*if vs is NULL, just return */
  {
    return;
  }
  free(vs->id);                /*free vi->id, and vs*/
    free(vs);
}


path_t*
new_path ()
{
  path_t* new = (path_t*)malloc(sizeof(path_t));  /*use malloc to return a chunk of memory to path_t new*/
  if(new == NULL)
  {
    return NULL;
  }
  new->id = (int32_t*)malloc(sizeof(int32_t));   /*if new-> id is NULL return NULL and free new*/
  if(new->id==NULL)
  {
    free(new);
    return NULL;
  }
   return new;
}


void
free_path (path_t* path)
{
  if(path==NULL)          /*if vs is NULL, just return */
  {
    return;
  }
  free(path->id);       /*free path->id, and path */
    free(path);
}
