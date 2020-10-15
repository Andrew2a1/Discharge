#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include "graphicobject.h"

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    virtual ~Editor() = default;

    virtual GraphicObject *getTarget() const = 0;
};

#endif // EDITOR_H
