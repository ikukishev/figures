#include "cgldrawer.h"

static const char *vertexShaderSource =
    "attribute highp vec4 posAttr;\n"
    "attribute lowp vec4 colAttr;\n"
    "varying lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying lowp vec4 col;\n"
    "void main() {\n"
    "   gl_FragColor = col;\n"
    "}\n";


CGLDrawer::CGLDrawer(QWindow *parent)
    : OpenGLWindow(parent)
    , m_program(0)
    , m_frame(0)
{
    QSurfaceFormat format;
    format.setSamples(16);
    setFormat(format);
    setAnimating(true);
}

GLuint CGLDrawer::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}

void CGLDrawer::initialize()
{
    initializeOpenGLFunctions();
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");
    xRot = 0;
    yRot = 0;
    zRot = 0;
}

void CGLDrawer::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    m_program->bind();

    static QVector4D eye = QVector4D(10,10,10,1);

    QMatrix4x4 eyeConv;
    eyeConv.setToIdentity();
    eyeConv.rotate(xRot / 16.0, 1.0, 0.0, 0.0);
    eyeConv.rotate(yRot / 16.0, 0.0, 1.0, 0.0);
    eyeConv.rotate(zRot / 16.0, 0.0, 0.0, 1.0);
    eye = eyeConv * eye;
    xRot = 0;
    zRot = 0;
    yRot = 0;


    QMatrix4x4 matrix;
    matrix.perspective(60.0f, (float)width()/((float)height()), 0.1f, 100.0f);
    matrix.lookAt(QVector3D(eye), QVector3D(0,0,0), QVector3D(0,0,1));

//    GLfloat plane[] = {
//        10.0f,  10.0f, 0.0f,
//        10.0f, -10.0f, 0.0f,
//        -10.0f, -10.0f,0.0f,

//        -10.0f, -10.0f, 0.0f,
//        -10.0f,10.0f,0.0f,
//        10.0f,  10.0f,0.0f,

//    };

//    GLfloat planeColor[] = {
//        0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f, 0.5f,

//        0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f, 0.5f,
//        0.5f, 0.5f, 0.5f,

//    };

    QMatrix4x4 coordMatrix = matrix;
    matrix.translate(0,0,0.1f);

    m_program->setUniformValue(m_matrixUniform, coordMatrix);

