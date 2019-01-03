/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"



void GraphTools::initializeGraph(Graph& graph)
{
    vector<Vertex> v = graph.getVertices();
    vector<Edge> e = graph.getEdges();

    for(size_t i = 0; i < v.size(); i++) {
        graph.setVertexLabel(v[i], "UNEXPLORED");
    }

    for(size_t i = 0; i < e.size(); i++) {
        graph.setEdgeLabel(e[i].source, e[i].dest, "UNEXPLORED");
    } 
}

void GraphTools::traverseGraphDFS(Graph& graph)
{
    vector<Vertex> v = graph.getVertices();
    for(size_t i = 0; i < v.size(); i++) {
        if(graph.getVertexLabel(v[i]) == "UNEXPLORED") {
            DFS(graph, v[i]);
        }
    }
}

void GraphTools::DFS(Graph& graph, Vertex v)
{
    graph.setVertexLabel(v, "VISITED");
    vector<Vertex> av = graph.getAdjacent(v);

    for(size_t i = 0; i < av.size(); i++) {
        if(graph.getVertexLabel(av[i]) == "UNEXPLORED") {
            graph.setEdgeLabel(v, av[i], "DISCOVERY");
            DFS(graph, av[i]);
        } else if(graph.getEdgeLabel(v, av[i]) == "UNEXPLORED") {
            graph.setEdgeLabel(v, av[i], "CROSS"); //supposed to be labeled 'BACK'
        }
    }
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    initializeGraph(graph);
    vector<Vertex> startAV = graph.getAdjacent(graph.getStartingVertex());
    int w = graph.getEdgeWeight(graph.getStartingVertex(), startAV[0]);
    Vertex a = graph.getStartingVertex(), b = startAV[0];

    queue<Vertex> q;
    graph.setVertexLabel(graph.getStartingVertex(), "VISITED");
    q.push(graph.getStartingVertex());

    while(!q.empty()) {
        Vertex v = q.front();
        q.pop();

        vector<Vertex> av = graph.getAdjacent(v);
        for(size_t i = 0; i < av.size(); i++) {
            if(graph.getVertexLabel(av[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, av[i], "DISCOVERY");
                graph.setVertexLabel(av[i], "VISITED");
                q.push(av[i]);
            } else if(graph.getEdgeLabel(v, av[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, av[i], "CROSS");
            }

            if(graph.getEdgeWeight(v, av[i]) < w) {
                w = graph.getEdgeWeight(v, av[i]);
                a = v;
                b = av[i];
            }
        }
    }

    graph.setEdgeLabel(a, b, "MIN");
    return w;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    unordered_map<Vertex, Vertex> path;
    initializeGraph(graph);

    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);

    while(!q.empty()) {
        Vertex v = q.front();
        q.pop();

        vector<Vertex> av = graph.getAdjacent(v);
        for(size_t i = 0; i < av.size(); i++) {
            if(graph.getVertexLabel(av[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, av[i], "DISCOVERY");
                graph.setVertexLabel(av[i], "VISITED");
                q.push(av[i]);
                path[av[i]] = v;
            } else if(graph.getEdgeLabel(v, av[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, av[i], "CROSS");
            }
        }
    }

    int ct = 0;
    while(end != start) {
        ct++;
        graph.setEdgeLabel(end, path[end], "MINPATH");
        end = path[end];
    }
    return ct;
}

bool GraphTools::comp(Edge a, Edge b)
{
    return a.weight < b.weight;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    vector<Vertex> v = graph.getVertices();
    DisjointSets vsets;
    vsets.addelements(v.size());
    
    vector<Edge> e = graph.getEdges();
    sort(e.begin(), e.end(), comp);

    Vertex a, b;

    for(size_t i = 0; i < e.size(); i++) {
        a = e[i].source;
        b = e[i].dest;

        if(vsets.find(a) != vsets.find(b)) {
            vsets.setunion(a, b);
            graph.setEdgeLabel(a, b, "MST");
        }
    }  
}
