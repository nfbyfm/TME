#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include <Control/controller.h>


/**
 * @brief Main Entrypoint of the Application. creates an instance of the Controller-class (contains model and Views) and opens any filenames given.
 *
 * @param argc
 * @param argv
 * @return QApplication
 */
int main(int argc, char *argv[])
{


    Q_INIT_RESOURCE(i18n);
    Q_INIT_RESOURCE(stylesheets);

    QApplication app(argc, argv);

    Controller *contr = new Controller;

    //open file if arguments are given
    /*
    if(argc > 1)
    {
        QString fileName = QString::fromStdString(argv[0]);

        contr->openFile(QFileInfo(fileName));
    }
    */


    QCoreApplication::setApplicationName("TME");
    QCoreApplication::setOrganizationName("nfbyfm");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Text-Math-Editor");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);


    foreach (const QString &fileName, parser.positionalArguments())
        contr->openFile(QFileInfo(fileName));


    return app.exec();
}
