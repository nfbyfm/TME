#ifndef MAPAGE_H
#define MAPAGE_H

#include <QObject>

/**
 * @brief abstract class for Documentpages ('Interface' for Templates, Documentpages and the like)
 *
 */
class MAPage : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief first constructor for abstract page-class. Width an d Height get set to A4-format (210 x 297 mm).
     *
     * @param parent usually nullptr
     */
    explicit MAPage(QObject *parent = nullptr);



    /**
     * @brief setter-function for the pageheight
     *
     * @param h Page-Height in Millimeters
     */
    void setHeight(float h);
    void setWidht(float w);
    /**
     * @brief getter-function for the pagewidth
     *
     * @return float Pagewidth in Millimeters
     */
    float getWidth();
    float getHeight();

private:
    float width;        //**< Pagewidth in Millimeters */
    float height;       //**< Pageheight in Millimeters */

signals:

public slots:
};

#endif // MAPAGE_H
