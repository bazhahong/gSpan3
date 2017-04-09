#include"Children.h"

void Children::getChildren() {

	graph2code.resize(0);
	graph2code.resize(g.vertexLabel.size(), -1);

	code2graph.resize(0);
	code2graph.resize(g.vertexLabel.size(), -1);

	edgeVisited.resize(0);
	for (size_t i = 0;i < g.vertexLabel.size();i++) {
		vector<bool> temp;
		temp.resize(0);
		temp.resize(g.vertexLabel.size(), false);
		edgeVisited.push_back(temp);
	}
	//Ѱ������·��
	rmPath.resize(0);
	rmPath.resize(gc.size() + 1, -1);
	for (size_t i = 0;i < gc.size();i++) {
		if (gc[i].forward() && gc[i].to > rmPath[gc[i].from]) {
			rmPath[gc[i].from] = gc[i].to;
		}
	}

	//ƥ���һ������ͽ�������ƥ�����
	for (size_t i = 0;i < g.vertexLabel.size();i++) {
		if (gc[0].fromLabel != g.vertexLabel[i])
			continue;
		graph2code[i] = 0;
		code2graph[0] = (int)i;
		DFS(0);
		graph2code[i] = -1;
		code2graph[0] = -1;
	}
}

void Children::DFS(int current) {

	//ƥ����ɣ������Ӵ�
	if (current >= gc.size()) {
		//������·����չ��ע�����
		vector<int> rmPoint;
		rmPoint.push_back(0);
		//��������·���ϵĽڵ�
		for (size_t i = 0;rmPath[i] > -1;i = rmPath[i]) {
			rmPoint.push_back(rmPath[i]);
		}
		//����ı���i����Ϊunsigned���ͣ�������˼����ϸ����һ�¾�֪���ˣ�
		for (size_t i = 0;i < rmPoint.size();i++) {
			int from = code2graph[rmPoint[i]];
			int fromLabel = g.vertexLabel[from];
			for (size_t j = 0;j < g.edgeLabel[from].size();j++) {
				int to = g.edgeTo[from][j];
				int eLabel = g.edgeLabel[from][j];
				int toLabel = g.vertexLabel[to];

				if (edgeVisited[from][to])
					continue;
				//���Ҷ���Ĵ������

				//��֦����:������Ƶ��������
				if (ef(fromLabel, eLabel, toLabel) < ef.min_sup)
					continue;

				//��֦����:�����ȵ�һ����С�ıߵ�����
				Edge5 e(0, 1, fromLabel, eLabel, toLabel);
				if (e < gc[0])
					continue;
				assert(gc[0] < e || gc[0] == e);//�Ҳ�������֦�����ǲ���Ҫ�ģ�

				if (i == rmPoint.size() - 1) {
					if (graph2code[to] > -1) {//���־ɵĽڵ�
						Edge5 e(graph2code[from], graph2code[to], fromLabel, eLabel, toLabel);
						assert(e.backword());
						//if(e.forward())//��ӦΪ����ı�
						//  continue;
						this->insert(e);
					}
					else {//�����µĽڵ�
						Edge5 e(graph2code[from], rmPoint.back() + 1, fromLabel, eLabel, toLabel);
						this->insert(e);
					}
				}
				else {
					//�����Ҷ���Ĵ������
					if (graph2code[to] > -1)
						continue;
					Edge5 e(graph2code[from], rmPoint.back() + 1, fromLabel, eLabel, toLabel);
					this->insert(e);
				}

			}

		}

		return;
	}
	//����ƥ��
	Edge5& e = gc[current];
	int from = code2graph[e.from];
	int fromLabel = g.vertexLabel[from];

	//��ʼ��ǩһ��ƥ�����
	assert(fromLabel == e.fromLabel);

	for (size_t i = 0;i < g.edgeTo[from].size();i++) {

		int to = g.edgeTo[from][i];
		int toLabel = g.vertexLabel[to];
		int eLabel = g.edgeLabel[from][i];

		//�˱��Ѿ����ʹ���
		if (edgeVisited[from][to] == true)
			continue;

		//�߲�ƥ��
		if (e.eLabel != eLabel)
			continue;
		//��ֹ�ڵ㲻ƥ��
		if (e.toLabel != toLabel)
			continue;
		//�ߵı��ƥ��ɹ�

		if (e.forward() && graph2code[to] == -1) {
			edgeVisited[from][to] = true;
			edgeVisited[to][from] = true;
			graph2code[to] = e.to;
			code2graph[e.to] = to;
			DFS(current + 1);
			graph2code[to] = -1;
			code2graph[e.to] = -1;
			edgeVisited[from][to] = false;
			edgeVisited[to][from] = false;
		}
		else if (e.backword() && graph2code[to] > -1) {
			//���ﲻ̫�ԣ�
			edgeVisited[from][to] = true;
			edgeVisited[to][from] = true;
			DFS(current + 1);
			edgeVisited[from][to] = false;
			edgeVisited[to][from] = false;
		}
		//���⻹�����ַǷ��������
	}
}
