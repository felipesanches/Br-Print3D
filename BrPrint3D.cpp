#include "BrPrint3D.h"
#include "ui_Pandora.h"


BrPrint3D::BrPrint3D(QWidget *parent) : QMainWindow(parent),
ui(new Ui::BrPrint3D)
{
    ui->setupUi(this);

}

BrPrint3D::~BrPrint3D()
{
    delete ui;

}

QSettings settings(QDir::currentPath()+"/br.ini",QSettings::IniFormat); //INI File


/*******************************************************************************************************************/
/* Code Organization - English
 * Function Init
 *
 * --Actions MenuBar--
 * Exit
 * Change Language
 * About -> BrPrint, Documentation, Help, Legal Warning
 *
 * Function Hide/Show Configuration
 * Function's of Search
 *  Locate Slier
 *  Locar Cura
 *  Locate Arduino -> Not used
 * Actions about Slicer
 *  Start Slicing
 *  Stop Slicing
 * Actions MenuBar
 *  Import Gcode ready to print
 *  Open Gcode or STL
 *  Connect/Disconnect 3DPrinter
 * Actions Save Configs
 * Action Statics of Print Job
 * Action Load Cofigs
 *
 * --Actions RTO--
 * MenuBar
 *  Start Print Job(Play)
 *  Pause Print Job
 *  Stop Print Job
 *  Stop Print job on Emergency
 * Manual Control:
 *  Move X to 0
 *  Move Y to 0
 *  Move Z to 0
 *  Move XYZ to 0
 *  Move X to Left - width
 *  Move X to Right - width
 *  Move Y to Back -heigh
 *  Move Y to Front -heigh
 *  Move Z to Up -Vertical
 *  Move Z to Down -Vertical
 *  Retract Fill
 *  Expulse Fill 1x
 *  Expulse Fill 2x
 *  Set Speed of feed fill
 *  Set flow rate of fill
 *  Set cooler fan
 *  ON/OFF bed heating
 *  ON/OFF Extruders heating
 *
 * --3D Actions--
 * Render model from GCODE
 * Render model fom STL
 * Rotate model
 * Zoom in/out
 * Prism Print Area
 * Render model during the print job
 * --Convenience Functions--
 * Thread monitoring of temperature
 * Thread monitoring of extruder position
 * Thread monitoring connection of arduino -> not used
 * Block/Unblock button position of extruder to safety
 * Close Event
 * */
//Below comments its only for me-> Lays
/*Organização do Código - Portuguese
 * Função de Inicialização da Pandora
 *
 * --Ações MenuBar--
 *  Sair
 *  Alterar Idioma -> Portugues/Ingles
 *  Sobre -> BrPrint, Documentação, Ajuda, Aviso Legal
 *
 * Função Hide/Show Configurações
 * Funções de Busca
 *  Locate Slicer
 *  Locate Cura
 *  Locate Arduino
 * Funções de Ações sobre Slicer
 *  Iniciar Fatiamento
 *  Cancelar Fatiamento
 * Ações Barra de Menu
 *  Importar GCODE pronto pra impressão
 *  Abrir GCODE ou STL
 *  Conectar/Desconectar Impressora
 * Ação Salvar Configurações
 * Ação estatísticas de impressão
 * Ação Carregar Configurações
 *
 * --Ações com a Impressora--
 * Ações Barra de Menu
 *  Iniciar Impressão
 *  Pausar Impressão
 *  Cancelar Impressão
 *  Parada de Emergência
 * Controle Manual:
 *  Mover X para 0
 *  Mover Y para 0
 *  Mover Z para 0
 *  Mover XYZ para 0
 *  Mover X para Esquerda - largura
 *  Mover X para Direita - largura
 *  Mover Y para Trás -profundidade
 *  Mover Y para Frente -profundidade
 *  Mover Z para Cima -altura
 *  Mover Z para Baixo -altura
 *  Recolher Filamento
 *  Expulsar Filamento 1x
 *  Expulsar Filamento 2x
 *  Set Velocidade de alimentação de filamento
 *  Set Vazão de saída de filamento
 *  Set velocidade do cooler
 *  Ligar/Desligar aquecimento da Mesa
 *  Ligar/Desligar aquecimento do(s) Extrusore(s)
 *
 *--Ações 3D--
 * Renderizar Objeto a partir de um GCODE
 * Renderizar Objeto a partir de um STL
 * Rotacionar Objeto
 * Zoom in/out do Objeto
 * Ter um cubo de impressão nas medidas de área inseridas pelo usuário
 * Renderizar objeto durante impressão
 *
 * --Funções de Conveniencia--
 * Thread de Monitoramento de Temperatura
 * Thread de Monitoramento de Posição do Extrusor
 * Thread de Monitoramento de Conexão de Arduino
 * Função de Liberação de Botões de Extrusores a partir da qnt selecionada
 * Desabilitar botões de movimento de extrusor durante impressão
 * Ação CloseEvent - Verificar se o usuario deseja mesmo fechar o programa
 * Detectar idioma da máquina e carregar pandora com o idioma do sistema
 *

*/

