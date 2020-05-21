#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "GL/glew.h"

#include <string>
#include <list>

struct GLContextInfo
{
    struct {
        GLint Major, Minor;
        std::string Driver;
        std::string ShadingLanguage;
    } Version;
    std::string Vendor;
    std::string Renderer;
    std::list<std::string> SupportedExtensions;
    std::list<std::string> SupportedGLSLVersions;
};


class Graphics
{
public:
    bool Initialize(unsigned int width, unsigned int height, const std::string& vertShaderPath, const std::string& fragShaderPath);
    void CleanUp();
    void Render();
    void Resize(unsigned int width, unsigned int height);
    GLContextInfo GetContextInfos();

private:

};

#endif // GRAPHICS_H