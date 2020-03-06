#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "mp5.h"
#include "mp10.h"


//
// These variables hold the heads of two singly-linked lists of
// requests.
//
// The available list consists of unpaired requests: partner
// should be NULL, and next is used to form the list.
//
// The shared list consists of groups with non-empty start and end
// vertex intersections.  Only one of the requests in the group is in
// the list.  The others are linked through the first's partner field
// and then through the next field of the others in the group.  The
// next field of the first request in a group is used to form the
// shared list.
//
// Note: for MP2, you should only build groups of two in the shared
// list.
//
/*introductory paragraph!!! for MP10
Writing C subroutines that manage dynamic allocation of vertex sets
andpaths, subroutines that enable,calculate and use"mini maps" based
on a high lebel of a pyramid tree, and a subroutine that attempts to find
a partner for a request among a likned list of unparired request,
Successful pairing must then be moved in to a list of paired
requests.*/
static request_t* available = NULL;
static request_t* shared = NULL;


int32_t
handle_request (graph_t* g, pyr_tree_t* p, heap_t* h, request_t* r)
{
  r->partner = NULL;
  r->src_vs = new_vertex_set ();                       /*malloc location*/
  r->dst_vs = new_vertex_set ();
  r->path = new_path ();
  if(r->src_vs==NULL||r->dst_vs==NULL||r->path==NULL)   /*if it is fails, just free*/
  {
    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    free_path(r->path);
    return 0;
  }
  find_nodes(&(r->from),r->src_vs,p,0);
  find_nodes(&(r->to),r->dst_vs,p,0);
  if(r->src_vs->count == 0 || r->dst_vs->count == 0)
  {
    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    free_path(r->path);
    return 0;
  }
  mark_vertex_minimap (g, p);
  build_vertex_set_minimap (g, r->src_vs);
  build_vertex_set_minimap (g, r->dst_vs);
  vertex_set_t* match_from = new_vertex_set();
  vertex_set_t* match_to = new_vertex_set();
  match_from->id_array_size = r->src_vs->count;
  match_to->id_array_size= r->dst_vs->count;
  int32_t* temp = (int32_t*)malloc(match_from->id_array_size * sizeof(int32_t));
  if(temp== NULL)
  {
    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    free_path(r->path);
    free_vertex_set(match_from);
    free_vertex_set(match_to);
    return 0;
  }
  int32_t* temp_1 = (int32_t*)malloc(match_to->id_array_size * sizeof(int32_t));
  if(temp_1== NULL)
  {
    free_vertex_set(r->src_vs);
    free_vertex_set(r->dst_vs);
    free_path(r->path);
    free_vertex_set(match_from);
    free_vertex_set(match_to);
    free(temp);
    return 0;
  }
  match_from->id=temp;
  match_to->id=temp_1;
  request_t* new;
  for(new = available;new!=NULL;new=new->next)
  {
    if(((new->src_vs->minimap&r->src_vs->minimap)==0)||((new->dst_vs->minimap&r->dst_vs->minimap)==0))
    {
      continue;
    }
    int a,b,c;
    a=merge_vertex_sets(new->src_vs,r->src_vs,match_from);
    b=merge_vertex_sets(new->dst_vs,r->dst_vs,match_to);
    path_t* path_1= NULL;
    c=dijkstra(g,h,match_from,match_to,path_1);
    if((a&b&c)==1)
    {
      request_t* find;
      for(find = available;find->next!=NULL;find = find->next)
      {
        if(find->next == new)
        {
          find->next = new->next;
          available = find;
        }
      }
      new->path = path_1;
      r->path = path_1;
      r->partner = new;
      r->partner->partner = NULL;
      r->partner->next =NULL;
      r->next = shared;
      shared = r;
      free_vertex_set(r->src_vs);
      free_vertex_set(r->dst_vs);
      free_path(r->path);
      free_vertex_set(match_from);
      free_vertex_set(match_to);
      free(temp);
      free(temp_1);
      return 1;
    }
    if(r->partner ==NULL)
      { r->next = available;
        available =r;
        free_vertex_set(r->src_vs);
        free_vertex_set(r->dst_vs);
        free_path(r->path);
        free_vertex_set(match_from);
        free_vertex_set(match_to);
        free(temp);
        free(temp_1);
        return 1;
      }
  }
    return 0;
}


void
print_results ()
{
    request_t* r;
    request_t* prt;

    printf ("Matched requests:\n");
    for (r = shared; NULL != r; r = r->next) {
        printf ("%5d", r->uid);
	for (prt = r->partner; NULL != prt; prt = prt->next) {
	    printf (" %5d", prt->uid);
	}
	printf (" src=%016lX dst=%016lX path=%016lX\n", r->src_vs->minimap,
		r->dst_vs->minimap, r->path->minimap);
    }

    printf ("\nUnmatched requests:\n");
    for (r = available; NULL != r; r = r->next) {
        printf ("%5d src=%016lX dst=%016lX\n", r->uid, r->src_vs->minimap,
		r->dst_vs->minimap);
    }
}


int32_t
show_results_for (graph_t* g, int32_t which)
{
    request_t* r;
    request_t* prt;

    // Can only illustrate one partner.
    for (r = shared; NULL != r; r = r->next) {
	if (which == r->uid) {
	    return show_find_results (g, r, r->partner);
	}
	for (prt = r->partner; NULL != prt; prt = prt->next) {
	    if (which == prt->uid) {
		return show_find_results (g, prt, r);
	    }
	}
    }

    for (r = available; NULL != r; r = r->next) {
        if (which == r->uid) {
	    return show_find_results (g, r, r);
	}
    }
    return 0;
}


static void
free_request (request_t* r)
{
    free_vertex_set (r->src_vs);
    free_vertex_set (r->dst_vs);
    if (NULL != r->path) {
	free_path (r->path);
    }
    free (r);
}

void
free_all_data ()
{
    request_t* r;
    request_t* prt;
    request_t* next;

    // All requests in a group share source and destination vertex sets
    // as well as a path, so we need free those elements only once.
    for (r = shared; NULL != r; r = next) {
	for (prt = r->partner; NULL != prt; prt = next) {
	    next = prt->next;
	    free (prt);
	}
	next = r->next;
	free_request (r);
    }

    for (r = available; NULL != r; r = next) {
	next = r->next;
	free_request (r);
    }
}
