#ifndef BRPRINT3D_H
#define BRPRINT3D_H
#include <QMainWindow>
#include <Windows/loading.h>
#include <Windows/documentation.h>
#include <Windows/aboutbrprint.h>
#include <Windows/help.h>
#include <Windows/legalwarning.h>
#include <Windows/loading.h>

#include "points.h"
#include "KI/Repetier.h"
#include "threadRotine.h"
#include "arduinolistener.h"
#include "control3d.h"
#include "manualcontrol.h"
#include "printerconfigs.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <QTranslator>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include <QVariant>
#include <QSettings>
#include <QObject>
#include <QList>
#include <QInputDialog>
#include <QList>
#include <QStandardPaths>



namespace Ui {
class BrPrint3D;
}

class BrPrint3D : public QMainWindow
{
    Q_OBJECT

public:
    explicit BrPrint3D(QWidget *parent = 0);
    ~BrPrint3D();
    void init();
    void readstl(QString file);
    void renderGcode(QString str);
    void readgcode(QString text);

private slots:
    void locate_Arduino(bool b);
    //void on_bt_hide_clicked();

    void on_bt_import_clicked();
    void on_bt_open_clicked();
    void on_bt_connect_clicked(bool checked);
    void on_bt_play_clicked();
    void on_bt_pause_clicked(bool checked);
    void on_bt_stop_clicked();
    void on_bt_emergency_clicked();

    void updateTemp(double *temp_Extruders, double tempTable);
    void updateExt(double posX, double posY, double posZ);

    void isPrintJobRunning(bool b);



private:

    Ui::BrPrint3D *ui;
    double *tempMesa;
    double *tempExtruders;
    int extrudersInUse;
    bool isCommaDecimalMark;
    bool resetWhenConnect;
    QTranslator translator;
    Repetier *printer_object=NULL;
    QStringList *open_files;                            //Lista de arquivos abertos
    ThreadRoutine *temp=NULL;
    arduinoListener *ard_List;

    //Definicoes Slicer
    QString pathslicer;                         //Caminho do slicer
    QString pathcura;                           //Caminho Cura
    QString pathextern;                         //Caminho slicer externo

    //Lista de Pontos do gcode
    QList<Points*> gcodeDots;
    //
    QString pathGcode;                  //Caminho do GCODE

    bool garbage; //Garbage - variable unused


    void locate_Slicer();
    void locate_Cura();


protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

};

#endif // BRPRINT3D_H
