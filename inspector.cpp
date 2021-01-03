#include "inspector.h"

Inspector::Inspector(){
    mTransform = new Transform;
    mTransformLabel = new QWidget(this);
    mTransformLayout = new QHBoxLayout;

    mTransformLblX = new QLineEdit(this);
    mTransformLblY = new QLineEdit(this);
    mTransformLblZ = new QLineEdit(this);
    mTransformLayout->addWidget(mTransformLblX);
    mTransformLayout->addWidget(mTransformLblY);
    mTransformLayout->addWidget(mTransformLblZ);
    mTransformLabel->setLayout(mTransformLayout);

    connect(mTransformLblX,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeTransform(const QString)));
    connect(mTransformLblY,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeTransform(const QString)));
    connect(mTransformLblZ,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeTransform(const QString)));

}
Inspector::~Inspector(){

}
void Inspector::slotChangeTransform(const QString text){

    float value;
    value = (QStringRef(&text, 0, text.size())).toFloat();
    if(qobject_cast<QLineEdit*>(sender()) == mTransformLblX){ //X
        curModel->setRotation(&value,nullptr,nullptr);
        qDebug()<<"is X";
    }
    else if(qobject_cast<QLineEdit*>(sender()) == mTransformLblY){ //Y
        curModel->setRotation(nullptr,&value,nullptr);
        qDebug()<<"is Y";
    }
    else{ //Z
        curModel->setRotation(nullptr, nullptr, &value);
        qDebug()<<"is Z";
    }
}
