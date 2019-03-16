#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

class QOpenGLShaderProgram;

class TriangleWindow : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
	TriangleWindow();

	void initializeGL() override;
	void paintGL() override;

private:
	GLuint m_posAttr;
	GLuint m_colAttr;
	GLuint m_matrixUniform;

	QOpenGLShaderProgram* m_program;
	int m_frame;
};

#endif // TRIANGLEWINDOW_H
