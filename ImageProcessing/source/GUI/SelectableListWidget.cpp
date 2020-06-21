#include "SelectableListWidget.h"
#include <AppLogic/SelectTools/SelectableList.h>
#include <QComboBox>
#include <QVBoxLayout>

SelectableListWidget::SelectableListWidget( SelectableList* list, QWidget* parent )
	: QGroupBox( QString::fromStdWString( list->GetName() ), parent ), list_( list )
{
	mainLayout = new QVBoxLayout( this );
	setLayout( mainLayout );
	comboBox_ = new QComboBox( this );
	mainLayout->addWidget( comboBox_ );
	connect( comboBox_, &QComboBox::currentTextChanged,
			 this, &SelectableListWidget::TextChanged_ );
}

void SelectableListWidget::AddSelectableName( const std::wstring& name )
{
	comboBox_->addItem( QString::fromStdWString( name ) );
}

void SelectableListWidget::TextChanged_( const QString& str )
{
	if ( curSelectedWidget_ )
	{
		delete curSelectedWidget_;
		curSelectedWidget_ = nullptr;
	}
	if ( auto selectable = list_->SelectableChanged( str.toStdWString() ) )
	{
		curSelectedWidget_ = selectable->CreateWidget( this );
		mainLayout->addWidget( curSelectedWidget_ );
	}
}