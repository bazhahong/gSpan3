#ifndef GRAPHSET2_H
#define GRAPHSET2_H

#include <vector>
#include "Graph.h"
#include "GraphData.h"
#include "GraphDataSet.h"

using namespace std;
class GraphSet :public vector<Graph> {
public:
	int vertex_label_size;
	int edge_label_size;

	GraphSet();//�յĹ��캯��

	GraphSet(int vertexLabelSize, int edgeLabelSize);
	void show();
};

#endif