/*-----------Pandora Initialization--------*/
/*This function makes the initialization of the UI.
Loading previously saved settings, locating slicers and Arduino connection.*/
void BrPrint3D::init()
{   Loading *l=new Loading();
    //l->setParent(this,Qt::Window);
    //l->show();

    //Call init Printer Configs
    ui->gb_PrinterConfigs->init(&settings);

    //Call init Manual Control
    ui->tb_ManualControl->init();


    //Hide Config Menu
    ui->gb_PrinterConfigs->hide();
    ui->openGLWidget->setGeometry(20,160,900,510);

    //Disable Play Button
    ui->bt_play->setEnabled(false);

    //Disable Manual Control of Printer
    ui->tb_ManualControl->widget(2)->setEnabled(false);
    //Disable Slicer Tab - Because is not done
    //QTabWidget *t = ui->tb_ManualControl->widget(1);
    //t->widget(2)->setEnabled(false);


    //Start the thread that is listening if Arduino is connect or not
    this->ard_List = new arduinoListener;
    connect(ard_List,SIGNAL(arduinoConnect(bool)),this,SLOT(locate_Arduino(bool)));
    this->ard_List->start();
    //Connect a signal to hide extruders if change on qnt of extruders
    connect(ui->gb_PrinterConfigs,SIGNAL(hideExtruders(int)),ui->tb_ManualControl,SLOT(hideExtruders(int)));
}
/*-----------Actions of MenuBar----------*/

