#ifndef INSPECTOR_H
#define INSPECTOR_H
#include "editor.h"
#include "model.h"
#include "transform.h"

class Inspector : public Editor
{
    Q_OBJECT
public:
    Inspector();
    ~Inspector();
    Model* curModel;
private:
    QWidget* mTransformLabel;
    QHBoxLayout* mTransformLayout;
    Transform* mTransform;
    QLineEdit* mTransformLblX;
    QLineEdit* mTransformLblY;
    QLineEdit* mTransformLblZ;
private slots:
   void slotChangeTransform(const QString);
};

#endif // INSPECTOR_H