//    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, plane);
//    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, planeColor);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
//    glDrawArrays(GL_TRIANGLES, 0, 6);

    GLfloat axexs[] = {
        10.0f, 0.0f, 0.0f,
        -10.0f, 0.0f, 0.0f,
        0.0f, 10.0f, 0.0f,
        0.0f, -10.0f, 0.0f,
    };

    GLfloat axexsColor[] = {
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    };

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, axexs);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, axexsColor);
    glDrawArrays(GL_LINES, 0, 4);


    const int countAxessDrops = 10;
    GLfloat axexsDrops[ countAxessDrops*4*2*3 ];
    GLfloat axexsDropsColor[ countAxessDrops*4*2*3 ];
    for (int i = 0; i<countAxessDrops; i++)
    {
        int index=i*2*3;
        axexsDrops[index] = (float)(i+1);
        axexsDrops[index+1] = (float)(10);
        axexsDrops[index+2] = (float)(0);
        axexsDrops[index+3] = (float)(i+1);
        axexsDrops[index+4] = (float)(-10);
        axexsDrops[index+5] = (float)(0);
        axexsDropsColor[index] = 0.3f;
        axexsDropsColor[index+1] = 0.5f;
        axexsDropsColor[index+2] = 0.3f;
        axexsDropsColor[index+3] =  0.3f;
        axexsDropsColor[index+4] = 0.5f;
        axexsDropsColor[index+5] =  0.3f;
    }

    for (int i = 0; i<countAxessDrops; i++)
    {
        int index=countAxessDrops*3*2 + i*2*3;
        axexsDrops[index] = (float)(-i-1);
        axexsDrops[index+1] = (float)(10);
        axexsDrops[index+2] = (float)(0);
        axexsDrops[index+3] = (float)(-i-1);
        axexsDrops[index+4] = (float)(-10);
        axexsDrops[index+5] = (float)(0);
        axexsDropsColor[index] = 0.3f;
        axexsDropsColor[index+1] = 0.5f;
        axexsDropsColor[index+2] = 0.3f;
        axexsDropsColor[index+3] =  0.3f;
        axexsDropsColor[index+4] = 0.5f;
        axexsDropsColor[index+5] =  0.3f;
    }

    for (int i = 0; i<countAxessDrops; i++)
    {
        int index=countAxessDrops*3*2*2 + i*2*3;
        axexsDrops[index] = (float)(10);
        axexsDrops[index+1] = (float)(i+1);
        axexsDrops[index+2] = (float)(0);
        axexsDrops[index+3] = (float)(-10);
        axexsDrops[index+4] = (float)(i+1);
        axexsDrops[index+5] = (float)(0);
        axexsDropsColor[index] = 0.3f;
        axexsDropsColor[index+1] = 0.5f;
        axexsDropsColor[index+2] = 0.3f;
        axexsDropsColor[index+3] =  0.3f;
        axexsDropsColor[index+4] = 0.5f;
        axexsDropsColor[index+5] =  0.3f;
    }

    for (int i = 0; i<countAxessDrops; i++)
    {
        int index=countAxessDrops*3*2*3 + i*2*3;
        axexsDrops[index] = (float)(10);
        axexsDrops[index+1] = (float)(-i-1);
        axexsDrops[index+2] = (float)(0);
        axexsDrops[index+3] = (float)(-10);
        axexsDrops[index+4] = (float)(-i-1);
        axexsDrops[index+5] = (float)(0);
        axexsDropsColor[index] = 0.3f;
        axexsDropsColor[index+1] = 0.5f;
        axexsDropsColor[index+2] = 0.3f;
        axexsDropsColor[index+3] =  0.3f;
        axexsDropsColor[index+4] = 0.5f;
        axexsDropsColor[index+5] =  0.3f;
    }

    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, axexsDrops);
    glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, axexsDropsColor);
    glDrawArrays(GL_LINES, 0, countAxessDrops*4*2);

    if (m_drawData.getVertexes().get() != nullptr && m_drawData.getColores().get() != nullptr)
    {
        std::vector<glm::vec3> * vVertices = m_drawData.getVertexes().get();
        std::vector<glm::vec3> * vColors = m_drawData.getColores().get();
        if (vVertices->size() >= 3)
        {
            GLfloat * vertices = (GLfloat*)vVertices->data();
            GLfloat * colors = (GLfloat*)vColors->data();
            matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 0, 1);
            m_program->setUniformValue(m_matrixUniform, matrix);

            glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, 0, vertices);
            glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);
            glDrawArrays(GL_TRIANGLES, 0, vVertices->size());
        }
    }

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    m_program->release();

    ++m_frame;
}

void CGLDrawer::setXRotation(int angle)
{
    if (angle != xRot) {
        xRot = angle;
        render();
    }
}

void CGLDrawer::setYRotation(int angle)
{
    if (angle != yRot) {
        yRot = angle;
        render();
    }
}

void CGLDrawer::setZRotation(int angle)
{
    if (angle != zRot) {
        zRot = angle;
        render();

    }
}

void CGLDrawer::mouseMoveEvent(QMouseEvent *ev)
{
    int dx = ev->x() - lastPos.x();
    int dy = ev->y() - lastPos.y();

    if (ev->buttons() & Qt::LeftButton) {
       setXRotation(xRot + 8 * dy);
       setYRotation(yRot + 8 * dx);
    } else if (ev->buttons() & Qt::RightButton) {
       setXRotation(xRot + 8 * dy);
       setZRotation(zRot + 8 * dx);
    }
    lastPos = ev->pos();
}

void CGLDrawer::setDrawData(const DrawData &drawData)
{
    m_drawData = drawData;
}
