#ifndef INSPECTOR_H
#define INSPECTOR_H
#include "editor.h"
#include "model.h"
#include "transform.h"

class GLWindow;

class Inspector : public Editor
{
    Q_OBJECT
public:
    Inspector();
    ~Inspector();
    void setCurModel(Model*);
    void setMainWindow(GLWindow *);

private:
     GLWindow* mWindow;
    Model* curModel;
    QWidget* mTransformLabel;
    QVBoxLayout* mTransformLayout;
    Transform* mTransform;

    QLineEdit* mTrLbls[9];// labels of transform cur-model. 0 - 2 : position. 3 - 5 : rotation. 6 - 8 : scale.
    QLabel* curModelLbl;
    QLabel* camXRotate;
    QPushButton* bMotions[4];

private slots:
   void slotChangeRotation(const QString);
   void slotChangePosition(const QString);
   void slotChangeScale(const QString);
   void slotChangeCamRot(GLfloat);
   void slotSetRotation(Vector3 vec);
};

#endif // INSPECTOR_H
