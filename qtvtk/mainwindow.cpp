#include "mainwindow.h"
#include "ui_mainwindow.h"

/** @file
* Mainwindow definition file
*/


/**
 * @brief MainWindow initialisation
 *
 * Sets all of the connections.
 * Sets light intensity for light sources and syncs to the light slider.
 */
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cout << ui->sceneWidget->getLightIntensity()*100<< endl;
    ui->sliderLight->setValue(ui->sceneWidget->getLightIntensity()*100);
    connect(ui->actionHexahedron, &QAction::triggered,this,&MainWindow::showHexahedron);
    connect(ui->actionTetrahedron, &QAction::triggered, this, &MainWindow::showTetrahedron);
    connect(ui->actionPyramid, &QAction::triggered, this, &MainWindow::showPyramid);
    connect(ui->actionBackground, &QPushButton::clicked, this, &MainWindow::showBackgroundColorDialog);
    connect(ui->sliderLight, &QSlider::sliderMoved , this, &MainWindow::sliderIntensity);
    connect(ui->actionReset, &QPushButton::clicked, this, &MainWindow::reset);
    connect(ui->setColor,&QPushButton::clicked, this, &MainWindow::setActorColor);
    connect(ui->actionClip, &QPushButton::clicked, this, &MainWindow::setClip);
    connect(ui->actionShrink, &QPushButton::clicked, this, &MainWindow::setShrink);
    connect(ui->actionSaveActor, &QPushButton::clicked, this, &MainWindow::saveSelected);
    connect(ui->actionNext, &QPushButton::clicked,this, &MainWindow::highlightNext);
    connect(ui->actionRemove, &QPushButton::clicked, this, &MainWindow::removeActor);
    connect(ui->actionSave_All, &QAction::triggered, this, &MainWindow::saveAll);
    connect(ui->actionAboutDialog, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionQuit, &QAction::triggered, this, &MainWindow::quit);
    connect(ui->actionOpenFile, &QAction::triggered, this, &MainWindow::openFile);
}

MainWindow::~MainWindow() { delete ui; }

/**
 * @brief Show set background color dialog
 *
 * Set background color via QColorDialog which also displays current color of the background.
 * And asks user to input new color for background
 */
void MainWindow::showBackgroundColorDialog()
{
    QColor current = ui->sceneWidget->getBackground();
    QColor next = QColorDialog(current,nullptr).getColor();
    ui->sceneWidget->setBackground(next);
}

/**
 * @brief Show set actor color dialog
 *
 * Set background color via QColorDialog which also displays current color of the selected actor.
 * And asks user to input new color for the selected actor
 */
void MainWindow::setActorColor()
{
    vtkActor * our_actor = ui->sceneWidget->getPickedActor();
    if(our_actor!=nullptr)
    {
        QColor current = ui->sceneWidget->getActorColor(our_actor);
        QColor next = QColorDialog(current,nullptr).getColor();
        ui->sceneWidget->setActorColor(next,our_actor);
    }
}

/**
 * @brief Remove selected actor
 *
 * Removes selected actor
 */
void MainWindow::removeActor()
{
    ui->sceneWidget->removePickedActor();
}

/**
 * @brief Reset GUI and renderer
 *
 * Sends special exit code to the main() which closes and relaunches GUI
 */
void MainWindow::reset()
{
    qApp->exit(228);
}

/**
 * @brief Select next actor
 *
 * Selects next actor to be picked actor.
 * Draws outline around newly picked actor.
 * Updates properties table to show new values for the actor
 */
void MainWindow::highlightNext()
{
    vtkSmartPointer<vtkActor> our_actor = ui->sceneWidget->ChooseActor();
    if(our_actor != nullptr)
    {
        ui->sceneWidget->setOutlineFilter(our_actor);
        update_property_table(our_actor);
    }

}

/**
 * @brief Set light intensity from slider value
 *
 * Sets light intensity of light sources based on the value read from the slider
 */
void MainWindow::sliderIntensity()
{
    ui->sceneWidget->setLightIntensity((double)ui->sliderLight->value()/100);
}

/**
 * @brief Set clip filter to picked actor
 *
 * Cuts picked actor in half
 */
void MainWindow::setClip()
{
    ui->sceneWidget->setClipFilter(ui->sceneWidget->getPickedActor());
}

/**
 * @brief Set shrink filter to picked actor
 *
 * Shrinks picked actor
 */
void MainWindow::setShrink()
{
    ui->sceneWidget->setShrinkFilter(ui->sceneWidget->getPickedActor());
}

/**
 * @brief Set outline filter to picked actor
 *
 * Creates outline about picked actor
 */
void MainWindow::setOutline()
{
    ui->sceneWidget->setOutlineFilter(ui->sceneWidget->getPickedActor());
}

