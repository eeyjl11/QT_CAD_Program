#include "scenewidget.h"

/** @file
* Scenewidget definition file
*/

/**
 * @brief Constructor for Scenewidget
 */

SceneWidget::SceneWidget(QWidget* parent)
    : QVTKOpenGLNativeWidget(parent)
{
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    setRenderWindow(window.Get());

    // Camera
    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
    camera->SetViewUp(0, 1, 0);
    camera->SetPosition(0, 0, 10);
    camera->SetFocalPoint(0, 0, 0);

    vtkSmartPointer<vtkLight> light = vtkSmartPointer<vtkLight>::New();
    light->SetLightTypeToSceneLight();
    light->SetPosition( 30, 30, 30 );
    light->SetPositional( true );
    light->SetConeAngle( 60 );
    light->SetFocalPoint( 0, 0, 0 );
    light->SetDiffuseColor( 1, 1, 1 );
    light->SetAmbientColor( 1, 1, 1 );
    light->SetSpecularColor( 1, 1, 1 );
    light->SetIntensity( 0.8 );

    // Renderer
    m_renderer = vtkSmartPointer<vtkRenderer>::New();
    m_renderer->SetActiveCamera(camera);
    m_renderer->SetBackground(0.5, 0.5, 0.5);
    m_renderer->AddLight(light);
    renderWindow()->AddRenderer(m_renderer);
}

/**
 * @brief Add actor to the scene
 *
 * Adds actor to the widget renderer
 * @param actor
 * Input Actor that needs to be added to the scene
 */
void SceneWidget::addActor(vtkSmartPointer<vtkActor> actor)
{
    m_renderer->AddActor(actor);

    renderWindow()->Render();
}

/**
 * @brief Remove last actor from scene
 *
 * Removes last added actor from the widget renderer
 */
void SceneWidget::removeLastActor()
{
    vtkActor* actor = m_renderer->GetActors()->GetLastActor();
    if (actor != nullptr) {
        m_renderer->RemoveActor(actor);
    }

    renderWindow()->Render();
}

/**
 * @brief Set scene background color
 *
 * Sets background color to the widget renderer
 * @param input_color
 * Input color of types QColor
 */
void SceneWidget::setBackground(QColor &input_color)
{
    int r;
    int g;
    int b;
    input_color.getRgb(&r,&g,&b);
    m_renderer->SetBackground((double)(r)/255,(double)(g)/255,(double)(b)/255);
    renderWindow()->Render();
}

/**
 * @brief Get scene background color
 *
 * Get current background color from the widget renderer
 * @return current color of type QColor
 */
QColor SceneWidget::getBackground()
{
    double r;
    double g;
    double b;
    m_renderer->GetBackground(r,g,b);
    return QColor((int)(r*255),(int)(g*255),(int)(b*255));
}

/**
 * @brief Set light intensity
 *
 * Set light intensity to all light sources in the widget renderer
 * @param input_intensity
 * double intensity value from 0 to 1
 */
void SceneWidget::setLightIntensity(double input_intensity)
{
    vtkSmartPointer<vtkLightCollection> lights = m_renderer->GetLights();
    lights->InitTraversal();
    while(1)
    {
        vtkLight * light = lights->GetNextItem();
        if(light != nullptr)
        {
            light->SetIntensity( input_intensity );
        }
        else
        {
            break;
        }
    }
    renderWindow()->Render();
}

/**
 * @brief Set color of provided actor
 *
 * @param input_color
 * QColor color to set to input_actor
 * @param input_actor
 * vtkActor to which color needs to be set
 */
void SceneWidget::setActorColor(QColor &input_color,vtkActor * input_actor)
{
    if(checkActor(input_actor))
    {
        input_actor->GetProperty()->SetColor((double)input_color.red()/255,(double)input_color.green()/255,(double)input_color.blue()/255);
        renderWindow()->Render();
    }
    return;
}

/**
 * @brief Get color of provided actor
 * @param input_actor
 * vtkActor to get color value from
 * @return QColor color of the the input_actor
 */
QColor SceneWidget::getActorColor(vtkActor * input_actor)
{
    double * color_double = input_actor->GetProperty()->GetColor();
    int r = (int)(color_double[0]*255);
    int g = (int)(color_double[1]*255);
    int b = (int)(color_double[2]*255);
    QColor result (r,g,b);
    return result;
}

