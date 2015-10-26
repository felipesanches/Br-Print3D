#ifndef PRINTERCONFIGS_H
#define PRINTERCONFIGS_H

#include <QWidget>
#include <QSettings>

namespace Ui {
class PrinterConfigs;
}

class PrinterConfigs : public QWidget
{
    Q_OBJECT

public:
    explicit PrinterConfigs(QWidget *parent = 0);
    ~PrinterConfigs();
   void init(QSettings *settings);

private:
    Ui::PrinterConfigs *ui;
    QSettings settings;
    QString extruderTemperature="";         //Temperatura Default Extrusor
    QString bedTemperature="";            //Temperatura Default Mesa
    QString extruderMAXTemp="";             //Temperatura Maxima do Extrusor
    QString bedMAXTemp="";                //Temperatura Maxima da Mesa
    QString areaX="2";                       //Tamanho da mesa no eixo X
    QString areaY="2";                       //Tamanho da mesa no eixo Y
    QString areaZ="2";                       //Tamanho da mesa no eixo Z
    QString rateMoviment;                        //Taxa de Movimento da Mesa
    QString extruderSpeed;                       //Velocidade do Extrusor
    QString extruderRetraction;                  //Velocidade de Retracao do Extrusor
    QString extruderQnt;              //Quantidade de extrusores
    QString connectionType;
    QString transmissionRate;
    QString firmwareType;
    QString cacheSize;
    QString connectionPort;
    int resetOnConnect, resetOnEmergency, printLog, qntextruders;
    QString feedZ;
    QString extruderMAXVol;

};

#endif // PRINTERCONFIGS_H
