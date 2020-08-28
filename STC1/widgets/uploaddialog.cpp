#include "uploaddialog.h"
#include "ui_uploaddialog.h"

//-----------------------------------------------------------------------------
UploadDialog::UploadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadDialog)
{
    ui->setupUi(this);
    ui->btnClose->setEnabled(false);
    connect(ui->btnClose, &QPushButton::clicked, this, &UploadDialog::close);
}
//-----------------------------------------------------------------------------
UploadDialog::~UploadDialog()
{
    delete ui;
}
//-----------------------------------------------------------------------------
void UploadDialog::slot_onError(QString inErrMessage)
{
    ui->listWidget->addItem(inErrMessage);
    ui->listWidget->scrollToBottom();
}
//-----------------------------------------------------------------------------
void UploadDialog::slot_onUpdateProc(int inPos, int inMax)
{
    ui->progressBar->setMaximum(inMax);
    ui->progressBar->setValue(inPos);

    if (inPos == inMax)
        ui->btnClose->setEnabled(true);
}
//-----------------------------------------------------------------------------
