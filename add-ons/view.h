#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QtEvents>


class View : public QGraphicsView
{
    Q_OBJECT
public:
    using QGraphicsView::QGraphicsView;
private:
    int numScheduledScalings;
private slots:
    void wheelEvent(QWheelEvent *event);
    void scalingTime(qreal x);
    void animFinished();
};

#endif // VIEW_H
