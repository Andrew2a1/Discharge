#ifndef MODIFICATOREDITOR_H
#define MODIFICATOREDITOR_H

#include "editor.h"
#include "simulationgraphicobject.h"

#include <QList>

namespace Ui {
class ModificatorEditor;
}

class ModificatorEditor : public Editor
{
    Q_OBJECT

private:
    Ui::ModificatorEditor *ui;
    SimulationGraphicObject *simGraphic = nullptr;

public:
    explicit ModificatorEditor(QWidget *parent = nullptr);
    ~ModificatorEditor();

    virtual GraphicObject *getTarget() const override;

    SimulationGraphicObject *getSimGraphic() const;
    void setSimGraphic(SimulationGraphicObject *value);

private slots:
    void moveSelectedUp();
    void moveSelectedDown();

    void removeSelected();
    void addModificator(const QString &name);

    void changeCurrent(int current);
    void updateOrder();
};

#endif // MODIFICATOREDITOR_H
