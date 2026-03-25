/* ------------------------------------------------------- */
class Window {
public:
    virtual void Draw() = 0;
};

// https://en.wikipedia.org/wiki/X_Window_System
class XWindow: public Window {
public:
    virtual void Draw() override;
};

// https://en.wikipedia.org/wiki/Presentation_Manager
class PMWindow: public Window {
public:
    virtual void Draw() override;
};

class IconWindow: public Window {
};

class XIconWindow: public IconWindow {
public:
    virtual void Draw() override;
};

class PMIconWindow: public IconWindow {
public:
    virtual void Draw() override;
};
/* ------------------------------------------------------- */
/* -----------------------bridge-------------------------- */

class WindowImp;
class Window {
public:
    Window(WindowImp* imp);
    virtual void Draw() = 0;
protected:
    WindowImp* GetWindowImp() { return _imp; }
private: 
    WindowImp* _imp;
};

class WindowImp {
public:
    virtual void Draw() = 0;   
};

class IconWindow : public Window { 
public:
    IconWindow(WindowImp* imp): Window(imp) {}
    void Draw() override {
        WindowImp* imp = GetWindowImp(); 
        imp->Draw();
    }
};

class XWindowImp : public WindowImp { 
public: 
    void Draw() override; 
};

class PMWindowImp : public WindowImp { 
public: 
    void Draw() override; 
};

