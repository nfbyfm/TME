#include "imageform.h"
#include "ui_imageform.h"

Imageform::Imageform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Imageform)
{
    ui->setupUi(this);

    ui->comboBox_SizeUnit->clear();
    ui->comboBox_SizeUnit->addItem(tr("mm"));
    ui->comboBox_SizeUnit->addItem(tr("px"));
    ui->comboBox_SizeUnit->setCurrentIndex(1);

    connect(ui->doubleSpinBox_ImageWidth, SIGNAL(valueChanged(double)), this, SLOT(widthChanged(double)));
    connect(ui->doubleSpinBox_ImageHeight, SIGNAL(valueChanged(double)), this, SLOT(heightChanged(double)));
    connect(ui->pushButtonFilePath, SIGNAL(released()), this,SLOT(changeFile()));
    connect(ui->pushButton_Update, SIGNAL(released()), this, SLOT(updateImage()));

    //temporary. Non-essential for first release.
    ui->comboBox_SizeUnit->setEnabled(false);
    ui->comboBox_SizeUnit->setVisible(false);
    ui->label_3->setVisible(false);

    ui->label_Preview->setText("");

}

Imageform::~Imageform()
{
    delete ui;
}

void Imageform::retranslateUI()
{
    ui->retranslateUi(this);
}


void Imageform::widthChanged(double width)
{
    if(ui->checkBox_KeepRatio->isChecked())
        ui->doubleSpinBox_ImageHeight->setValue(width/imageRatio);
}
void Imageform::heightChanged(double height)
{
    if(ui->checkBox_KeepRatio->isChecked())
        ui->doubleSpinBox_ImageWidth->setValue(imageRatio*height);
}

void Imageform::setEnabled(bool enable)
{
    if(!enable)
    {
        ui->lineEditFileURL->setText("");
        ui->comboBox_SizeUnit->setCurrentIndex(1);
        ui->doubleSpinBox_ImageHeight->setValue(0);
        ui->doubleSpinBox_ImageWidth->setValue(0);
        ui->label_Preview->clear();
    }

    ui->lineEditFileURL->setEnabled(enable);
    ui->pushButtonFilePath->setEnabled(enable);
    ui->doubleSpinBox_ImageHeight->setEnabled(enable);
    ui->doubleSpinBox_ImageWidth->setEnabled(enable);
    ui->checkBox_KeepRatio->setEnabled(enable);
    ui->pushButton_Update->setEnabled(enable);
    ui->comboBox_SizeUnit->setEnabled(enable);

}

void Imageform::setImageProperties(QTextImageFormat *newImageFormat)
{
    if(newImageFormat != nullptr)
    {
        newFileSet = false;
        setEnabled(true);
        ui->checkBox_KeepRatio->setChecked(true);

        QString fileName = newImageFormat->name();
        if(fileName.contains("file:///"))
            fileName = fileName.remove("file:///",Qt::CaseInsensitive);

        if(newImageFormat->height() >0)
        {
            imageRatio = newImageFormat->width()/newImageFormat->height();

            ui->doubleSpinBox_ImageHeight->setValue(newImageFormat->height());
        }
        else
        {
            imageRatio = 1;

            ui->doubleSpinBox_ImageHeight->setValue(newImageFormat->height());
            ui->doubleSpinBox_ImageWidth->setValue(newImageFormat->width());
        }

        ui->lineEditFileURL->setText(fileName);

        QPixmap previewPic(fileName);
        int labelHeight = ui->label_Preview->height();
        int labelWidth = ui->label_Preview->width();
        ui->label_Preview->setPixmap(previewPic.scaled(labelWidth,labelHeight,Qt::KeepAspectRatio));


    }
    else
    {
        setEnabled(false);
    }
}

void Imageform::changeFile()
{
    //show FileDialog
    QFileInfo fInfo(ui->lineEditFileURL->text() );
    QString file = QFileDialog::getOpenFileName(this, tr("Select an image"),fInfo.dir().absolutePath(), tr("JPEG (*.jpg *jpeg)\n" "PNG (*.png)\n" "Bitmap Files (*.bmp)\n" "GIF (*.gif)\n" ));

    newFileSet = false;

    if(!file.isEmpty())
    {
        QString currentFile = ui->lineEditFileURL->text();
        if(currentFile !=file)
        {
            ui->lineEditFileURL->setText(file);
            newFileSet = true;

            QImage image = QImageReader ( file ).read();
            double imgWidth = image.width();
            double imgHeight = image.height();

            if(ui->comboBox_SizeUnit->currentText().contains("mm"))
            {
                imgHeight = image.heightMM();
                imgWidth =  image.widthMM();
            }


            bool oldState = ui->doubleSpinBox_ImageHeight->blockSignals(true);
            ui->doubleSpinBox_ImageHeight->setValue(imgHeight);
            ui->doubleSpinBox_ImageHeight->blockSignals(oldState);

            oldState = ui->doubleSpinBox_ImageWidth->blockSignals(true);
            ui->doubleSpinBox_ImageWidth->setValue(imgWidth);
            ui->doubleSpinBox_ImageWidth->blockSignals(oldState);

            imageRatio = imgWidth/imgHeight;

            QPixmap previewPic(file);
            int labelHeight = ui->label_Preview->height();
            int labelWidth = ui->label_Preview->width();
            ui->label_Preview->setPixmap(previewPic.scaled(labelWidth,labelHeight,Qt::KeepAspectRatio));

            //qDebug()<<"file has been set anew.";
        }
    }
    else
        qDebug()<<"set new file called but nothing has changed";

}

void Imageform::updateImage()
{
    emit resizeImage( ui->doubleSpinBox_ImageWidth->value(), ui->doubleSpinBox_ImageHeight->value(),  ui->lineEditFileURL->text(), newFileSet );
}

