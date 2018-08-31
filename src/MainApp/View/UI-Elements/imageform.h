#ifndef IMAGEFORM_H
#define IMAGEFORM_H

#include <QWidget>
#include <QTextImageFormat>
#include <QImageReader>
#include <QFileDialog>
#include <QPixmap>
#include <QDebug>

/**
 * @brief UI-element for editing Images used in the document
 *
 */
namespace Ui {
class Imageform;
}

class Imageform : public QWidget
{
    Q_OBJECT

public:
    explicit Imageform(QWidget *parent = nullptr);
    ~Imageform();

    /**
     * @brief function for enabling / disabling all UI-Elements
     *
     */
    void setEnabled(bool enable);

    /**
     * @brief function for getting image-data
     *
     */
    void setImageProperties(QTextImageFormat *newImageFormat);

    /**
     * @brief function for retranlation of the ui
     *
     */
    void retranslateUI();

private:
    Ui::Imageform *ui;

    /**
     * @brief ratio of width and height of the selected image
     *
     */
    double imageRatio;

    /**
     * @brief for telling whether the image has changed completely or just the size
     *
     */
    bool newFileSet;

signals:
    /**
     * @brief signal for the resizing of the selected image
     *
     */
    void resizeImage(double width, double height, QString newFilename, bool useNewFile);

private slots:
    /**
     * @brief detection of user-input
     *
     */
    void widthChanged(double width);

    /**
     * @brief detection of user-input
     *
     */
    void heightChanged(double height);

    /**
     * @brief detection of user-input / button-push
     *
     */
    void updateImage();

    /**
     * @brief detection of user-input: show file-dialog for setting a new image
     *
     */
    void changeFile();
};

#endif // IMAGEFORM_H