/**
 * @brief Save picked actor
 *
 * Summons save dialog.
 * Saves picked actor to chosen filename.
 * Saves in 3 different types: vtk, stl and mod.
 * Type is determined from chosen filename extention.
 */
void MainWindow::saveSelected()
{
    vtkSmartPointer<vtkActor> our_actor = ui->sceneWidget->getPickedActor();
    if(ui->sceneWidget->checkActor(our_actor))
    {
        QString QfileName = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                                         "3D model Files (*.vtk *.stl *.mod)");
        QStringList fileNameSplit = QfileName.split(".");
        //File extention is the last bit of the split
        QString extention = fileNameSplit.at(fileNameSplit.size() - 1);
        vtkSmartPointer<vtkGeometryFilter>geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
        geometryFilter->SetInputConnection(our_actor->GetMapper()->GetInputConnection(0,0));
        geometryFilter->Update();
        vtkPolyData* polydata = geometryFilter->GetOutput();
        //Extention cases
        if(!QString::compare(extention,"stl", Qt::CaseInsensitive))
        {
            cout << "stl" << endl;
            vtkNew<vtkSTLWriter> stlWriter;
            stlWriter->SetFileName(QfileName.toStdString().c_str());
            stlWriter->SetInputData(polydata);
            stlWriter->Write();
        }
        else if(!QString::compare(extention,"vtk", Qt::CaseInsensitive))
        {
            cout << "vtk" << endl;
            vtkNew<vtkPolyDataWriter> polyDataWriter;
            polyDataWriter->SetFileName(QfileName.toStdString().c_str());
            polyDataWriter->SetInputData(polydata);
            polyDataWriter->Write();
        }
        //If extention is invalid return
        else if(!QString::compare(extention,"mod", Qt::CaseInsensitive))
        {
            cout << "mod" << endl;
            saveMOD_single(our_actor, QfileName);
        }
        else
        {
            cout << "invalid" << endl;
            return;
        }
    }
}

/**
 * @brief Save All actors to the single file
 *
 * Summons save dialog.
 * Saves all actors to chosen filename.
 * Saves in 2 different types: vtk and stl
 * Type is determined from chosen filename extention.
 */
void MainWindow::saveAll()
{

    vtkActorCollection * actors = ui->sceneWidget->getAllActors();
    vtkSmartPointer<vtkAppendPolyData> our_append_filter = vtkSmartPointer<vtkAppendPolyData>::New();

    if(actors != nullptr)
    {
        actors->InitTraversal();

        while(1)
        {
            vtkActor * actor = actors->GetNextActor();
            if(actor != nullptr)
            {
                if(actor != ui->sceneWidget->getOutlineActor())
                {
                    cout << "Actor" << endl;
                    cout << actor << endl;
                    vtkSmartPointer<vtkGeometryFilter>geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
                    geometryFilter->SetInputConnection(actor->GetMapper()->GetInputConnection(0,0));
                    geometryFilter->Update();
                    vtkPolyData* polydata = geometryFilter->GetOutput();
                    our_append_filter->AddInputData(polydata);
                }
            }
            else
            {
                break;
            }
        }
        our_append_filter->Update();


        vtkPolyData * our_combined_polydata = our_append_filter->GetOutput();


        if(our_combined_polydata != nullptr)
        {
            QString QfileName = QFileDialog::getSaveFileName(this, tr("Save file"), "",
                                                             "3D model Files (*.vtk *.stl)");
            QStringList fileNameSplit = QfileName.split(".");
            //File extention is the last bit of the split
            QString extention = fileNameSplit.at(fileNameSplit.size() - 1);

            //Extention cases
            if(!QString::compare(extention,"stl", Qt::CaseInsensitive))
            {
                cout << "stl" << endl;
                vtkNew<vtkSTLWriter> stlWriter;
                stlWriter->SetFileName(QfileName.toStdString().c_str());
                stlWriter->SetInputData(our_combined_polydata);
                stlWriter->Write();
            }
            else if(!QString::compare(extention,"vtk", Qt::CaseInsensitive))
            {
                cout << "vtk" << endl;
                vtkNew<vtkPolyDataWriter> polyDataWriter;
                polyDataWriter->SetFileName(QfileName.toStdString().c_str());
                polyDataWriter->SetInputData(our_combined_polydata);
                polyDataWriter->Write();
            }
            else
            {
                cout << "invalid" << endl;
                return;
            }
        }
    }
}

/**
 * @brief Show about Dialog
 *
 * Shows information about the program
 */
void MainWindow::about()
{
    QMessageBox::about(this, "About", "by Group 5 for Year 2 ECE Computing project practical");
}

/**
 * @brief Show quit Dialog
 *
 * Exits application
 */
void MainWindow::quit()
{
    qApp->exit(0);
}

/**
 * @brief Open File
 *
 * Supports vtk,stl and mod types.
 * Summons open file dialog.
 * Adds new actor(s) to the scene.
 * Parser is determined by extention.
 */
