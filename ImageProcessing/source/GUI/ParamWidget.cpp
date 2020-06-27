#include "ParamWidget.h"
#include <AppLogic/SelectTools/Selectable.h>
#include <GUI/ParamsWidget.h>
#include <vlCore/glsl_math.hpp>
#include <QFileDialog>
#include <VLExtension/Util/FBX_Support/FbxResource.h>
#include <codecvt>

namespace
{
constexpr int cMaxSliderValue = 1000;

}

///////////////////////////////////////////////////////////////
// FloatParamWidget ///////////////////////////////////////////
FloatParamWidget::FloatParamWidget( float& param, float min, float max, ParamsWidget* paramsWidget )
	: QSlider( Qt::Orientation::Horizontal, paramsWidget ), paramsWidget_( paramsWidget ),
	param_( param ), min_( min ), max_( max )
{
	connect( this, SIGNAL( valueChanged( int ) ),
			 this, SLOT( sliderValueChanged_( int ) ) );

	setMinimum( 0 );
	setMaximum( cMaxSliderValue );

	float alpha = ( param - min ) / ( max - min );
	setValue( (int)vl::mix( float( 0 ), float( cMaxSliderValue ), alpha ) );
}

void FloatParamWidget::sliderValueChanged_( int value )
{
	param_ = vl::mix( min_, max_, float( value ) / float( cMaxSliderValue ) );
	paramsWidget_->OnUpdate();
}
///////////////////////////////////////////////////////////////
// IntParamWidget /////////////////////////////////////////////
IntParamWidget::IntParamWidget( int& param, int min, int max, ParamsWidget* paramsWidget )
	: QSlider( Qt::Orientation::Horizontal, paramsWidget ), paramsWidget_( paramsWidget ),
	param_( param ), min_( min ), max_( max )
{
	connect( this, SIGNAL( valueChanged( int ) ),
			 this, SLOT( sliderValueChanged_( int ) ) );

	setMinimum( min_ );
	setMaximum( max_ );
	setValue( param );
}

void IntParamWidget::sliderValueChanged_( int value )
{
	param_ = value;
	paramsWidget_->OnUpdate();
}

///////////////////////////////////////////////////////////////
// BoolParamWidget /////////////////////////////////////////////
BoolParamWidget::BoolParamWidget( bool& param, ParamsWidget* paramsWidget )
	: QCheckBox( paramsWidget ), paramsWidget_( paramsWidget ),
	param_( param )
{
	connect( this, SIGNAL( stateChanged( int ) ),
			 this, SLOT( checkBoxValueChanged_( int ) ) );
	setValue_( param );
}

void BoolParamWidget::setValue_( bool value )
{
	setCheckState( value ? Qt::CheckState::Checked : Qt::CheckState::Unchecked );
}

void BoolParamWidget::checkBoxValueChanged_( int value )
{
	param_ = value;
	paramsWidget_->OnUpdate();
}

///////////////////////////////////////////////////////////////
// FileParamWidget /////////////////////////////////////////////
FileParamWidget::FileParamWidget( ParamsWidget* paramsWidget )
	: QPushButton( paramsWidget ), paramsWidget_( paramsWidget )
{
	connect( this, &QPushButton::clicked,
			 this, [this] { onClicked_(); } );

	fileFilter_ = "All files (*.*)";
}

void FileParamWidget::SetFileFilter( const QString& fileFilter )
{
	fileFilter_ = fileFilter; // sample: "Images (*.png *.xpm *.jpg);;All files (*.*)"
}

void FileParamWidget::onClicked_()
{
	file_name_ = QFileDialog::getOpenFileName(	this,
											QString::fromUtf8( "Open file" ),
											QDir::currentPath(),
											fileFilter_ ).toStdWString();
	onFileNameChanged();
	paramsWidget_->OnUpdate();
}

///////////////////////////////////////////////////////////////
// TextureParamWidget /////////////////////////////////////////////
TextureParamWidget::TextureParamWidget( vl::Texture& param, ParamsWidget* paramsWidget )
	:	FileParamWidget( paramsWidget ),
		tex_format_( vl::ETextureFormat::TF_RGBA ),
		param_( param )
{
	SetFileFilter( "Images (*.png *.jpg *.bmp );;All files (*.*)" );
	setText( "Load Texture" );
}

void TextureParamWidget::SetTextureFormat( vl::ETextureFormat format )
{
	tex_format_ = format;
}

void TextureParamWidget::onFileNameChanged()
{
	param_.createTexture2D( vl::loadImage( file_name_ ).get(), tex_format_ );
}

///////////////////////////////////////////////////////////////
// GeometryParamWidget /////////////////////////////////////////////
GeometryParamWidget::GeometryParamWidget( vl::Geometry& param, ParamsWidget* paramsWidget )
	: FileParamWidget( paramsWidget ),
	param_( param )
{
	SetFileFilter( "Geometries (*.fbx *.FBX );;All files (*.*)" );
	setText( "Load FBX Geometry" );
}

void GeometryParamWidget::onFileNameChanged()
{
	using WStringConverter = std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>;
	FbxResource fbxFile;
	fbxFile.LoadFile( WStringConverter().to_bytes( file_name_ ) );

	auto geom = fbxFile.GetGeometry( 0, { 0 } );
	param_.deepCopyFrom( *geom );
	param_.computeNormals();
}