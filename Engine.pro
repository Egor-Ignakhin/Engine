QT       += core gui opengl quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
LIBS += -lopengl32 -lglu32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CoreTime.cpp \
    Test-game-2d/Scripts/Levels/brokenfieldlevel.cpp \
    Test-game-2d/Scripts/Levels/depressedcitylevel.cpp \
    Test-game-2d/Scripts/Levels/destroyedtownlevel.cpp \
    Test-game-2d/Scripts/Levels/foggyforestlevel.cpp \
    Test-game-2d/Scripts/Levels/trenchlevel.cpp \
    Test-game-2d/Scripts/artillerytower.cpp \
    Test-game-2d/Scripts/firetower.cpp \
    Test-game-2d/Scripts/shootingtower.cpp \
    Test-game-2d/Scripts/tower.cpp \
    component.cpp \
    coreengine.cpp \
    cube.cpp \
    editor.cpp \
    enginelauncher.cpp \
    glwindow.cpp \
    inspector.cpp \
    level.cpp \
    level1.cpp \
    levelscreator.cpp \
    main.cpp \
    model.cpp \
    testmodel.cpp \
    transform.cpp \
    vector3.cpp

HEADERS += \
    CoreTime.h \
    Test-game-2d/Scripts/Levels/brokenfieldlevel.h \
    Test-game-2d/Scripts/Levels/depressedcitylevel.h \
    Test-game-2d/Scripts/Levels/destroyedtownlevel.h \
    Test-game-2d/Scripts/Levels/foggyforestlevel.h \
    Test-game-2d/Scripts/Levels/trenchlevel.h \
    Test-game-2d/Scripts/artillerytower.h \
    Test-game-2d/Scripts/firetower.h \
    Test-game-2d/Scripts/shootingtower.h \
    Test-game-2d/Scripts/tower.h \
    component.h \
    coreengine.h \
    cube.h \
    editor.h \
    enginelauncher.h \
    glwindow.h \
    inspector.h \
    level.h \
    level1.h \
    levelscreator.h \
    model.h \
    testmodel.h \
    transform.h \
    vector3.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES +=
