#include "delocalizer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MM");
    QCoreApplication::setApplicationName("de_lupdate");
    QCoreApplication::setApplicationVersion("1.0");

    QApplication a(argc, argv);
    Delocalizer d;



    return a.exec();
}
