#include "GraphDataSet.h"
#include <algorithm>
#include <vector>


//���ļ��ж�ȡͼ����

void GraphDataSet::readFromFile(ifstream &in) {
	GraphData *gd = NULL;
	char state;
	char temp[30];

	while (in >> state) {
		if (state == 't') {
			if (gd) {
				this->push_back(*gd);//����ԭ����ͼ
				delete gd;//����
				gd = NULL;//��ֵ��ֹ����Ұָ��
			}
			gd = new GraphData;//�½�
			in.getline(temp, 30);//������һ��

		}
		else if (state == 'v') {
			int vLabel, id;
			in >> id;
			in >> vLabel;
			gd->vertexLabel.push_back(vLabel);//���ö����ǩ
			gd->vertexMask.push_back(true);//���ö�������
			//Ƶ��ͳ��
			if (vLabels.size() < vLabel + 1)
				vLabels.resize(vLabel + 1, 0);
			vLabels[vLabel]++;

		}
		else if (state == 'e') {
			int from, to, eLabel;
			in >> from;
			in >> to;
			in >> eLabel;
			gd->from.push_back(from);
			gd->to.push_back(to);
			gd->edgeLabel.push_back(eLabel);
			gd->edgeMask.push_back(true);
			//Ƶ��ͳ��
			if (eLabels.size() < eLabel + 1)
				eLabels.resize(eLabel + 1, 0);
			eLabels[eLabel]++;
		}
		else {
			cerr << "File format is unsupport!Please check your input!\n";
			exit(0);

		}
	}

	//�������һ��ͼ������
	if (gd) {
		this->push_back(*gd);//����ԭ����ͼ
		delete gd;//����
		gd = NULL;//��ֵ��ֹ����Ұָ��
	}
	//ͼ�Ѿ���������ˣ�


}

//��ͼ�����еı�ǩ����Ƶ�������й��˺����±�š�
void GraphDataSet::reLabel(double min_sup_rate) {
	//����֧�ֶ���ֵ
	this->min_sup = min_sup_rate*this->size();//double��intû�������
	if (min_sup < 1)
		min_sup = 1;
	//����������Ƶ�ʵ���
	LabelInfoSet vertexOrder(vLabels);
	LabelInfoSet edgeOrder(eLabels);
	//��Ƶ�ʽ�������
	sort(vertexOrder.begin(), vertexOrder.end());
	sort(edgeOrder.begin(), edgeOrder.end());
	//�������
	reverse(vertexOrder.begin(), vertexOrder.end());
	reverse(edgeOrder.begin(), edgeOrder.end());
	//���˷�Ƶ�����
	vertexOrder.filter(min_sup);
	edgeOrder.filter(min_sup);
	//�������
	vertex_label_size = vertexOrder.setOrder();
	edge_label_size = edgeOrder.setOrder();
	for (size_t i = 0;i < vertexOrder.size();i++) {
		if (vertexOrder[i].mask == true)
			nodeLabelRecover.push_back(vertexOrder[i].label);
	}

	for (size_t i = 0;i < edgeOrder.size();i++) {
		if (edgeOrder[i].mask == true)
			edgeLabelRecover.push_back(edgeOrder[i].label);
	}

	//����Label��ת����
	sort(vertexOrder.begin(), vertexOrder.end(), LabelInfo::compareByLabel);
	sort(edgeOrder.begin(), edgeOrder.end(), LabelInfo::compareByLabel);
	//���±��
	for (size_t i = 0;i < this->size();i++) {//����ÿһ��GraphData
		int id = 0;//�Զ��㸳���µı��
		//reLabel����
		for (size_t j = 0;j < (*this)[i].vertexLabel.size();j++) {//��������
			int &Label = (*this)[i].vertexLabel[j];//�ҵ��˶�������Ӧ�ı�ǩ
			if (vertexOrder[Label].mask == false)//�˱�ǩ��Ƶ��
			{
				(*this)[i].vertexMask[j] = false;//���ò��ɼ�
				(*this)[i].newId.push_back(-1);
			}
			else {
				(*this)[i].newId.push_back(id);//�����µ�id
				id++;//id������
			}
			Label = vertexOrder[Label].order;//relabel����Ƶ���ı��Ϊ-1
		}
		//reLabel��
		for (size_t k = 0;k < (*this)[i].edgeLabel.size();k++) {//�����߱�
			int &from = (*this)[i].from[k];
			int &to = (*this)[i].to[k];
			bool mask = (*this)[i].edgeMask[k];
			int &Label = (*this)[i].edgeLabel[k];
			vector<int> &v = (*this)[i].vertexLabel;
			vector<int> &ids = (*this)[i].newId;
			vector<bool> &vmask = (*this)[i].vertexMask;

			if (edgeOrder[Label].mask == false)
				(*this)[i].edgeMask[k] = false;//�߲�Ƶ��

			else if (vmask[from] == false || vmask[to] == false) {
				(*this)[i].edgeMask[k] = false;//�������ӵĶ��㲻Ƶ��
			}
			from = ids[from];//reAssign
			to = ids[to];//reAssign
			Label = edgeOrder[Label].order;//reLabel
		}//end for
	}//end for

}

LabelInfo::LabelInfo(int l, int f, int o) {
	label = l;
	frequency = f;
	order = o;
	mask = true;//Ĭ��Ϊ�棬�д���������
}

bool LabelInfo::operator<(LabelInfo &b) {
	return this->frequency < b.frequency ? true : false;
}

bool LabelInfo::compareByLabel(const LabelInfo &a, const LabelInfo &b) {
	return a.label < b.label ? true : false;
}

LabelInfoSet::LabelInfoSet(vector<int> &labels) {
	for (unsigned i = 0;i < labels.size();i++) {
		this->push_back(LabelInfo(i, labels[i], -1));
	}
}

int LabelInfoSet::setOrder() {
	unsigned j = 0;
	for (unsigned i = 0;i < (*this).size();i++) {
		if ((*this)[i].mask) {
			(*this)[i].order = j;
			j++;
		}
	}
	return j;//�������±�ŵ�����
}

void LabelInfoSet::filter(int min_sup) {
	for (unsigned i = 0;i < (*this).size();i++) {
		if ((*this)[i].frequency < min_sup)
			(*this)[i].mask = false;
	}
}
