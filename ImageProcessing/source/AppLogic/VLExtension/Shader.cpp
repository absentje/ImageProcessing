#include "Shader.h"
#include <vlGraphics/GLSL.hpp>

Shader::Shader()
    : last_vs(nullptr), last_fs(nullptr)
{

}

void	Shader::SetVShader(const std::wstring& path)
{
    file_path_of_vs = path;
    vl::ref<vl::GLSLProgram> glsl_ = gocGLSLProgram();
    BindUVAttributes();

    if (last_vs)
        glsl_->detachShader(last_vs);

    vl::ref<vl::GLSLVertexShader> vs_ = nullptr;
    if (!file_path_of_vs.empty()){
        vs_ = new vl::GLSLVertexShader(file_path_of_vs);
        glsl_->attachShader(vs_.get());
    }
    last_vs = vs_.get();
}

void	Shader::SetFShader(const std::wstring& path)
{
    file_path_of_fs = path;
    vl::ref<vl::GLSLProgram> glsl_ = gocGLSLProgram();
    BindUVAttributes();

    if (last_fs)
        glsl_->detachShader(last_fs);

    vl::ref<vl::GLSLFragmentShader> fs_ = nullptr;
    if (!file_path_of_fs.empty()){
        fs_ = new vl::GLSLFragmentShader(file_path_of_fs);
        glsl_->attachShader(fs_.get());
    }
    last_fs = fs_.get();
}

void	Shader::ReloadShaders()
{
    SetVShader(file_path_of_vs);
    SetFShader(file_path_of_fs);
}

void	Shader::SetColor(vl::vec4 clr)
{
    if (!pUniColor)
    {
        pUniColor = new vl::Uniform("inColor");
        setUniform(pUniColor.get());
    }
    pUniColor->setUniform(clr);
}

void Shader::BindUVAttributes()
{
    vl::ref<vl::GLSLProgram> glsl = gocGLSLProgram();

    const int UV_SIZE = 11;
    const int FIRST_VL_TEX_ATTRIBUTE_NUMBER = vl::VA_TexCoord0;

    const std::string UV_prefix = "UV[";

    for (int i = 0; i != UV_SIZE; ++i)
    {
        const int CURRENT_VL_TEX_ATTRIBUTE_NUMBER = FIRST_VL_TEX_ATTRIBUTE_NUMBER + i;

        glsl->bindAttribLocation(CURRENT_VL_TEX_ATTRIBUTE_NUMBER, (UV_prefix + std::to_string(i) + "]").c_str());
    }
}
