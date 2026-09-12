/**
 * ============================================================================
 * MODULE 11: Design Patterns & Architecture
 * FILE: 01_design_patterns_demo.cpp
 * 
 * DEMONSTRATES:
 * 1. Meyers Thread-Safe Singleton Pattern
 * 2. CRTP Static Polymorphism vs Virtual Dynamic Polymorphism
 * 3. Policy-Based Design Logger Architecture
 * ============================================================================
 */

#include <iostream>
#include <string>
#include <memory>

// 1. MEYERS SINGLETON PATTERN
class ConfigurationManager {
private:
    std::string m_appMode = "Production";
    ConfigurationManager() {
        std::cout << "ConfigurationManager initialized.\n";
    }

public:
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;

    static ConfigurationManager& getInstance() {
        static ConfigurationManager instance; // Guaranteed thread-safe static init in C++11
        return instance;
    }

    std::string getMode() const { return m_appMode; }
    void setMode(std::string mode) { m_appMode = mode; }
};

// 2. CRTP STATIC POLYMORPHISM DEMO
template <typename Derived>
class RenderEngine {
public:
    void render() {
        // Dispatch to derived implementation at COMPILE TIME!
        static_cast<Derived*>(this)->drawFrame();
    }
};

class OpenGLRenderer : public RenderEngine<OpenGLRenderer> {
public:
    void drawFrame() {
        std::cout << "[CRTP Static Dispatch] Rendering frame via OpenGL Pipeline...\n";
    }
};

class VulkanRenderer : public RenderEngine<VulkanRenderer> {
public:
    void drawFrame() {
        std::cout << "[CRTP Static Dispatch] Rendering frame via Vulkan Low-Overhead Pipeline...\n";
    }
};

// 3. POLICY-BASED DESIGN
struct ConsoleWriterPolicy {
    static void write(const std::string& msg) {
        std::cout << "[Console Policy]: " << msg << "\n";
    }
};

struct HTMLWriterPolicy {
    static void write(const std::string& msg) {
        std::cout << "<p class='log'>" << msg << "</p>\n";
    }
};

template <typename OutputPolicy>
class AppLogger : public OutputPolicy {
public:
    void logMessage(const std::string& text) {
        OutputPolicy::write(text);
    }
};

int main() {
    std::cout << "--- 1. MEYERS SINGLETON DEMO ---" << std::endl;
    std::cout << "Current App Mode: " << ConfigurationManager::getInstance().getMode() << "\n";
    ConfigurationManager::getInstance().setMode("High-Performance-Tuning");
    std::cout << "Updated App Mode: " << ConfigurationManager::getInstance().getMode() << "\n\n";

    std::cout << "--- 2. CRTP STATIC POLYMORPHISM DEMO ---" << std::endl;
    OpenGLRenderer ogl;
    VulkanRenderer vulkan;

    ogl.render();    // Zero vtable lookup overhead! Fully inlined!
    vulkan.render();

    std::cout << "\n--- 3. POLICY-BASED DESIGN DEMO ---" << std::endl;
    AppLogger<ConsoleWriterPolicy> consoleLogger;
    consoleLogger.logMessage("System initialization clean.");

    AppLogger<HTMLWriterPolicy> htmlLogger;
    htmlLogger.logMessage("Web dashboard status OK.");

    return 0;
}
