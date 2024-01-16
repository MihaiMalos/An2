#pragma once

#include <QPoint>
#include <memory>

using NodePtr = std::shared_ptr<class Node>;

class Node
{
private:
    int info;
    QPointF coord;

public:
    Node(int inf = -1);
    Node(QPointF cood, int inf = -1);

    QPointF GetCoord() const;
    int GetInfo() const;

    void SetInfo(int inf);

    bool operator==(const Node& other) const;

    static float GetDistance(const QPointF& a, const QPointF& b);
};

