#include <vector>

#ifndef RANDOMGRAPH_GRAPHNODE_H
#define RANDOMGRAPH_GRAPHNODE_H

enum GraphNodeType {
    graphNode,
    weightedGraphNode
};

template<typename K>
class GraphNode {
public:
    GraphNode() = default;
    GraphNode(const K &name);
    GraphNode(const GraphNode<K> &other) = default;
    ~GraphNode() = default;

    K getName() const;
    void setName(const K &name);

    std::size_t neighborsAmount() const;
    std::vector<GraphNode<K>> getNeighbors() const;

    bool containNeighbor(const GraphNode<K> &graphNode) const;
    bool addConnection(const GraphNode<K> &graphNode);

    bool operator==(const GraphNode<K> &other) const;

    virtual GraphNodeType identify() const;

protected:
    K name_;
    std::vector<GraphNode<K>> neighbors_;
};


template<typename K>
GraphNode<K>::GraphNode(const K &name) {
    name_ = name;
    neighbors_ = std::vector<GraphNode<K>>();
}

template<typename K>
K GraphNode<K>::getName() const {
    return name_;
}

template<typename K>
void GraphNode<K>::setName(const K &name) {
    name_ = name;
}

template<typename K>
std::size_t GraphNode<K>::neighborsAmount() const {
    return neighbors_.size();
}

template<typename K>
std::vector<GraphNode<K>> GraphNode<K>::getNeighbors() const {
    return neighbors_;
}

template<typename K>
bool GraphNode<K>::containNeighbor(const GraphNode<K> &graphNode) const {
    for (auto &neighbor : neighbors_) {
        if (neighbor == graphNode) {
            return true;
        }
    }
    return false;
}

template<typename K>
bool GraphNode<K>::addConnection(const GraphNode<K> &graphNode) {
    if (this->containNeighbor(graphNode)) {
        return false;
    }
    neighbors_.push_back(graphNode);
    return true;
}

template<typename K>
bool GraphNode<K>::operator==(const GraphNode<K> &other) const {
    if (other.name_ == name_) {
        return true;
    }
    return false;
}

template<typename K>
GraphNodeType GraphNode<K>::identify() const {
    return graphNode;
}

#endif //RANDOMGRAPH_GRAPHNODE_H