void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "",
                                                    "3D model Files (*.vtk *.stl *.mod)");

    // Open file
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    // Return on Cancel
    if (!file.exists())
        return;
    //Find file extention
    //Split file by '.' character
    QStringList fileNameSplit = fileName.split(".");
    //File extention is the last bit of the split
    QString extention = fileNameSplit.at(fileNameSplit.size() - 1);
    //Extention cases
    if(!QString::compare(extention,"stl", Qt::CaseInsensitive))
    {
        cout << "stl" << endl;
        openFileSTL(fileName);
    }
    else if(!QString::compare(extention,"vtk", Qt::CaseInsensitive))
    {
        cout << "vtk" << endl;
        openFileVTK(fileName);
    }
    //If extention is invalid return
    else if(!QString::compare(extention,"mod", Qt::CaseInsensitive))
    {
        cout << "mod" << endl;
        openFileMOD(fileName);
    }
    else
    {
        cout << "invalid" << endl;
        return;
    }
}

/**
 * @brief Show hexahedron
 *
 * Creates and shows new hexahedron actor with predetermined sizes
 */
void MainWindow::showHexahedron()
{
    vtkNew<vtkNamedColors> colors;

    // create polyhedron (cube)
    vtkIdType pointIds[8] = {0, 1, 2, 3, 4, 5, 6, 7};

    vtkNew<vtkPoints> points;
    points->InsertNextPoint(-1.0, -1.0, -1.0);
    points->InsertNextPoint(1.0, -1.0, -1.0);
    points->InsertNextPoint(1.0, 1.0, -1.0);
    points->InsertNextPoint(-1.0, 1.0, -1.0);
    points->InsertNextPoint(-1.0, -1.0, 1.0);
    points->InsertNextPoint(1.0, -1.0, 1.0);
    points->InsertNextPoint(1.0, 1.0, 1.0);
    points->InsertNextPoint(-1.0, 1.0, 1.0);

    vtkNew<vtkIdList> faces;
    vtkIdType face0[4] = {0, 3, 2, 1};
    vtkIdType face1[4] = {0, 4, 7, 3};
    vtkIdType face2[4] = {4, 5, 6, 7};
    vtkIdType face3[4] = {5, 1, 2, 6};
    vtkIdType face4[4] = {0, 1, 5, 4};
    vtkIdType face5[4] = {2, 3, 7, 6};

    auto addFace = [&](const vtkIdType face[4]) {
        faces->InsertNextId(4);
        for (int i = 0; i < 4; ++i)
        {
            faces->InsertNextId(face[i]);
        }
    };

    addFace(face0);
    addFace(face1);
    addFace(face2);
    addFace(face3);
    addFace(face4);
    addFace(face5);

    vtkNew<vtkUnstructuredGrid> ugrid;
    ugrid->SetPoints(points);
    ugrid->InsertNextCell(VTK_POLYHEDRON, 8, pointIds, 6, faces->GetPointer(0));

    material our_material;
    color our_color;
    our_color.set(0,0,255);
    our_material.set_color(our_color);
    our_material.set_density(1.);
    our_material.set_name("Blank");

    // Add data set to 3D view
    mod_sink(ugrid, our_material);
}

/**
 * @brief Show tetrahedron
 *
 * Creates and shows new tetrahedron actor with predetermined sizes
 */
void MainWindow::showTetrahedron()
{
    vtkNew<vtkNamedColors> colors;

    vtkIdType pointIds[4] = {0, 1, 2, 3};

    vtkNew<vtkPoints> points;

    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 2.0, 0.0);
    points->InsertNextPoint(1.0, 2.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 1.0);

    vtkNew<vtkIdList> faces; //?

    vtkIdType face1[3] = {0, 1, 2};
    vtkIdType face2[3] = {1, 2, 3};
    vtkIdType face3[3] = {2, 0, 3};
    vtkIdType face4[3] = {0, 1, 3};

    auto addFace = [&](const vtkIdType face[3]) {
        faces->InsertNextId(3);
        for (int i = 0; i < 3; ++i)
        {
            faces->InsertNextId(face[i]);
        }
    };
    addFace(face1);
    addFace(face2);
    addFace(face3);
    addFace(face4);

    vtkNew<vtkUnstructuredGrid> ugrid;
    ugrid->SetPoints(points);
    ugrid->InsertNextCell(VTK_POLYHEDRON, 4, pointIds, 4, faces->GetPointer(0));

    material our_material;
    color our_color;
    our_color.set(0,255,0);
    our_material.set_color(our_color);
    our_material.set_density(1.);
    our_material.set_name("Blank");

    // Add data set to 3D view
    mod_sink(ugrid, our_material);
}

/**
 * @brief Show Pyramid
 *
 * Creates and shows new pyramid actor with predetermined sizes
 */
