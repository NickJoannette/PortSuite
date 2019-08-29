#include "exportdialog.h"

ExportDialog::ExportDialog()
{

    setLabelText(QFileDialog::Accept, tr("Save"));
    setNameFilter(tr("Excel file (.xls .xlsx);;CSV file (.csv);;JSON file (.json)"));
    setViewMode(QFileDialog::List);
    setWindowTitle("Export Data");
}

