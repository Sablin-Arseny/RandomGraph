#include "WeightedGraphNode.h"

#ifndef RANDOMGRAPH_WEIGHTEDGRAPH_H
#define RANDOMGRAPH_WEIGHTEDGRAPH_H


template<typename K>
class WeightedGraph {
public:
    WeightedGraph() = default;
    WeightedGraph(const WeightedGraphNode<K> &graphNode);
    WeightedGraph(const WeightedGraph &other) = default;
    ~WeightedGraph() = default;

    bool add(const WeightedGraphNode<K> &graphNode);

    bool remove(const WeightedGraphNode<K> &graphNode);
    bool remove(const K &name);

    bool contain(const WeightedGraphNode<K> &graphNode) const;
    bool contain(const K &name) const;

    void removeAll();
    std::size_t size() const;

    bool operator==(const WeightedGraph<K> &other) const;
    bool operator<<(const WeightedGraphNode<K> &graphNode);


private:
    std::vector<WeightedGraphNode<K>> graph_;
};

template<typename K>
WeightedGraph<K>::WeightedGraph(const WeightedGraphNode<K> &graphNode) {
    graph_.push_back(graphNode);
}

template<typename K>
bool WeightedGraph<K>::add(const WeightedGraphNode<K> &graphNode) {
    if (this->contain(graphNode.getName())) {
        return false;
    }
    graph_.push_back(graphNode);
    return true;
}

template<typename K>
bool WeightedGraph<K>::remove(const K &name) {
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
bool WeightedGraph<K>::remove(const WeightedGraphNode<K> &graphNode) {
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
bool WeightedGraph<K>::contain(const K &name) const {
    for (auto &node: graph_) {
        if (node.getName() == name) {
            return true;
        }
    }
    return false;
}

template<typename K>
bool WeightedGraph<K>::contain(const WeightedGraphNode<K> &graphNode) const {
    for (auto &node: graph_) {
        if (node.getName() == graphNode.getName()) {
            return true;
        }
    }
    return false;
}

template<typename K>
void WeightedGraph<K>::removeAll() {
    graph_.clear();
}

template<typename K>
std::size_t WeightedGraph<K>::size() const {
    return graph_.size();
}

template<typename K>
bool WeightedGraph<K>::operator==(const WeightedGraph<K> &other) const {
    if (this->size() != other.size()) {
        return false;
    }
    for (auto &node: graph_) {
        if (!other.contain(node.getName())) {
            return false;
        }
    }
    return true;
}

template<typename K>
bool WeightedGraph<K>::operator<<(const WeightedGraphNode<K> &graphNode) {
    return add(graphNode);
}


#endif //RANDOMGRAPH_WEIGHTEDGRAPH_H
