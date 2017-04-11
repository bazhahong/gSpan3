#include "GSpan.h"
#include <set>
#include "FSGraph.h"
using namespace std;
//���г���,�㷨��Ҫʵ��������
//����Ƶ��һ�ߣ�Ȼ��ֱ���ھ��Ӵ�
void GSpan::run() {
	//���ʹ�ö�̬���飿
	//int *edgeFrequency=new int[gs.vertex_label_size][gs.edge_label_size][gs.vertex_label_size];
	//EdgeFrequency ef(gs.vertex_label_size,gs.edge_label_size);

	ef.init(gs.vertex_label_size, gs.edge_label_size, min_sup);
	for (size_t i = 0;i < gs.vertex_label_size;i++) {//����ö�٣������ֵ���
		for (size_t j = 0;j < gs.edge_label_size;j++) {
			for (size_t k = i;k < gs.vertex_label_size;k++) {//ֻͳ�������Ǽ��ɣ���k��i��ʼ;
				int count = 0;

				for (size_t g = 0;g < gs.size();g++) {
					if (gs[g].hasEdge(i, j, k)) {
						count++;
					}
				}

				ef(i, j, k) = count;
				ef(k, j, i) = count;
			}//end for
		}//end for
	}//end for
	for (size_t i = 0;i < gs.vertex_label_size;i++) {//����ö�٣������ֵ���
		for (size_t j = 0;j < gs.edge_label_size;j++) {
			for (size_t k = i;k < gs.vertex_label_size;k++) {//ֻͳ�������Ǽ��ɣ���k��i��ʼ;��

				if (ef(i, j, k) < min_sup)
					continue;
				Edge5 e(0, 1, i, j, k);
				DFScode gc;
				gc.push_back(e);
				FSGraph subGraph;
				subGraph.gc = gc;

				for (size_t g = 0;g < gs.size();g++) {
					if (gs[g].hasEdge(i, j, k)) {
						subGraph.supporter.push_back(g);//����֧����
					}
				}

				subGraphMining(subGraph);//Ƶ������ͼ�ھ�

				for (size_t g = 0;g < gs.size();g++) {
					gs[g].removeEdge(i, j, k);
				}
			}//end for
		}//end for
	}//end for
	getMaximal();
}//end run

void GSpan::subGraphMining(FSGraph &subGraph) {
	//cout<<gc[0].fromLabel<<" "<<gc[0].eLabel<<" "<<gc[0].toLabel<<" "<<gc.supporter.size()<<endl;
	//return;
	subGraph.g = subGraph.gc.toGraph(subGraph.g);
	if (!subGraph.gc.isMin(subGraph.g))
		return;

	if (resultSet.size() > 0) {
		if (subGraph.gc.size() > resultSet.back().gc.size())
			resultSet.back().isMaximal = false;
		else
			resultSet.back().isMaximal = true;
	}
	//��������
	resultSet.push_back(subGraph);
	//subGraph = resultSet.back();
	map<Edge5, vector<int>> summary;

	//�ھ��Ӵ�
	for (size_t i = 0;i < subGraph.supporter.size();i++) {
		//���һ��֧����
		Graph &g = gs[subGraph.supporter[i]];
		Children c(g, subGraph.gc, ef);
		c.getChildren();
		//���һ���Ӵ�
		set<Edge5>::iterator itr;
		for (itr = c.begin();itr != c.end();itr++) {
			const Edge5 &child = *itr;
			//��ؼ��Ĵ������ڱ����ҳ����ˣ�
			summary[child].push_back(subGraph.supporter[i]);
		}

	}
	map<Edge5, vector<int>>::iterator itr;

	//subGraph.isMaximal = true;
	//int pre_size = resultSet.size();
	for (itr = summary.begin();itr != summary.end();itr++) {

		//�ȼ����Ǽ����
		if (itr->second.size() < min_sup)
			continue;
		//�������Ƶ���Ӵ������Ǽ���ģ���ʹƵ���Ӵ���DFScode������С��
		//resultSet.back().isMaximal = false;

		//DFScode child_gc = subGraph.gc;//���Ƹ�ĸ
		FSGraph childGraph;
		childGraph.gc = subGraph.gc;
		childGraph.gc.push_back(itr->first);//��������ı�
		//childGraph.gc = child_gc;
		childGraph.supporter = (itr->second);//���֧����
		subGraphMining(childGraph);//�Ӵ��ھ�
	}
	//if(pre_size == resultSet.size())//û���Ӵ������������Ǽ���ģ�
	//	subGraph.isMaximal = false;



}

//��ý��
FrequentSubGraphSet& GSpan::getResult() {
	return resultSet;
}

FrequentSubGraphSet& GSpan::getMaximal() {
	for (size_t i = 0;i < resultSet.size();i++) {
		if (resultSet[i].isMaximal == true)
			maximalResultSet.push_back(resultSet[i]);
	}
	return maximalResultSet;
}
//չʾ���
void GSpan::show() {
	cout << "Graph Set Size: " << gs.size() << endl;
	cout << "Minimum Support Count: " << min_sup << endl;
	cout << "Frequent SubGraph Number: " << resultSet.size() << endl;
	cout << endl;

	resultSet.show();
}

void GSpan::showMaximal() {
	cout << "Graph Set Size: " << gs.size() << endl;
	cout << "Minimum Support Count: " << min_sup << endl;
	cout << "Frequent SubGraph Number: " << resultSet.size() << endl;
	cout << "Maximal Frequent SubGraph Number: " << maximalResultSet.size() << endl;
	cout << endl;

	maximalResultSet.show();

}

void GSpan::save(ofstream &nodeList, ofstream &edgeList, FrequentSubGraphSet &gset)
{
	for (size_t i = 0; i < gset.size();i++) {
		nodeList << i << ", " << gset[i].gc[0].fromLabel << endl;
		for (size_t j = 0;j < gset[i].gc.size();j++) {
			Edge5 e = gset[i].gc[j];
			if (e.forward())
				nodeList << i << ", " << e.toLabel << endl;
			edgeList << i << ", " << e.from << ", " << e.to << ", " << e.eLabel << endl;
		}
	}
}

void GSpan::save(ofstream & nodeList, ofstream & edgeList, FrequentSubGraphSet & gset, vector<int> nodeLabelRecover, vector<int> edgeLabelRecover)
{
	for (size_t i = 0; i < gset.size();i++) {
		nodeList << i << ", " << nodeLabelRecover[gset[i].gc[0].fromLabel] << endl;
		for (size_t j = 0;j < gset[i].gc.size();j++) {
			Edge5 e = gset[i].gc[j];
			if (e.forward())
				nodeList << i << ", " << nodeLabelRecover[e.toLabel] << endl;
			edgeList << i << ", " << e.from << ", " << e.to << ", " << edgeLabelRecover[e.eLabel] << endl;
		}
	}
}

