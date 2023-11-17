#include "mainwindow.h"
#include "Ball.h"
#include "Robot.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QScreen>
#include <QPixmap>

class SoccerField : public QGraphicsView {
public:
    SoccerField(float windowWidth, float windowHeight) {
        float fieldWidth = windowHeight * 0.8;  // Ajuste a proporção conforme necessário
        float fieldLength = fieldWidth * 1.9;  // Ajuste a proporção conforme necessário

        scene = new QGraphicsScene(this);
        setScene(scene);

        // Carregar a imagem de background
        QPixmap backgroundImage("/home/luckwu/Desktop/Horie_Luckwu_SSL-Estimator/Phoenixpp/img_src/SSLbackground.png"); // Substitua pelo caminho da sua imagem
        scene->setBackgroundBrush(backgroundImage.scaled(windowWidth, windowHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

        // Desenhar o campo com base nas proporções em relação ao tamanho da janela
        QGraphicsRectItem *field = new QGraphicsRectItem((windowWidth - fieldLength) / 2, (windowHeight - fieldWidth) / 2, fieldLength, fieldWidth);
        field->setPen(QPen(Qt::white)); // Configurar a cor da borda
        scene->addItem(field);

        // Adicionar linhas laterais
        QGraphicsLineItem *leftLine = new QGraphicsLineItem((windowWidth - fieldLength) / 2, (windowHeight - fieldWidth) / 2, (windowWidth - fieldLength) / 2, (windowHeight + fieldWidth) / 2);
        QGraphicsLineItem *rightLine = new QGraphicsLineItem((windowWidth + fieldLength) / 2, (windowHeight - fieldWidth) / 2, (windowWidth + fieldLength) / 2, (windowHeight + fieldWidth) / 2);

        leftLine->setPen(QPen(Qt::white)); // Configurar a cor da linha
        rightLine->setPen(QPen(Qt::white)); // Configurar a cor da linha

        scene->addItem(leftLine);
        scene->addItem(rightLine);

        // Adicionar linhas de gol
        float goalWidth = fieldWidth * 0.15;  // Ajuste a proporção conforme necessário
        float goalLineOffset = (fieldWidth - goalWidth) / 2;

        QGraphicsLineItem *leftGoalLine = new QGraphicsLineItem((windowWidth - fieldLength) / 2, goalLineOffset + (windowHeight - fieldWidth) / 2, (windowWidth - fieldLength) / 2, goalLineOffset + goalWidth + (windowHeight - fieldWidth) / 2);
        QGraphicsLineItem *rightGoalLine = new QGraphicsLineItem((windowWidth + fieldLength) / 2, goalLineOffset + (windowHeight - fieldWidth) / 2, (windowWidth + fieldLength) / 2, goalLineOffset + goalWidth + (windowHeight - fieldWidth) / 2);

        leftGoalLine->setPen(QPen(Qt::white)); // Configurar a cor da linha
        rightGoalLine->setPen(QPen(Qt::white)); // Configurar a cor da linha

        scene->addItem(leftGoalLine);
        scene->addItem(rightGoalLine);

        // Adicionar círculo central
        float centerCircleRadius = fieldWidth * 0.1;  // Ajuste a proporção conforme necessário

        QGraphicsEllipseItem *centerCircle = new QGraphicsEllipseItem(((windowWidth - fieldLength) / 2 + (windowWidth + fieldLength) / 2 - centerCircleRadius * 2) / 2,
                                                                      ((windowHeight - fieldWidth) / 2 + (windowHeight + fieldWidth) / 2 - centerCircleRadius * 2) / 2,
                                                                      centerCircleRadius * 2,
                                                                      centerCircleRadius * 2);

        centerCircle->setPen(QPen(Qt::white)); // Configurar a cor da borda
        scene->addItem(centerCircle);

        // Adicionar linha de meio de campo
        QGraphicsLineItem *midfieldLine = new QGraphicsLineItem((windowWidth - fieldLength) / 2 + fieldLength / 2, (windowHeight - fieldWidth) / 2, (windowWidth - fieldLength) / 2 + fieldLength / 2, (windowHeight + fieldWidth) / 2);
        midfieldLine->setPen(QPen(Qt::white)); // Configurar a cor da linha
        scene->addItem(midfieldLine);

        // Adicionar áreas dos gols
        float goalAreaWidth = fieldWidth * 0.4;  // Ajuste a proporção conforme necessário
        float goalAreaLength = fieldLength * 0.15; // Ajuste a proporção conforme necessário

        QGraphicsRectItem *leftGoalArea = new QGraphicsRectItem((windowWidth - fieldLength) / 2, ((windowHeight - fieldWidth) / 2 + (windowHeight + fieldWidth) / 2 - goalAreaWidth) / 2, goalAreaLength, goalAreaWidth);
        QGraphicsRectItem *rightGoalArea = new QGraphicsRectItem((windowWidth + fieldLength) / 2 - goalAreaLength, ((windowHeight - fieldWidth) / 2 + (windowHeight + fieldWidth) / 2 - goalAreaWidth) / 2, goalAreaLength, goalAreaWidth);

        leftGoalArea->setPen(QPen(Qt::white)); // Configurar a cor da borda
        rightGoalArea->setPen(QPen(Qt::white)); // Configurar a cor da borda

        scene->addItem(leftGoalArea);
        scene->addItem(rightGoalArea);

        // Ajustar o tamanho da visualização com base nas proporções
        setFixedSize(windowWidth, windowHeight);
    }

    void addObjectToField(QGraphicsItem *object, float x, float y) {
        // Adicionar objeto ao campo com base nas coordenadas em relação às dimensões do campo
        object->setPos((width() - scene->width()) / 2 + x, (height() - scene->height()) / 2 + y);
        scene->addItem(object);
    }
    void addBolaToCenter(Ball *bola) {
        float x = (scene->width() - bola->boundingRect().width()) / 2;
        float y = (scene->height() - bola->boundingRect().height()) / 2;

        // Ajuste a posição para o meio de campo
        x += (scene->width() - bola->boundingRect().width()) / 4;

        addObjectToField(bola, x, y);
    }

    void addRobosToSides(Robot *robot, int numRobos) {
        float spacing = (scene->width() - 2 * robot->boundingRect().width()) / (numRobos + 1);

        for (int i = 0; i < numRobos; ++i) {
            float x = (i + 1) * spacing;
            float y = (scene->height() - robot->boundingRect().height()) / 2;

            Robot *newRobot = new Robot(i, 1, x, y, 1, 1, 1, 0); // Exemplo de criação de novo robô
            addObjectToField(newRobot, x, y);
        }
    }

private:
    QGraphicsScene *scene;
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // Obtenha o tamanho da tela
    QScreen *screen = a.primaryScreen();
    QRect screenGeometry = screen->geometry();

    // Use o tamanho da tela para criar um campo responsivo
    float windowWidth = screenGeometry.width() * 0.8;
    float windowHeight = screenGeometry.height() * 0.8;

    SoccerField soccerField(windowWidth, windowHeight);
    Ball bola(windowWidth/2,windowHeight/2,2,1);

    Robot robot(1,1,20,20,1,1,1,0);

    soccerField.addBolaToCenter(&bola);
    soccerField.addRobosToSides(&robot, 6); // Adiciona 6 robôs de cada lado



    //soccerField.addObjectToField(&bola, 0, 0);
    //soccerField.addObjectToField(&robot,50,50);

    soccerField.show();

    return a.exec();
}
