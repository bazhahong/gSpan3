#ifndef DFSCODE_H
#define DFSCODE_H

#include<vector>
#include"Edge5.h"
#include"Graph.h"
#include"assert.h"

using namespace std;

class DFScode:public vector<Edge5>{
public:
	//vector<int>supporter;//֧����
	//Graph g;//���Ա���һ����

	DFScode(){
	}

	DFScode(const DFScode &parent){
		for(size_t i=0;i<parent.size();i++){
			this->push_back(parent[i]);
		}
	}

    Graph& toGraph(Graph& g);

	//��д����������ô�þ���ô�ã�

    bool isMin(Graph &g);

    bool isMin(const Graph& g,const DFScode &gc);

    void show();

private:
	//����Ҫ�ľֲ�����
	bool is_min;
	vector<int> *pgraph2code;
	vector<vector<bool>> *pedgeVisited;
	
    void DFS(const Graph& g,vector<int>& v,int current,int next);

};

#endif
