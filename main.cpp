#include"GraphDataSet.h"
#include"GraphSet.h"
#include"Graph.h"
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include"Edge5.h"
#include"gSpan.h"
#include"test.h"
#include<stdlib.h>

using namespace std;

int main(int argc,char**argv){

    //���������в���
    ifstream in(argv[1]);
    ofstream out(argv[2]);
    double min_sup_rate=atof(argv[3]);

    //��֤����������в���
    if(argc!=4){
        cerr<<"The number of argument is wrong, please check your input!\n";
        return 0;
    }else if(!in){
        cerr<<"The input file path is invalid, please check your input!\n";
        return 0;

    }else if(!out){
        cerr<<"The output file path is invalid, please check your input!\n";
        return 0;
    }else if(!(min_sup_rate>0&&min_sup_rate<=1)){
        cerr<<"The min_sup_rate argument is invalid, it should between 0 and 1!\n";
        return 0;
    }

    Test test;

    //����ͼ���ݼ��϶���
    GraphDataSet* gds=new GraphDataSet;
    //��ȡ�ļ�����
    gds->readFromFile(in);
    //���и��ݱ��Ƶ�����±�ŵ�Ԥ����
    gds->reLabel(min_sup_rate);
    //�����ڽӱ�ṹ
    GraphSet gs(*gds);
    //gs.show();
    //ʹ�ú�����ͼ���ݼ��϶��󣬼����ڴ�ռ�á�
    delete gds;
    //ͼ�ھ�
    int min_sup=(int)(min_sup_rate*gs.size());
    if(min_sup<1)
        min_sup=1;
    GSpan gSpan(min_sup,gs);
	clock_t begin = clock();
    gSpan.run();
	clock_t end = clock();
    //gSpan.show();
	gSpan.showMaximal();
    //չʾ���
    //�ر��ļ�������
    in.close();
    out.close();
    clog<<"-----------------------------------------------"<<endl;
    clog<<"gSpan:                        "<<endl;
    clog<<"Graph Set Size:               "<<gSpan.gs.size()<<endl;
    clog<<"Minimum Support Count:        "<<gSpan.min_sup<<endl;
    clog<<"Frequent Subgraph Number:     "<<gSpan.resultSet.size()<<endl;
    clog<<"Use Time:                     "<<end-begin<<"ms"<<endl;
    clog<<"-----------------------------------------------"<<endl;

    return 0;
}
