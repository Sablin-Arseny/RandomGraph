#include "Graph.h"
#include "GraphNode.h"
#include "WeightedGraphNode.h"
#include "WeightedGraph.h"
#include <random>

#ifndef RANDOMGRAPH_GENERATOR_H
#define RANDOMGRAPH_GENERATOR_H
enum GraphType {
    DIRECTIONAL_WEIGHTED,
    NONDIRECTIONAL_WEIGHTED,
    DIRECTIONAL_UNWEIGHTED,
    NONDIRECTIONAL_UNWEIGHTED,
};


class Generator {
public:
    Generator() = default;
    Generator(GraphType type, int minNodes, int maxNodes, int minConnections,
              int maxConnections, int minWeights, int maxWeights);
    Generator(GraphType type, int minNodes, int maxNodes, int minConnections,
              int maxConnections);
    Generator(const Generator &other) = default;
    ~Generator() = default;

    GraphType getGraphType() const;
    std::pair<int, int> getNodesInterval() const;
    std::pair<int, int> getConnectionsInterval() const;
    std::pair<int, int> getWeightsInterval() const;

    void setGraphType(GraphType type);
    bool setNodesInterval(int minNodes, int maxNodes);
    bool setConnectionsInterval(int minConnections, int maxConnections);
    bool setWeightsInterval(int minWeights, int maxWeights);

    Graph<int> generate() const;
    WeightedGraph<int> generateWeighted() const;

private:
    GraphType type_ = NONDIRECTIONAL_UNWEIGHTED;

    int minNodes_;
    int maxNodes_;

    int minConnections_;
    int maxConnections_;

    int minWeights_;
    int maxWeights_;
};

Generator::Generator(GraphType type, int minNodes, int maxNodes, int minConnections,
                     int maxConnections, int minWeights, int maxWeights) {
    if (type == DIRECTIONAL_UNWEIGHTED || type == NONDIRECTIONAL_UNWEIGHTED) {
        throw;
    }
    type_ = type;
    minNodes_ = minNodes;
    maxNodes_ = maxNodes;
    minConnections_ = minConnections;
    maxConnections_ = maxConnections;
    minWeights_ = minWeights;
    maxWeights_ = maxWeights;
}

Generator::Generator(GraphType type, int minNodes, int maxNodes, int minConnections,
                     int maxConnections) {
    if (type == DIRECTIONAL_WEIGHTED || type == NONDIRECTIONAL_WEIGHTED) {
        throw;
    }
    type_ = type;
    minNodes_ = minNodes;
    maxNodes_ = maxNodes;
    minConnections_ = minConnections;
    maxConnections_ = maxConnections;
    minWeights_ = 0;
    maxWeights_ = 0;
}

GraphType Generator::getGraphType() const {
    return type_;
}

std::pair<int, int> Generator::getNodesInterval() const {
    return std::make_pair(minNodes_, maxNodes_);
}

std::pair<int, int> Generator::getConnectionsInterval() const {
    return std::make_pair(minConnections_, maxConnections_);
}

std::pair<int, int> Generator::getWeightsInterval() const {
    return std::make_pair(minWeights_, maxWeights_);
}

void Generator::setGraphType(GraphType type) {
    type_ = type;
}

bool Generator::setNodesInterval(int minNodes, int maxNodes) {
    if (minNodes > maxNodes) {
        return false;
    }
    minNodes_ = minNodes;
    maxNodes_ = maxNodes;
    return true;
}

bool Generator::setConnectionsInterval(int minConnections, int maxConnections) {
    if (minConnections > maxConnections) {
        return false;
    }
    minConnections_ = minConnections;
    maxConnections_ = maxConnections;
    return true;
}

bool Generator::setWeightsInterval(int minWeights, int maxWeights) {
    if (minWeights > maxWeights) {
        return false;
    }
    if (type_ == DIRECTIONAL_UNWEIGHTED || type_ == NONDIRECTIONAL_UNWEIGHTED) {
        return false;
    }
    minWeights_ = minWeights;
    maxWeights_ = maxWeights;
    return true;
}

WeightedGraph<int> Generator::generateWeighted() const {
    if (type_ == DIRECTIONAL_UNWEIGHTED || type_ == NONDIRECTIONAL_UNWEIGHTED) {
        throw;
    }

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distributionNodes(minNodes_, maxNodes_);

    int nodesAmount = distributionNodes(gen);
    WeightedGraph<int> graph = WeightedGraph<int>();

    std::uniform_int_distribution<> distributionConnections(minConnections_, maxConnections_);
    std::uniform_int_distribution<> distributionWeights(minWeights_, maxWeights_);
    std::uniform_int_distribution<> distributionTarget(0, nodesAmount - 1);

    std::vector<WeightedGraphNode<int>> graphNodes = std::vector<WeightedGraphNode<int>>();
    for (int i = 0; i < nodesAmount; ++i) {
        WeightedGraphNode<int> graphNode = WeightedGraphNode<int>(i);
        graphNodes.push_back(graphNode);
    }
    for (int i = 0; i < nodesAmount; ++i) {
        int connectionAmount = distributionConnections(gen);
        while (connectionAmount >= nodesAmount) {
            connectionAmount = distributionConnections(gen);
        }
        int count = 0;
        while (count < connectionAmount && graphNodes[i].neighborsAmount() < connectionAmount) {
            int weight = distributionWeights(gen);
            int target = distributionTarget(gen);
            if (graphNodes[i].addConnection(graphNodes[target], weight)) {
                ++count;
                if (type_ == NONDIRECTIONAL_WEIGHTED) {
                    graphNodes[target].addConnection(graphNodes[i], weight);
                }
            }
        }
    }
    for (int i = 0; i < nodesAmount; ++i) {
        graph << graphNodes[i];
    }

    return graph;
}

Graph<int> Generator::generate() const {
    if (type_ == DIRECTIONAL_WEIGHTED || type_ == NONDIRECTIONAL_WEIGHTED) {
        throw;
    }

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<> distributionNodes(minNodes_, maxNodes_);

    int nodesAmount = distributionNodes(gen);
    Graph<int> graph = Graph<int>();

    std::uniform_int_distribution<> distributionConnections(minConnections_, maxConnections_);
    std::uniform_int_distribution<> distributionTarget(0, nodesAmount - 1);

    std::vector<GraphNode<int>> graphNodes = std::vector<GraphNode<int>>();
    for (int i = 0; i < nodesAmount; ++i) {
        GraphNode<int> graphNode = GraphNode<int>(i);
        graphNodes.push_back(graphNode);
    }
    for (int i = 0; i < nodesAmount; ++i) {
        int connectionAmount = distributionConnections(gen);
        while (connectionAmount >= nodesAmount) {
            connectionAmount = distributionConnections(gen);
        }
        int count = 0;
        while (count < connectionAmount && graphNodes[i].neighborsAmount() < connectionAmount) {
            int target = distributionTarget(gen);
            if (graphNodes[i].addConnection(graphNodes[target])) {
                ++count;
                if (type_ == NONDIRECTIONAL_UNWEIGHTED) {
                    graphNodes[target].addConnection(graphNodes[i]);
                }
            }
        }
    }
    for (int i = 0; i < nodesAmount; ++i) {
        graph << graphNodes[i];
    }

    return graph;
}


#endif //RANDOMGRAPH_GENERATOR_H
