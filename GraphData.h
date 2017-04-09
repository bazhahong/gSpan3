#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include <vector>
#include "Graph.h"
using namespace std;

class GraphData {

public:
	vector<int> newId;//ΪreLabel��Ľڵ㸳���µ�id
	vector<int> vertexLabel;//�ڵ��ǩ
	vector<bool> vertexMask;//�ڵ�����
	vector<int> from;//�ߵ�from����
	vector<int> to;//�ߵ�to����
	vector<int> edgeLabel;//�߱�ǩ
	vector<bool> edgeMask;//������

	Graph& buildGraph(Graph &g);
};
#endif
