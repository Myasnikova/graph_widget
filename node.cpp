#include "node.h"

CNode::CNode(int index, QObject *parent) :
    QObject(parent), 
	QGraphicsItem(), 
	index(index)
{

}

void CNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::blue);
    painter->setBrush(Qt::white);
	QRectF r = NODE_SIZE;
    painter->drawEllipse(r);

	painter->setPen(Qt::black);
	painter->setFont(QFont("Arial", 12));
	painter->drawText(r, Qt::AlignCenter, QString::number(index));
	setZValue(1);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CNode::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if (event->buttons() == Qt::LeftButton)
	{
		this->setPos(mapToScene(event->pos()) - ARROW_HEAD_OFFSET);
		scene()->update();
	}
}

CEdge::CEdge(CNode* from, CNode* till, QObject *parent) :
	QObject(parent),
	QGraphicsItem(),
	from(from),
	till(till)
{

}

void CEdge::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::black);
	QPointF s = mapToScene(from->pos()) + ARROW_HEAD_OFFSET;
	QPointF f = mapToScene(till->pos()) + ARROW_HEAD_OFFSET;
	QLineF l(s, f);
	QLineF n1(l.pointAt(1 - (ARROW_HEAD_WIDTH / l.length())), l.p2());
	QLineF n2(n1);
	n1.setAngle(QLineF(s, f).normalVector().angle());
	n2.setAngle(QLineF(f, s).normalVector().angle());
	rect = QRectF(l.p1(), l.p2());
	painter->drawLine(l);
	l.setLength(l.length() - NODE_RAD);
	painter->setBrush(QBrush(Qt::black));
	painter->drawPolygon(QPolygonF({ n1.pointAt(ARROW_HEAD_WIDTH_KOEFF),n2.pointAt(ARROW_HEAD_WIDTH_KOEFF),l.p2() }));
	Q_UNUSED(option);
	Q_UNUSED(widget);
}
