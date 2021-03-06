#include "attributeeditorwidget.h"
#include <QPainter>

#include <QLabel>
#include <QDoubleSpinBox>
#include <QLineEdit>

#include <QTextStream>

AttributeEditorWidget::AttributeEditorWidget(GraphicObject *target, QWidget *parent) :
    Editor(parent),
    target(target)
{
    mainLayout = new QGridLayout(this);
    this->lower();

    addSection("Attributes");
}

GraphicObject *AttributeEditorWidget::getTarget() const
{
    return target;
}

void AttributeEditorWidget::addSection(const QString &name)
{
    mainLayout->addWidget(new QLabel(name, this),
                          mainLayout->rowCount(),
                          0, 1, 2, Qt::AlignCenter);
}

void AttributeEditorWidget::addStringAttr(const QString &name,
                                          std::function<void(const QString&)> callback,
                                          const QString &defaultValue)
{
    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->insert(defaultValue);

    connect(lineEdit, &QLineEdit::textChanged, callback);

    mainLayout->addWidget(new QLabel(name, this));
    mainLayout->addWidget(lineEdit);
}

void AttributeEditorWidget::addDoubleAttr(const QString &name,
                                          std::function<void(double)> callback,
                                          double defaultValue)
{
    QDoubleSpinBox *spinBox = new QDoubleSpinBox(this);

    spinBox->setMinimum(-1e16);
    spinBox->setMaximum(1e16);
    spinBox->setSingleStep(0.125);
    spinBox->setDecimals(15);
    spinBox->setValue(defaultValue);

    connect(spinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), callback);

    mainLayout->addWidget(new QLabel(name, this));
    mainLayout->addWidget(spinBox);
}

void AttributeEditorWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(this->rect(), QColor(255, 255, 255, 128));
    painter.drawRect(this->rect());

    QWidget::paintEvent(event);
}

template<typename T>
void AttributeEditorWidget::addAttr(const QString &name,
                                    std::function<void (T)> callback,
                                    const T &defaultValue)
{

    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->insert(QString("%1").arg(defaultValue));

    connect(lineEdit, &QLineEdit::textChanged,
                [=](const QString& newValue)
                {
                    QTextStream textStream(newValue.toLocal8Bit());
                    T value;
                    textStream >> value;
                    callback(value);
                });

    mainLayout->addWidget(new QLabel(name, this));
    mainLayout->addWidget(lineEdit);
}
