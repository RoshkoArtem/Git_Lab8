#pragma once

#include <cstdint>
#include <functional>
#include <string>

#include <GLFW/glfw3.h>

// Бітові маски модифікаторів
enum class Modifier : unsigned int
{
    None    = 0,
    Shift   = GLFW_MOD_SHIFT,
    Control = GLFW_MOD_CONTROL,
    Alt     = GLFW_MOD_ALT,
    Super   = GLFW_MOD_SUPER
};

enum class Action
{
    Release = GLFW_RELEASE,
    Press   = GLFW_PRESS,
    Repeat  = GLFW_REPEAT
};

enum class ButtonCode
{
    Button_1 = GLFW_MOUSE_BUTTON_1,
    Button_2 = GLFW_MOUSE_BUTTON_2,
    Button_3 = GLFW_MOUSE_BUTTON_3,
    Button_4 = GLFW_MOUSE_BUTTON_4,
    Button_5 = GLFW_MOUSE_BUTTON_5,
    Button_6 = GLFW_MOUSE_BUTTON_6,
    Button_7 = GLFW_MOUSE_BUTTON_7,

    Left   = GLFW_MOUSE_BUTTON_LEFT,
    Right  = GLFW_MOUSE_BUTTON_RIGHT,
    Middle = GLFW_MOUSE_BUTTON_MIDDLE
};

// Для лаби достатньо кількох клавіш (стрілки + пробіл/escape)
enum class KeyCode
{
    UNKNOWN = GLFW_KEY_UNKNOWN,

    Space   = GLFW_KEY_SPACE,
    Escape  = GLFW_KEY_ESCAPE,

    UP      = GLFW_KEY_UP,
    DOWN    = GLFW_KEY_DOWN,
    LEFT    = GLFW_KEY_LEFT,
    RIGHT   = GLFW_KEY_RIGHT,

    W = GLFW_KEY_W,
    A = GLFW_KEY_A,
    S = GLFW_KEY_S,
    D = GLFW_KEY_D
};

class ViewerWindow
{
    friend void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    friend void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    friend void cursorCallback(GLFWwindow* window, double xpos, double ypos);
    friend void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

public:
    using KeyCallback       = std::function<void(KeyCode, Action, Modifier)>;
    using CursorPosCallback = std::function<void(double, double)>;
    using MouseCallback     = std::function<void(ButtonCode, Action, Modifier, double, double)>;
    using ScrollCallback    = std::function<void(double, double)>;

    ViewerWindow(const std::string& title, uint32_t width, uint32_t height);
    ~ViewerWindow();

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    void setKeyCallback      (const KeyCallback& callback);
    void setCursorPosCallback(const CursorPosCallback& callback);
    void setMouseCallback    (const MouseCallback& callback);
    void setScrollCallback   (const ScrollCallback& callback);

    GLFWwindow* getGLFWHandle() const;

private:
    GLFWwindow* m_ptrHandle{nullptr};
    uint32_t    m_width{0};
    uint32_t    m_height{0};

    KeyCallback       m_keyClBck;
    CursorPosCallback m_cursorPosClBck;
    MouseCallback     m_mouseClBck;
    ScrollCallback    m_scrollClBck;
};
