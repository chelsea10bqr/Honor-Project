#include <stdint.h>
#include <stdio.h>

#include "mp5.h"
#include "mp9.h"
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

int32_t
match_requests (graph_t* g, pyr_tree_t* p, heap_t* h,
		request_t* r1, request_t* r2,
		vertex_set_t* src_vs, vertex_set_t* dst_vs, path_t* path)
{

   src_vs->count = 0;                                      /*initialize the count value before calling find_nodes*/
	  find_nodes(&(r1->from), src_vs, p, 0);
   dst_vs-> count = 0;                                    /*initialize the count value before calling find_nodes*/
		find_nodes(&(r1->to), dst_vs, p, 0 );

	trim_nodes(g,src_vs,&(r2->from));                       /*use trim_nodes to remove vertex which is out of the range for starting point and ending point*/
	trim_nodes(g,dst_vs,&(r2->to));

  return dijkstra(g,h,src_vs,dst_vs,path);               /*return dijkstra function value, whether have a shortest path*/
}
