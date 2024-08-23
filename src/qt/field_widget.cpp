//
// Created by ebert on 8/22/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_field_widget.h" resolved

#include "Phoenixpp/qt/field_widget.h"
#include <QPainter>
// #include "ui_field_widget.h"

namespace phoenixpp::qt {
FieldWidget::FieldWidget(QWidget *parent) : QWidget(parent)
    // ,ui(new Ui::FieldWidget) { ui->setupUi(this);
{
}
void FieldWidget::updateField(const messaging::EnvironmentPtr& environment) {
    if(environment.get() == NULL) return;
    this->environment = environment;
    update();
}

void FieldWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::darkGreen);
    painter.drawRect(0, 0, width(), height());
    if(environment.get() == NULL ||
        !environment->received.load() ||
        !environment->field.valid) return;

    QPen whitePen(Qt::white);
    int thickness = 2, boundaryWidth = environment->field.boundary_width.load();
    int fieldLength = environment->field.field_length.load(),
        fieldWidth = environment->field.field_width.load();
    whitePen.setWidth(thickness);
    painter.setPen(whitePen);

    double scaleX = static_cast<double>(width()) / fieldLength;
    double scaleY = static_cast<double>(height()) / fieldWidth;

    // Draw the outer boundary
    painter.drawRect(
        boundaryWidth * scaleX,
        boundaryWidth * scaleY,
        fieldLength * scaleX - 2 * boundaryWidth * scaleX,
        fieldWidth * scaleY - 2 * boundaryWidth * scaleY
    );

    // Draw the center line
    painter.drawLine(
        width() / 2,
        boundaryWidth * scaleY,
        width() / 2,
        fieldWidth * scaleY - boundaryWidth * scaleY
    );

    // Draw the center circle
    painter.drawEllipse(
        QPointF(width() / 2, height() / 2),
        environment->field.centerRadius * scaleX,
        environment->field.centerRadius * scaleY
    );
    painter.drawPoint(
        width() / 2,
        height() / 2
    );
    // Draw the goals
    painter.drawRect(
        (boundaryWidth - environment->field.goal_depth.load()) * scaleX,
        (height() - environment->field.goal_width.load() * scaleY) / 2,
        environment->field.goal_depth.load() * scaleX,
        environment->field.goal_width.load() * scaleY
    );

    painter.drawRect(
        width() - boundaryWidth * scaleX,
        (height() - environment->field.goal_width.load() * scaleY) / 2,
        environment->field.goal_depth.load() * scaleX,
        environment->field.goal_width.load() * scaleY
    );

    // Draw the penalty areas
    painter.drawRect(
        boundaryWidth * scaleX,
        (height() - environment->field.penalty_area_width.load() * scaleY) / 2,
        environment->field.penalty_area_depth.load() * scaleX,
        environment->field.penalty_area_width.load() * scaleY
    );

    painter.drawRect(
        width() - boundaryWidth * scaleX - environment->field.penalty_area_depth.load() * scaleX,
        (height() - environment->field.penalty_area_width.load() * scaleY) / 2,
        environment->field.penalty_area_depth.load() * scaleX,
        environment->field.penalty_area_width.load() * scaleY
    );
}

void FieldWidget::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);
    updateAspectRatio();
}
void FieldWidget::updateAspectRatio() {
    int currentHeight = height();
    setFixedSize(currentHeight * 3 / 2, currentHeight);
}

FieldWidget::~FieldWidget() {
    // delete ui;
}
} // phoenixpp::qt
