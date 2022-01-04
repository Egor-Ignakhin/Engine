#ifndef ENGINELAUNCHER_H
#define ENGINELAUNCHER_H


class EngineLauncher
{
public:
    EngineLauncher();
    bool GetCanLoadEditor(){
        return canLoadEditor;
    }
private:
    bool canLoadEditor = false;

};

#endif // ENGINELAUNCHER_H