/**
 * @brief Remove currently selected actor
 *
 * Remove actor and its outline actor from the widget renderer
 */
void SceneWidget::removePickedActor()
{
    if(LastOutLine != nullptr)
    {
        m_renderer->RemoveActor(LastOutLine);
        m_renderer->RemoveActor(LastPickedActor);
        renderWindow()->Render();
    }
}
/**
 * @brief Get currently selected actor
 *
 * @return vtkActor that is currently selected and highlighted
 */
vtkActor * SceneWidget::getPickedActor()
{
    return LastPickedActor;
}

/**
 * @brief Select next actor
 *
 * Select currently unselected actor that is after the currently selected actor.
 * If no actor was previously selected, selects first actor
 * @return vtkActor newly selected and highlighted
 */
vtkActor * SceneWidget::ChooseActor()
{
    m_renderer->RemoveActor(LastOutLine);
    vtkActorCollection * actors = m_renderer->GetActors();
    vtkSmartPointer<vtkActor> FirstActor;

    if(actors != nullptr)
    {
        actors->InitTraversal();
        int chosen = 0;
        int i = 0;
        while(1)
        {
            vtkActor * actor = actors->GetNextActor();
            if(actor != nullptr)
            {
                cout << "Actor" << endl;
                cout << actor << endl;

                if( chosen == -1 || FirstActor == actor)
                {
                    LastPickedActor = actor;
                    return actor;
                }
                if( i == 0)
                {
                    FirstActor = actor;
                }
                if(actor == LastPickedActor)
                {
                    chosen = -2;
                }
                chosen++;
                i++;
            }
            else
            {
                break;
            }
        }
    }
    LastPickedActor = FirstActor;
    return FirstActor;
}

/**
 * @brief Get Light intensity
 *
 * Get light intesity for first light from the widget renderer
 * @return double intensity from 0 to 1
 */
double SceneWidget::getLightIntensity()
{
    vtkSmartPointer<vtkLightCollection> lights = m_renderer->GetLights();
    lights->InitTraversal();
    vtkSmartPointer<vtkLight> light = lights->GetNextItem();
    return light->GetIntensity();
}

/**
 * @brief Set clip filter to actor
 *
 * Sets clip filter to provided vtkActor.
 * Cuts the actor in half
 * @param input_actor
 * vtkActor to apply clip filter to
 */
void SceneWidget::setClipFilter(vtkActor * input_actor)
{
    if(checkActor(input_actor))
    {
        vtkSmartPointer<vtkMapper> our_mapper =  input_actor->GetMapper();
        vtkAlgorithmOutput *  our_init_data = our_mapper->GetInputConnection(0,0);
        vtkSmartPointer<vtkPlane> planeLeft = vtkSmartPointer<vtkPlane>::New();
        double * center;
        center = input_actor->GetCenter();

        planeLeft->SetOrigin(center[0], center[1], center[2]);
        planeLeft->SetNormal(1.0, 0.0, 0.0);
        vtkSmartPointer<vtkClipDataSet> clipFilter = vtkSmartPointer<vtkClipDataSet>::New();
        clipFilter->SetInputConnection(0,our_init_data);
        clipFilter->Update();
        //clipFilter->SetInputConnection( our_mapper->GetInput()->GetOutputPort() ) ;
        clipFilter->SetClipFunction( planeLeft.Get() );
        our_mapper->SetInputConnection( clipFilter->GetOutputPort() );
        renderWindow()->Render();
        cout << "Clip" << endl;
    }
}

/**
 * @brief Set shrink filter to actor
 *
 * Sets shrink filter to provided vtkActor.
 * Shrinks actor by factor of 0.8
 * @param input_actor
 * vtkActor to apply shrink filter to
 */
