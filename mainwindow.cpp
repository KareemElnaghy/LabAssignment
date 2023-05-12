#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    size = 0;
    normalSearch = false;
    binarySearch = false;
    timeTaken_sort= 0;
    timeTaken_search = 0;
    idx = -1;
    sorted = false;
    arrayGenerated = false;
    targetValue = false;

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_normal_button_clicked()
{
    try {
        if (!arrayGenerated) {
            throw runtime_error("Please generate an array before searching.");
        }

        normalSearch = true;
        binarySearch = false;

        ui->searchDisplay_Label->setText("Using: Normal Search");

        ui->normal_button->setStyleSheet("background-color: green;");
        QFont font = ui->normal_button->font();
        font.setBold(true);
        ui->normal_button->setFont(font);

        ui->binary_button->setStyleSheet("");
        ui->binary_button->setFont(QFont());
    }
    catch (runtime_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}



void MainWindow::on_binary_button_clicked()
{
    try {
        if (!arrayGenerated) {
            throw runtime_error("Please generate an array before searching.");
        }
        normalSearch = false;
        binarySearch = true;

        ui->searchDisplay_Label->setText("Using: Binary Search");
        ui->binary_button->setStyleSheet("background-color: green;");
        QFont font = ui->normal_button->font();
        font.setBold(true);
        ui->binary_button->setFont(font);

        ui->normal_button->setStyleSheet("");
        ui->normal_button->setFont(QFont());

    }
    catch (runtime_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}


void MainWindow::on_generate_button_clicked()
{
    resetAll();

    size = ui->size_line_edit->text().toInt();
    try
    {
    if(size <= 0)
    {
        throw runtime_error("Enter a Valid Size and Try Again!");
    }
    else
    {
    size++;

    arr = new int [size];

    Fill();
    printArr();
    ui->sizeDisplay_Label->setText("The Dataset Size is: "+ QString::number(size-1));
    ui->error_label->setText("");
    }
    }
    catch(runtime_error& e){
        QMessageBox::critical(this, "Error", e.what());
    }

}

void MainWindow::MergeSort(int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(start, mid);
        MergeSort(mid+1, end);
        Merge(start, mid, end);
    }
}

void MainWindow::Merge(int left, int mid, int right)
{
    int i, j, k;
       i = left;
       j = mid + 1;
       k = 0;
       int* temp = new int[right - left + 1];
       while (i <= mid && j <= right)
       {
           if (*(arr + i) <= *(arr + j))
           {
               *(temp + k++) = *(arr + i);
               i++;
           }
           else
           {
               *(temp + k++) = *(arr + j);
               j++;
           }

       }
       while (i <= mid)
       {
           *(temp + k++) = *(arr + i++);
       }
       while (j <= right)
       {
           *(temp + k++) = *(arr + j++);
       }
       for (int i = left, k = 0; i <= right; i++,k++)
       {
           *(arr + i) = *(temp + k);
       }
       delete[]temp;
}

void MainWindow::on_mergeSort_button_clicked()
{
    size = ui->size_line_edit->text().toInt();
    try
    {
    if(size == 0)
    {
        throw runtime_error("Enter a Valid Size and Try Again!");

    }
    if(sorted == false)
    {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    MergeSort(0, size - 1);
    chrono::steady_clock::time_point then = chrono::steady_clock::now();
    timeTaken_sort = chrono::duration_cast<chrono::nanoseconds>(then-now).count();
    ui->sortDisplay_Label->setText(ui->sortDisplay_Label->text() + "Merge Sort");
    ui->status_Label->setText("Sorted Array");
    sorted = true;
     ui->error_label->setText("");
    printArr();

    QFont font = ui->mergeSort_button->font();
    font.setBold(true);
    ui->mergeSort_button->setFont(font);
}
    else
    {
         ui->error_label->setText("The Array is Sorted, Regenerate to Proceed!");
    }
}
    catch(runtime_error& e)
    {
        QMessageBox::critical(this, "Error", e.what());
    }

}


void MainWindow::on_stl_button_clicked()
{
    size = ui->size_line_edit->text().toInt();
    try
    {
    if(size == 0)
    {
        throw runtime_error("Enter a Valid Size and Try Again!");

    }

    if(sorted == false)
    {
    chrono::steady_clock::time_point now = chrono::steady_clock::now();
    sort(arr, arr+size);
    chrono::steady_clock::time_point then = chrono::steady_clock::now();
    timeTaken_sort = chrono::duration_cast<chrono::nanoseconds>(then-now).count();
    ui->sortDisplay_Label->setText(ui->sortDisplay_Label->text() + "STL Sort");
    ui->status_Label->setText("Sorted Array");
    sorted = true;
     ui->error_label->setText("");
    printArr();

    QFont font = ui->stl_button->font();
    font.setBold(true);
    ui->stl_button->setFont(font);
}
    else
    {
         ui->error_label->setText("The Array is Sorted, Regenerate to Proceed!");
    }
    }
        catch(runtime_error& e)
        {
            QMessageBox::critical(this, "Error", e.what());
        }

}


void MainWindow::on_findIt_button_clicked()
{
    if(!arrayGenerated)
    {
        ui->error_label->setText("Array Not Generated, Please Generate Array!");
        return;
    }

    if(ui->targetVal_text_edit->text() == "" || ui->targetVal_text_edit->text().toInt() <= 0)
    {
        ui->error_label->setText("Enter a Valid Value to Search for!!");
        return;
    }


int value = ui->targetVal_text_edit->text().toInt();



   if(binarySearch)
   {
       chrono::steady_clock::time_point now = chrono::steady_clock::now();
       idx = Normal(value);
       chrono::steady_clock::time_point then = chrono::steady_clock::now();

       timeTaken_search = chrono::duration_cast<chrono::nanoseconds>(then-now).count();


       ui->error_label->setText("");
   }


    else if(normalSearch)
    {
        chrono::steady_clock::time_point now = chrono::steady_clock::now();
        idx = Normal(value);
        chrono::steady_clock::time_point then = chrono::steady_clock::now();

        timeTaken_search = chrono::duration_cast<chrono::nanoseconds>(then-now).count();



        ui->error_label->setText("");
    }

   else
   {
       ui->error_label->setText("No Search Method Selected, Please Try Again!");
       return;
   }

   QFont font = ui->findIt_button->font();
   font.setBold(true);
   ui->findIt_button->setFont(font);

   QMessageBox msgBox;
   if(binarySearch)
   {
       msgBox.setWindowTitle("BinarySearchQT");
       if(idx != -1)
       {
           msgBox.setText("The value was found in the array at index "+QString::number(idx)+"\n");

       }
       else
       {
           msgBox.setText("The value was not found in the array \n");
       }
       msgBox.setText(msgBox.text() + "The time needed to find it in nanoseconds : "+QString::number(timeTaken_search) +"\n");
       msgBox.setText(msgBox.text() + "Sorting time was : "+QString::number(timeTaken_sort) +"\n");

       if(timeTaken_sort == 0)
       {
            msgBox.setText(msgBox.text() + "No Sorting Method Selected \n");
       }

}
   else if(normalSearch)
   {
       msgBox.setWindowTitle("NormalSearchQT");
       if(idx != -1)
       {
           msgBox.setText("The value was found in the array at index "+QString::number(idx)+"\n");
       }
       else
       {
           msgBox.setText("The value was not found in the array \n");
       }
       msgBox.setText(msgBox.text() + "The time needed to find it in nanoseconds : "+QString::number(timeTaken_search) +"\n");
       msgBox.setText(msgBox.text() + "Sorting time was : "+QString::number(timeTaken_sort) +"\n");

       if(timeTaken_sort == 0)
       {
            msgBox.setText(msgBox.text() + "No Sorting Method Selected \n");
       }

   }

   msgBox.exec();
}

void MainWindow::printArr()
{
    ui->listWidget->clear();

        for (int i = 0; i < size; i++)
        {

            QListWidgetItem* item = new QListWidgetItem(QString::number(arr[i]));


            ui->listWidget->addItem(item);

        }

        ui->listWidget->show();

}

int MainWindow::Binary(int val)
{
    int low, high;
    low = 0;
    high = size - 1;


    while(low <= high)
    {
        int mid = low + (high-1)/2;

        if(arr[mid]== val)
            return mid;

        if(arr[mid] < val)
            low = mid-1;
        else
            high = mid-1;
    }


    return -1;

}
int MainWindow::Normal(int val)
{
    for(int i = 0; i<size; i++)
    {
        if(arr[i] == val)
            return i;
    }

    return -1;
}

void MainWindow::Fill()
{
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % size) + 1;
    }
}

void MainWindow::Swap(int& x, int& y)
{
    {
        int temp = x;
        x = y;
        y = temp;
    }
}





void MainWindow::on_exit_Button_clicked()
{
   this->close();
}

void MainWindow::resetAll()
{
    sorted = false;
    normalSearch = false;
    binarySearch = false;
    arrayGenerated = true;
    ui->status_Label->setText("Unsorted Array");
    ui->searchDisplay_Label->setText("Using:");
    ui->sortDisplay_Label->setText("Sorting Using ");
    ui->normal_button->setStyleSheet("");
    ui->normal_button->setFont(QFont());
    ui->binary_button->setStyleSheet("");
    ui->binary_button->setFont(QFont());
    ui->mergeSort_button->setStyleSheet("");
    ui->mergeSort_button->setFont(QFont());
    ui->stl_button->setStyleSheet("");
    ui->stl_button->setFont(QFont());
    ui->findIt_button->setStyleSheet("");
    ui->findIt_button->setFont(QFont());
}

