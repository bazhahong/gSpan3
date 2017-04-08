#ifndef GSPAN_H
#define GSPAN_H

#include"GraphDataSet.h"
#include"GraphSet.h"
#include"Graph.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<map>
#include"Edge5.h"
#include"DFScode.h"
#include"Children.h"
#include"EdgeFrequency.h"
#include"FrequentSubGraphSet.h"
using namespace std;

class GSpan{
public:
	
	int min_sup;//��С֧�ֶ�
	GraphSet &gs;//���ݼ�
	//GraphSet resultSet;//�����
	FrequentSubGraphSet resultSet;
	
	GSpan(int _min_sup,GraphSet &_gs):min_sup(_min_sup),gs(_gs){ }//��������Ҫ�Ĳ���
	void run();//���г���
	FrequentSubGraphSet& getResult();
	void show();

private:
    void subGraphMining(FSGraph &gc);//�ھ���ͼ


};

#endif
