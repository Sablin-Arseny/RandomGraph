#include "GraphNode.h"
#ifndef RANDOMGRAPH_GRAPH_H
#define RANDOMGRAPH_GRAPH_H

template<typename K>
class Graph {
public:
    Graph() = default;
    Graph(const GraphNode<K> &graphNode);
    Graph(const Graph &other) = default;
    ~Graph() = default;

    bool add(const GraphNode<K> &graphNode);

    bool remove(const GraphNode<K> &graphNode);
    bool remove(const K &name);

    bool contain(const GraphNode<K> &graphNode) const;
    bool contain(const K &name) const;

    void removeAll();
    std::size_t size() const;

    bool operator==(const Graph<K> &other) const;


private:
    std::vector<GraphNode<K>> graph_;
};

template<typename K>
Graph<K>::Graph(const GraphNode<K> &graphNode) {
    graph_.push_back(graphNode);
}

template<typename K>
bool Graph<K>::add(const GraphNode<K> &graphNode) {
    if (this->contain(graphNode.getName())) {
        return false;
    }
    graph_.push_back(graphNode);
    return true;
}

template<typename K>
bool Graph<K>::remove(const K &name) {
    if (!this->contain(name)) {
        return false;
    }
    for (auto &graphNode : graph_) {
        if (graphNode.getName() == name) {
            std::swap(graphNode, graph_.back());
            graph_.pop_back();
            return true;
        }
    }
    return true;
}

template<typename K>
bool Graph<K>::remove(const GraphNode<K> &graphNode) {
    if (!this->contain(graphNode)) {
        return false;
    }
    for (auto &node : graph_) {
        if (node.getName() == graphNode.getName()) {
            std::swap(node, graph_.back());
            graph_.pop_back();
            return true;
        }
    }
    return true;
}

template<typename K>
bool Graph<K>::contain(const K &name) const {
    for (auto &node: graph_) {
        if (node.getName() == name) {
            return true;
        }
    }
    return false;
}

template<typename K>
bool Graph<K>::contain(const GraphNode<K> &graphNode) const {
    for (auto &node: graph_) {
        if (node.getName() == graphNode.getName()) {
            return true;
        }
    }
    return false;
}

template<typename K>
void Graph<K>::removeAll() {
    graph_.clear();
}

template<typename K>
std::size_t Graph<K>::size() const {
    return graph_.size();
}

template<typename K>
bool Graph<K>::operator==(const Graph<K> &other) const {
    if (this->size() != other.size()) {
        return false;
    }
    for (auto &node: graph_) {
        if (!other.contain(node)) {
            return false;
        }
    }
    return true;
}

#endif //RANDOMGRAPH_GRAPH_H
