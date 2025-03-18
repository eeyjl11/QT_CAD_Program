#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

/** @file
* SceneWidget declaration file
*/

#include <QVTKOpenGLNativeWidget.h>
#include <vtkDataSet.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkCamera.h>
#include <vtkColor.h>
#include <vtkDataSetMapper.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkProperty.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <vtkCollectionIterator.h>
#include <vtkPickingManager.h>
#include <vtkActorCollection.h>
#include <vtkClipDataSet.h>
#include <QColor>
#include <vtkPlane.h>
#include <vtkShrinkFilter.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkInformation.h>
#include <vtkInformationKey.h>
#include <vtkAppendPolyData.h>
#include <vtkGeometryFilter.h>

#include <vector>


/**
 * @brief The SceneWidget class
 * Class for the vtk widget
 */
class SceneWidget : public QVTKOpenGLNativeWidget {
    Q_OBJECT
public:
    explicit SceneWidget(QWidget* parent = nullptr);
    void addActor(vtkSmartPointer<vtkActor> actor);
    void removeLastActor();
    void setActorColor(QColor &input_color,vtkActor * input_actor);
    QColor getActorColor(vtkActor * input_actor);
    vtkActor * getPickedActor();
    vtkActor * ChooseActor();
    void setBackground(QColor &input_color);
    QColor getBackground();
    void setLightIntensity(double input_intensity);
    double getLightIntensity();
    void setClipFilter(vtkActor * input_actor);
    void setShrinkFilter(vtkActor * input_actor);
    void setOutlineFilter(vtkActor * input_actor);
    void removePickedActor();
    bool checkActor(vtkActor * input_actor);
    int getActorCount();
    vtkActor * getOutlineActor();
    vtkActorCollection * getAllActors();

public slots:
    void zoomToExtent();

private:
    /**
     * @brief VTK Renderer
     * Stores all rendering data for vtk
     */
    vtkSmartPointer<vtkRenderer> m_renderer;
    /**
     * @brief Currently selected actor
     */
    vtkActor* LastPickedActor;
    /**
     * @brief Actor used to highlight actor
     */
    vtkActor* LastOutLine;
};

#endif // SCENEWIDGET_H
