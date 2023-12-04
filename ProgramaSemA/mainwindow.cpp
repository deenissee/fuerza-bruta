#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}
Neurona::Neurona(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue, Neurona *sig)
{
    this->id=id;
    this->voltaje=voltaje;
    this->posicion_x=posicion_x;
    this->posicion_y=posicion_y;
    this->red=red;
    this->blue=blue;
    this->green=green;
    this->sig=sig;
}
//AGREGAR INICIO
void Administrar::agregrarInicio(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    Neurona *tmp=new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue, nullptr);
    if(!h)
    {
        h=tmp;
    }
    else
    {
        tmp->sig=h;
        h=tmp;
    }
}

//AGREGAR FINAL
void Administrar::agregarFinal(int id, float voltaje, int posicion_x, int posicion_y, int red, int green, int blue)
{
    Neurona *tmp=new Neurona(id, voltaje, posicion_x, posicion_y, red, green, blue, nullptr);
    if(!h)
    {
        h=tmp;
    }
    else
    {
        Neurona *aux=h;

        while(aux->sig!=nullptr)
        {
            aux=aux->sig;
        }
        aux->sig=tmp;
    }
}
//FUNCION MOSTRAR
void Administrar::mostrar()
{
    Neurona *aux=h;
    if(h){
        while(aux){
            std::cout<<"Neurona: "<<aux->id<<std::endl;
            std::cout<<"Voltaje: "<<aux->voltaje<<std::endl;
            std::cout<<"posicion en X: "<<aux->posicion_x<<std::endl;
            std::cout<<"Posicion en Y: "<<aux->posicion_y<<std::endl;
            std::cout<<"Rojo: "<<aux->red<<std::endl;
            std::cout<<"Verde: "<<aux->green<<std::endl;
            std::cout<<"Azul: "<<aux->blue<<std::endl;
            aux=aux->sig;
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Lista vacia");
        msgBox.exec();
    }

}

Administrar *lis=new Administrar();
int id, posicion_x, posicion_y, red, green, blue, buscar;
float voltaje;

//INSERTAR ID
void MainWindow::on_insertarID_textChanged(const QString &arg1)
{
    std::string idStd = arg1.toStdString();
    bool band =! idStd.empty() && std::all_of(idStd.begin(), idStd.end(), [](char cad){
        return std::isdigit(static_cast<unsigned char>(cad));
    });

    if (band)
    {
        id= std::stoi(idStd);
    }
}
//INSERTAR VOLTAJE
void MainWindow::on_insertarVOLT_valueChanged(int arg1)
{
    voltaje = arg1;
}
//INSERTAR POSICION X
void MainWindow::on_insertPX_valueChanged(int arg1)
{
    posicion_x = arg1;
}
//INSERTAR POSICION Y
void MainWindow::on_insertPY_valueChanged(int arg1)
{
    posicion_y = -arg1;
}
//INSERTAR RED
void MainWindow::on_insertRED_valueChanged(int value)
{
    red = value;
}
//INSERTAR BLUE
void MainWindow::on_insertBLUE_valueChanged(int value)
{
    blue = value;
}
//INSERTAR GREEN
void MainWindow::on_insertGREEN_valueChanged(int value)
{
    green = value;
}
//INSERTAR AL INICIO
void MainWindow::on_agregarINICIO_clicked()
{
    lis->agregrarInicio(id, voltaje, posicion_x, posicion_y, red, green, blue);
    vaciar();
}
//INSERTAR AL FINAL
void MainWindow::on_insertarFINAL_clicked()
{
    lis->agregarFinal(id, voltaje, posicion_x, posicion_y, red, green, blue);
    vaciar();
}
//MOSTRAR NEURONAS EN PLAINTEXTEDIT
void MainWindow::on_mostrar_neuronas_clicked()
{
    QString lista;
    Neurona *aux=lis->h;

    if(aux)
    {
        while(aux)
        {
            QString mostrar = "Neurona: " + QString::number(aux->id) + "\n";
            mostrar += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            mostrar += "Posicion X: " + QString::number(aux->posicion_x) + "\n";
            mostrar += "Posicion Y: " + QString::number(aux->posicion_y) + "\n";
            mostrar += "Rojo: " + QString::number(aux->red) + "\n";
            mostrar += "Verde: " + QString::number(aux->green) + "\n";
            mostrar += "Azul: " + QString::number(aux->blue) + "\n\n";

            lista += mostrar;
            aux=aux->sig;
        }
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Lista vacia");
        msgBox.exec();
    }
    ui->plainTextEdit->setPlainText(lista);

}
//VACIAR VALORES
void MainWindow::vaciar()
{
    id=0;
    voltaje=0.0;
    posicion_x=0;
    posicion_y=0;
    red=0;
    green=0;
    blue=0;

    ui->insertarID->clear();
    ui->insertarVOLT->setValue(0);
    ui->insertPX->setValue(0);
    ui->insertPY->setValue(0);
    ui->insertRED->setValue(0);
    ui->insertBLUE->setValue(0);
    ui->insertGREEN->setValue(0);
}
//GUARDAR
void MainWindow::on_guardar_archivo_clicked()
{
    //elegir la ubicación y el nombre del archivo
    QString archivo= QFileDialog::getSaveFileName(this, tr("Save File"), "/home", tr("Text files (*.txt)"));

    if (!archivo.isEmpty())
    {
        //crear objeto para escribir en el archivo
        std::ofstream file(archivo.toStdString());

        if(file.is_open())
        {
            //recorrer la lista
            Neurona* actual= lis->h;
            while(actual)
            {
                file<<actual->id<<'|'<<actual->voltaje<<'|'<<actual->posicion_x<<'|'<<actual->posicion_y<<'|'<<actual->red<<'|'<<actual->green<< '|'<<actual->blue<<'*';
                actual=actual->sig;
            }
            file.close();
            QMessageBox msgBox;
            msgBox.setText("Se han guardado los elementos");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Error al abrir el archivo");
            msgBox.exec();
        }
    }
}
//CARGAR
void MainWindow::on_cargar_archivo_clicked()
{
    QString archivo= QFileDialog::getOpenFileName(this, tr("Save File"), "/home", tr("Text files (*.txt)"));

    if(!archivo.isEmpty())
    {
        //conv nombre de archivo de qstring to std::string
        std::string filenameStd= archivo.toStdString();

        //objeto para leer archivo
        std::ifstream file(filenameStd);

        if (file.is_open())
        {
            int id, posicion_x, posicion_y, red, green, blue;
            float voltaje;

            //leer archivo linea por linea
            while(file>>id>>voltaje>>posicion_x>>posicion_y>>red>>green>>blue)
            {
                lis->agregarFinal(id, voltaje, posicion_x, posicion_y, red, green, blue);
            }
            file.close();

            QMessageBox msgBox;
            msgBox.setText("Se han cargado las neuronas a la lista");
            msgBox.exec();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("Error al abrir el archivo");
            msgBox.exec();
        }
    }
}
//ID A BUSCAR
void MainWindow::on_spinBox_valueChanged(int arg1)
{
    buscar = arg1;
}
//MOSTRAR NEURONAS EN LA TABLA
void MainWindow::on_search_clicked()
{
    Neurona* id_neurona = lis->buscar(buscar);

    if (id_neurona != nullptr)
    {
        QStringList inf;
        inf << "Neurona ID" << "Voltaje" << "Posición X" << "Posición Y" << "Red" << "Blue" << "Green";

        ui->tableWidget->setColumnCount(7);
        ui->tableWidget->setHorizontalHeaderLabels(inf);
        ui->tableWidget->clearContents();

        //numero de filas
        ui->tableWidget->setRowCount(1);

        //valor de cualquier tipo
        QVariantList valor =
            {
                id_neurona->id,
                id_neurona->voltaje,
                id_neurona->posicion_x,
                id_neurona->posicion_y,
                id_neurona->red,
                id_neurona->blue,
                id_neurona->green
            };
        //crea elementos para cada celda de las filas
        for (int i = 0; i < 7; ++i)
        {
            QTableWidgetItem* element = new QTableWidgetItem(valor[i].toString());
            ui->tableWidget->setItem(0, i, element);
        }

        //ajustar contenido de columnas
        ui->tableWidget->resizeColumnsToContents();
        ui->tableWidget->resizeRowsToContents();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("No existen elementos");
        msgBox.exec();
    }
}
//DIBUJAR NEURONAS
void MainWindow::on_dibujar_clicked()
{
    QPen pen;
    QBrush Brush;
    int ancho, alto, x, y;

    //lista
    Neurona* aux = lis->h;

    if(aux!=nullptr)
    {

    while (aux != nullptr)
        {
            QColor color(aux->red, aux->green, aux->blue);
            pen.setColor(color);
            Brush.setColor(color);
            Brush.setStyle(Qt::SolidPattern);
            //obtener la posicion
            x=aux->posicion_x;
            y=aux->posicion_y;
            ancho= aux->voltaje;
            alto= aux->voltaje;

            QGraphicsEllipseItem* ellipse = scene->addEllipse(x, y, alto, ancho, pen, Brush);
            aux =aux->sig;
    }
    ui->graphicsView;
    }
    else
    {
    QMessageBox msgBox;
    msgBox.setText("No existen neuronas");
    msgBox.exec();
    }
}
//ORDENAR ID METODO BURBUJA
void Administrar::ordenarId()
{
    if (!h)
    {
            QMessageBox msgBox;
            msgBox.setText("No hay neuronas en la lista");
            msgBox.exec();
    }

    Neurona *aux = h;
    Neurona *tmp = nullptr;
    bool band = true;
    int temp_id, temp_posx, temp_posy, temp_red, temp_green, temp_blue;
    float temp_volt;

    while (band)
    {
            band= false;//cambia a true si se realiza un cambio
            aux= h;

            while (aux->sig != tmp) //recorre hasta el nodo antes de temp
            {
            if (aux->id > aux->sig->id)//intercambio
            {
                temp_id = aux->id;
                temp_volt = aux->voltaje;
                temp_posx = aux->posicion_x;
                temp_posy = aux->posicion_y;
                temp_red = aux->red;
                temp_green = aux->green;
                temp_blue = aux->blue;

                aux->id= aux->sig->id;
                aux->voltaje= aux->sig->voltaje;
                aux->posicion_x= aux->sig->posicion_x;
                aux->posicion_y= aux->sig->posicion_y;
                aux->red= aux->sig->red;
                aux->green= aux->sig->green;
                aux->blue= aux->sig->blue;

                aux->sig->id= temp_id;
                aux->sig->voltaje= temp_volt;
                aux->sig->posicion_x= temp_posx;
                aux->sig->posicion_y= temp_posy;
                aux->sig->red= temp_red;
                aux->sig->green= temp_green;
                aux->sig->blue= temp_blue;

                band= true;
            }
            aux= aux->sig;
            }
            tmp= aux;
    }
}
//ORDENAR VOLTAJE METODO BURBUJA
void Administrar::ordenarVoltaje()
{
    if (!h)
    {
            QMessageBox msgBox;
            msgBox.setText("No existen neurona");
            msgBox.exec();
    }

    Neurona *aux= h;
    Neurona *tmp= nullptr;
    bool band= true;
    int temp_id, temp_posx, temp_posy, temp_red, temp_green, temp_blue;
    float temp_volt;

    while (band)
    {
            band= false;
            aux= h;

            while (aux->sig != tmp)
            {
            if (aux->voltaje > aux->sig->voltaje)
            {
                temp_id= aux->id;
                temp_volt= aux->voltaje;
                temp_posx= aux->posicion_x;
                temp_posy= aux->posicion_y;
                temp_red= aux->red;
                temp_green= aux->green;
                temp_blue= aux->blue;

                aux->id= aux->sig->id;
                aux->voltaje= aux->sig->voltaje;
                aux->posicion_x= aux->sig->posicion_x;
                aux->posicion_y= aux->sig->posicion_y;
                aux->red= aux->sig->red;
                aux->green= aux->sig->green;
                aux->blue= aux->sig->blue;

                aux->sig->id= temp_id;
                aux->sig->voltaje= temp_volt;
                aux->sig->posicion_x= temp_posx;
                aux->sig->posicion_y= temp_posy;
                aux->sig->red= temp_red;
                aux->sig->green= temp_green;
                aux->sig->blue= temp_blue;

                band= true;
            }
            aux= aux->sig;
            }
            tmp= aux;
    }
}
//MOSTRAR ID ORDENADO
void MainWindow::on_ordenar_id_clicked()
{
    lis->ordenarId();
    ui->mostrarOrdenar->clear();

    Neurona *aux= lis->h;
    while(aux)
    {
            QString mostrar = "Neurona: " + QString::number(aux->id) + "\n";
            mostrar += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            mostrar += "Posición en X: " + QString::number(aux->posicion_x) + "\n";
            mostrar += "Posición en Y: " + QString::number(aux->posicion_y) + "\n";
            mostrar += "Rojo: " + QString::number(aux->red) + "\n";
            mostrar += "Verde: " + QString::number(aux->green) + "\n";
            mostrar += "Azul: " + QString::number(aux->blue) + "\n\n";

            ui->mostrarOrdenar->setPlainText(mostrar);

            aux = aux->sig;
    }
}
//MOSTRAR VOLTAJE ORDENADO
void MainWindow::on_ordenar_voltaje_clicked()
{
    lis->ordenarVoltaje();
    ui->mostrarOrdenar->clear();

    Neurona *aux= lis->h;
    while(aux)
    {
            QString mostrar = "Neurona: " + QString::number(aux->id) + "\n";
            mostrar += "Voltaje: " + QString::number(aux->voltaje) + "\n";
            mostrar += "Posición en X: " + QString::number(aux->posicion_x) + "\n";
            mostrar += "Posición en Y: " + QString::number(aux->posicion_y) + "\n";
            mostrar += "Rojo: " + QString::number(aux->red) + "\n";
            mostrar += "Verde: " + QString::number(aux->green) + "\n";
            mostrar += "Azul: " + QString::number(aux->blue) + "\n\n";

            ui->mostrarOrdenar->setPlainText(mostrar);

            aux= aux->sig;
    }
}
//FUERZA BRUTA
void MainWindow::unir_neuronas()
{
    QList<QGraphicsItem*> lineas = scene->items();//lista de elemntos
    for (QGraphicsItem* item : lineas)
    {
            if (item->type() == QGraphicsLineItem::Type)//tipo linea
            {
            scene->removeItem(item);//eliminar y liberar memoria
            delete item;
            }
    }

    //conectar neuronas cercanas
    if (mostrar_linea)
    {
            Neurona *aux = lis->h;
            while (aux != nullptr)//recorrer neurona
            {
            Neurona* neu_cerc = nullptr;
            //almacena distancia min
            float minimo = std::numeric_limits<float>::max();

            Neurona* temp = lis->h;//comparar actual con el resto
            while (temp != nullptr)
            {
                if (aux != temp)
                {
                    //calcular distancias
                    float centro_x1 = aux->posicion_x + aux->voltaje / 2;
                    float centro_y1 = aux->posicion_y + aux->voltaje / 2;
                    float centro_x2 = temp->posicion_x + temp->voltaje / 2;
                    float centro_y2 = temp->posicion_y + temp->voltaje / 2;
                    float distancia = sqrt(pow(centro_x2 - centro_x1, 2) + pow(centro_y2 - centro_y1, 2));

                    if (distancia < minimo)
                    {
                        minimo = distancia;
                        neu_cerc = temp;
                    }
                }
                temp = temp->sig;
            }

            if (neu_cerc != nullptr)
            {

                QPointF inicio(aux->posicion_x + aux->voltaje / 2, aux->posicion_y + aux->voltaje / 2);
                QPointF dest(neu_cerc->posicion_x + neu_cerc->voltaje / 2, neu_cerc->posicion_y + neu_cerc->voltaje / 2);

                scene->addLine(QLineF(inicio, dest));//agregar linea
                QGraphicsTextItem* texto = scene->addText(QString::number(minimo));
                texto->setPos((inicio + dest) / 2);
            }
            aux = aux->sig;
            }
    }
    ui->graphicsView->viewport()->update();
    /*QList<QGraphicsItem*> lineas = scene->items();
    for (QGraphicsItem* item : lineas) {
            if (item->type() == QGraphicsLineItem::Type) {
            scene->removeItem(item);
            delete item;
            }
    }

    if (lineasVisibles) {
            Neurona* aux = lis->h;
            while (aux != nullptr) {
            Neurona* neuronaMasCercana = nullptr;
            float distanciaMinima = std::numeric_limits<float>::max();

            Neurona* temp = lis->h;
            while (temp != nullptr) {
                if (aux != temp) {
                    float centro_x1 = aux->posicion_x + aux->voltaje / 2;
                    float centro_y1 = aux->posicion_y + aux->voltaje / 2;
                    float centro_x2 = temp->posicion_x + temp->voltaje / 2;
                    float centro_y2 = temp->posicion_y + temp->voltaje / 2;
                    float distancia = sqrt(pow(centro_x2 - centro_x1, 2) + pow(centro_y2 - centro_y1, 2));

                    if (distancia < distanciaMinima) {
                        distanciaMinima = distancia;
                        neuronaMasCercana = temp;
                    }
                }
                temp = temp->sig;
            }

            if (neuronaMasCercana != nullptr) {
                    //int idNodoInicio = aux->id;
                    //int idNodoFin = neuronaMasCercana->id;
                    //float peso = distanciaMinima;
                    QPointF centroInicio(aux->posicion_x + aux->voltaje / 2, aux->posicion_y + aux->voltaje / 2);
                    QPointF centroFin(neuronaMasCercana->posicion_x + neuronaMasCercana->voltaje / 2, neuronaMasCercana->posicion_y + neuronaMasCercana->voltaje / 2);

                    scene->addLine(QLineF(centroInicio, centroFin));
                    QGraphicsTextItem* texto = scene->addText(QString::number(distanciaMinima));
                    texto->setPos((centroInicio + centroFin) / 2);
                }
                aux = aux->sig;
            }
            }
            ui->graphicsView->viewport()->update();
                /*
                QPointF puntoInicio(aux->posicion_x + aux->voltaje / 2, aux->posicion_y + aux->voltaje / 2);
                QPointF puntoFin(neuronaMasCercana->posicion_x + neuronaMasCercana->voltaje / 2, neuronaMasCercana->posicion_y + neuronaMasCercana->voltaje / 2);

                // Crear una línea
                QGraphicsLineItem* linea = scene->addLine(QLineF(puntoInicio, puntoFin));

                // Crear un texto para mostrar la dirección y el peso
                QGraphicsTextItem* texto = new QGraphicsTextItem;
                texto->setPlainText(QString::number(neuronaMasCercana->id));
                texto->setPos((puntoInicio + puntoFin) / 2);  // Coloca el texto en el centro de la línea
                scene->addItem(texto);
            }
            aux = aux->sig;
            }
    }

    ui->graphicsView->viewport()->update();
*/
}
//MOSTRAR LINEAS
void MainWindow::on_lineaas_clicked()
{
    mostrar_linea = !mostrar_linea;
    unir_neuronas();
}