//This Action change the language of the program to English
void BrPrint3D::on_actionEnglish_triggered()
{
    qApp->removeTranslator(&translator);
    translator.load(":/Translations/EN_english.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);

}
//This Action change the language of the program to Portuguese
void BrPrint3D::on_actionPortuguese_triggered()
{
    qApp->removeTranslator(&translator);
    translator.load(":/Translations/PT_portuguese.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}
//This action show on screen the Legal Warning Window of BrPrint
void BrPrint3D::on_actionLegalWarning_triggered()
{
    LegalWarning *w=new LegalWarning();
    w->show();

}
//This Action Close the program - Necessary???
void BrPrint3D::on_actionClose_triggered()
{

}

//This action show on screen the Documentation Window of BrPrint
void BrPrint3D::on_actionDocumentation_triggered()
{
    Documentation *w= new Documentation();
    w->show();
}

//This action show on screen the Help Window
void BrPrint3D::on_actionHelp_triggered()
{
    Help *w= new Help();
     w->show();
}

//This action show on screen the about Window of BrPrint
void BrPrint3D::on_actionAboutBrPrint_triggered()
{
    aboutBrPrint *w= new aboutBrPrint();
    w->show();
}







/*----------Actions---------------------*/
//This action Hide/Show The Configuration of Printer
void BrPrint3D::on_bt_Hide_clicked()
{
    if(ui->bt_Hide->text()==tr("Configuration - Show"))
    {
        ui->bt_Hide->setText(tr("Configuration - Hide"));
        ui->gb_PrinterConfigs->show();
       // ui->openGLWidget->setGeometry(460,160,480,510);
    }
    else
    {
        ui->bt_Hide->setText(tr("Configuration - Show"));
        ui->gb_PrinterConfigs->hide();
       // ui->openGLWidget->setGeometry(20,160,900,510);
    }
}

//This function locate the port that the arduino is connect
void BrPrint3D::locate_Arduino(bool b)
{   this->ard_List->wait(2000);
    this->ard_List->quit();
    this->ard_List->deleteLater();
    QList<QString> ports;
    garbage=std::system("dmesg | grep -i usb > usbport.txt");
    QFile usbport("usbport.txt");
    if(usbport.open(QIODevice::ReadOnly|QIODevice::Text))
    {   QTextStream in(&usbport);
        QString file = in.readAll();
        usbport.close();
        QString port,ant=NULL;
        std::string temp = file.toStdString();
        const char *look = temp.c_str();
        //qDebug()<<QString(word)
        look = strstr(look, "Arduino");
        while(look != NULL)
        {
            look = strstr(look, "tty");
            for(int i = 0; look[i] != ':'; i++)
                port+=look[i];
            if(ant!=port)
            {   ports.append("/dev/"+port);
                ant=port;
            }
            port.clear();
            look = strstr(look, "Arduino");
        }
    }
    if(!ports.isEmpty())
    {   ui->cb_Connection_Port->addItems(ports);
        QMessageBox msg;
        msg.setText("The arduino is connect at new ports then default, please check on Configs Menu to switch ports!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
    }


}

//This action import a GCODE file to print
void BrPrint3D::on_bt_import_clicked()
{
    pathGcode=QFileDialog::getOpenFileName(this, "Open File",QDir::homePath(),"*.gcode");

    if(!pathGcode.isEmpty() && QFileInfo(pathGcode).completeSuffix()=="gcode")
    {   QFile gcode(pathGcode);
        if(gcode.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&gcode);
            QString text = in.readAll();
            readgcode(text);
            gcode.close();
            ui->GCodePreview->setPlainText(text);
            if(ui->bt_connect->isChecked())
                ui->bt_play->setEnabled(true);

        }
    }
}
//This action open a GCODE or STL file
void BrPrint3D::on_bt_open_clicked()
{
    pathGcode=QFileDialog::getOpenFileName(this, "Open File",QDir::homePath(),"*.gcode");

    if(!pathGcode.isEmpty() && QFileInfo(pathGcode).completeSuffix()=="gcode")
    {   QFile gcode(pathGcode);
        if(gcode.open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(&gcode);
            QString text = in.readAll();
            readgcode(text);
            gcode.close();
            ui->GCodePreview->setPlainText(text);
        }
    }
   /* else if(QFileInfo(filename).completeSuffix()=="STL" ||QFileInfo(filename).completeSuffix()=="stl")
    {
        //ui->GCodePreview->setPlainText("");
        //QVector<triangle> QFileInfo(filename).baseName();
        //ERRADO!
       // QFile stl(filename);
        //readstl(filename);
        //Renderiza Imagem
    }*/
}
//This function transform the gcode file on a vector of points and send to OpenGL to draw
void BrPrint3D::readgcode(QString text)
{
    QStringList list = text.split("\n",QString::SkipEmptyParts);


    float x=0,y=0,z=0;
    for(int i=0; i!=list.size(); i++)
    {
        if(list[i].startsWith(";")==false)
        {
            QStringList aux = list[i].split(" ");
            //qDebug() << QStringList(aux) << "\n";
            for(int j=1;j!=aux.size();j++)
            {
                if(aux[j].startsWith("X") && aux[j+1].startsWith("Y"))
                {
                    //ler ponto
                    QString x_str = aux[j].section("X",1);
                     x = x_str.toFloat();
                    QString y_str = aux[j+1].section("Y",1);
                     y = y_str.toFloat();
                      Points *p= new Points();
                      p->addPoint(x,y,z);
                      gcodeDots.append(p);
                }
               else if(aux[j].startsWith("Z"))
                {
                  //ler ponto
                    QString z_str = aux[j].section("Z",1);
                    z = z_str.toFloat();
                    Points *p= new Points();
                    p->addPoint(x,y,z);
                    gcodeDots.append(p);
                }
            }//fim for j
        }
    }//fim for i
  ui->openGLWidget->openGcode(&gcodeDots);
  ui->openGLWidget->update();
}
//This action connect the 3D printer
void BrPrint3D::on_bt_connect_clicked(bool checked)
{  QMessageBox msg;
    int maxX,maxY,maxZ,transmitionRate,bufferSize;
    std::string serialPort;
   if(checked==true)
   {    PrinterSettings p = ui->gb_PrinterConfigs->getCurrentSettings();
        if(!p.areaX.isEmpty() && !p.areaY.isEmpty() && !p.areaZ.isEmpty())
        {
            maxX = p.areaX.toInt();
            maxY = p.areaY.toInt();
            maxZ = p.areaZ.toInt();
            transmitionRate = p.transmissionRate.toInt();
            serialPort = p.connectionPort.toInt();
            bufferSize = p.cacheSize.toInt();
            ui->tb_ManualControl->widget(2)->setEnabled(true);
        }
        else
        {    msg.setText(tr("Make sure you have all the necessary settings for connection!"));
             msg.setIcon(QMessageBox::Warning);
             msg.exec();
             ui->bt_connect->setChecked(false);
             return;
        }

        if(p.resetOnConnect==true)
             this->resetWhenConnect = true;
        else
             this->resetWhenConnect = false;


        //This check the decimal point valid
        QLocale locale;
        QChar c = locale.decimalPoint();
        if(c=='.')
            this->isCommaDecimalMark = false;
         else
            this->isCommaDecimalMark = true;


        try
        {
            printer_object = new Repetier(transmitionRate, serialPort, bufferSize, maxX, maxY, maxZ, resetWhenConnect, isCommaDecimalMark);
            this->qntExtruders = printer_object->getNoOfExtruders();
            emit setExtrudersQnt(this->qntExtruders);
            //Send to manual control the PrinterObjetct to control the 3dprinter
            ui->tb_ManualControl->getPrinterObject(&this->printer_object);

           //Enable button for start printing
           ui->bt_play->setEnabled(true);
           //Message the user that the connections is successful
           msg.setText(tr("Successful Connection"));
           msg.setIcon(QMessageBox::Information);
           msg.exec();
        }
        catch(std::string exc)
        {   QString e =QString::fromUtf8(exc.c_str());
            msg.setText(e);
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
            ui->tb_ManualControl->widget(2)->setEnabled(false);
            ui->bt_connect->setChecked(false);
        }

     }//fim if check true
     else
     {
       this->printer_object->setBedTemp(0);
       int qnt = this->printer_object->getNoOfExtruders();
       for(int i=0;i<qnt;i++)
       {
           this->printer_object->setExtrTemp(i,0);
       }
       //Stop and Kill the thread
       ui->tb_ManualControl->stopThreadRoutine();
       //Kill the object
       this->printer_object->~Repetier();
       //Off Bed
       ui->tb_ManualControl->setBedStatus(false);
       //Off Extruder
       ui->tb_ManualControl->setExtruderStatus(false);
       //Disable the ManualControl
       ui->tb_ManualControl->widget(2)->setEnabled(false);
     }
}


/*-----------Printer Actions-----------*/
//This actions start the printer job
void BrPrint3D::on_bt_play_clicked()
{     QMessageBox msg;
     if(!pathGcode.isEmpty())
     {  //destroy the thread
         this->temp->setLoop(true);
         this->temp->wait(2000);
         this->temp->quit();
         this->temp->~ThreadRoutine();
         try
         {
            std::string path = pathGcode.toUtf8().constData();
            this->printer_object->openFile(path,ui->ck_logImpressao->isChecked());

          }
         catch(std::string exc)
         {
             QMessageBox msg;
             msg.setIcon(QMessageBox::Critical);
             QString str = QString::fromUtf8(exc.c_str());
             msg.setText(str);
             msg.exec();

         }
         ui->bt_play->setEnabled(false);
         ui->bt_pause->setEnabled(true);
         ui->bt_stop->setEnabled(true);
         this->printer_object->startPrintJob(true);
         msg.setText(tr("Print Job Started"));
         msg.exec();
         //Create a new thread and connect some signals
        temp = new ThreadRoutine(this->printer_object,&extrudersInUse);
         this->temp->start();

         connect(temp,SIGNAL(updateTemp(double*,double)),this,SLOT(updateTemp(double*,double)));
         connect(temp,SIGNAL(updateExt(double,double,double)),this,SLOT(updateExt(double,double,double)));
         connect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));

         //Disable some buttons - to safety
         disableAxisButtons();
         ui->cb_Extruder_qnt->setEnabled(false);
     }
}
//Pensar melhor aqui, por causa do dialog box finalizado/pausado
//This action pause the print job
void BrPrint3D::on_bt_pause_clicked(bool checked)
{
    if(checked==true)
    {     this->printer_object->stopPrintJob();
          disconnect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));
    }
    else
    {   this->printer_object->startPrintJob(false);
        connect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));
    }

}
//This action stop the print job
void BrPrint3D::on_bt_stop_clicked()
{
    ui->bt_play->setEnabled(true);
    ui->bt_pause->setEnabled(false);
    ui->bt_stop->setEnabled(false);
    this->printer_object->stopPrintJob();
    this->printer_object->closeFile();
    try{
    this->printer_object->setBedTemp(0);
    }
    catch(std::string exc)
    {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.exec();
    }

    for(int i=0;i<this->extrudersInUse;i++)
        this->printer_object->setExtrTemp(i,0);
    enableAxisButtons();
}
//This action stop print job in emergency case
void BrPrint3D::on_bt_emergency_clicked()
{   QMessageBox msg;
    try
    {
      this->temp->setLoop(true);
       this->temp->wait(2000);
       this->temp->quit();
       this->temp->~ThreadRoutine();

       msg.setText("Emergency Stop Clicked, click on 'Ok' and wait!");
       msg.setIcon(QMessageBox::Critical);
       msg.exec();
       this->printer_object->scramPrinter();
       msg.setText("Emergency Stop Succeful!");
       msg.setIcon(QMessageBox::Critical);
       msg.exec();
       this->printer_object->~Repetier();
       ui->bt_connect->setChecked(false);
       enableAxisButtons();

    }
    catch(std::string exc)
    {
        QString str = QString::fromUtf8(exc.c_str());
        msg.setText(str);
        msg.setIcon(QMessageBox::Critical);
        msg.exec();
    }
}