void MainWindow::showPyramid()
{
    vtkNew<vtkNamedColors> colors;

    vtkIdType pointIds[5] = {0, 1, 2, 3, 4};

    vtkNew<vtkPoints> points;

    points->InsertNextPoint(0.0, 0.0, 0.0);
    points->InsertNextPoint(0.0, 2.0, 0.0);
    points->InsertNextPoint(2.0, 2.0, 0.0);
    points->InsertNextPoint(2.0, 0.0, 0.0);
    points->InsertNextPoint(1.0, 1.0, 1.0);

    vtkNew<vtkIdList> faces; //?

    vtkIdType face0[3] = {0, 1, 4};
    vtkIdType face1[3] = {1, 2, 4};
    vtkIdType face2[3] = {2, 3, 4};
    vtkIdType face3[3] = {3, 0, 4};

    vtkIdType base[4] = {0,1,2,3};

    auto addFace = [&](const vtkIdType face[3]) {
        faces->InsertNextId(3);
        for (int i = 0; i < 3; ++i)
        {
            faces->InsertNextId(face[i]);
        }
    };
    // Add Square Base
    faces->InsertNextId(4);
    for (int i = 0; i < 4; ++i)
    {
        faces->InsertNextId(base[i]);
    }

    addFace(face0);
    addFace(face1);
    addFace(face2);
    addFace(face3);

    vtkNew<vtkUnstructuredGrid> ugrid;
    ugrid->SetPoints(points);
    ugrid->InsertNextCell(VTK_POLYHEDRON, 5, pointIds, 5, faces->GetPointer(0));

    material our_material;
    color our_color;
    our_color.set(255,0,0);
    our_material.set_color(our_color);
    our_material.set_density(1.);
    our_material.set_name("Blank");

    // Add data set to 3D view
    mod_sink(ugrid, our_material);
}

/**
 * @brief STL parser
 *
 * Create unstructured grid from chosen stl file.
 * Create blank material as STL data does not hold any color or material data
 * @param fileName - Filename of file from which stl data is read
 */
void MainWindow::openFileSTL(const QString& fileName)
{
    // Create reader

    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(fileName.toStdString().c_str());

    // Read the file
    reader->Update();

    vtkNew<vtkAppendFilter> appendFilter;
    appendFilter->AddInputData(reader->GetOutput());
    appendFilter->Update();

    vtkNew<vtkUnstructuredGrid> unstructuredGrid;
    unstructuredGrid->ShallowCopy(appendFilter->GetOutput());

    material our_material;
    color our_color;
    our_color.set(255,255,255);
    our_material.set_color(our_color);
    our_material.set_density(1.);
    our_material.set_name("Blank");
    // Add data set to 3D view
    mod_sink(unstructuredGrid, our_material);
}

/**
 * @brief VTK parser
 *
 * Create unstructured grid from chosen vtk file.
 * Create blank material as VTK data does not hold any color or material data
 * @param fileName - Filename of file from which vtk data is read
 */
void MainWindow::openFileVTK(const QString& fileName)
{

    // Create reader

    vtkNew<vtkPolyDataReader> reader;
    reader->SetFileName(fileName.toStdString().c_str());

    // Read the file
    reader->Update();

    vtkNew<vtkAppendFilter> appendFilter;
    appendFilter->AddInputData(reader->GetOutput());
    appendFilter->Update();

    vtkNew<vtkUnstructuredGrid> unstructuredGrid;
    unstructuredGrid->ShallowCopy(appendFilter->GetOutput());

    material our_material;
    color our_color;
    our_color.set(255,255,255);
    our_material.set_color(our_color);
    our_material.set_density(1.);
    our_material.set_name("Blank");

    // Add data set to 3D view
    mod_sink(unstructuredGrid, our_material);
}

/**
 * @brief MOD parser
 *
 * Create unstructured grid from chosen mod file.
 * Create material based on data from file.
 * @param fileName - Filename of file from which mod data is read
 */
void MainWindow::openFileMOD(const QString &fileName)
{
    vector<material> our_materials;
    vector<vertece3d> our_verteces;
    vector<Tetrahedron> our_tetrahedrons;
    vector<Hexahedron> our_hexahedrons;
    vector<Pyramid> our_pyramids;

    int errors = model::parser(fileName.toStdString(), our_materials, our_verteces, our_tetrahedrons, our_hexahedrons, our_pyramids);
    if(errors)
    {
        cout << "Found " << errors << " errors" << endl;
    }
    makePyramid(our_pyramids, our_materials, our_verteces);
    makeHexahedron(our_hexahedrons, our_materials, our_verteces);
    makeTetrahedron(our_tetrahedrons, our_materials, our_verteces);
}

/**
 * @brief Pyramid helper for mod file type
 *
 * Creates and adds pyramid actors to the scene based on infromation provided
 * @param input_pyramids - input Pyramid vector
 * @param input_materials - input Materials vector
 * @param input_verteces - input Verteces vector
 */
