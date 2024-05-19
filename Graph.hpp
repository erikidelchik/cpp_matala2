#include <iostream>
#include <vector>

using namespace std;

namespace ariel {
    class Graph {
        vector<vector<int>> myGraph;

    public:
        int countEdges() const;

        void setGraph(int i,int j,int value);

        vector<vector<int>> getGraph() const;

        void loadGraph(vector<vector<int>> mat);

        void printGraph();

        //1

        Graph& operator+=(const Graph &other);

        Graph& operator-=(const Graph &other);

        Graph operator+(const Graph &other);

        Graph operator-(const Graph &other);


        //2
        bool operator<=(const Graph &other) const;

        bool operator<(const Graph &other) const;

        bool operator>=(const Graph &other) const;

        bool operator>(const Graph &other) const;

        Graph& operator=(const Graph &other);

        bool operator==(const Graph &other) const;

        bool operator!=(const Graph &other) const;

        //3
        //graph++
        Graph operator++(int);

        //++graph
        Graph operator++();

        //graph--
        Graph operator--(int);

        //--graph
        Graph operator--();

        //4
        Graph operator*(int num);
        friend Graph operator*(int num,Graph &graph);


        //5
        Graph operator*(const Graph &other) const;


        //6
        friend ostream& operator<<(ostream &os,const Graph &graph);

    };
}
