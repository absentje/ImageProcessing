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

void SelectableListWidget::SetCurrentSelectedWidget( QWidget* widget )
{
	if ( curSelectedWidget_ )
	{
		delete curSelectedWidget_;
		curSelectedWidget_ = nullptr;
	}
	if ( widget )
	{
		curSelectedWidget_ = widget;
		mainLayout->addWidget( curSelectedWidget_ );
	}
}

void SelectableListWidget::TextChanged_( const QString& str )
{
	if ( curSelectedWidget_ )
	{
		delete curSelectedWidget_;
		curSelectedWidget_ = nullptr;
	}

	auto it = list_->selectables_.find( str.toStdWString() );
	if ( it != list_->selectables_.end() )
	{
		auto selectable = it->second;
		curSelectedWidget_ = selectable->CreateWidget( this );
		selectable->Enable();
		mainLayout->addWidget( curSelectedWidget_ );
	}
}