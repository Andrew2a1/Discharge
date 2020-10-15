#include "modificatoreditor.h"
#include "ui_modificatoreditor.h"

#include <QLabel>
#include <QAction>
#include <QComboBox>

#include "physical/modificators/Modificator.h"
#include "physical/modificators/ModificatorFactory.h"
#include "physical/SimulationSubject.h"

ModificatorEditor::ModificatorEditor(QWidget *parent) :
    Editor(parent),
    ui(new Ui::ModificatorEditor)
{
    ui->setupUi(this);

    connect(ui->downButton, &QPushButton::clicked, this, &ModificatorEditor::moveSelectedDown);
    connect(ui->upButton, &QPushButton::clicked, this, &ModificatorEditor::moveSelectedUp);
    connect(ui->listWidget, &QListWidget::currentRowChanged, this, &ModificatorEditor::changeCurrent);
    connect(ui->removeButton, &QPushButton::clicked, this, &ModificatorEditor::removeSelected);

    for(const auto& name: ModificatorFactory::instance()->names())
    {
        ui->comboBox->addItem(QString::fromStdString(name));
    }

    connect(ui->comboBox, QOverload<const QString&>::of(&QComboBox::activated),
            this, &ModificatorEditor::addModificator);
}

ModificatorEditor::~ModificatorEditor()
{
    delete ui;
}

GraphicObject *ModificatorEditor::getTarget() const
{
    return simGraphic;
}

SimulationGraphicObject *ModificatorEditor::getSimGraphic() const
{
    return simGraphic;
}

void ModificatorEditor::setSimGraphic(SimulationGraphicObject *value)
{
    simGraphic = value;

    if(!simGraphic)
        return;

    ui->listWidget->clear();
    for(const auto &modificator: simGraphic->getPhysical()->getModificators())
        ui->listWidget->addItem(QString::fromStdString(modificator->name()));
}

void ModificatorEditor::moveSelectedUp()
{
    if(ui->listWidget->selectedItems().isEmpty())
        return;

    QListWidgetItem *selected = ui->listWidget->selectedItems().first();
    int row = ui->listWidget->row(selected);

    selected = ui->listWidget->takeItem(row);
    ui->listWidget->insertItem(qMax(0, row - 1), selected);
    ui->listWidget->setItemSelected(selected, true);

    updateOrder();
}

void ModificatorEditor::moveSelectedDown()
{
    if(ui->listWidget->selectedItems().isEmpty())
        return;

    QListWidgetItem *selected = ui->listWidget->selectedItems().first();
    int row = ui->listWidget->row(selected);

    selected = ui->listWidget->takeItem(row);
    ui->listWidget->insertItem(qMin(ui->listWidget->count(), row + 1), selected);
    ui->listWidget->setItemSelected(selected, true);

    updateOrder();
}

void ModificatorEditor::removeSelected()
{
    if(ui->listWidget->selectedItems().isEmpty())
        return;

    QListWidgetItem *selected = ui->listWidget->selectedItems().first();
    ui->listWidget->removeItemWidget(selected);
    delete selected;

    updateOrder();
}

void ModificatorEditor::addModificator(const QString &name)
{
    ui->listWidget->addItem(name);
    updateOrder();
}

void ModificatorEditor::changeCurrent(int current)
{
    Q_UNUSED(current);
    updateOrder();
}

void ModificatorEditor::updateOrder()
{
    ModificatorFactory *factory = ModificatorFactory::instance();
    QList<Modificator*> modificators;

    for(int i = 0; i < ui->listWidget->count(); ++i)
        modificators.append(factory->get(ui->listWidget->item(i)->text().toStdString()));

    simGraphic->getPhysical()->setModificators(modificators.toStdList());
}
