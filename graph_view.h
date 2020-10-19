#ifndef GRAPH_VIEW_H
#define GRAPH_VIEW_H

#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QPair>
#include <node.h>
#include <graph.h>
#include "./ui_graph_view.h"

class MyGraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	MyGraphicsScene(QObject *parent = nullptr);
	~MyGraphicsScene() {}
	void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
	int getNodeCount() { return node_count; }

signals:
	void mousePressed(QPointF);
	void newEdge(CNode*, CNode*);
	void delNode(CNode*);
	void delEdge(CEdge*);

private:
	int node_count;
	CNode * last_node;
};
class CGraphView : public QWidget, public Ui_GraphView
{
    Q_OBJECT

public:
    explicit CGraphView(QWidget *parent = 0);
    ~CGraphView();

private slots:
    void onSceneClicked(QPointF);
	void onNewEdge(CNode* n1, CNode*n2);
	void onDelNode(CNode* n);
	void onDelEdge(CEdge* e);
private:
	CGraph<CNode,CEdge> g;
    MyGraphicsScene *scene;
};

#endif // GRAPH_VIEW_H
