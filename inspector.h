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
    GLWindow* mWindow;
    Inspector();
    ~Inspector();   
    void setCurModel(Model*);
private:
    Model* curModel;
    QWidget* mTransformLabel;
    QVBoxLayout* mTransformLayout;
    Transform* mTransform;

    QLineEdit* mTransformPosLblX;
    QLineEdit* mTransformPosLblY;
    QLineEdit* mTransformPosLblZ;
    QLineEdit* mTransformRotLblX;
    QLineEdit* mTransformRotLblY;
    QLineEdit* mTransformRotLblZ;
    QLineEdit* mTransformScaleLblX;
    QLineEdit* mTransformScaleLblY;
    QLineEdit* mTransformScaleLblZ;
    QLabel* curModelLbl;
    QLineEdit* camXRotate;

private slots:
   void slotChangeRotation(const QString);
   void slotChangePosition(const QString);
   void slotChangeScale(const QString);
   void slotChangeCamRot(const QString);
};

#endif // INSPECTOR_H
