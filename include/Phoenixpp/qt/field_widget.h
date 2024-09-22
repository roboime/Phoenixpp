//
// Created by ebert on 8/22/2024.
//

#ifndef FIELD_WIDGET_H
#define FIELD_WIDGET_H

#include <QWidget>
#include <QResizeEvent>
#include <Phoenixpp/messaging/DecisionsStore.h>
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
    void updateField(const messaging::EnvironmentPtr& environment, const std::shared_ptr<messaging::DecisionsStore>& decisionsStore);
protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
private:
    messaging::EnvironmentPtr environment;
    std::shared_ptr<messaging::DecisionsStore> decisionsStore;
    void drawField(QPainter& painter);
    void drawRobots(QPainter& painter);
    void drawBalls(QPainter& painter);
    void drawLineFromRobotToBall(QPainter& painter);
    void updateFPS();
    double fps;
//    Ui::FieldWidget *ui;
};
} // phoenixpp::qt

#endif //FIELD_WIDGET_H
