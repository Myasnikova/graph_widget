#include "graph_view.h"

CGraphView::CGraphView(QWidget *parent): QWidget(parent)
{
    setupUi(this);

    this->resize(640,640);      
    this->setFixedSize(640,640);

    scene = new MyGraphicsScene(this); 
	bool b = connect(scene, &MyGraphicsScene::mousePressed, this, &CGraphView::onSceneClicked);
	b &= (bool)connect(scene, &MyGraphicsScene::newEdge, this, &CGraphView::onNewEdge);
	b &= (bool)connect(scene, &MyGraphicsScene::delNode, this, &CGraphView::onDelNode);
	b &= (bool)connect(scene, &MyGraphicsScene::delEdge, this, &CGraphView::onDelEdge);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); 
    graphicsView->resize(600,600);
    graphicsView->setScene(scene);
    graphicsView->setRenderHint(QPainter::Antialiasing);
	graphicsView->setCacheMode(QGraphicsView::CacheNone);
    scene->setSceneRect(0,0,500,500);
	
}

CGraphView::~CGraphView()
{
	scene->clear();
}

void CGraphView::onSceneClicked(QPointF p)
{
    CNode *item = new CNode(scene->getNodeCount());
    item->setPos(p);
    scene->addItem(item);
	g.addNode(item->getIndex(),item);
	scene->update();
}
void CGraphView::onNewEdge(CNode* n1, CNode*n2)
{
	if (g.getEdge(n1->getIndex(), n2->getIndex()))
		return;
	CEdge *item = new CEdge(n1, n2);
	scene->addItem(item);
	scene->update();
	g.addEdge(n1->getIndex(), n2->getIndex(), item);
}
void CGraphView::onDelNode(CNode* n)
{
	int index = n->getIndex();
	for (auto i : g.getEdges(index))
	{
		scene->removeItem(i);
	}
	scene->removeItem(n);
	g.delNode(index);
	//g.printEdges();
	scene->update();
}
void CGraphView::onDelEdge(CEdge* e)
{
	auto key = e->getNodeKeys();
	g.delEdge(key.first, key.second);
	scene->removeItem(e);
	scene->update();
}
MyGraphicsScene::MyGraphicsScene(QObject * parent): 
	QGraphicsScene(parent), 
	node_count(0),
	last_node(nullptr)
{	
}
void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	CNode* node = qgraphicsitem_cast<CNode*>(itemAt(mouseEvent->scenePos(), QTransform()));
	last_node = nullptr;
	if (mouseEvent->button() == Qt::LeftButton && !node)
	{
		emit mousePressed(mouseEvent->scenePos());
		node_count++;
	}
	if (mouseEvent->button() == Qt::RightButton)
	{
		if (node)
		{
			last_node = qgraphicsitem_cast<CNode*>(node);
		}
		else
		{
			CEdge* edge = qgraphicsitem_cast<CEdge*>(itemAt(mouseEvent->scenePos(), QTransform()));
			if (edge)
			{
				emit delEdge(edge);
			}
		}
	}
	QGraphicsScene::mousePressEvent(mouseEvent);
}
void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (mouseEvent->button() == Qt::RightButton)
	{
		CNode*new_node = qgraphicsitem_cast<CNode*>(itemAt(mouseEvent->scenePos(), QTransform()));
		if (last_node && new_node)
		{
			if (last_node != new_node)
			{
				emit newEdge(last_node, new_node);
			}
			else
			{
				emit delNode(new_node);
			}
			last_node = nullptr;
		}
	}
	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}