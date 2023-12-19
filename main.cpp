#include <iostream>
#include "GraphNode.h"
#include "WeightedGraphNode.h"
#include "Graph.h"
#include "Generator.h"
#include <cassert>

int main() {
    // Тесты класса GraphNode
    // Конструктор по умолчанию
    GraphNode<int> test1 = GraphNode<int>();
    assert(test1.getName() == 0);
    assert(test1.neighborsAmount() == 0);

    // Конструктор инициализации
    GraphNode<int> test2 = GraphNode<int>(2);
    assert(test2.getName() == 2);

    // Конструктор копирования
    GraphNode<int> test3 = GraphNode<int>(test2);
    assert(test3.getName() == test2.getName());
    assert(test2 == test3);

    // Геттер и сеттер
    test1.setName(1);
    test3.setName(3);
    assert(test1.getName() == 1);
    assert(test3.getName() == 3);

    // Identify
    assert(test1.identify() == graphNode);

    // addConnection и neighborAmount
    test1.addConnection(test2);
    test2.addConnection(test1);
    test2.addConnection(test3);
    test3.addConnection(test2);

    assert(test1.neighborsAmount() == 1);
    assert(test2.neighborsAmount() == 2);
    assert(test3.neighborsAmount() == 1);

    assert(test1.getNeighbors().size() == 1);

    std::cout << "Test for class GraphNode passed" << std::endl;

    // Тесты класса WeightedGraphNode
    // Конструктор по умолчанию
    WeightedGraphNode<int> test4 = WeightedGraphNode<int>();
    assert(test4.getName() == 0);
    assert(test4.neighborsAmount() == 0);

    // Конструктор инициализации
    WeightedGraphNode<int> test5 = WeightedGraphNode<int>(5);
    assert(test5.getName() == 5);

    // Конструктор копирования
    WeightedGraphNode<int> test6 = WeightedGraphNode<int>(test5);
    assert(test5.getName() == test6.getName());
    assert(test5 == test6);

    // Геттер и сеттер
    test4.setName(4);
    test6.setName(6);
    assert(test4.getName() == 4);
    assert(test6.getName() == 6);

    // addConnection, getWeights
    test4.addConnection(test5, 20);
    test5.addConnection(test6, 15);
    test6.addConnection(test4, 10);

    assert(test4.neighborsAmount() == 1);
    assert(test5.neighborsAmount() == 1);
    assert(test6.neighborsAmount() == 1);
    assert(test4.getNeighbors().size() == 1);
    assert(test5.getWeights()[0] == 15);

    // identify
    assert(test4.identify() == weightedGraphNode);
    assert(test5.identify() == weightedGraphNode);
    assert(test6.identify() == weightedGraphNode);

    std::cout << "Test for class WeightedGraphNode passed" << std::endl;

    // Тесты класса Graph
    // Конструктор по умолчанию
    Graph<int> graphTest1 = Graph<int>();
    assert(graphTest1.size() == 0);

    // Конструктор инициализации
    Graph<int> graphTest2 = Graph<int>(test2);
    assert(graphTest2.size() == 1);
    assert(graphTest2.contain(test2) == true);
    assert(graphTest2.contain(test2.getName()) == true);

    // Конструктор копирования
    Graph<int> graphTest3 = Graph<int>(graphTest2);
    assert((graphTest2 == graphTest3) == true);

    // add, remove
    graphTest2.add(test1);
    assert(graphTest2.size() == 2);
    graphTest2.add(test3);
    assert(graphTest2.size() == 3);
    graphTest2.add(test3);
    assert(graphTest2.size() == 3);
    graphTest2.remove(test1);
    assert(graphTest2.size() == 2);
    graphTest2.remove(2);
    assert(graphTest2.size() == 1);
    graphTest2.remove(test1);
    assert(graphTest2.size() == 1);
    graphTest2.removeAll();
    assert(graphTest2.size() == 0);

    std::cout << "Test for class Graph passed" << std::endl;

    // Тесты класса WeightedGraph
    // Конструктор по умолчанию
    WeightedGraph<int> weightedGraphTest1 = WeightedGraph<int>();
    assert(weightedGraphTest1.size() == 0);

    // Конструктор инициализации
    WeightedGraph<int> weightedGraphTest2 = WeightedGraph<int>(test5);
    assert(weightedGraphTest2.size() == 1);
    assert(weightedGraphTest2.contain(test5) == true);
    assert(weightedGraphTest2.contain(test5.getName()) == true);

    // Конструктор копирования
    WeightedGraph<int> weightedGraphTest3 = WeightedGraph<int>(weightedGraphTest2);
    assert((weightedGraphTest2 == weightedGraphTest3) == true);

    // add, remove
    weightedGraphTest2.add(test4);
    assert(weightedGraphTest2.size() == 2);
    weightedGraphTest2.add(test6);
    assert(weightedGraphTest2.size() == 3);
    weightedGraphTest2.add(test6);
    assert(weightedGraphTest2.size() == 3);
    weightedGraphTest2.remove(test4);
    assert(weightedGraphTest2.size() == 2);
    weightedGraphTest2.remove(5);
    assert(weightedGraphTest2.size() == 1);
    weightedGraphTest2.remove(test4);
    assert(weightedGraphTest2.size() == 1);
    weightedGraphTest2.removeAll();
    assert(weightedGraphTest2.size() == 0);

    std::cout << "Test for class WeightedGraph passed" << std::endl;


    // Тесты класса Generator
    // Конструктор по умолчанию
    Generator generatorTest1 = Generator();
    assert(generatorTest1.getGraphType() == NONDIRECTIONAL_UNWEIGHTED);

    // Конструктор инициализации
    Generator generatorTest2 = Generator(DIRECTIONAL_WEIGHTED, 5, 10, 2, 5, 10, 20);
    assert(generatorTest2.getNodesInterval().first == 5);
    assert(generatorTest2.getNodesInterval().second == 10);
    assert(generatorTest2.getConnectionsInterval().first == 2);
    assert(generatorTest2.getConnectionsInterval().second == 5);
    assert(generatorTest2.getWeightsInterval().first == 10);
    assert(generatorTest2.getWeightsInterval().second == 20);
    assert(generatorTest2.getGraphType() == DIRECTIONAL_WEIGHTED);

    Generator generatorTest3 = Generator(DIRECTIONAL_UNWEIGHTED, 6, 11, 1, 3);
    assert(generatorTest3.getNodesInterval().first == 6);
    assert(generatorTest3.getNodesInterval().second == 11);
    assert(generatorTest3.getConnectionsInterval().first == 1);
    assert(generatorTest3.getConnectionsInterval().second == 3);
    assert(generatorTest3.getGraphType() == DIRECTIONAL_UNWEIGHTED);

    // Конструктор копирования
    Generator generatorTest4 = Generator(generatorTest2);
    assert(generatorTest4.getNodesInterval().first == 5);
    assert(generatorTest4.getNodesInterval().second == 10);
    assert(generatorTest4.getConnectionsInterval().first == 2);
    assert(generatorTest4.getConnectionsInterval().second == 5);
    assert(generatorTest4.getWeightsInterval().first == 10);
    assert(generatorTest4.getWeightsInterval().second == 20);
    assert(generatorTest4.getGraphType() == DIRECTIONAL_WEIGHTED);

    // Сеттеры
    generatorTest1.setGraphType(NONDIRECTIONAL_WEIGHTED);
    generatorTest1.setNodesInterval(4, 11);
    generatorTest1.setConnectionsInterval(1, 3);
    generatorTest1.setWeightsInterval(50, 60);

    assert(generatorTest1.getNodesInterval().first == 4);
    assert(generatorTest1.getNodesInterval().second == 11);
    assert(generatorTest1.getConnectionsInterval().first == 1);
    assert(generatorTest1.getConnectionsInterval().second == 3);
    assert(generatorTest1.getWeightsInterval().first == 50);
    assert(generatorTest1.getWeightsInterval().second == 60);
    assert(generatorTest1.getGraphType() == NONDIRECTIONAL_WEIGHTED);

    std::cout << "Test for class Generator passed" << std::endl;

    std::cout << "All tests are passed" << std::endl;

    Graph<int> graph = generatorTest3.generate();

    return 0;
}