void SceneWidget::setShrinkFilter(vtkActor *input_actor)
{
    if(checkActor(input_actor))
    {
        vtkSmartPointer<vtkMapper> our_mapper =  input_actor->GetMapper();
        vtkAlgorithmOutput *  our_init_data = our_mapper->GetInputConnection(0,0);
        vtkSmartPointer<vtkShrinkFilter> shrinkFilter = vtkSmartPointer<vtkShrinkFilter>::New();
        shrinkFilter->SetInputConnection(our_init_data);
        shrinkFilter->SetShrinkFactor(.8);
        shrinkFilter->Update();
        our_mapper->SetInputConnection(0,shrinkFilter->GetOutputPort() );
        renderWindow()->Render();
        cout << "Shrink" << endl;
    }
}

/**
 * @brief Set outline to actor
 *
 * Sets outline to provided vtkActor.
 * Creates new actor that highlights provided actor.
 * Saves outline actor to LastOutline to show that this actor is "Fake".
 * @param input_actor
 * vtkActor to apply outline filter to
 */
void SceneWidget::setOutlineFilter(vtkActor *input_actor)
{
    if(checkActor(input_actor))
    {
        vtkSmartPointer<vtkMapper> our_mapper =  input_actor->GetMapper();
        vtkAlgorithmOutput *  our_init_data = our_mapper->GetInputConnection(0,0);
        // Create the outline
        vtkSmartPointer<vtkOutlineFilter> outline = vtkSmartPointer<vtkOutlineFilter>::New();
        outline->SetInputConnection(our_init_data);
        vtkSmartPointer<vtkPolyDataMapper> outlineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        outlineMapper->SetInputConnection(outline->GetOutputPort());
        vtkSmartPointer<vtkActor>outlineActor = vtkSmartPointer<vtkActor>::New();
        outlineActor->SetMapper(outlineMapper);
        outlineActor->GetProperty()->SetColor(0,1.,0); //Set RED outline
        outlineActor->GetProperty()->SetMetallic(0.2);
        LastOutLine = outlineActor;
        addActor(outlineActor);
    }
}

/**
 * @brief Check if actor exists
 * @param input_actor
 * vtkActor pointer that needs to be checked for existance in the widget renderer
 * @return 0 - Actor does not exist in renderer
 * @return 1 - Actor exists in renderer
 */
bool SceneWidget::checkActor(vtkActor *input_actor)
{
    vtkActorCollection * actors = m_renderer->GetActors();
    vtkSmartPointer<vtkActor> FirstActor;

    if(actors != nullptr)
    {
        actors->InitTraversal();
        int chosen = 0;
        int i = 0;
        while(1)
        {
            vtkActor * actor = actors->GetNextActor();
            if(actor != nullptr)
            {
                cout << "Actor" << endl;
                cout << actor << endl;

                if(input_actor == actor)
                {
                    return 1;
                }
            }
            else
            {
                break;
            }
        }
    }
    return 0;
}

/**
 * @brief Get total number of actors
 *
 * Get total number of actors in the widget renderer
 * @return number of actors excluding outline actor
 */
int SceneWidget::getActorCount()
{
    vtkActorCollection * actors = m_renderer->GetActors();
    vtkSmartPointer<vtkActor> FirstActor;
    int i = 0;
    if(actors != nullptr)
    {
        actors->InitTraversal();

        while(1)
        {
            vtkActor * actor = actors->GetNextActor();
            if(actor != nullptr)
            {
                if(actor!=LastOutLine)
                {
                    cout << "Actor" << endl;
                    cout << actor << endl;
                    i++;
                }
            }
            else
            {
                break;
            }
        }
    }
    return i;
}

/**
 * @brief Get collection of actors from renderer
 * @return vtkActorCollection of all actors in the widget renderer
 */

vtkActorCollection * SceneWidget::getAllActors()
{
    return m_renderer->GetActors();
}

/**
 * @brief Get outline actor
 *
 * Get "Fake" actor that is used to draw oultine of selected actor
 * @return vtkActor that is outline
 */
vtkActor * SceneWidget::getOutlineActor()
{
    return LastOutLine;
}

/**
 * @brief Change camera to zoom to last added actor
 */
void SceneWidget::zoomToExtent()
{
    // Zoom to extent of last added actor
    vtkSmartPointer<vtkActor> actor = m_renderer->GetActors()->GetLastActor();
    if (actor != nullptr) {
        m_renderer->ResetCamera(actor->GetBounds());
    }

    renderWindow()->Render();
}
