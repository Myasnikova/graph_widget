#include "graph_view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGraphView w;
    w.show();

    return a.exec();
}
