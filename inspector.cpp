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


    mTrLbls[0] = new QLineEdit("0", parentAllPoslbls);
    mTrLbls[1] = new QLineEdit("0", parentAllPoslbls);
    mTrLbls[2] = new QLineEdit("0", parentAllPoslbls);

    mTrLbls[3] = new QLineEdit("0", parentAllRotlbls);
    mTrLbls[4] = new QLineEdit("0", parentAllRotlbls);
    mTrLbls[5] = new QLineEdit("0", parentAllRotlbls);

    mTrLbls[6] = new QLineEdit("1", parentAllScalelbls);
    mTrLbls[7] = new QLineEdit("1", parentAllScalelbls);
    mTrLbls[8] = new QLineEdit("1", parentAllScalelbls);

    mTransformLayout->addWidget(parentAllPoslbls);
    mTransformLayout->addWidget(parentAllRotlbls);
    mTransformLayout->addWidget(parentAllScalelbls);


    posLayout->addWidget(mTrLbls[0]);
    posLayout->addWidget(mTrLbls[1]);
    posLayout->addWidget(mTrLbls[2]);
    parentAllPoslbls->setLayout(posLayout);

    rotLayout->addWidget(mTrLbls[3]);
    rotLayout->addWidget(mTrLbls[4]);
    rotLayout->addWidget(mTrLbls[5]);
    parentAllRotlbls->setLayout(rotLayout);


    scaleLayout->addWidget(mTrLbls[6]);
    scaleLayout->addWidget(mTrLbls[7]);
    scaleLayout->addWidget(mTrLbls[8]);

    curModelLbl = new QLabel("0",this);
    camXRotate = new QLabel(this);
    bMotions[0] = new QPushButton("forward");
    bMotions[1] = new QPushButton("backward");
    bMotions[2] = new QPushButton("right");
    bMotions[3] = new QPushButton("left");
    bGameMode = new QPushButton("start");
    bGameMode->setStyleSheet("background-color : red");
    mTransformLayout->addWidget(curModelLbl);
    mTransformLayout->addWidget(camXRotate);
    mTransformLayout->addWidget(bMotions[0]);
    mTransformLayout->addWidget(bMotions[1]);
    mTransformLayout->addWidget(bMotions[2]);
    mTransformLayout->addWidget(bMotions[3]);
    mTransformLayout->addWidget(bGameMode);

    parentAllScalelbls->setLayout(scaleLayout);

    mTransformLabel->setLayout(mTransformLayout);

    //connect position fields
    connect(mTrLbls[0],SIGNAL(textEdited(const QString)),
            SLOT(slotChangePosition(const QString)));
    connect(mTrLbls[1],SIGNAL(textEdited(const QString)),
            SLOT(slotChangePosition(const QString)));
    connect(mTrLbls[2],SIGNAL(textEdited(const QString)),
            SLOT(slotChangePosition(const QString)));

    //connect rotation fields
    connect(mTrLbls[3],SIGNAL(textEdited(const QString)),
            SLOT(slotChangeRotation(const QString)));
    connect(mTrLbls[4],SIGNAL(textEdited(const QString)),
            SLOT(slotChangeRotation(const QString)));
    connect(mTrLbls[5],SIGNAL(textEdited(const QString)),
            SLOT(slotChangeRotation(const QString)));  

    //connect scale fields
    connect(mTrLbls[6],SIGNAL(textEdited(const QString)),
            SLOT(slotChangeScale(const QString)));
    connect(mTrLbls[7],SIGNAL(textEdited(const QString)),
            SLOT(slotChangeScale(const QString)));
    connect(mTrLbls[8],SIGNAL(textEdited(const QString)),
            SLOT(slotChangeScale(const QString)));   
}

Inspector::~Inspector(){

}

void Inspector::slotChangePosition(const QString text){
    float value = (QStringRef(&text, 0, text.size())).toFloat();
    QLineEdit* lineSender = (QLineEdit*) sender();

    Vector3 p = curModel->getPosition();//position

    if(lineSender == mTrLbls[0]){
        p.x = value;
    }
    else if(lineSender == mTrLbls[1]){
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

    if(lineSender == mTrLbls[3]){
        r.x = value;
    }
    else if(lineSender == mTrLbls[4]){
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
    if(lineSender == mTrLbls[6]){
        s.x = value;
    }
    else if(lineSender == mTrLbls[7]){
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
void Inspector::slotChangeCamRot(GLfloat value){
   // QStringRef value(&txt, 0, txt.size());//.toFloat();
    camXRotate->setText("Camera x rotate = " + QString::number(value));

}
void Inspector::slotSetRotation(Vector3 vec){
     mTrLbls[3]->setText(QString::number(vec.x));
     mTrLbls[4]->setText(QString::number(vec.y));
     mTrLbls[5]->setText(QString::number(vec.z));
}
void Inspector::setMainWindow(GLWindow *w){
    mWindow = w;    
    connect(bMotions[0], SIGNAL(clicked()), w ,SLOT(slotForwardMove()));
    connect(bMotions[1], SIGNAL(clicked()), w ,SLOT(slotBackwardMove()));
    connect(bMotions[2], SIGNAL(clicked()), w ,SLOT(slotRightMove()));
    connect(bMotions[3], SIGNAL(clicked()), w ,SLOT(slotLeftMove()));
    connect(mWindow, SIGNAL(signalChangeYCamRot(GLfloat)),SLOT(slotChangeCamRot(GLfloat)));
    connect(bGameMode, SIGNAL(clicked()), w,SLOT(slotChangeGameMode()));
}
