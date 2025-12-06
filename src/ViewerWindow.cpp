#include "ViewerWindow.h"

#include <glad/glad.h>
#include <iostream>
#include <stdexcept>

static void printGlfwError(const char* where)
{
    const char* desc = nullptr;
    int code = glfwGetError(&desc);
    if (code != GLFW_NO_ERROR)
    {
        std::cerr << "[GLFW ERROR] " << where << " : ("
                  << code << ") " << (desc ? desc : "unknown") << '\n';
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    (void)scancode;

    auto* wnd = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (!wnd || !wnd->m_keyClBck)
        return;

    wnd->m_keyClBck(
        static_cast<KeyCode>(key),
        static_cast<Action>(action),
        static_cast<Modifier>(mods)
    );
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    auto* wnd = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (!wnd || !wnd->m_mouseClBck)
        return;

    double xpos{}, ypos{};
    glfwGetCursorPos(window, &xpos, &ypos);

    wnd->m_mouseClBck(
        static_cast<ButtonCode>(button),
        static_cast<Action>(action),
        static_cast<Modifier>(mods),
        xpos,
        ypos
    );
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
    auto* wnd = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (!wnd || !wnd->m_cursorPosClBck)
        return;

    wnd->m_cursorPosClBck(xpos, ypos);
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    auto* wnd = static_cast<ViewerWindow*>(glfwGetWindowUserPointer(window));
    if (!wnd || !wnd->m_scrollClBck)
        return;

    wnd->m_scrollClBck(xoffset, yoffset);
}

ViewerWindow::ViewerWindow(const std::string& title, uint32_t width, uint32_t height)
    : m_width(width)
    , m_height(height)
{
    if (!glfwInit())
    {
        printGlfwError("glfwInit");
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_ptrHandle = glfwCreateWindow(
        static_cast<int>(width),
        static_cast<int>(height),
        title.c_str(),
        nullptr,
        nullptr
    );

    if (!m_ptrHandle)
    {
        printGlfwError("glfwCreateWindow");
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(m_ptrHandle);

    static bool gladInitialized = false;
    if (!gladInitialized)
    {
        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            std::cerr << "Failed to initialize GLAD\n";
            glfwDestroyWindow(m_ptrHandle);
            glfwTerminate();
            throw std::runtime_error("Failed to initialize GLAD");
        }
        gladInitialized = true;
    }

    glfwSetWindowUserPointer(m_ptrHandle, this);

    glfwSetKeyCallback(m_ptrHandle,        keyCallback);
    glfwSetMouseButtonCallback(m_ptrHandle, mouseButtonCallback);
    glfwSetCursorPosCallback(m_ptrHandle,  cursorCallback);
    glfwSetScrollCallback(m_ptrHandle,     scrollCallback);
}

ViewerWindow::~ViewerWindow()
{
    if (m_ptrHandle)
    {
        glfwDestroyWindow(m_ptrHandle);
        glfwTerminate();
    }
}

uint32_t ViewerWindow::getWidth() const
{
    return m_width;
}

uint32_t ViewerWindow::getHeight() const
{
    return m_height;
}

void ViewerWindow::setKeyCallback(const KeyCallback& callback)
{
    m_keyClBck = callback;
}

void ViewerWindow::setCursorPosCallback(const CursorPosCallback& callback)
{
    m_cursorPosClBck = callback;
}

void ViewerWindow::setMouseCallback(const MouseCallback& callback)
{
    m_mouseClBck = callback;
}

void ViewerWindow::setScrollCallback(const ScrollCallback& callback)
{
    m_scrollClBck = callback;
}

GLFWwindow* ViewerWindow::getGLFWHandle() const
{
    return m_ptrHandle;
}
