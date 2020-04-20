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

	QStringList stringList = { "" };
	for ( auto& selectable : list_->selectables_ )
	{
		stringList.push_back( QString::fromStdWString( selectable.second->GetName() ) );
	}
	comboBox_->addItems( stringList );
	connect( comboBox_, &QComboBox::currentTextChanged,
			 this, &SelectableListWidget::TextChanged_ );
}

void SelectableListWidget::TextChanged_( const QString& str )
{
	if ( auto selectable = getSelectable_( curSelectedStr_ ) )
	{
		selectable->Disable();
		if ( curSelectedWidget_ )
		{
			delete curSelectedWidget_;
			curSelectedWidget_ = nullptr;
		}
	}

	curSelectedStr_ = str.toStdWString();

	if ( auto selectable = getSelectable_( curSelectedStr_ ) )
	{
		curSelectedWidget_ = selectable->CreateWidget( this );
		selectable->Enable();
		mainLayout->addWidget( curSelectedWidget_ );
	}
}

vl::ref<Selectable> SelectableListWidget::getSelectable_( const std::wstring& str )
{
	auto it = list_->selectables_.find( str );
	return it != list_->selectables_.end() ? it->second : nullptr;
}