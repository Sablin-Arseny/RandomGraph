#include "GraphNode.h"

#ifndef RANDOMGRAPH_WEIGHTEDGRAPHNODE_H
#define RANDOMGRAPH_WEIGHTEDGRAPHNODE_H

template<typename K>
class WeightedGraphNode: public GraphNode<K> {
public:
    WeightedGraphNode() = default;
    WeightedGraphNode(const K &name);
    WeightedGraphNode(const WeightedGraphNode<K> &other) = default;
    ~WeightedGraphNode() = default;

    std::vector<int> getWeights() const;

    bool addConnection(const WeightedGraphNode<K> &weightedGraphNode, int weight);

    GraphNodeType identify() const override;

private:
    std::vector<int> weights_;
};

template<typename K>
WeightedGraphNode<K>::WeightedGraphNode(const K &name) {
    GraphNode<K>::name_ = name;
}

template<typename K>
std::vector<int> WeightedGraphNode<K>::getWeights() const {
    return weights_;
}

template<typename K>
bool WeightedGraphNode<K>::addConnection(const WeightedGraphNode<K> &weightedGraphNode, int weight) {
    if (this->containNeighbor(weightedGraphNode)) {
        return false;
    }
    GraphNode<K>::neighbors_.push_back(weightedGraphNode);
    weights_.push_back(weight);
    return true;
}

template<typename K>
GraphNodeType WeightedGraphNode<K>::identify() const {
    return weightedGraphNode;
}


#endif //RANDOMGRAPH_WEIGHTEDGRAPHNODE_H
