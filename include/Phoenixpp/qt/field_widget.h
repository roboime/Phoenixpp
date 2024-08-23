//
// Created by ebert on 8/22/2024.
//

#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include <QWidget>
#include <Phoenixpp/messaging/environment.h>

namespace phoenixpp::qt {
//QT_BEGIN_NAMESPACE
//namespace Ui { class FieldWidget; }
//QT_END_NAMESPACE

class FieldWidget : public QWidget {
Q_OBJECT

public:
    explicit FieldWidget(QWidget *parent = nullptr);
    ~FieldWidget() override;
    void updateField(const messaging::EnvironmentPtr& environment);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    messaging::EnvironmentPtr environment;
    void updateAspectRatio();
//    Ui::FieldWidget *ui;
};
} // phoenixpp::qt

#endif //FIELD_WIDGET_H
