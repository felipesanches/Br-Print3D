#include "brprint3d.h"
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


    //Hide Config Menu
    ui->Menu_Control_Left->hide();
    ui->openGLWidget->setGeometry(20,160,900,510);

    //Disable Play Button
    ui->bt_play->setEnabled(false);

    //If slic3er exists in Ini file, load path, else locate
    pathslicer=QVariant (settings.value("slic3r")).toString();
    if(pathslicer.isEmpty())
        locate_Slicer();
    else
    {   ui->cb_Slicer->addItem("Slic3r");
        ui->bt_addSlicer->setEnabled(false);
    }

    //If cura exists in Ini file, load path, else locate
    pathcura=QVariant (settings.value("cura")).toString();
    if(pathcura.isEmpty())
        locate_Cura();
    else
        ui->cb_Slicer->addItem("Cura Engine");

    //Disable Manual Control of Printer
    ui->Manual_Control->setDisabled(true);
    //Disable Slicer Tab - Because is not done
    ui->Slicer->setEnabled(false);

    //Start the thread that is listening if Arduino is connect or not
    this->ard_List = new arduinoListener;
    connect(ard_List,SIGNAL(arduinoConnect(bool)),this,SLOT(locate_Arduino(bool)));
    this->ard_List->start();
    QStringList ports;
    ui->cb_Connection_Port->addItems(ports);
}
/*-----------Actions of MenuBar----------*/
//This Action Close the program - Necessary???
void BrPrint3D::on_actionFechar_triggered()
{
    //Do some things -> Is print job running? alert Is something that need to be save? alert...
}
//This Action change the language of the program to Portuguese
void BrPrint3D::on_actionPortuguese_triggered()
{
    qApp->removeTranslator(&translator);
    translator.load(":/Translations/PT_portuguese.qm");
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
}
//This Action change the language of the program to English
void BrPrint3D::on_actionEnglish_triggered()
{
   qApp->removeTranslator(&translator);
   translator.load(":/Translations/EN_english.qm");
   qApp->installTranslator(&translator);
   ui->retranslateUi(this);

}
//This action show on screen the Legal Warning Window of BrPrint
void BrPrint3D::on_actionAviso_Legal_triggered()
{
    LegalWarning *w=new LegalWarning();
    w->show();
}
//This action show on screen the Documentation Window of BrPrint
void BrPrint3D::on_actionDocumenta_o_triggered()
{

    Documentation *w= new Documentation();
    w->show();
}
//This action show on screen the Help Window
void BrPrint3D::on_actionAjuda_triggered()
{
    Help *w= new Help();
     w->show();
}
//This action show on screen the about Window of BrPrint
void BrPrint3D::on_actionSobre_o_BrPrint3D_triggered()
{
    aboutBrPrint *w= new aboutBrPrint();
    w->show();
}

/*----------Actions---------------------*/
//This action Hide/Show The Configuration of Printer
void BrPrint3D::on_bt_hide_clicked()
{
    if(ui->bt_hide->text()==tr("Configuration - Show"))
    {
        ui->bt_hide->setText(tr("Configuration - Hide"));
        ui->Menu_Control_Left->show();
        ui->openGLWidget->setGeometry(460,160,480,510);
    }
    else
    {
        ui->bt_hide->setText(tr("Configuration - Show"));
        ui->Menu_Control_Left->hide();
        ui->openGLWidget->setGeometry(20,160,900,510);
    }
}
//This function locate the Sli3er program and save on Ini file
void BrPrint3D::locate_Slicer()
{   QMessageBox msg;
    garbage=std::system("whereis slic3r > slic3r.txt");
    std::ifstream slicer("slic3r.txt");
    char path[201];
    if(!slicer)
    {
        msg.setText("Bin Slic3r could not be open!");
        msg.exec();
    }
    else
    {   if(!slicer.eof())
        {   slicer.getline(path,sizeof(path));//Lê a linha do arquivo
            if(path[7]=='\0')
            {
               msg.setText("Slic3r not found! To search click on add Slicer on tab Slicer!");
               ui->cb_Slicer->addItem("Slic3er (Not Found)");
               //msg.exec();
            }
            else
            {   for(int i=8;path[i]!=' ';i++)
                {
                    pathslicer+=path[i];
                }
                ui->cb_Slicer->addItem("Slic3r");
                settings.setValue("slic3r",pathslicer);//Save the path on ini file
                settings.sync();//Atualiza ini
            }
        }
    }
}
//This function locate the Cura program and save on Ini file
void BrPrint3D::locate_Cura()
{   QMessageBox msg;
    garbage=std::system("whereis cura > cura.txt");
    std::ifstream cura("cura.txt");
    char path[201];
    if(!cura)
    {
        msg.setText("Bin Cura could not be open!");
        msg.exec();
    }
    else
    {
        if(!cura.eof())
        {
            cura.getline(path,sizeof(path));//read line of the file
            if(path[5]=='\0')
            {
                ui->cb_Slicer->addItem("Cura Engine (Not Found)");
            }
            else
            {
                for(int j=6;path[j]!=' ';j++)
                {
                    pathcura+=path[j];
                }
               ui->cb_Slicer->addItem("Cura Engine");
               settings.setValue("cura",pathcura);
               settings.sync();
            }
        }
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
   {
        if(!ui->tb_AreaPrint_X->text().isEmpty() && !ui->tb_AreaPrint_Y->text().isEmpty() && !ui->tb_AreaPrint_Z->text().isEmpty())
        {
            maxX = ui->tb_AreaPrint_X->text().toInt();
            maxY = ui->tb_AreaPrint_Y->text().toInt();
            maxZ = ui->tb_AreaPrint_Z->text().toInt();
            transmitionRate = ui->cb_Transmition_Rate->currentText().toInt();
            serialPort = ui->cb_Connection_Port->currentText().toStdString();
            bufferSize = ui->cb_Cache_Size->currentText().toInt();
            ui->Manual_Control->setEnabled(true);
        }
        else
        {    msg.setText(tr("Make sure you have all the necessary settings for connection!"));
             msg.setIcon(QMessageBox::Warning);
             msg.exec();
             ui->bt_connect->setChecked(false);
             return;
        }
        if(ui->ck_resetonConnect->isChecked()==true)
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


        try{
            printer_object = new Repetier(transmitionRate, serialPort, bufferSize, maxX, maxY, maxZ, resetWhenConnect, isCommaDecimalMark);
            this->qntExtruders = printer_object->getNoOfExtruders();
            for(int i=1;i<=qnt;i++)
            {   QString item = QVariant(i+1).toString();
                ui->cb_Extruder_qnt->addItem(item);
            }
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
            ui->Manual_Control->setEnabled(false);
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

       ui->tb_ManualControl->stopThreadRoutine();
       this->printer_object->~Repetier();
       //Check Bed to false
       ui->bt_Bed->setChecked(false);
       ui->bt_Bed->setStyleSheet("");
      //Check extruder to false
       ui->bt_extruderTemp->setChecked(false);
       ui->bt_extruderTemp->setStyleSheet("");


       ui->Manual_Control->setDisabled(true);
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



