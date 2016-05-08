#include "app.h"

App::App(QWidget *parent) : QGLWidget(parent)
{
	Camera *camera = new Camera(Vec3(0.0, 0.0, 4.0), Quaternion(0, Vec3(1.0, 0.0, 0.0)), width() / height());

    scene = new Scene(camera);
    shaderManager = new ShaderManager();
    renderer = new Renderer(scene, shaderManager);
	isCapturingCursor = false;
	setFocusPolicy(Qt::StrongFocus);
	init();
}

App::~App() {
    delete shaderManager;
    delete renderer;
    delete scene;
}

void App::init()
{
	resize(800, 600);

    startTimer(30);

    initGlew();

    initShaders();

	SceneBuilder::buildScene(scene, renderer);

    setMouseTracking(true);

    QCursor curs = cursor();
    QPoint p(width() / 2, height() / 2);
    curs.setPos(mapToGlobal(p));
	setCursor(curs);
}

void App::changeEmitter(int type)
{
	SceneBuilder::changeScene(scene, renderer, type);
}

void App::initGlew()
{
    glInit();
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
		cout<<"glewInit failed, aborting. error: "<< glewGetErrorString(err) << endl;
}

void App::initShaders()
{
    shaderManager->init();
    shaderManager->addShader("default");
}

void App::initializeGL() {
    timer.start();
    float c = 0;
    glClearColor(c, c, c, c);
    glEnable(GL_DEPTH_TEST);
}

void App::resizeGL(int w, int h)
{
    Camera *camera = scene->getCamera();

    if(camera) {
        camera->setAspectRatio(w / h);
    }
}

void App::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->render(timer.elapsed());
}

void App::timerEvent(QTimerEvent *)
{
    updateGL();
}

void App::mouseMoveEvent(QMouseEvent *event)
{
    QCursor curs = cursor();
    if(isCapturingCursor) {
        const float mouseSensivity = 1e-2f;
        QPoint p(width() / 2, height() / 2);
        QPoint cursorPos = event->pos();

        float dx = cursorPos.x() - p.x();
        float dy = cursorPos.y() - p.y();

        Camera *camera = scene->getCamera();

        if(camera != NULL && curs.shape() == Qt::BlankCursor) {
            camera->rotateY(dx * mouseSensivity);
            camera->rotateX(dy * mouseSensivity);

            event->accept();
        }

        lastCursorPos = cursorPos;

        curs.setPos(mapToGlobal(p));
        curs.setShape(Qt::BlankCursor);

        setCursor(curs);
    }
    else if(curs.shape() == Qt::BlankCursor) {
        curs.setShape(Qt::ArrowCursor);
        setCursor(curs);
    }
}

void App::keyPressEvent(QKeyEvent* event)
{
    Camera *camera = scene->getCamera();
	const float camSpeed = 0.5;

    switch(event->key())
    {
        case Qt::Key_Alt:
            isCapturingCursor = !isCapturingCursor;
            break;

		case Qt::Key_Left:
            camera->translate(-camera->right() * camSpeed);
            break;

        case Qt::Key_Right:
            camera->translate(camera->right() * camSpeed);
            break;

        case Qt::Key_Up:
            camera->translate(camera->forward() * camSpeed);
            break;

        case Qt::Key_Down:
            camera->translate(-camera->forward() * camSpeed);
            break;
    }
}