void MainWindow::makePyramid(vector<Pyramid> &input_pyramids, vector<material> &input_materials, vector<vertece3d> &input_verteces)
{
    if(input_pyramids.size() == 0)
    {
        return;
    }
    cout << "Pyramids : " << input_pyramids.size() << endl;
    for (int i = 0; i < input_pyramids.size(); i++)
    {
        cout << "ID: " << input_pyramids[i].get_id() << endl;

        material our_material = input_materials[input_pyramids[i].get_material_id()];

        vtkIdType pointIds[5] = {0, 1, 2, 3, 4};

        vtkNew<vtkPoints> points;
        int verteceID[] = {input_pyramids[i].get_p0_id(),input_pyramids[i].get_p1_id(),
                           input_pyramids[i].get_p2_id(),input_pyramids[i].get_p3_id(),
                           input_pyramids[i].get_p4_id()};
        for (int j = 0; j < 5; j++)
        {
            points->InsertNextPoint(input_verteces[verteceID[j]].get_vector3d().getxCoord(), input_verteces[verteceID[j]].get_vector3d().getyCoord(), input_verteces[verteceID[j]].get_vector3d().getzCoord());
        }

        vtkNew<vtkIdList> faces; //?

        vtkIdType face0[3] = {0, 1, 4};
        vtkIdType face1[3] = {1, 2, 4};
        vtkIdType face2[3] = {2, 3, 4};
        vtkIdType face3[3] = {3, 0, 4};

        vtkIdType base[4] = {0,1,2,3};

        auto addFace = [&](const vtkIdType face[3]) {
            faces->InsertNextId(3);
            for (int k = 0; k < 3; ++k)
            {
                faces->InsertNextId(face[k]);
            }
        };
        // Add Square Base
        faces->InsertNextId(4);
        for (int i = 0; i < 4; ++i)
        {
            faces->InsertNextId(base[i]);
        }

        addFace(face0);
        addFace(face1);
        addFace(face2);
        addFace(face3);

        vtkNew<vtkUnstructuredGrid> ugrid;
        ugrid->SetPoints(points);
        ugrid->InsertNextCell(VTK_POLYHEDRON, 5, pointIds, 5, faces->GetPointer(0));

        mod_sink(ugrid,our_material);
    }
}

/**
 * @brief Hexahedron helper for mod file type
 *
 * Creates and adds hexahedron actors to the scene based on infromation provided
 * @param input_hexahedrons - input Pyramid vector
 * @param input_materials - input Materials vector
 * @param input_verteces - input Verteces vector
 */
void MainWindow::makeHexahedron(vector<Hexahedron> &input_hexahedrons, vector<material> &input_materials, vector<vertece3d> &input_verteces)
{
    cout << "Hexahedrons : " << input_hexahedrons.size() << endl;
    if(input_hexahedrons.size() == 0)
    {
        return;
    }
    for (int i = 0; i < input_hexahedrons.size(); i++)
    {
        cout << "ID: " << input_hexahedrons[i].get_id() << endl;

        material our_material = input_materials[input_hexahedrons[i].get_material_id()];

        vtkIdType pointIds[8] = {0, 1, 2, 3, 4, 5, 6, 7};

        vtkNew<vtkPoints> points;
        int verteceID[] = {input_hexahedrons[i].get_p0_id(),input_hexahedrons[i].get_p1_id(),
                           input_hexahedrons[i].get_p2_id(),input_hexahedrons[i].get_p3_id(),
                           input_hexahedrons[i].get_p4_id(),input_hexahedrons[i].get_p5_id(),
                           input_hexahedrons[i].get_p6_id(),input_hexahedrons[i].get_p7_id()};
        for (int j = 0; j < 8; j++)
        {
            points->InsertNextPoint(input_verteces[verteceID[j]].get_vector3d().getxCoord(), input_verteces[verteceID[j]].get_vector3d().getyCoord(), input_verteces[verteceID[j]].get_vector3d().getzCoord());
        }

        vtkNew<vtkIdList> faces;
        vtkIdType face0[4] = {0, 3, 2, 1};
        vtkIdType face1[4] = {0, 4, 7, 3};
        vtkIdType face2[4] = {4, 5, 6, 7};
        vtkIdType face3[4] = {5, 1, 2, 6};
        vtkIdType face4[4] = {0, 1, 5, 4};
        vtkIdType face5[4] = {2, 3, 7, 6};

        auto addFace = [&](const vtkIdType face[4]) {
            faces->InsertNextId(4);
            for (int k = 0; k < 4; ++k)
            {
                faces->InsertNextId(face[k]);
            }
        };

        addFace(face0);
        addFace(face1);
        addFace(face2);
        addFace(face3);
        addFace(face4);
        addFace(face5);

        vtkNew<vtkUnstructuredGrid> ugrid;
        ugrid->SetPoints(points);
        ugrid->InsertNextCell(VTK_POLYHEDRON, 8, pointIds, 6, faces->GetPointer(0));

        mod_sink(ugrid,our_material);
    }
}

