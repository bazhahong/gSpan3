#include"DFScode.h"

Graph &DFScode::toGraph(Graph &g){
    DFScode &gc=*this;//Ϊ��ʹ�÷���
    if (gc.empty())
        return g;//���Ϊ���򷵻�

    g.addVertex(gc[0].fromLabel);//��ʼ����һ������
    //����ÿһ����Ԫ��
    for(size_t i=0;i<gc.size();i++){
        if(gc[i].forward())
            g.addVertex(gc[i].toLabel);//�����µĶ���

        g.addEdge(gc[i].from,gc[i].to,gc[i].eLabel);//�����
        g.addEdge(gc[i].to,gc[i].from,gc[i].eLabel);//��������

    }
    //˳��copyһ��û����ɣ�
    //this->g=g;
    return g;
}

bool DFScode::isMin(Graph &g){
    return isMin(g,*this);
}

bool DFScode::isMin(const Graph &g, const DFScode &gc){
    assert(!(gc.empty()));
    is_min=true;
    //DFScode &gc=*this;
    pgraph2code=new vector<int>();
    pgraph2code->resize(0);
    pgraph2code->resize(g.vertexLabel.size(),-1);
    vector<int> &graph2code=*pgraph2code;
    pedgeVisited=new vector<vector<bool>>;
    vector<vector<bool>> &edgeVisited=*pedgeVisited;
    edgeVisited.resize(g.vertexLabel.size());
    for(size_t i=0;i<g.vertexLabel.size();i++){
        edgeVisited[i].resize(0);
        edgeVisited[i].resize(g.vertexLabel.size(),false);
    }//init edgeVisited data struct;

    for(size_t i=0;i<g.vertexLabel.size();i++){
        int x=g.vertexLabel[i];

        //��һ�ּ�֦��ʽ
        if(x > gc[0].fromLabel)
            continue;

        assert(x==gc[0].fromLabel);
        //if(x < s[0].fromLabel)
        //	return false;//�����϶�������С�ģ�������������������ܳ��֣�


        vector<int> v(1,(int)i);//size + init value
        graph2code[i]=0;
        DFS(g,v,0,1);
        graph2code[i]=-1;
    }

    delete pedgeVisited;
    delete pgraph2code;

    return is_min;
}

void DFScode::DFS(const Graph &g, vector<int> &v, int current, int next){
    DFScode &s=*this;
    vector<int> &graph2code=*pgraph2code;
    vector<vector<bool>> &edgeVisited=*pedgeVisited;
    //current��ʾ��ǰ�Ƚϵ��ǵڼ�����
    if(current >= (int)s.size())
        return;

    vector<int>bak;//������ʧ��ʱ���ڻָ�ջ

    while(!v.empty()){
        bool flag = false;
        int x = v.back();//��ȡ��ǰ���ڵ�ͼ�еĶ���λ��

        for(size_t i=0;i<g.edgeTo[x].size();i++){
            int y=g.edgeTo[x][i];
            if(edgeVisited[x][y])//���Ѿ������ʹ���
                continue;

            //���ҵ�һ��δ�����ʵı�
            flag=true;

            //�����ߺ�DFScode�е�һ��������Ҫ�����Ƚ�
            if(graph2code[y]==-1){//û�з��ʹ�

                Edge5 e(graph2code[x],next,g.vertexLabel[x],g.edgeLabel[x][i],g.vertexLabel[y]);

                if(s[current]<e)
                    continue;

                //������̫С��������Խ�����
                if(e<s[current]){
                    is_min=false;
                    return;
                }
                graph2code[y]=next;//�����µı��
                v.push_back(y);

				edgeVisited[x][y]=true;
				edgeVisited[y][x]=true;
                
				DFS(g,v,current+1,next+1);
                //�Ӻ���ıȽϽ���з���
                if(!is_min)
                    return;

				edgeVisited[x][y]=false;
				edgeVisited[y][x]=false;

                v.pop_back();
                graph2code[y]=-1;

            }else{

                Edge5 e(graph2code[x],graph2code[y],g.vertexLabel[x],g.edgeLabel[x][i],g.vertexLabel[y]);
                if(s[current]<e)
                    continue;

                //������̫С��������Խ�����
                if(e<s[current]){
                    is_min=false;
                    return;
                }

				edgeVisited[x][y]=true;
				edgeVisited[y][x]=true;

                DFS(g,v,current+1,next);
                //�Ӻ����ıȽϽ���з���
                if(!is_min)
                    return;
				edgeVisited[x][y]=false;
				edgeVisited[y][x]=false;
            }//����Ķ����Ѿ����ʹ���

            
        }//end for
        //��ջ���ڵ����ڽӵı߷�����ϵ�ʱ��

        if(flag)//˵���ҵ���ƥ��ıߣ����ǲ���ʧ��
            break;
        //û���ҵ�ƥ��ıߣ����ǻ���,���ų���ƥ��
        bak.push_back(v.back());
        v.pop_back();

    }//end while
    //���е�����϶��Ѿ��ҵ�ƥ��ı��ˣ����ǱȽϽ����ʧ�ܵ�
    //�ָ�ջ�Ľ����ʹ֮��Ӱ����һ�������
    while(!bak.empty()){
        v.push_back(bak.back());
        bak.pop_back();
    }//ջv����ʹ����Ϊ�˼��ٿռ���˷ѣ�������Բ�ʹ��bakջ��
}

void DFScode::show(){
    cout<<"DFS code:"<<endl;
    for(vector<Edge5>::iterator itr=this->begin();itr<this->end();itr++){
        itr->show();
    }
    cout<<endl;
}
