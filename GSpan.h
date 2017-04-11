#ifndef GSPAN_H
#define GSPAN_H

#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <time.h>
#include "Graph.h"
#include "Edge5.h"
#include "DFScode.h"
#include "Children.h"
#include "GraphSet.h"
#include "GraphDataSet.h"
#include "EdgeFrequency.h"
#include "FrequentSubGraphSet.h"
using namespace std;

class GSpan {
public:

	int min_sup;//��С֧�ֶ�

	GraphSet &gs;//���ݼ�

	FrequentSubGraphSet resultSet;//Ƶ����ͼ�����

	FrequentSubGraphSet maximalResultSet;//����Ƶ����ͼ�����

	GSpan(int _min_sup, GraphSet &_gs) :min_sup(_min_sup), gs(_gs) { }//��������Ҫ�Ĳ���

	void run();//���г���

	FrequentSubGraphSet& getResult();//��ȡƵ����ͼ

	FrequentSubGraphSet& getMaximal();//��ȡ����Ƶ����ͼ

	void show();//�����̨���Ƶ����ͼ�ھ���Ϣ

	void showMaximal();//�����̨�������Ƶ����ͼ�ھ���Ϣ

	void save(ofstream &nodeList, ofstream &edgeList, FrequentSubGraphSet &gset);

	void save(ofstream &nodeList, ofstream &edgeList, FrequentSubGraphSet &gset, vector<int>nodeLabelRecover, vector<int>edgeLabelRecover);


private:
	void subGraphMining(FSGraph &gc);//�ھ���ͼ

	EdgeFrequency ef;


};

#endif