/**
 * @brief Tetrahedron helper for mod file type
 *
 * Creates and adds tetrahedron actors to the scene based on infromation provided
 * @param input_pyramids - input Tetrahedron vector
 * @param input_materials - input Materials vector
 * @param input_verteces - input Verteces vector
 */
void MainWindow::makeTetrahedron(vector<Tetrahedron> &input_tetrahedrons, vector<material> &input_materials, vector<vertece3d> &input_verteces)
{
    cout << "Tetrahedrons : " << input_tetrahedrons.size() << endl;
    if(input_tetrahedrons.size() == 0)
    {
        return;
    }
    for (int i = 0; i < input_tetrahedrons.size(); i++)
    {
        cout << "ID: " << input_tetrahedrons[i].get_id() << endl;

        material our_material = input_materials[input_tetrahedrons[i].get_material_id()];

        vtkIdType pointIds[8] = {0, 1, 2, 3};

        vtkNew<vtkPoints> points;
        int verteceID[] = {input_tetrahedrons[i].get_p0_id(),input_tetrahedrons[i].get_p1_id(),
                           input_tetrahedrons[i].get_p2_id(),input_tetrahedrons[i].get_p3_id()};
        for (int j = 0; j < 4; j++)
        {
            points->InsertNextPoint(input_verteces[verteceID[j]].get_vector3d().getxCoord(), input_verteces[verteceID[j]].get_vector3d().getyCoord(), input_verteces[verteceID[j]].get_vector3d().getzCoord());
        }

        vtkNew<vtkIdList> faces;

        vtkIdType face0[3] = {0, 1, 2};
        vtkIdType face1[3] = {1, 2, 3};
        vtkIdType face2[3] = {2, 0, 3};
        vtkIdType face3[3] = {0, 1, 3};

        auto addFace = [&](const vtkIdType face[3]) {
            faces->InsertNextId(3);
            for (int k = 0; k < 3; ++k)
            {
                faces->InsertNextId(face[k]);
            }
        };
        addFace(face0);
        addFace(face1);
        addFace(face2);
        addFace(face3);

        vtkNew<vtkUnstructuredGrid> ugrid;
        ugrid->SetPoints(points);
        ugrid->InsertNextCell(VTK_POLYHEDRON, 4, pointIds, 4, faces->GetPointer(0));

        mod_sink(ugrid,our_material);
    }
}

/**
 * @brief Common code for all file types parser
 *
 * Saves material name and density to special fields which can be accessed later.
 * Gets and converts color from material and converts it to vtkColor format
 *
 * @param input_ugrid - Input unstructured grid
 * @param input_material - Input material
 */
void MainWindow::mod_sink(vtkNew<vtkUnstructuredGrid> &input_ugrid, material &input_material)
{


    color our_color = input_material.get_color();
    string our_material_name = input_material.get_name();
    double our_density = input_material.get_density();

    // Getting data from FieldData was found to be strange, could only get 1 array at a time therefore a small hack will be used, by giving array a name of material_name
    // That does not work for some reason, meaning that there is a problem with strings in being saved in FieldData

    vtkNew<vtkDoubleArray> density;
    density->SetNumberOfComponents(1);
    density->SetName("Density");
    density->InsertNextValue(our_density);
    input_ugrid->GetFieldData()->AddArray(density);

    vtkNew<vtkStringArray> material_name;
    material_name->SetNumberOfComponents(1);
    material_name->SetName("Material_Name");
    material_name->InsertNextValue(our_material_name);
    input_ugrid->GetFieldData()->AddArray(material_name);

    cout << "Material Info:" << our_color.get_hex() << endl;
    vtkColor3d color = vtkColor3d((double)our_color.get_red()/255.0, (double)our_color.get_green()/255.0,(double)our_color.get_blue()/255.0);
    cout << "Color Debug: " << color.GetRed() << "," << color.GetGreen() << "," << color.GetBlue() << endl;
    render_actor(input_ugrid,color);
}

/**
 * @brief Render actor from unstructured grid
 *
 * Creates actor from unstructured grid.
 * Sets actor color.
 * @param input_ugrid - Input unstructured grid
 * @param input_color - Input color to set to actor
 */
void MainWindow::render_actor(vtkNew<vtkUnstructuredGrid> &input_ugrid, vtkColor3d &input_color)
{
    cout << "Color Debug: " << input_color.GetRed() << "," << input_color.GetGreen() << "," << input_color.GetBlue() << endl;

    // Create a mapper and actor
    vtkNew<vtkDataSetMapper> mapper;
    mapper->SetInputData(input_ugrid);

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(input_color.GetData());
    ui->sceneWidget->addActor(actor);
}

