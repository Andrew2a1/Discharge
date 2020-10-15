#ifndef ATTRIBUTEEDITORWIDGET_H
#define ATTRIBUTEEDITORWIDGET_H

#include "editor.h"
#include <QGridLayout>

#include <functional>
#include "graphicobject.h"

class AttributeEditorWidget : public Editor
{
    Q_OBJECT

private:
    QGridLayout *mainLayout;
    GraphicObject *target;

public:
    explicit AttributeEditorWidget(GraphicObject *target, QWidget *parent = nullptr);

    virtual GraphicObject *getTarget() const override;

    void addSection(const QString &name);

    void addStringAttr(const QString &name,
                       std::function<void(const QString&)> callback,
                       const QString &defaultValue = QString());

    void addDoubleAttr(const QString &name,
                       std::function<void(double)> callback,
                       double defaultValue = double());

    template<typename T>
    void addAttr(const QString &name,
                 std::function<void(T)> callback,
                 const T &defaultValue = T());

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // ATTRIBUTEEDITORWIDGET_H
