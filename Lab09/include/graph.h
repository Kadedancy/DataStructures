#pragma once
#include <iostream>
#include <map>
#include <stdexcept>
#include <sstream>
#include <vector>

template<typename N, typename E>
class Graph {
private:
    std::map<N, std::map<N, E>> graph;

public:
    /// <summary>
    /// add node to graph
    /// </summary>
    void addNode(const N& node)
    {
        graph[node] = std::map<N, E>();
    }

    /// <summary>
    /// Add an edge between two nodes
    /// </summary>
    void addEdge(const N& start, const N& dest, const E& val)
    {
        graph[start][dest] = val;
    }

    /// <summary>
    /// Check if the graph contains a node
    /// </summary>
    bool containsNode(const N& node) {
        for (auto it = std::begin(graph); it != std::end(graph); ++it)
        {
            if (it->first == node)
            {
                return true;
            }
        }
        return false;
    }

    /// <summary>
    /// Check if the graph contains an edge
    /// </summary>
    bool containsEdge(const N& start, const N& dest)
    {
        for (auto it = std::begin(graph); it != std::end(graph); ++it)
        {
            if (it->first == start)
            {
                for (auto inner_it = std::begin(it->second); inner_it != std::end(it->second); ++inner_it)
                {
                    if (inner_it->first == dest)
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    /// <summary>
    /// Remove a node from the graph
    /// </summary>
    void removeNode(const N& node) 
    {
        graph.erase(node);
        for (auto it = std::begin(graph); it != std::end(graph); ++it)
        {
            it->second.erase(node);
        }
    }

    /// <summary>
    /// Remove an edge between two nodes
    /// </summary>
    void removeEdge(const N& start, const N& dest) {
        for (auto it = std::begin(graph); it != std::end(graph); ++it)
        {
            if (it->first == start)
            {
                it->second.erase(dest);
            }
        }
    }

    /// <summary>
    /// Get the weight of an edge between two nodes
    /// </summary>
    E getEdge(const N& start, const N& dest)
    {
        if (!containsEdge(start, dest))
        {
            throw std::runtime_error("Edge not found");
        }
        return graph[start][dest];
    }

    /// <summary>
    /// Get all neighbors of a node
    /// </summary>
    std::map<N, E> getNeighbors(const N& node)
    {
        if (!containsNode(node))
        {
            throw std::runtime_error("Node not found");
        }
        return graph[node];
    }

    /// <summary>
    /// Get all nodes in the graph
    /// </summary>
    std::vector<N> getNodes()
    {
        std::vector<N> nodes;
        for (auto it = std::begin(graph); it != std::end(graph); ++it)
        {
            nodes.push_back(it->first);
        }
        return nodes;
    }

    /// <summary>
    /// << operator overload to print the graph in adjacency list style
    /// </summary>
    friend std::ostream& operator<<(std::ostream& os, const Graph<N, E>& g)
    {
        for (auto it = std::begin(g.graph); it != std::end(g.graph); ++it)
        {
            os << it->first << " | ";
            for (auto inner_it = std::begin(it->second); inner_it != std::end(it->second); ++inner_it)
            {
                os << "(" << inner_it->first << ":" << inner_it->second << ") ";
            }
            os << std::endl;
        }
        return os;
    }
};