/**
 * @brief Update property table with given actor infromation
 *
 * If actor exists puts following infomation to the property table in GUI:
 * - Number of actors currently displayed
 * - Number of cells for provided actor
 * - Density of actor
 * - Surface area of actor
 * - Volume of actor
 * - Weight of actor
 *
 * @param input_actor
 */
void MainWindow::update_property_table(vtkActor * input_actor)
{
    if(input_actor != nullptr)
    {
        vtkSmartPointer<vtkMapper> our_mapper =  input_actor->GetMapper();
        vtkSmartPointer<vtkUnstructuredGrid> ugrid = vtkUnstructuredGrid::SafeDownCast(our_mapper->GetInput());
        vtkSmartPointer<vtkFieldData> our_field_data = ugrid->GetFieldData();

        vtkDoubleArray *doubleArray = vtkDoubleArray::SafeDownCast(our_field_data->GetArray("Density"));

        vtkSmartPointer<vtkGeometryFilter> our_geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
        our_geometryFilter->SetInputData(ugrid);
        our_geometryFilter->Update();

        vtkSmartPointer<vtkTriangleFilter> our_triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
        our_triangleFilter->SetInputData(our_geometryFilter->GetOutput());
        our_triangleFilter->Update();

        vtkNew<vtkMassProperties> mass;
        // Mass only takes polydata therefore geometry filter must be used on unstructured grid
        // As mass filter only works with triangles, triangle filter must also be used
        mass->AddInputData(our_triangleFilter->GetOutput());
        mass->Update();

        int actor_count = ui->sceneWidget->getActorCount();
        int cells_count_value = ugrid->GetCells()->GetNumberOfCells();
        double density_value = doubleArray->GetValue(0);
        double surface_area = mass->GetSurfaceArea();
        double volume_value = mass->GetVolume();
        double weight_value = mass->GetVolume() * doubleArray->GetValue(0);

        QTableWidgetItem * number_of_actors = new QTableWidgetItem(QString::number(actor_count));
        QTableWidgetItem * cells_count = new QTableWidgetItem(QString::number(cells_count_value));
        QTableWidgetItem * density = new QTableWidgetItem(QString::number(density_value));
        QTableWidgetItem * surfaceArea = new QTableWidgetItem(QString::number(surface_area));
        QTableWidgetItem * volume = new QTableWidgetItem(QString::number(volume_value));
        QTableWidgetItem * weight = new QTableWidgetItem(QString::number(weight_value));

        ui->tableWidget->setItem(0,0,number_of_actors);
        ui->tableWidget->setItem(0,1,cells_count);
        ui->tableWidget->setItem(0,2,density);
        ui->tableWidget->setItem(0,3,surfaceArea);
        ui->tableWidget->setItem(0,4,volume);
        ui->tableWidget->setItem(0,5,weight);
    }
}

/**
 * @brief Single actor save MOD helper
 *
 * Saves actor to the mod file if actor exists
 * @param input_actor - vtkActor to save to file
 * @param QfileName - Filename of file to save data to
 */
