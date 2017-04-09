#include "test.h"
#include "assert.h"
#include <iostream>

using namespace std;


void Test::DFSCodeTest() {
	DFScode gc;
	Graph g;
	gc.push_back(Edge5(0, 1, 0, 0, 1));
	gc.push_back(Edge5(1, 2, 1, 1, 0));
	gc.push_back(Edge5(2, 0, 0, 0, 0));
	gc.push_back(Edge5(2, 3, 0, 2, 2));
	gc.push_back(Edge5(3, 1, 2, 1, 1));
	gc.push_back(Edge5(1, 4, 1, 3, 2));


	//g=gc.toGraph(g);
	//g.show();
	//���Բ�����С��DFScode
	//cout<<gc.isMin()<<endl;
	//assert(!gc.isMin());

	//������С��DFScode
	gc.clear();
	gc.push_back(Edge5(0, 1, 0, 0, 0));
	gc.push_back(Edge5(1, 2, 0, 0, 1));
	gc.push_back(Edge5(2, 0, 1, 1, 0));
	gc.push_back(Edge5(2, 3, 1, 1, 2));
	gc.push_back(Edge5(3, 0, 2, 2, 0));
	gc.push_back(Edge5(2, 4, 1, 3, 2));
	//cout<<gc.isMin()<<endl;
	//assert(gc.isMin());

	//�������������ԣ�Ӧ��û������
}

void Test::ChildrenTest() {

	//���Ի���
	DFScode gc, gc2;
	Graph g;
	gc.push_back(Edge5(0, 1, 0, 0, 0));
	gc.push_back(Edge5(1, 2, 0, 0, 1));
	gc.push_back(Edge5(2, 0, 1, 1, 0));
	gc.push_back(Edge5(2, 3, 1, 1, 2));
	gc.push_back(Edge5(3, 0, 2, 2, 0));
	gc.push_back(Edge5(2, 4, 1, 3, 2));

	gc2.push_back(Edge5(0, 1, 0, 0, 1));
	gc2.push_back(Edge5(1, 2, 1, 1, 0));
	gc2.push_back(Edge5(2, 0, 0, 0, 0));
	gc2.push_back(Edge5(2, 3, 0, 2, 2));
	gc2.push_back(Edge5(3, 1, 2, 1, 1));
	gc2.push_back(Edge5(1, 4, 1, 3, 2));

	g = gc2.toGraph(g);
	g.addVertex(0);
	g.addVertex(0);
	g.addEdge(2, 5, 0);
	g.addEdge(5, 2, 0);
	g.addEdge(4, 6, 0);
	g.addEdge(6, 4, 0);
	g.addEdge(0, 4, 0);
	g.addEdge(4, 0, 0);
	//���Զ���
	//Children c(g, gc);
	//c.getChildren();
}
