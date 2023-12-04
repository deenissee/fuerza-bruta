#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class Neurona;

#include <QMainWindow>
#include<iostream>
#include<string>
#include<QSpinBox>
#include<QPlainTextEdit>
#include<QWidget>
#include<QFileDialog>
#include<QMessageBox>
#include<fstream>
#include<QFile>
#include<QTextStream>
#include<QTableWidget>
#include<QString>
#include<QGraphicsView>
#include<QBrush>
#include<QRandomGenerator>
#include<QGraphicsScene>
#include <QGraphicsEllipseItem>
#include<QTextEdit>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsLineItem>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>
#include <QtWidgets>
#include <QPlainTextEdit>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void vaciar();
    void clean();

private slots:

    void on_insertarID_textChanged(const QString &arg1);

    void on_insertarVOLT_valueChanged(int arg1);

    void on_insertPX_valueChanged(int arg1);

    void on_insertPY_valueChanged(int arg1);

    void on_insertRED_valueChanged(int value);

    void on_insertBLUE_valueChanged(int value);

    void on_insertGREEN_valueChanged(int value);

    void on_agregarINICIO_clicked();

    void on_insertarFINAL_clicked();

    void on_plainTextEdit_textChanged();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_search_clicked();

    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

    void on_crearneurona_clicked();

    void on_dibujar_clicked();

    void on_ordenarID_clicked();

    void on_plainTextEdit_2_blockCountChanged(int newBlockCount);

    void on_ordenarVolt_clicked();

    void dibujarLineasFuerzaBruta();

    void on_lineaas_clicked();

    void on_mostrar_neuronas_clicked();

    void on_guardar_archivo_clicked();

    void on_cargar_archivo_clicked();

    void on_pushButton_2_clicked();

    void on_ordenar_id_clicked();

    void on_ordenar_voltaje_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    bool mostrar_linea;
    void unir_neuronas();
    void conectar(Neurona* ne1, Neurona& ne2);
    float distanciaNeuronas(const Neurona* ne1, const Neurona* ne2);
};

class Neurona
{
public:
    int id, posicion_x, posicion_y, red, green, blue;
    float voltaje;

    Neurona();
    Neurona *sig;
    Neurona(int,float,int,int,int,int,int,Neurona*);
};

class Administrar
{
public:
    Neurona *h;
    Administrar()
    {
        h=nullptr;
    }
    Administrar(Neurona*ptr)
    {
        h=ptr;
    }
    void agregrarInicio(int,float,int,int,int,int,int);
    void agregarFinal(int,float,int,int,int,int,int);
    void mostrar();
    void ordenarId();
    void ordenarVoltaje();
    Neurona* buscar(int id)
    {
        Neurona* aux = h;
        while (aux != nullptr) {
            if (aux->id == id) {
                return aux;
            }
            aux = aux->sig;
        }
        return nullptr;  // Si no se encuentra la neurona
    }
};

#endif // MAINWINDOW_H