void MainWindow::saveMOD_single(vtkActor * input_actor, QString QfileName)
{
    if(input_actor!=nullptr)
    {
        vtkSmartPointer<vtkMapper> our_mapper =  input_actor->GetMapper();
        vtkSmartPointer<vtkUnstructuredGrid> ugrid = vtkUnstructuredGrid::SafeDownCast(our_mapper->GetInput());
        vtkSmartPointer<vtkFieldData> our_field_data = ugrid->GetFieldData();

        vtkDoubleArray *doubleArray = vtkDoubleArray::SafeDownCast(our_field_data->GetArray("Density"));


        vtkSmartPointer<vtkIdList> pointsIds = vtkSmartPointer<vtkIdList>::New();
        //Get points of cells
        ugrid->GetCellPoints(0,pointsIds);

        vtkSmartPointer<vtkPoints> points = ugrid->GetPoints();

        vector<material> materials;
        vector<vertece3d> vertecies;
        vector<Tetrahedron> tetrahedrons;
        vector<Hexahedron> hexahedrons;
        vector<Pyramid> pyramids;

        QColor qt_color = ui->sceneWidget->getActorColor(input_actor);

        color mod_color =  color(qt_color.red(), qt_color.green(), qt_color.blue());

        Tetrahedron tmp_tetrahedron;
        Pyramid tmp_pyramid;
        Hexahedron tmp_hexahedron;

        double our_density = doubleArray->GetValue(0);

        material mod_material = material(0,"blank",mod_color,our_density);
        materials.push_back(mod_material);

        vertece3d vertece0;
        vertece3d vertece1;
        vertece3d vertece2;
        vertece3d vertece3;
        vertece3d vertece4;
        vertece3d vertece5;
        vertece3d vertece6;
        vertece3d vertece7;

        vertece0.set_id(0);
        vertece1.set_id(1);
        vertece2.set_id(2);
        vertece3.set_id(3);
        vertece4.set_id(4);
        vertece5.set_id(5);
        vertece6.set_id(6);
        vertece7.set_id(7);

        vertecies.push_back(vertece0);
        vertecies.push_back(vertece1);
        vertecies.push_back(vertece2);
        vertecies.push_back(vertece3);
        vertecies.push_back(vertece4);
        vertecies.push_back(vertece5);
        vertecies.push_back(vertece6);
        vertecies.push_back(vertece7);

        //Depending on number of points determine shape
        switch (pointsIds->GetNumberOfIds())
        {
        case 4:
            cout << "Terahedron" << endl;
            for(int i = 0; i < 4; i++)
            {
                vector3d tmp_vector = vector3d(points->GetPoint(i)[0], points->GetPoint(i)[1], points->GetPoint(i)[2] );
                vertecies.at(i).set_vector3d(tmp_vector);
            }
            tmp_tetrahedron = Tetrahedron(vertecies.at(0).get_vector3d(),vertecies.at(1).get_vector3d(),
                                          vertecies.at(2).get_vector3d(),vertecies.at(3).get_vector3d()
                                          );
            tmp_tetrahedron.set_p0_id(vertecies.at(0).get_id());
            tmp_tetrahedron.set_p1_id(vertecies.at(1).get_id());
            tmp_tetrahedron.set_p2_id(vertecies.at(2).get_id());
            tmp_tetrahedron.set_p3_id(vertecies.at(3).get_id());
            tmp_tetrahedron.set_colour(mod_color);
            tmp_tetrahedron.set_material_id(0);
            tmp_tetrahedron.set_id(0);
            tetrahedrons.push_back(tmp_tetrahedron);
            break;
        case 5:
            cout << "Pyramid" << endl;
            for(int i = 0; i < 5; i++)
            {
                vector3d tmp_vector = vector3d(points->GetPoint(i)[0], points->GetPoint(i)[1], points->GetPoint(i)[2] );
                vertecies.at(i).set_vector3d(tmp_vector);
            }
            tmp_pyramid = Pyramid(vertecies.at(0).get_vector3d(),vertecies.at(1).get_vector3d(),
                                  vertecies.at(2).get_vector3d(),vertecies.at(3).get_vector3d(),vertecies.at(4).get_vector3d());

            tmp_pyramid.set_p0_id(vertecies.at(0).get_id());
            tmp_pyramid.set_p1_id(vertecies.at(1).get_id());
            tmp_pyramid.set_p2_id(vertecies.at(2).get_id());
            tmp_pyramid.set_p3_id(vertecies.at(3).get_id());
            tmp_pyramid.set_p4_id(vertecies.at(4).get_id());

            tmp_pyramid.set_colour(mod_color);
            tmp_pyramid.set_material_id(0);
            tmp_pyramid.set_id(0);
            pyramids.push_back(tmp_pyramid);
            break;
        case 8:
            cout << "Hexahedron" << endl;
            for(int i = 0; i < 8; i++)
            {
                vector3d tmp_vector = vector3d(points->GetPoint(i)[0], points->GetPoint(i)[1], points->GetPoint(i)[2] );
                vertecies.at(i).set_vector3d(tmp_vector);
            }
            tmp_hexahedron = Hexahedron(vertecies.at(0).get_vector3d(),vertecies.at(1).get_vector3d(),
                                        vertecies.at(2).get_vector3d(),vertecies.at(3).get_vector3d(),
                                        vertecies.at(4).get_vector3d(),vertecies.at(5).get_vector3d(),
                                        vertecies.at(6).get_vector3d(),vertecies.at(7).get_vector3d());

            tmp_hexahedron.set_p0_id(vertecies.at(0).get_id());
            tmp_hexahedron.set_p1_id(vertecies.at(1).get_id());
            tmp_hexahedron.set_p2_id(vertecies.at(2).get_id());
            tmp_hexahedron.set_p3_id(vertecies.at(3).get_id());
            tmp_hexahedron.set_p4_id(vertecies.at(4).get_id());
            tmp_hexahedron.set_p5_id(vertecies.at(5).get_id());
            tmp_hexahedron.set_p6_id(vertecies.at(6).get_id());
            tmp_hexahedron.set_p7_id(vertecies.at(7).get_id());

            tmp_hexahedron.set_colour(mod_color);
            tmp_hexahedron.set_material_id(0);
            tmp_hexahedron.set_id(0);
            hexahedrons.push_back(tmp_hexahedron);
            break;
        default:
            cout << "Unknown" << endl;
            cout << "Number of points: " << pointsIds->GetNumberOfIds() << endl;
            break;

        }

        model::deparser(QfileName.toStdString() , materials, vertecies, tetrahedrons, hexahedrons, pyramids);
    }
}
