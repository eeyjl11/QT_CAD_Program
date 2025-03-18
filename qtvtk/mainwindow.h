#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/** @file
* Mainwindow declaration file
*/


#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QColorDialog>
#include <QPushButton>
#include <QSlider>
#include <QCheckBox>
#include <QMessageBox>

#include <vtkActor.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSTLReader.h>
#include <vtkSTLWriter.h>
#include <vtkDataSetReader.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkTriangleFilter.h>
#include <vtkAppendFilter.h>
#include <vtkGeometryFilter.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkInformation.h>
#include <vtkAlgorithmOutput.h>
#include <vtkPolyDataReader.h>
#include <vtkPolyDataWriter.h>

#include <vtkStringArray.h>
#include <vtkDoubleArray.h>
#include <vtkFieldData.h>
#include <vtkCellData.h>

#include <vtkMassProperties.h>
#include <vtkTriangleFilter.h>

#include "model.h"
#include "material.h"
#include "vector3D.h"
#include "cell.h"
#include "scenewidget.h"

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * Class for main window of this application GUI
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void showBackgroundColorDialog();
    void sliderIntensity();
    //! Show the 'Open file...' dialog
    void openFile();
    void reset();
    void removeActor();
    void setActorColor();
    void setClip();
    void setShrink();
    void setOutline();
    void saveSelected();
    void saveAll();
    void about();
    void quit();


protected:
    void openFileSTL(const QString& fileName);
    void openFileVTK(const QString& fileName);
    void openFileMOD(const QString& fileName);
    void showHexahedron();
    void showTetrahedron();
    void showPyramid();
    void makePyramid(vector<Pyramid> &input_pyramids, vector<material> &input_materials, vector<vertece3d> &input_verteces);
    void makeHexahedron(vector<Hexahedron> &input_hexahedrons, vector<material> &input_materials, vector<vertece3d> &input_verteces);
    void makeTetrahedron(vector<Tetrahedron> &input_tetrahedrons, vector<material> &input_materials, vector<vertece3d> &input_verteces);
    void mod_sink(vtkNew<vtkUnstructuredGrid> &input_ugrid, material &input_material);
    void render_actor(vtkNew<vtkUnstructuredGrid> &input_ugrid, vtkColor3d &input_color);
    void highlightNext();
    void update_property_table(vtkActor * input_actor);
    void saveMOD_single(vtkActor * input_actor, QString input_filename);
private:
    Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