/*------------Other Functions--------*/

//This slot inform the user that the print job is end
void BrPrint3D::isPrintJobRunning(bool b)
{   //This function return if the print job is finalized
    QMessageBox msg;
    if(b==true)
    {   disconnect(temp,SIGNAL(finishedJob(bool)),this,SLOT(isPrintJobRunning(bool)));
        msg.setText("Print job finish or paused!");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
        if(ui->bt_pause->isChecked()==false)
        {    enableAxisButtons();
            ui->cb_Extruder_qnt->setEnabled(true);
        }
    }
}
//This is a close event
void BrPrint3D::closeEvent(QCloseEvent *event)
{
    QMessageBox msg;
        if(this->printer_object->isPrintJobRunning()==true)
        {   msg.setText("The print job is running, Are you sure you want to continue?");
            msg.setIcon(QMessageBox::Warning);
            msg.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
            msg.setDefaultButton(QMessageBox::Cancel);
            int result = msg.exec();
            switch (result)
            {

            case QMessageBox::Cancel:
                event->accept();
                break;
            case QMessageBox::Ok:
            {
                this->printer_object->stopPrintJob();
                this->printer_object->closeFile();
                event->accept();
            }break;
            default:
                break;
            }

        }
        event->accept();
}
//This Action hide/show buttons of extruders starting from qnt choose by the user


