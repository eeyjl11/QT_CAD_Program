#include "mainwindow.h"

#include <QApplication>
#include <QSurfaceFormat>

#include <QVTKOpenGLNativeWidget.h>

/** @file
* Main file
*/

/**
 * @brief Main
 * Main function which launches the QT window of the application
 * If GUI exists with exit code 228, relauches GUI
 */
int main(int argc, char* argv[])
{
    // Restart Code of 228 works as QApplication reset function, called via "Reset" Button
    int RESTART_CODE = 228;
    int exit_code = 0;
    do
    {
        QSurfaceFormat::setDefaultFormat(QVTKOpenGLNativeWidget::defaultFormat());

        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        exit_code = a.exec();
    }
    while (exit_code == RESTART_CODE);

    return exit_code;
}
