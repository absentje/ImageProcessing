#pragma once
#include <vlGraphics/Shader.hpp>
#include <vlGraphics/GLSL.hpp>
#include <string>

namespace VLExtension
{
class Shader: public vl::Shader
{
    VL_INSTRUMENT_CLASS( Shader, vl::Shader )
public:
    Shader();

    void	SetVShader( const std::wstring& path );
    void	SetFShader( const std::wstring& path );

    const std::wstring& GetFilePathOfVS() const { return file_path_of_vs; }
    const std::wstring& GetFilePathOfFS() const { return file_path_of_fs; }

    void	ReloadShaders();

    void	SetColor( vl::vec4 clr );

private:
    void BindUVAttributes();

    std::wstring file_path_of_vs;
    std::wstring file_path_of_fs;

    vl::GLSLShader* last_vs;
    vl::GLSLShader* last_fs;

    vl::ref<vl::Uniform>	pUniColor;
};
}