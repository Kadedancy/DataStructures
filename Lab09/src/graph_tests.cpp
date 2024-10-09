#include <gtest/gtest.h>
#include <graph.h> 

TEST(GraphTest, AddNodeAndContainsNode) {
    Graph<int, double> myGraph;
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);

    ASSERT_TRUE(myGraph.containsNode(1));
    ASSERT_TRUE(myGraph.containsNode(2));
    ASSERT_TRUE(myGraph.containsNode(3));
    ASSERT_FALSE(myGraph.containsNode(4));
}

TEST(GraphTest, AddEdgeAndContainsEdge) {
    Graph<int, double> myGraph;
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);

    myGraph.addEdge(1, 2, 1.5);
    myGraph.addEdge(1, 3, 2.0);
    myGraph.addEdge(2, 3, 1.0);

    ASSERT_TRUE(myGraph.containsEdge(1, 2));
    ASSERT_TRUE(myGraph.containsEdge(1, 3));
    ASSERT_TRUE(myGraph.containsEdge(2, 3));
    ASSERT_FALSE(myGraph.containsEdge(2, 1));
}

TEST(GraphTest, GetEdge) {
    Graph<int, double> myGraph;
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);

    myGraph.addEdge(1, 2, 1.5);
    myGraph.addEdge(1, 3, 2.0);
    myGraph.addEdge(2, 3, 1.0);

    ASSERT_DOUBLE_EQ(myGraph.getEdge(1, 2), 1.5);
    ASSERT_DOUBLE_EQ(myGraph.getEdge(1, 3), 2.0);
    ASSERT_DOUBLE_EQ(myGraph.getEdge(2, 3), 1.0);
}

TEST(GraphTest, RemoveNode) {
    Graph<int, double> myGraph;
    myGraph.addNode(1);
    myGraph.addNode(2);
    myGraph.addNode(3);

    myGraph.addEdge(1, 2, 1.5);
    myGraph.addEdge(1, 3, 2.0);
    myGraph.addEdge(2, 3, 1.0);

    myGraph.removeNode(1);
    ASSERT_FALSE(myGraph.containsNode(1));
    ASSERT_FALSE(myGraph.containsEdge(1, 2));
    ASSERT_FALSE(myGraph.containsEdge(1, 3));
}