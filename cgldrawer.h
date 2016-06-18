#ifndef CGLDRAWER_H
#define CGLDRAWER_H

#include "openglwindow.h"
#include "cfigure.h"

#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QMouseEvent>
#include <QtCore/qmath.h>



class CGLDrawer : public OpenGLWindow
{
public:
    CGLDrawer(QWindow *parent = 0);

    void initialize() Q_DECL_OVERRIDE;
    void render() Q_DECL_OVERRIDE;

    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    virtual void mouseMoveEvent(QMouseEvent * ev);

    void setDrawData(const DrawData& drawData);


private:
    GLuint loadShader(GLenum type, const char *source);

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    int xRot;
    int yRot;
    int zRot;
    QPoint lastPos;
    DrawData m_drawData;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};

#endif // CGLDRAWER_H
