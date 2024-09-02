//
// Created by ebert on 8/22/2024.
//

// You may need to build the project (run Qt uic code generator) to get "ui_field_widget.h" resolved

#include "Phoenixpp/qt/field_widget.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPainterPath>
// #include "ui_field_widget.h"

namespace phoenixpp::qt {
FieldWidget::FieldWidget(QWidget *parent) : QWidget(parent)
    // ,ui(new Ui::FieldWidget) { ui->setupUi(this);
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}
void FieldWidget::updateField(const messaging::EnvironmentPtr& environment) {
    if(environment.get() == NULL) return;
    this->environment = environment;
    update();
}
QSize FieldWidget::sizeHint() const {
    int widgetHeight = height();
    int widgetWidth = widgetHeight * 3 / 2;
    return QSize(widgetWidth, widgetHeight);
}

QSize FieldWidget::minimumSizeHint() const {
    return QSize(150, 100);  // Minimum size with the correct aspect ratio
}

void FieldWidget::drawRobots(QPainter& painter) {
    if (environment.get() == nullptr || !environment->received.load()) {
        return;
    }
    int boundaryWidth = environment->field.boundary_width.load();
    int fieldLength = environment->field.field_length.load(), fieldWidth = environment->field.field_width.load();
    double scaleX = static_cast<double>(width()) / (fieldLength + 2 * boundaryWidth);
    double scaleY = static_cast<double>(height()) / (fieldWidth + 2 * boundaryWidth);

    painter.setPen(QPen(Qt::black, 1));
    for (const auto& robotGroup : {std::ref(environment->blueRobots), std::ref(environment->yellowRobots)}) {
        for (const auto& robot : robotGroup.get()) {
            if (!robot.valid.load()) continue;
            const double robotX = width() / 2 + robot.positionX.load() * scaleX;
            const double robotY = height() / 2 - robot.positionY.load() * scaleY;
            const double robotRadius = robot.radius.load() * scaleX;
            const double kickerDistance = robot.kickerDistance.load() * scaleX;
            QColor robotColor = (robot.color.load() == messaging::Color::BLUE) ? Qt::blue : Qt::yellow;
            const double theta = 2 * std::acos(kickerDistance / robotRadius);
            const double orientation = -robot.orientation.load();
            const double startAngle = orientation + theta / 2;
            const double endAngle = orientation + 2 * M_PI - theta / 2;
            const double startX = robotX + robotRadius * cos(startAngle);
            const double startY = robotY + robotRadius * sin(startAngle);
            const double endX = robotX + robotRadius * cos(endAngle);
            const double endY = robotY + robotRadius * sin(endAngle);
            QRectF robotRect(robotX - robotRadius, robotY - robotRadius, 2 * robotRadius, 2 * robotRadius);
            QPainterPath robotPath;
            robotPath.moveTo(startX, startY);
            robotPath.arcTo(robotRect, -startAngle * 180.0 / M_PI, -(endAngle - startAngle) * 180.0 / M_PI);
            robotPath.lineTo(endX, endY);
            painter.setBrush(robotColor);
            painter.setPen(Qt::NoPen);
            painter.drawPath(robotPath);
            painter.setPen(QPen(Qt::black, 1));
            painter.drawPath(robotPath);
            painter.drawLine(QPointF(startX, startY), QPointF(endX, endY));
            QRectF textRect(robotX - robotRadius, robotY - robotRadius, 2 * robotRadius, 2 * robotRadius);
            QFont font = painter.font();
            font.setPointSize(10);
            font.setBold(true);
            painter.setFont(font);
            painter.drawText(textRect, Qt::AlignCenter, QString::number(robot.id.load()));
        }
    }
}

void FieldWidget::drawBalls(QPainter& painter) {
    if (environment.get() == nullptr || !environment->received.load()) {
        return;
    }
    int boundaryWidth = environment->field.boundary_width.load();
    int fieldLength = environment->field.field_length.load(), fieldWidth = environment->field.field_width.load();
    double scaleX = static_cast<double>(width()) / (fieldLength + 2 * boundaryWidth);
    double scaleY = static_cast<double>(height()) / (fieldWidth + 2 * boundaryWidth);
    painter.setPen(QPen(Qt::black, 1));
    QColor orangeColor(255, 165, 0);
    painter.setBrush(orangeColor); // Set the color to orange for the balls
    for (const auto& ball : environment->balls) {
        if (!ball.valid.load()) continue;
        double ballX = width() / 2 + ball.positionX.load() * scaleX;
        double ballY = height() / 2 - ball.positionY.load() * scaleY;
        double ballRadius = ball.radius.load() * scaleX;
        painter.drawEllipse(QPointF(ballX, ballY), ballRadius, ballRadius);
    }
}

void FieldWidget::drawField(QPainter& painter) {
    if (environment.get() == nullptr || !environment->received.load() || !environment->field.valid) {
        return;
    }
    int thickness = 2, boundaryWidth = environment->field.boundary_width.load();
    int fieldLength = environment->field.field_length.load(), fieldWidth = environment->field.field_width.load();
    double scaleX = static_cast<double>(width()) / (fieldLength + 2 * boundaryWidth);
    double scaleY = static_cast<double>(height()) / (fieldWidth + 2 * boundaryWidth);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::darkGreen);
    painter.drawRect(0, 0, width(), height());
    QPen whitePen(Qt::white);
    whitePen.setWidth(thickness);
    painter.setPen(whitePen);
    painter.drawRect(
        thickness/2,
        thickness/2,
        width() - thickness,
        height() - thickness
    );
    painter.drawRect(
        boundaryWidth * scaleX,
        boundaryWidth * scaleY,
        fieldLength * scaleX,
        fieldWidth * scaleY
    );
    painter.drawEllipse(
        QPointF(width() / 2, height() / 2),
        environment->field.centerRadius * scaleX,
        environment->field.centerRadius * scaleY
    );
    painter.drawLine(
        width() / 2,
        boundaryWidth * scaleY,
        width() / 2,
        fieldWidth * scaleY + boundaryWidth * scaleY
    );
    painter.drawPoint(
        width() / 2,
        height() / 2
    );
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

void FieldWidget::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    drawField(painter);
    drawRobots(painter);
    drawBalls(painter);
    updateFPS();
    QFont font = painter.font();
    font.setPointSize(12);   // Set font size for FPS display
    painter.setFont(font);
    painter.setPen(Qt::white);  // White color for text
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignRight, QString("FPS: %1").arg(fps, 0, 'f', 2));
}

void FieldWidget::updateFPS() {
    static int frameCount = 0;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    frameCount++;
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime);
    if (duration.count() > 1000) {
        fps = frameCount * 1000.0 / duration.count();
        frameCount = 0;
        lastTime = currentTime;
    }
}

void FieldWidget::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);
    int widgetWidth = event->size().width();
    int widgetHeight = event->size().height();
    if (widgetWidth > widgetHeight * 3 / 2) {
        widgetWidth = widgetHeight * 3 / 2;
    } else {
        widgetHeight = widgetWidth * 2 / 3;
    }
    resize(widgetWidth, widgetHeight);
}

FieldWidget::~FieldWidget() {
    // delete ui;
}
} // phoenixpp::qt
