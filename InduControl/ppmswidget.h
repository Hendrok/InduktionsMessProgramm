#ifndef PPPMSWIDGET_H
#define PPPMSWIDGET_H

#include <QWidget>

class DataPoint;

class PpmsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PpmsWidget(QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    void newData(std::shared_ptr<const DataPoint> dpoint);

private:
    void createUI();
};

#endif // PPPMSWIDGET_H
