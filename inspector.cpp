#include "inspector.h"
#include "glwindow.h"
#include "vector3.h"
#include "levelscreator.h"

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
    QLabel* titleTransform = new QLabel("Transform", this);
    QFont titlesFont = titleTransform->font();
    titlesFont.setPixelSize(25);
    titleTransform->setFont(titlesFont);
    QPushButton* openCreator = new QPushButton("Open levels creator", this);

    QLabel* titlePosition = new QLabel("Position", this);
    mTrLbls[0] = new QLineEdit("0", parentAllPoslbls);
    mTrLbls[1] = new QLineEdit("0", parentAllPoslbls);
    mTrLbls[2] = new QLineEdit("0", parentAllPoslbls);

    QLabel* titleRotation = new QLabel("Rotation", this);
    mTrLbls[3] = new QLineEdit("0", parentAllRotlbls);
    mTrLbls[4] = new QLineEdit("0", parentAllRotlbls);
    mTrLbls[5] = new QLineEdit("0", parentAllRotlbls);

    QLabel* titleScale = new QLabel("Scale", this);
    mTrLbls[6] = new QLineEdit("1", parentAllScalelbls);
    mTrLbls[7] = new QLineEdit("1", parentAllScalelbls);
    mTrLbls[8] = new QLineEdit("1", parentAllScalelbls);

    titleTransform->setAlignment(Qt::AlignHCenter);
    mTransformLayout->addWidget(titleTransform);
    mTransformLayout->addWidget(parentAllPoslbls);
    mTransformLayout->addWidget(parentAllRotlbls);
    mTransformLayout->addWidget(parentAllScalelbls);

    posLayout->addWidget(titlePosition);
    posLayout->addWidget(mTrLbls[0]);
    posLayout->addWidget(mTrLbls[1]);
    posLayout->addWidget(mTrLbls[2]);
    parentAllPoslbls->setLayout(posLayout);

    rotLayout->addWidget(titleRotation);
    rotLayout->addWidget(mTrLbls[3]);
    rotLayout->addWidget(mTrLbls[4]);
    rotLayout->addWidget(mTrLbls[5]);
    parentAllRotlbls->setLayout(rotLayout);

    scaleLayout->addWidget(titleScale);
    scaleLayout->addWidget(mTrLbls[6]);
    scaleLayout->addWidget(mTrLbls[7]);
    scaleLayout->addWidget(mTrLbls[8]);

    curModelLbl = new QLabel("0",this);
    camRotateVector[0] = new QLabel(this);
    camRotateVector[1] = new QLabel(this);
    camRotateVector[2] = new QLabel(this);
    bGameMode = new QPushButton("start");
    bGameMode->setStyleSheet("background-color : red");
    mTransformLayout->addWidget(curModelLbl);
    mTransformLayout->addWidget(camRotateVector[0]);
    mTransformLayout->addWidget(camRotateVector[1]);
    mTransformLayout->addWidget(camRotateVector[2]);
    mTransformLayout->addWidget(bGameMode);
    mTransformLayout->addWidget(openCreator);

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

    mLvlsCreator = new LevelsCreator;
    connect(openCreator, SIGNAL(clicked()), mLvlsCreator, SLOT(open()));
}

Inspector::~Inspector(){

}

void Inspector::slotChangePosition(const QString text){
    float value = (QStringRef(&text, 0, text.size())).toFloat();
    QLineEdit* lineSender = (QLineEdit*) sender();

    Vector3 p = curModel->transform.position();//position

    if(lineSender == mTrLbls[0]){
        p.x = value;
    }
    else if(lineSender == mTrLbls[1]){
        p.y = value;
    }
    else{
        p.z = value;
    }
     curModel->transform.setPosition(p);

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

    Vector3 r  =  curModel->transform.rotation();//rotation

    if(lineSender == mTrLbls[3]){
        r.x = value;
    }
    else if(lineSender == mTrLbls[4]){
        r.y = value;
    }
    else{
        r.z = value;
    }

    curModel->transform.setRotation(r);


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

    Vector3 s =  curModel->transform.scale();//scale
    if(lineSender == mTrLbls[6]){
        s.x = value;
    }
    else if(lineSender == mTrLbls[7]){
        s.y = value;
    }
    else{
        s.z = value;
    }

    curModel->transform.setScale(s);

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
void Inspector::slotChangeCamRot(Vector3 vec){
   // QStringRef value(&txt, 0, txt.size());//.toFloat();
    camRotateVector[0] ->setText("Camera x rotate = " + QString::number(vec.x));
    camRotateVector[1] ->setText("Camera y rotate = " + QString::number(vec.y));
    camRotateVector[2] ->setText("Camera z rotate = " + QString::number(vec.z));

}
void Inspector::slotSetRotation(Vector3 vec){
     mTrLbls[3]->setText(QString::number(vec.x));
     mTrLbls[4]->setText(QString::number(vec.y));
     mTrLbls[5]->setText(QString::number(vec.z));
}
void Inspector::setMainWindow(GLWindow *w){
    mWindow = w;       
    connect(mWindow, SIGNAL(signalChangeCamRot(Vector3)),SLOT(slotChangeCamRot(Vector3)));
    connect(bGameMode, SIGNAL(clicked()), w,SLOT(slotChangeGameMode()));
}
