#ifndef NODE_H
#define NODE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QVector>
#include <QCursor>
#include <QLineF>
#include <QPolygonF>
#include <QPair>

#define NODE_RAD 20
#define NODE_SIZE QRectF (0,0,2*NODE_RAD,2*NODE_RAD)
#define ARROW_HEAD_OFFSET QPointF(NODE_RAD, NODE_RAD)
#define ARROW_HEAD_WIDTH 40
#define ARROW_HEAD_WIDTH_KOEFF 0.2


class CNode : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit CNode(int index = -1, QObject *parent = 0);
	~CNode() {}
	int getIndex() { return index; }
	enum { Type = UserType + 1 };
	int type() const override {return Type;}

private:
	QRectF boundingRect() const { return NODE_SIZE;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event) {}
	int index;

};
class CEdge : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:
	explicit CEdge(CNode* from, CNode* till, QObject *parent = 0);
	~CEdge() {}
	enum { Type = UserType + 2 };
	int type() const override { return  Type;}
	QPair<int, int> getNodeKeys() { return qMakePair(from->getIndex(), till->getIndex()); }
private:
	QRectF rect;
	QPolygonF arrowHead;
	QRectF boundingRect() const{return rect;}
	CNode* from, *till;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // NODE_H
