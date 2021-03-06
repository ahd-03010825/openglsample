#include "trianglewindow.h"

#include <QOpenGLShaderProgram>
#include <QPainter>

TriangleWindow::TriangleWindow() :
	m_program(nullptr),
	m_frame(0)
{}

void TriangleWindow::initializeGL()
{
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simplematrix.vsh");
	m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simplecolor.fsh");
	m_program->link();
	m_posAttr = m_program->attributeLocation("posAttr");
	m_colAttr = m_program->attributeLocation("colAttr");
	m_matrixUniform = m_program->uniformLocation("matrix");

	initializeOpenGLFunctions();
}

void TriangleWindow::paintGL()
{
	QPainter painter(this);
	painter.beginNativePainting();

	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	glClear(GL_COLOR_BUFFER_BIT);

	m_program->bind();

	QMatrix4x4 matrix;
	matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
	matrix.translate(0, 0, -2);
	matrix.rotate(100.0f * m_frame / 10, 0, 1, 0);

	m_program->setUniformValue(m_matrixUniform, matrix);

	GLfloat vertices[] = {
			0.0f, 0.707f,
			-0.5f, -0.5f,
			0.5f, -0.5f
	};

	GLfloat colors[] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
	};

	glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	m_program->release();

	painter.endNativePainting();

	painter.save();

	painter.setPen(Qt::white);
	painter.drawText(QPointF(200, 200), "This is a test");

	painter.restore();

	++m_frame;
}
