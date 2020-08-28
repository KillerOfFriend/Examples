#ifndef UPLOADDIALOG_H
#define UPLOADDIALOG_H

#include <QDialog>

//-----------------------------------------------------------------------------
namespace Ui {
class UploadDialog;
}
//-----------------------------------------------------------------------------
class UploadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UploadDialog(QWidget *parent = 0);
    ~UploadDialog();

private:
    Ui::UploadDialog *ui;

public slots:

    /**
     * @brief slot_onError - Слот, принимающий сообщение об ошибке
     * @param inErrMessage - Сообщение об ошибке
     */
    void slot_onError(QString inErrMessage);

    /**
     * @brief slot_onUpdateProc - Слот, принимающий текущую позицию и и максимальное значение прогресса
     * @param inPos - Текущая позиция
     * @param inMax - Максимальная позиция
     */
    void slot_onUpdateProc(int inPos, int inMax);
};
//-----------------------------------------------------------------------------

#endif // UPLOADDIALOG_H
