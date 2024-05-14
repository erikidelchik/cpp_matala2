#include <iostream>
#include <vector>
#include "Graph.hpp"


namespace ariel {

        vector<vector<int>> Graph::getGraph() const {
            return this->myGraph;
        }
        void Graph::setGraph(int i,int j,int value){
            myGraph[i][j]=value;
        }

        int Graph::countEdges() const{
            int edges = 0;
            for (int i = 0; i < myGraph.size(); i++) {
                for (int j = i; j < myGraph.size(); j++) {
                    if ((myGraph[i][j] && !myGraph[j][i]) || (!myGraph[i][j] && myGraph[j][i]))
                        edges++;
                    else if (myGraph[i][j] && myGraph[j][i])
                        edges += 2;

                }
            }
            return edges;
        }

        void Graph::loadGraph(vector<vector<int>> mat) {
            if (!myGraph.empty()) myGraph.clear();
            for (int i = 0; i < mat.size(); i++) {
                if (mat.size() != mat[i].size()) {
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
                }
            }
            for (int i = 0; i < mat.size(); i++) {
                myGraph.push_back(mat[i]);
            }
        }

        void Graph::printGraph() {
            if (myGraph.empty()) throw string("graph is empty");

            size_t size = this->myGraph.size();
            for(int i=0;i<size;i++){
                cout<<"[";
                for(int j=0;j<size-1;j++){
                    cout<<to_string(myGraph[i][j])<<",";
                }
                cout<<to_string(myGraph[i][size-1]);
                cout<<"]\n";
            }

        }

        bool Graph::operator<=(Graph &other) const{
            return this->operator==(other) || this->operator<(other);
        }

        bool Graph::operator<(const Graph &other) const {
            if(this->countEdges()<other.countEdges()) return true;
            if(this->getGraph().size()<other.myGraph.size()) return true;
            return false;
        }

        bool Graph::operator>=(Graph &other) const{
            return this->operator==(other) || this->operator>(other);
        }

        bool Graph::operator>(const Graph &other) const {
            if(this->countEdges()>other.countEdges()) return true;
            if(this->getGraph().size()>other.myGraph.size()) return true;
            return false;
        }


        Graph& Graph::operator=(const Graph &other){
            this->loadGraph(other.myGraph);
            return *this;
        }

        bool Graph::operator==(const Graph &other) const{
            if(this->myGraph.size()!=other.myGraph.size()) return false;
            if(!(this->operator<(other)) && !(this->operator>(other))) return true;

            size_t size = myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(this->myGraph[i][j]!=other.myGraph[i][j])
                        return false;
                }
            }

            return true;
        }

        bool Graph::operator!=(const Graph &other) const{
            if(this->myGraph.size()!=other.myGraph.size()) return true;
            size_t size = myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(this->myGraph[i][j]!=other.myGraph[i][j])
                        return true;
                }
            }
            return false;
        }

        Graph& Graph::operator+=(const Graph &other){
            if(this->myGraph.size()!=other.myGraph.size())
                throw string("graphs are not of the same size");

            size_t size = myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j] = myGraph[i][j]+other.myGraph[i][j];
                }
            }
            return *this;
        }

        Graph& Graph::operator-=(const Graph &other){
            if(this->myGraph.size()!=other.myGraph.size())
                throw string("graphs are not of the same size");

            size_t size = myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j] = myGraph[i][j]-other.myGraph[i][j];
                }
            }
            return *this;
        }

        Graph Graph::operator+(const Graph &other){
            if(this->myGraph.size()!=other.myGraph.size()){
                throw string("graphs are not of the same size");
            }
            vector<vector<int>> res(this->getGraph().size(), vector<int>(getGraph().size()));
            for(int i=0;i<this->myGraph.size();i++){
                for(int j=0;j<this->myGraph.size();j++){
                    res[i][j] = myGraph[i][j]+other.myGraph[i][j];
                }
            }
            Graph g;
            g.loadGraph(res);
            return g;
        }

        Graph Graph::operator-(const Graph &other){
            if(this->myGraph.size()!=other.myGraph.size()){
                throw string("graphs are not of the same size");
            }
            vector<vector<int>> res(this->getGraph().size(), vector<int>(getGraph().size()));
            for(int i=0;i<this->myGraph.size();i++){
                for(int j=0;j<this->myGraph.size();j++){
                    res[i][j] = myGraph[i][j]-other.myGraph[i][j];
                }
            }
            Graph g;
            g.loadGraph(res);
            return g;
        }

        //graph++
        Graph Graph::operator++(int){
            size_t size = this->myGraph.size();
            Graph g;
            g.loadGraph(this->myGraph);
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j]++;
                }
            }
            return g;
        }

        //++graph
        Graph Graph::operator++(){
            size_t size = this->myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j]++;
                }
            }
            return *this;
        }

        //graph--
        Graph Graph::operator--(int){
            size_t size = this->myGraph.size();
            Graph g;
            g.loadGraph(this->myGraph);
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j]-=1;
                }
            }
            return g;
        }

        //--graph
        Graph Graph::operator--(){
            size_t size = this->myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j]-=1;
                }
            }
            return *this;
        }


        Graph Graph::operator*(Graph &other) const{
            if(this->getGraph().size()!=other.getGraph().size())
                throw string("multiplying this graphs is illegal");

            size_t size = this->getGraph().size();

            vector<vector<int>> res(myGraph.size(),vector<int>(myGraph.size()));
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    int x = 0;
                    for(int k=0;k<size;k++){
                        x+=this->myGraph[i][k]*other.myGraph[k][j];
                    }
                    res[i][j] = x;
                }
            }
            Graph g;
            g.loadGraph(res);
            return g;
        }

        Graph Graph::operator*(int num){
            size_t size = this->myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    this->myGraph[i][j] = num * this->myGraph[i][j];
                }
            }
            return *this;
        }

        Graph operator*(int num,Graph &graph){
            size_t size = graph.myGraph.size();
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    graph.myGraph[i][j] = num * graph.myGraph[i][j];
                }
            }
            return graph;
        }


         ostream& operator<<(ostream &os,const Graph &graph){
            size_t size = graph.myGraph.size();
            for(int i=0;i<size;i++){
                os<<"[";
                for(int j=0;j<size-1;j++){
                    os<<to_string(graph.myGraph[i][j])<<",";
                }
                os<<to_string(graph.myGraph[i][size-1]);
                os<<"]\n";
            }
            return os;
        }

}





