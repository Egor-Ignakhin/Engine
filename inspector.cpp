#include "inspector.h"
#include "glwindow.h"
#include "vector3.h"

Inspector::Inspector(){
    mTransform = new Transform;
    mTransformLabel = new QWidget(this);
    mTransformLayout = new QVBoxLayout;

    QHBoxLayout* posLayout = new QHBoxLayout;
    QHBoxLayout* rotLayout = new QHBoxLayout;
    QHBoxLayout* scaleLayout = new QHBoxLayout;

    QWidget* parentAllPoslbls = new QWidget(this);
    QWidget* parentAllRotlbls = new QWidget(this);
    QWidget* parentAllScalelbls = new QWidget(this);

    mTransformPosLblX = new QLineEdit("0", parentAllPoslbls);
    mTransformPosLblY = new QLineEdit("0", parentAllPoslbls);
    mTransformPosLblZ = new QLineEdit("0", parentAllPoslbls);

    mTransformRotLblX = new QLineEdit("0", parentAllRotlbls);
    mTransformRotLblY = new QLineEdit("0", parentAllRotlbls);
    mTransformRotLblZ = new QLineEdit("0", parentAllRotlbls);

    mTransformScaleLblX = new QLineEdit("1", parentAllScalelbls);
    mTransformScaleLblY = new QLineEdit("1", parentAllScalelbls);
    mTransformScaleLblZ = new QLineEdit("1", parentAllScalelbls);

    mTransformLayout->addWidget(parentAllPoslbls);
    mTransformLayout->addWidget(parentAllRotlbls);
    mTransformLayout->addWidget(parentAllScalelbls);


    posLayout->addWidget(mTransformPosLblX);
    posLayout->addWidget(mTransformPosLblY);
    posLayout->addWidget(mTransformPosLblZ);
    parentAllPoslbls->setLayout(posLayout);

    rotLayout->addWidget(mTransformRotLblX);
    rotLayout->addWidget(mTransformRotLblY);
    rotLayout->addWidget(mTransformRotLblZ);
    parentAllRotlbls->setLayout(rotLayout);


    scaleLayout->addWidget(mTransformScaleLblX);
    scaleLayout->addWidget(mTransformScaleLblY);
    scaleLayout->addWidget(mTransformScaleLblZ);

    curModelLbl = new QLabel("0",this);
    camXRotate = new QLineEdit(this);
    mTransformLayout->addWidget(curModelLbl);
    mTransformLayout->addWidget(camXRotate);

    parentAllScalelbls->setLayout(scaleLayout);

    mTransformLabel->setLayout(mTransformLayout);

    //connect position fields
    connect(mTransformPosLblX,SIGNAL(textEdited(const QString)),
            SLOT(slotChangePosition(const QString)));
    connect(mTransformPosLblY,SIGNAL(textEdited(const QString)),
            SLOT(slotChangePosition(const QString)));
    connect(mTransformPosLblZ,SIGNAL(textEdited(const QString)),
            SLOT(slotChangePosition(const QString)));

    //connect rotation fields
    connect(mTransformRotLblX,SIGNAL(textEdited(const QString)),
            SLOT(slotChangeRotation(const QString)));
    connect(mTransformRotLblY,SIGNAL(textEdited(const QString)),
            SLOT(slotChangeRotation(const QString)));
    connect(mTransformRotLblZ,SIGNAL(textEdited(const QString)),
            SLOT(slotChangeRotation(const QString)));  

    //connect scale fields
    connect(mTransformScaleLblX,SIGNAL(textEdited(const QString)),
            SLOT(slotChangeScale(const QString)));
    connect(mTransformScaleLblY,SIGNAL(textEdited(const QString)),
            SLOT(slotChangeScale(const QString)));
    connect(mTransformScaleLblZ,SIGNAL(textEdited(const QString)),
            SLOT(slotChangeScale(const QString)));

    connect(camXRotate,SIGNAL(textChanged(const QString)),SLOT(slotChangeCamRot(const QString)));
}

Inspector::~Inspector(){

}

void Inspector::slotChangePosition(const QString text){
    float value = (QStringRef(&text, 0, text.size())).toFloat();
    QLineEdit* lineSender = (QLineEdit*) sender();

    Vector3 p = curModel->getPosition();//position

    if(lineSender == mTransformPosLblX){
        p.x = value;
    }
    else if(lineSender == mTransformPosLblY){
        p.y = value;
    }
    else{
        p.z = value;
    }
     curModel->setPosition(p);

    //if text is empty then set '0'
    if(!text.isEmpty()){
        //if text starting with '.' then set '0' + '.'
        if(text[0] == '.'){
            lineSender->setText('0' + text);
        }
    }
    else{
        lineSender->setText(QString('0'));
    }
}

void Inspector::slotChangeRotation(const QString text){

    float value = (QStringRef(&text, 0, text.size())).toFloat();
    QLineEdit* lineSender = (QLineEdit*) sender();

    Vector3 r  = curModel->getRotation();//rotation

    if(lineSender == mTransformRotLblX){
        r.x = value;
    }
    else if(lineSender == mTransformRotLblY){
        r.y = value;
    }
    else{
        r.z = value;
    }

    curModel->setRotation(r);


    //if text is empty then set '0'
    if(!text.isEmpty()){
        //if text starting with '.' then set '0' + '.'
        if(text[0] == '.'){
            lineSender->setText('0' + text);
        }
    }
    else{
        lineSender->setText(QString('0'));
    }
}
void Inspector::slotChangeScale(const QString text){
    float value = (QStringRef(&text, 0, text.size())).toFloat();
    QLineEdit* lineSender = (QLineEdit*) sender();

    Vector3 s = curModel->getScale();//scale
    if(lineSender == mTransformScaleLblX){
        s.x = value;
    }
    else if(lineSender == mTransformScaleLblY){
        s.y = value;
    }
    else{
        s.z = value;
    }

    curModel->setScale(s);

    //if text is empty then set '0'
    if(!text.isEmpty()){
        //if text starting with '.' then set '0' + '.'
        if(text[0] == '.'){
            lineSender->setText('0' + text);
        }
    }
    else{
        lineSender->setText(QString('0'));
    }
}
void Inspector::setCurModel(Model* model){
    curModel = model;
    curModelLbl->setText( "Current object : " + curModel->name());

    connect(curModel,SIGNAL(signalChangeRotation(Vector3)),
            SLOT(slotSetRotation(Vector3)));
    connect(curModel,SIGNAL(signalChangeRotation(Vector3)),
            SLOT(slotSetRotation(Vector3)));
    connect(curModel,SIGNAL(signalChangeRotation(Vector3)),
            SLOT(slotSetRotation(Vector3)));
}
void Inspector::slotChangeCamRot(const QString txt){
    float value = (QStringRef(&txt, 0, txt.size())).toFloat();
    mWindow->xCamRot = value;
    curModel->additionalTurn.y = value;
}
void Inspector::slotSetRotation(Vector3 vec){
     mTransformRotLblX->setText(QString::number(vec.x));
     mTransformRotLblY->setText(QString::number(vec.y));
     mTransformRotLblZ->setText(QString::number(vec.z));
}
