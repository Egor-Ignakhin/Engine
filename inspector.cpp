#include "inspector.h"

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
    parentAllScalelbls->setLayout(scaleLayout);

    mTransformLabel->setLayout(mTransformLayout);

    //connect position fields
    connect(mTransformPosLblX,SIGNAL(textChanged(const QString)),
            SLOT(slotChangePosition(const QString)));
    connect(mTransformPosLblY,SIGNAL(textChanged(const QString)),
            SLOT(slotChangePosition(const QString)));
    connect(mTransformPosLblZ,SIGNAL(textChanged(const QString)),
            SLOT(slotChangePosition(const QString)));

    //connect rotation fields
    connect(mTransformRotLblX,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeRotation(const QString)));
    connect(mTransformRotLblY,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeRotation(const QString)));
    connect(mTransformRotLblZ,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeRotation(const QString)));

    //connect scale fields
    connect(mTransformScaleLblX,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeScale(const QString)));
    connect(mTransformScaleLblY,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeScale(const QString)));
    connect(mTransformScaleLblZ,SIGNAL(textChanged(const QString)),
            SLOT(slotChangeScale(const QString)));
}

Inspector::~Inspector(){

}

void Inspector::slotChangePosition(const QString text){
    float value = (QStringRef(&text, 0, text.size())).toFloat();
    QLineEdit* lineSender = (QLineEdit*) sender();

    GLfloat* r[] {nullptr, nullptr, nullptr};//position
    r[lineSender == mTransformPosLblX? 0 : lineSender == mTransformPosLblY? 1 : 2 ] = &value;

    curModel->setPosition(r[0], r[1], r[2]);

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

    GLfloat* r[] {nullptr, nullptr, nullptr};//rotation
    r[lineSender == mTransformRotLblX? 0 : lineSender == mTransformRotLblY? 1 : 2 ] = &value;

    curModel->setRotation(r[0], r[1], r[2]);

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

    GLfloat* r[] {nullptr, nullptr, nullptr};//rotation
    r[lineSender == mTransformScaleLblX? 0 : lineSender == mTransformScaleLblY? 1 : 2 ] = &value;

    curModel->setScale(r[0], r[1], r[2]);

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
